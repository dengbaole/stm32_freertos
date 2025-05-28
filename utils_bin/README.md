# Volwave固件开发工具箱

本项目为 `Volwave` 固件开发工具链的一部分，包含日常开发中需要使用到的二进制文件和脚本。主要用于消除对开发环境的二进制依赖。

## AStyle

直接包含了 `AStyle` 二进制，使得不再需要依赖宿主环境安装 `AStyle`

## KeilUtils

来源：https://github.com/Nigh/Keil_MacroPath

主要用于辅助使用 `Keil IDE` 的开发。这个工具提供了一种自动化的方法来修改 `Keil` 的工程文件，使其能够支持宏路径。

> - 将 `KeilUtils.exe` 放置在 `uvprojx` 后缀的工程文件相同的目录
> - 运行 `KeilUtils.exe init` 自动搜索工程并初始化配置
> - 运行 `KeilUtils.exe set MARCO_NAME PATH` 将路径 PATH 替换为宏 MARCO_NAME
> - 运行 `KeilUtils.exe list` 列举配置
> - 运行 `KeilUtils.exe path2macro` 将路径替换为宏
> - 运行 `KeilUtils.exe macro2path` 将宏替换回路径
> - 运行 `KeilUtils.exe remove MARCO_NAME` 删除配置的宏
> - 运行 `KeilUtils.exe replace foo bar` 将工程中的字符串 `foo` 替换为 `bar`


## p2a(picture-to-array)

来源：https://github.com/Nigh/picture-to-array

此工具用于将目录下的图片素材自动批量转换为 C 语言描述的位图形式。

## tcc

来源：https://bellard.org/tcc/

一个轻量高效的 C 编译器，使用它可以像脚本语言一样运行 C 程序，用于在编译工具链中实现仅仅靠 `makefile` 所难以完成的复杂功能。

## mpress

一个免费的高性能的 `PE32/PE32+/.NET/MAC-DARWIN` 格式可执行文件打包器，可以显著减小可执行文件的体积，并提高载入速度。
