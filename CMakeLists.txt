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

cmake_minimum_required ( VERSION 2.6 )
project ( packman )
include ( ExternalProject )

set ( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" )

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

# Compile the eventsystem
ExternalProject_Add ( EVENTSYSTEM
    PREFIX ${EXTERNALS_PREFIX}
    URL https://github.com/firecoders/eventsystem/archive/v0.2.2.tar.gz
    URL_HASH SHA256=35d4a3d6da47a67d501baa473997152e097efc67b8a1075db8098a5153a7d75b
    DOWNLOAD_NAME eventsystem-v0.2.2.tar.gz
    CMAKE_ARGS ${EXTERNALS_CMAKE_ARGS}
)

# Compile the 2D-gui
ExternalProject_Add ( 2D_GUI
    PREFIX ${EXTERNALS_PREFIX}
    URL https://github.com/firecoders/2D-gui/archive/v0.3.0.tar.gz
    URL_HASH SHA256=b454e4de5583ae9551bf172fcfd075e7df3e089e43e999b94243370a7b1fef0f
    DOWNLOAD_NAME 2D-gui-v0.3.0.tar.gz
    CMAKE_ARGS ${EXTERNALS_CMAKE_ARGS} -DFILEPATH=${EXTERNALS_PREFIX}
)

# Compile the gamelogic
ExternalProject_Add ( GAMELOGIC
    PREFIX ${EXTERNALS_PREFIX}
    URL https://github.com/firecoders/gamelogic/archive/v0.1.0.tar.gz
    URL_HASH SHA256=b4034eaf62d6d43bbf06eb09ae0baa673e444a702fe36dd5bd5885452054e559
    DOWNLOAD_NAME gamelogic-v0.1.0.tar.gz
    CMAKE_ARGS ${EXTERNALS_CMAKE_ARGS}
)

# Make sure sfml is installed
find_package ( SFML 2 COMPONENTS graphics window system )

# Import libeventsystem.a
add_library ( libeventsystem STATIC IMPORTED )
set_target_properties ( libeventsystem PROPERTIES IMPORTED_LOCATION ${EXTERNALS_PREFIX}/lib/libeventsystem.a )
add_dependencies ( libeventsystem EVENTSYSTEM )

# Import lib2D-gui.a
add_library ( lib2D-gui STATIC IMPORTED )
set_target_properties ( lib2D-gui PROPERTIES IMPORTED_LOCATION ${EXTERNALS_PREFIX}/lib/lib2D-gui.a )
add_dependencies ( lib2D-gui 2D_GUI )

# Import libgamelogic.a
add_library ( libgamelogic STATIC IMPORTED )
set_target_properties ( libgamelogic PROPERTIES IMPORTED_LOCATION ${EXTERNALS_PREFIX}/lib/libgamelogic.a )
add_dependencies ( libgamelogic GAMELOGIC )

add_subdirectory ( ${CMAKE_SOURCE_DIR}/src )
