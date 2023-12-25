<div align=center>
  <img width=64 src="app.ico">
</div>

<h1 align="center">
  SAST Evento Desktop 
</h1>
<p align="center">
  NJUPT SAST C++组 SoC项目
</p>

<p align="center">
<img src="https://img.shields.io/badge/frame-Qt6.5-blue">
<img src="https://img.shields.io/badge/std-C++17-yellow">
<img src="https://img.shields.io/badge/platform-Windows-white">
<img src="https://img.shields.io/badge/platform-Linux-green">
<img src="https://img.shields.io/badge/platform-macOS-orange">
</p>

## 简介

SAST Evento 是一个 SAST 的事件管理系统，平时我们在活动过程中一般都会遇到下面的问题：
- 活动信息收集仍然通过传统的共享表格，效率低
- 活动时间安排冲突需要手动排查、活动场地冲突也要手动排查
- 活动计划表虽然模板一样，但是每周都需要人手动更新，没法自动生成
- 同学们活动没有的反馈不高，活动完的收获没法量化
- 活动的质量没有比较好的反馈

针对上面的问题，我们决定SoC期间制作一个活动辅助系统帮助部长和讲师们更加顺畅地完成日常活动，减少沟通负担。

本项目是SAST Evento的桌面客户端版本。

## License

项目基于 [MIT License](./LICENSE) 发布

## Release

[Latest version](https://github.com/NJUPT-SAST/SAST-Evento-Desktop/releases/latest)
  - [Linux: sast-evento_appimage_x86_64.AppImage](https://github.com/NJUPT-SAST/SAST-Evento-Desktop/releases/latest/download/sast-evento_appimage_x86_64.AppImage)
  - [macOS: sast-evento_macOS.dmg](https://github.com/NJUPT-SAST/SAST-Evento-Desktop/releases/latest/download/sast-evento_macOS.dmg)
  - [Windows: sast-evento_win64.exe]( https://github.com/NJUPT-SAST/SAST-Evento-Desktop/releases/latest/download/sast-evento_win64.exe)

## Start

- Clone the repository

```
git clone --recursive https://github.com/NJUPT-SAST/SAST-Evento-Desktop.git
``````

- Build

```
cd SAST-Evento-Desktop
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=<YOUR_QT_SDK_DIR_PATH> -DCMAKE_BUILD_TYPE=Release -GNinja <PATH_TO_THE_REPOSITORY>
cmake --build . --config Release --target all --parallel
```

- Use your IDE (`Qt Creator` or `CLion`) to open the project. (only **CMake** supported).

## :link:Link

[sast-evento-backend](https://github.com/NJUPT-SAST/sast-evento-backend)
