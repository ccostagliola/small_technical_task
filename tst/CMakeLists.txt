########################################################################
# Copyright (c) 2023, Claudio Costagliola Fiedler
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
########################################################################
include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        58d77fa8070e8cec2dc1ed015d66b454c8d78850 #release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable (account_test account_test.cpp)
target_include_directories(account_test PRIVATE "${CMAKE_SOURCE_DIR}/src/h")

target_link_libraries(account_test
  PRIVATE
  GTest::gtest_main
  tech_task_lib)

gtest_discover_tests(account_test)