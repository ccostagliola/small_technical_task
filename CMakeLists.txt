########################################################################
# Copyright (c) 2023, Claudio Costagliola Fiedler
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
########################################################################
cmake_minimum_required(VERSION 3.20)

project(SmallTechnicalTask
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

add_executable(tech_task
  ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/main.cpp
)

add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(doc)