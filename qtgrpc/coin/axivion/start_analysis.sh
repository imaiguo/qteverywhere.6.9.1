#!/bin/bash
# Copyright (C) 2024 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

$HOME/bauhaus-suite/setup.sh --non-interactive
export PATH=/home/qt/bauhaus-suite/bin:$PATH
export BAUHAUS_CONFIG=$(cd $(dirname $(readlink -f $0)) && pwd)
export AXIVION_VERSION_NAME=$(git rev-parse HEAD)
export EXCLUDE_FILES="build/*:src/3rdparty/*"
export CAFECC_BASEPATH="/home/qt/work/qt/$TESTED_MODULE_COIN"
gccsetup --cc gcc --cxx g++ --config "$BAUHAUS_CONFIG"
cd "$CAFECC_BASEPATH"
BAUHAUS_IR_COMPRESSION=none COMPILE_ONLY=1 cmake -G Ninja -DAXIVION_ANALYSIS_TOOLCHAIN_FILE=/home/qt/bauhaus-suite/profiles/cmake/axivion-launcher-toolchain.cmake -DCMAKE_PREFIX_PATH=/home/qt/work/qt/qtgrpc/build -DCMAKE_PROJECT_INCLUDE_BEFORE=/home/qt/bauhaus-suite/profiles/cmake/axivion-before-project-hook.cmake -B build -S . --fresh
cmake --build build -j4
for MODULE in qtgrpc qtprotobuf; do
    export MODULE
    export PLUGINS=""
    export IRNAME=build/$MODULE.ir
    if [ "$MODULE" == "qtgrpc" ]
    then
        export TARGET_NAME="build/lib/libQt6Grpc.so.*.ir:build/lib/libQt6GrpcQuick.so.*.ir:"
        export PLUGINS="build/qml/QtGrpc/libgrpcquickplugin.so"
        export PACKAGE="Add-ons"
    elif [ "$MODULE" == "qtprotobuf" ]
    then
        export TARGET_NAME="build/lib/libQt6QtProtobuf.so.*.ir:build/lib/libQt6ProtobufQtGuiTypes.so:build/lib/libQt6ProtobufQtCoreTypes.so.*.ir:build/lib/libQt6ProtobufWellKnownTypes.so.*.ir"
        export PACKAGE="Add-ons"
    fi
    axivion_ci "$@"
done
