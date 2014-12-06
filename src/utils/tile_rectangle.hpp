/* packman, A packman implementation using the 2D-engine
   Copyright (c) 2014 firecoders

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE. */

#ifndef PACKMAN_UTILS_TILE_RECTANGLE_GUARD
#define PACKMAN_UTILS_TILE_RECTANGLE_GUARD

#include "engine/geometry/Rectangle.h"
#include "engine/geometry/Vector.hpp"
#include "engine/geometry/Interval.hpp"

namespace utils
{
    inline engine::geometry::Rectangle tile_rectangle ( engine::geometry::Vector < int > position )
    {
        return
        {
            engine::geometry::Interval < double >
            {
                ( double ) position.get_x (),
                ( double ) ( position.get_x () + 1 ) - 0.0000001,
            },
            engine::geometry::Interval < double >
            {
                ( double ) position.get_y (),
                ( double ) ( position.get_y () + 1 ) - 0.0000001,
            }
        };
    }
} /* namespace utils */

#endif // PACKMAN_UTILS_TILE_RECTANGLE_GUARD
