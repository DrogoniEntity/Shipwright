#!/bin/bash
cmake -S. -Bbuild/nx -GNinja -DCMAKE_TOOLCHAIN_FILE=/opt/devkitpro/cmake/Switch.cmake