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

## 编译

进入 `ros` 文件夹执行：

```shell
colcon build
```
