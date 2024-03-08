# C-Chest

[English](./README.md) [中文](./README_ZH.md)

一个使用Windows控制台完成的“推箱子”游戏

## 关于分支

该分支是为了适应非Windows Terminal 客户端所开发的，使用中文汉字构筑游戏UI的版本分支。

后续的BGM等功能开发也将在该分支完成。

## 开发方式

1. 使用Git克隆本仓库
2. 强烈推荐使用VSCode及其CMake插件来自动配置该工程。你可能需要提前配置好gcc环境（一种简单的办法是使用[vscch](https://mflink.top/%e6%9c%80%e7%ae%80%e5%8d%95%e7%9a%84vs-codecpp%e7%8e%af%e5%a2%83%e9%85%8d%e7%bd%ae%e6%95%99%e7%a8%8b/)）
3. 在CMake生成的./build文件夹中，运行'make'命令，将会自动生成.exe文件。

## BGM使用声明

本游戏使用GPL协议开源工程[furnace](https://github.com/tildearrow/furnace)的demo工程之一作为BGM。以下附作者信息：
曲名: You're Doing Well!
作者：TheDuccinator

- 如果你使用其他IDE，你只需要在仓库目录运行'cmake .'即可完成第二步的操作。

## Todo list

- [x]游戏内菜单
- [x]撤回功能
- [x]存档功能
- [x]步数记录
- [x]整洁的UI
- [x]更多的背景音乐和音效
