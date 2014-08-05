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

# Find source files for packman executable
file ( GLOB_RECURSE PACKMAN_EXECUTABLE_SRC ${CMAKE_SOURCE_DIR} *.cpp )
include_directories ( ${CMAKE_SOURCE_DIR}/src )

# Create packman executable
add_executable ( packman ${PACKMAN_EXECUTABLE_SRC} )

# Use Sfml for packman executable
include_directories ( ${SFML_INCLUDE_DIRS} )
target_link_libraries ( packman ${SFML_LIBRARIES} )

# Use 2D-engine for packman executable
include_directories ( ${EXTERNALS_PREFIX}/src/2D_ENGINE/inc )
target_link_libraries ( packman lib2D-engine )
