// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

import {Script, console} from "forge-std/Script.sol";
import {FutureBlockGame} from "../src/FutureBlockGame.sol";

contract FutureBlockGameScript is Script {
    function setUp() public {}

    function run() public {
        // Try to retrieve private key from environment, otherwise simulate or default
        uint256 deployerPrivateKey;
        try vm.envUint("PRIVATE_KEY") returns (uint256 key) {
            deployerPrivateKey = key;
        } catch {
            deployerPrivateKey = 0;
        }

        if (deployerPrivateKey != 0) {
            vm.startBroadcast(deployerPrivateKey);
        } else {
            vm.startBroadcast();
        }

        new FutureBlockGame();

        vm.stopBroadcast();
    }
}
