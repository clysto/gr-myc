# gr-myc

## 安装

推荐 conda/mamba 安装 gnuradio 和 gnuradio-build-deps 包。

```
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=<conda虚拟环境位置>
# 比如: cmake .. -DCMAKE_INSTALL_PREFIX="/home/maoyachen/.mambaforge/envs/dev"
make
make install
```

