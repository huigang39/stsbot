# STS 机器人

## 安装 ROS2

```shell
wget http://fishros.com/install -O fishros && . fishros
```

## 安装 Cartographer

```shell
sudo apt install ros-$ROS_DISTRO-cartographer*
```

## 克隆代码
克隆本项目及其子模块到本地：

```shell
git clone --recurse-submodules https://github.com/huigang39/stsbot.git
```

## 依赖

```shell
apt install qtmultimedia5-dev libqt5serialport5-dev
rosdep install -y -r -q --from-paths src --ignore-src --rosdistro humble -y
```

## 编译

进入 `ros` 文件夹执行：

```shell
colcon build
```

如果编译过程中遇到如下警告：
```shell
SetuptoolsDeprecationWarning: setup.py install is deprecated. Use build and pip and other standards-based tools.
  warnings.warn(
---
```

需要降低 `setuptools` 版本：
```shell
pip install setuptools==58.2.0
```
