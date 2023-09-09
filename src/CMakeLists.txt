########################################################################
# Copyright (c) 2023, Claudio Costagliola Fiedler
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
########################################################################
add_library(tech_task_lib
  STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/h/abstractAccount.h
  ${CMAKE_CURRENT_SOURCE_DIR}/h/account.h
  ${CMAKE_CURRENT_SOURCE_DIR}/h/personAccount.h
  ${CMAKE_CURRENT_SOURCE_DIR}/h/enterpriseAccount.h
  ${CMAKE_CURRENT_SOURCE_DIR}/h/accountId.h
  ${CMAKE_CURRENT_SOURCE_DIR}/h/accountMgr.h
  ${CMAKE_CURRENT_SOURCE_DIR}/h/visitor.h
  ${CMAKE_CURRENT_SOURCE_DIR}/h/singletonUniqueIdGenerator.h
  ${CMAKE_CURRENT_SOURCE_DIR}/cpp/accountMgr.cpp
)
target_link_libraries(tech_task PUBLIC tech_task_lib)

target_include_directories(tech_task PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/h")
target_include_directories(tech_task_lib PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/h")
