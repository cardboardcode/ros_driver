#!/usr/bin/env bash

# Copyright (C) Bey Hao Yun - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# Written by Bey Hao Yun <beyhy94@gmail.com>, August 2021

git submodule update --init --recursive
cd deps/pcl/ || exit

if [ ! -d 'build']; then
  mkdir build
fi

cd build || exit
echo $PWD
cmake -DCMAKE_INSTALL_PREFIX=$PWD/../local ..
make install -j$(nproc)
