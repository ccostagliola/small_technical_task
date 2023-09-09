########################################################################
# Copyright (c) 2023, Claudio Costagliola Fiedler
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.
########################################################################
option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen
  REQUIRED dot)
if (DOXYGEN_FOUND)
  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  message("Doxygen build started")

  add_custom_target(doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
    )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the documentation")
endif (DOXYGEN_FOUND)
