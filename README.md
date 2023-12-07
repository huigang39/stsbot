# EAIBOT

## EAIBOT 下位机

### PINOUT 引脚

|设备|引脚|
|:--:|:--:|
|左轮电机正向|6|
|左轮电机反向|7|
|右轮电机正向|10|
|右轮电机反向|9|
|左轮编码器正向|3|
|左轮编码器反向|2|
|右轮编码器正向|18|
|右轮编码器反向|19|

### MCU 平台

|Microcontroller|ATmega2560|
|:-:|:-:|
|Operating Voltage|5V|
|Input Voltage (recommended)|7-12V|
|Input Voltage (limit)|6-20V|
|Digital I/O Pins|54 (of which 15 provide PWM output)|
|Analog Input Pins|16|
|DC Current per I/O Pin |20 mA|
|DC Current for 3.3V Pin|50 mA|
|Flash Memory|256 KB of which 8 KB used by bootloader|
|SRAM|8 KB|
|EEPROM|4 KB|
|Clock Speed|16 MHz|
|LED_BUILTIN|13|

### Firmware 固件

[eaibot_firmware](https://github.com/huigang39/stsbot/tree/eaibot/eaibot_firmware)

使用 [PlatformIO](https://platformio.org/) 平台搭建

### 快速开始

#### 安装 VSCode

Windows 系统可在 Microsoft Store 内直接安装，Linux 系统可参考[官方文档](https://code.visualstudio.com/docs/setup/linux)进行安装。

对于 Linux 新手，如果在 Ubuntu 系统下安装，可以通过在终端键入 `sudo snap install --classic code` 后回车即可安装 VSCode，但该方法安装的 VSCode 将无法输入中文字符，该 Bug 尚不知何时能够解决，此为下策。

#### 安装 PlatformIO IDE

打开终端，`cd` 进入 `eaibot_firmware` 文件夹，键入 `code .` 即可在该文件夹下打开 VSCode。

打开 VSCode 后，点击左侧 Extensions 图标，打开插件管理界面，搜索 `PlatformIO IDE` 点击第一个搜索结果的 `install` 按钮，然后泡一杯茶，稍作等待即可。

> 注：倘若你没有科学上网，那么等待时间可能稍长且容易失败。

等待 VSCode 右下角弹出重启 VSCode，点击重启 VSCode 即可。VSCode 会自动重启随后根据 `platformio.ini` 配置文件中的信息自动安装依赖。

#### 烧录程序

确认 VSCode 低栏的项目选择为 `eaibot_firmware` 后，使用 `ctrl + alt + u` 快捷键即可自动编译并上传程序至单片机。

> 注：
>
> 1. 烧录时尽量不要外接其他 USB 转串口设备，否则软件可能将无法自动识别上传端口，除非在 platformio.ini 中手动指定程序上传端口。
>
> 2. 第一次在某平台（如 atmelavr、espressif 等平台）使用上传程序时，PlatformIO IDE 会自动下载烧录工具，稍作等待即可。

#### 测试

打开 EAIBOT 电源，按下急停按钮（防止小车意外启动），使用快捷键 `ctrl + alt + s` 打开串口监视器，键入 `e` 回车发送至串口。可以看到单片机返回了两个数字，分别是左右轮编码器的读数。推动 EAIBOT 使轮子发生转动，可以看到读数发生改变，且该改变为双向均可变化。

然后向右旋转急停按钮，退出急停模式，键入 `m 30 30` 以驱动小车，如果观察到 EAIBOT 向前移动即测试成功；倘若 EAIBOT 出现非直行（如左右偏航）情况，则可能为电源电压不足，导致两个电机无法同速，需要对 EAIBOT 进行充电。

## EAIBOT 上位机

