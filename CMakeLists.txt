# packman, A packman implementation using the 2D-engine
# Copyright (c) 2014 firecoders
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

cmake_minimum_required ( VERSION 3.0 )
project ( packman )
include ( ExternalProject )

# Output packman executable in root directory
set ( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/.. )

# Use C++11 standard
if ( CMAKE_CXX_COMPILER MATCHES ".*clang" )
    set ( CMAKE_COMPILER_IS_CLANG )
endif ( CMAKE_CXX_COMPILER MATCHES ".*clang" )

if ( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG )
    list ( APPEND CMAKE_CXX_FLAGS "-std=c++11" )
endif ( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG )

# Store external dependencies in build/external/
set ( EXTERNALS_PREFIX ${PROJECT_BINARY_DIR}/external )
set ( EXTERNALS_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNALS_PREFIX} )

# Compile the 2D-engine
ExternalProject_Add ( 2D_ENGINE
    PREFIX ${EXTERNALS_PREFIX}
    GIT_REPOSITORY https://github.com/firecoders/2D-engine
    CMAKE_ARGS ${EXTERNALS_CMAKE_ARGS}
)

# Make sure sfml is installed
find_package ( SFML 2 COMPONENTS graphics window system )

# Import lib2D-engine.a
add_library ( lib2D-engine STATIC IMPORTED )
set_target_properties ( lib2D-engine PROPERTIES IMPORTED_LOCATION ${EXTERNALS_PREFIX}/lib/lib2D-engine.a )
add_dependencies ( lib2D-engine 2D_ENGINE )

add_subdirectory ( ${CMAKE_SOURCE_DIR}/src )
