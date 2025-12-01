// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

// 1. 導入 OpenZeppelin 的 Ownable 合約
import "@openzeppelin/contracts/access/Ownable.sol";
import "@openzeppelin/contracts/token/ERC20/IERC20.sol";
import "@openzeppelin/contracts/token/ERC20/utils/SafeERC20.sol";

// 2. 繼承 Ownable
contract FutureBlockGame is Ownable {
    using SafeERC20 for IERC20;

    // --- 狀態定義 ---
    enum BetStatus {
        PENDING, // 等待區塊生成中
        WON, // 中獎，可領取
        LOST, // 未中獎
        EXPIRED, // 過期 (超過256個區塊，無法驗證)
        CLAIMED // 已領獎

    }

    struct Bet {
        uint256 amount; // 下注金額
        uint256 targetBlock; // 目標區塊 (例如下注時 block + 5)
        address player; // 玩家地址
        address token; // 下注代幣 (address(0) 為原生代幣)
        bool isClaimed; // 是否已領獎
    }

    // --- 遊戲參數 (可調整) ---
    // address public owner; // Removed: Ownable already has owner()
    uint256 public winThreshold = 505; // 勝率參數: < 505 則贏 (50.5%)
    uint256 public multiplier = 200; // 賠率參數: 200% (2倍) (基數100)
    // uint256 public maxBetAmount = 0.1 ether; // Moved to token specific config
    uint256 public cooldownTime = 1 minutes; // 冷卻時間 (防高頻機器人)

    mapping(uint256 => Bet) public bets;
    mapping(address => uint256) public lastBetTime; // 記錄玩家上次下注時間
    uint256 public betIdCounter;

    // Token whitelist & config
    mapping(address => bool) public allowedTokens;
    mapping(address => uint256) public tokenMaxBets;

    // --- 事件 ---
    event BetPlaced(uint256 betId, address player, address token, uint256 targetBlock, uint256 amount);
    event RewardClaimed(uint256 betId, address player, address token, uint256 amount);
    event TokenConfigUpdated(address token, bool allowed, uint256 maxBet);

    // 3. 建構子初始化 Ownable
    // 注意：OpenZeppelin v5.0+ 需要在建構子顯式傳入 initialOwner
    constructor() Ownable(msg.sender) {
        // Initialize native token config
        allowedTokens[address(0)] = true;
        tokenMaxBets[address(0)] = 0.1 ether;
    }

    // 1. 下注函數 (Native)
    function placeBet() external payable {
        _placeBet(address(0), msg.value);
    }

    // 1.1 下注函數 (ERC20)
    function placeBet(address token, uint256 amount) external {
        require(token != address(0), "Use placeBet() for native");

        // Transfer tokens first
        IERC20(token).safeTransferFrom(msg.sender, address(this), amount);

        _placeBet(token, amount);
    }

    function _placeBet(address token, uint256 amount) internal {
        require(allowedTokens[token], "Token not allowed");
        require(amount > 0, "Bet amount must be > 0");
        require(amount <= tokenMaxBets[token], "Bet too large");
        require(block.timestamp >= lastBetTime[msg.sender] + cooldownTime, "Cooldown active");

        // 設定目標區塊：為了安全建議 +3 或 +5，這裡設 +5
        uint256 target = block.number + 5;

        bets[betIdCounter] =
            Bet({amount: amount, targetBlock: target, player: msg.sender, token: token, isClaimed: false});

        lastBetTime[msg.sender] = block.timestamp;

        emit BetPlaced(betIdCounter, msg.sender, token, target, amount);
        betIdCounter++;
    }

    // 2. 核心邏輯：計算是否中獎 (Internal View)
    function _calculateWin(uint256 targetBlock) internal view returns (bool) {
        // 獲取區塊 Hash
        bytes32 bHash = blockhash(targetBlock);

        // 如果 Hash 為 0，代表區塊還沒生成，或是已經超過 256 個區塊過期了
        if (bHash == 0) return false;

        // 轉換為 0-999 的數字
        uint256 result = uint256(bHash) % 1000;

        // 判斷是否小於勝率門檻
        return result < winThreshold;
    }

    // 3. View 查詢函數 (前端一直呼叫這個)
    function getBetStatus(uint256 betId) external view returns (BetStatus, uint256) {
        Bet memory b = bets[betId];

        if (b.player == address(0)) return (BetStatus.EXPIRED, 0); // 不存在的訂單
        if (b.isClaimed) return (BetStatus.CLAIMED, 0);

        // Case A: 區塊還沒挖出來
        if (block.number <= b.targetBlock) {
            return (BetStatus.PENDING, 0);
        }

        // Case B: 區塊已經太老了 (超過 256 個區塊，blockhash 會回傳 0)
        // 注意：Solidity 的 blockhash 只支援最近 256 個區塊
        if (block.number > b.targetBlock + 250) {
            return (BetStatus.EXPIRED, 0);
        }

        // Case C: 計算結果
        bool won = _calculateWin(b.targetBlock);
        if (won) {
            uint256 reward = (b.amount * multiplier) / 100;
            return (BetStatus.WON, reward);
        } else {
            return (BetStatus.LOST, 0);
        }
    }

    // 4. 領獎函數 (只有 View 顯示 WON 時才呼叫)
    function claimReward(uint256 betId) external {
        Bet storage b = bets[betId];

        require(msg.sender == b.player, "Not your bet");
        require(!b.isClaimed, "Already claimed");
        require(block.number > b.targetBlock, "Wait for block");
        require(block.number <= b.targetBlock + 250, "Bet expired");

        // 這裡必須重新計算一次，不能依賴前端傳來的結果
        bool won = _calculateWin(b.targetBlock);
        require(won, "You lost");

        b.isClaimed = true;

        uint256 reward = (b.amount * multiplier) / 100;

        if (b.token == address(0)) {
            require(address(this).balance >= reward, "Contract low balance");
            payable(b.player).transfer(reward);
        } else {
            require(IERC20(b.token).balanceOf(address(this)) >= reward, "Contract low balance");
            IERC20(b.token).safeTransfer(b.player, reward);
        }

        emit RewardClaimed(betId, b.player, b.token, reward);
    }

    // --- 管理員功能 (使用 onlyOwner) ---

    // 4. 使用 onlyOwner 修飾符保護關鍵函數
    function setParams(uint256 _threshold, uint256 _multiplier, uint256 _cooldown) external onlyOwner {
        winThreshold = _threshold;
        multiplier = _multiplier;
        cooldownTime = _cooldown;
    }

    function setTokenConfig(address token, bool allowed, uint256 maxBet) external onlyOwner {
        allowedTokens[token] = allowed;
        tokenMaxBets[token] = maxBet;
        emit TokenConfigUpdated(token, allowed, maxBet);
    }

    // 緊急提款：把合約裡所有錢提出來
    function withdrawAll(address token) external onlyOwner {
        if (token == address(0)) {
            payable(owner()).transfer(address(this).balance);
        } else {
            uint256 balance = IERC20(token).balanceOf(address(this));
            IERC20(token).safeTransfer(owner(), balance);
        }
    }
}
