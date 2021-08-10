#!/usr/bin/env bash

# Copyright (C) Bey Hao Yun - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# Written by Bey Hao Yun <beyhy94@gmail.com>, August 2021

git submodule update --init --recursive
cd deps/pcl/
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=$PWD/../local ..
make install -j$(nproc)
