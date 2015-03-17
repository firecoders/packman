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

#ifndef UTILS_TYPEDEFS_GUARD
#define UTILS_TYPEDEFS_GUARD

#include <memory>

#include "engine/converters/Dict.hpp"

#include "engine/events/interfaces/Receiver.h"
#include "engine/events/interfaces/Subscribable.h"
#include "engine/events/interfaces/Node.h"
#include "engine/events/Broadcaster.hpp"

namespace utils
{
    typedef std::shared_ptr < engine::types::Dict > Event;
    typedef engine::events::Receiver     < Event > Event_receiver;
    typedef engine::events::Subscribable < Event > Event_subscribable;
    typedef engine::events::Node         < Event > Event_node;
    typedef engine::events::Broadcaster  < Event > Event_broadcaster;
    typedef std::weak_ptr < Event_receiver > Entry_point;
} /* namespace utils */

#endif // UTILS_TYPEDEFS_GUARD
