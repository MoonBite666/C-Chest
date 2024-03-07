# C-Chest

[English](./README.md) [中文](./README_ZH.md)
A windows console Sokoban game

## About this branch

This branch is developed to be compatible with non-Windows-Terminal CLI. It use Chinese character to build game UI.

BGM feature and so on will be developed in this branch.

## Way to develop

1. Git clone this repository
2. You're strongly recommended to use VSCode with cmake plugin to automatically configure the project. You may need configure gcc environment (one easy way is use [vscch](https://mflink.top/%e6%9c%80%e7%ae%80%e5%8d%95%e7%9a%84vs-codecpp%e7%8e%af%e5%a2%83%e9%85%8d%e7%bd%ae%e6%95%99%e7%a8%8b/)) before.
3. At ./build folder generate by cmake, run 'make' command and it will generate .exe file.

- If you're using some other IDEs, just run 'cmake ." command to substitude process 2.

## Todo list

- [x]Menu in game
- [x]Undo feature
- [x]Save feature
- [x]Step record
- [x]Neat UI
- [ ]More BGM and SE
