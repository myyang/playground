// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

import {Test, console} from "forge-std/Test.sol";
import {FutureBlockGame} from "../src/FutureBlockGame.sol";
import "@openzeppelin/contracts/token/ERC20/ERC20.sol";

// Simple Mock ERC20
contract MockERC20 is ERC20 {
    constructor() ERC20("Mock Token", "MCK") {}

    function mint(address to, uint256 amount) public {
        _mint(to, amount);
    }
}

contract FutureBlockGameTest is Test {
    FutureBlockGame public game;
    MockERC20 public token;
    address public player1 = address(0x123);
    address public player2 = address(0x456);

    function setUp() public {
        game = new FutureBlockGame();
        token = new MockERC20();

        vm.deal(player1, 100 ether);
        vm.deal(player2, 100 ether);

        token.mint(player1, 1000 ether);
        token.mint(player2, 1000 ether);

        vm.warp(1000); // Start at t=1000 to satisfy cooldown (ts >= 0 + 60)
    }

    function test_PlaceBet_Native() public {
        vm.startPrank(player1);

        uint256 betAmount = 0.05 ether;
        game.placeBet{value: betAmount}();

        // Check stored bet
        (uint256 amount, uint256 targetBlock, address player, address betToken, bool isClaimed) = game.bets(0);

        assertEq(amount, betAmount);
        assertEq(player, player1);
        assertEq(betToken, address(0));
        assertEq(targetBlock, block.number + 5);
        assertEq(isClaimed, false);

        vm.stopPrank();
    }

    function test_PlaceBet_ERC20() public {
        vm.startPrank(game.owner());
        game.setTokenConfig(address(token), true, 100 ether);
        vm.stopPrank();

        vm.startPrank(player1);

        uint256 betAmount = 10 ether;
        token.approve(address(game), betAmount);
        game.placeBet(address(token), betAmount);

        // Check stored bet
        (uint256 amount, uint256 targetBlock, address player, address betToken, bool isClaimed) = game.bets(0);

        assertEq(amount, betAmount);
        assertEq(player, player1);
        assertEq(betToken, address(token));
        assertEq(targetBlock, block.number + 5);
        assertEq(isClaimed, false);

        assertEq(token.balanceOf(address(game)), betAmount);

        vm.stopPrank();
    }

    function test_RevertIf_AmountZero() public {
        vm.startPrank(player1);
        vm.expectRevert("Bet amount must be > 0");
        game.placeBet{value: 0}();
        vm.stopPrank();
    }

    function test_RevertIf_AmountTooLarge() public {
        vm.startPrank(player1);
        vm.expectRevert("Bet too large");
        game.placeBet{value: 1 ether}(); // max is 0.1 for native
        vm.stopPrank();
    }

    function test_RevertIf_Cooldown() public {
        vm.startPrank(player1);
        game.placeBet{value: 0.01 ether}();

        vm.expectRevert("Cooldown active");
        game.placeBet{value: 0.01 ether}();

        // Advance time
        vm.warp(block.timestamp + 61);
        game.placeBet{value: 0.01 ether}(); // Should succeed
        vm.stopPrank();
    }

    function test_RevertIf_TokenNotAllowed() public {
        MockERC20 badToken = new MockERC20();
        badToken.mint(player1, 100);

        vm.startPrank(player1);
        badToken.approve(address(game), 100);

        vm.expectRevert("Token not allowed");
        game.placeBet(address(badToken), 10);
        vm.stopPrank();
    }

    function test_GetBetStatus_Pending() public {
        vm.startPrank(player1);
        game.placeBet{value: 0.01 ether}();

        (FutureBlockGame.BetStatus status,) = game.getBetStatus(0);
        assertEq(uint256(status), uint256(FutureBlockGame.BetStatus.PENDING));
        vm.stopPrank();
    }

    function test_GetBetStatus_Expired() public {
        vm.startPrank(player1);
        game.placeBet{value: 0.01 ether}();

        // Warp block number to target + 251
        // target is block.number + 5.
        // so target + 251 = block.number + 5 + 251
        vm.roll(block.number + 5 + 251);

        (FutureBlockGame.BetStatus status,) = game.getBetStatus(0);
        assertEq(uint256(status), uint256(FutureBlockGame.BetStatus.EXPIRED));
        vm.stopPrank();
    }

    function test_OwnerCanSetParams() public {
        game.setParams(600, 300, 10);
        assertEq(game.winThreshold(), 600);
        assertEq(game.multiplier(), 300);
        assertEq(game.cooldownTime(), 10);
    }

    function test_OwnerCanSetTokenConfig() public {
        game.setTokenConfig(address(token), true, 500 ether);
        assertEq(game.allowedTokens(address(token)), true);
        assertEq(game.tokenMaxBets(address(token)), 500 ether);
    }

    function test_RevertIf_NotOwnerSetParams() public {
        vm.prank(player1);
        // Expect OwnableUnauthorizedAccount(address)
        // We can just verify it reverts
        vm.expectRevert();
        game.setParams(600, 300, 10);
    }
}
