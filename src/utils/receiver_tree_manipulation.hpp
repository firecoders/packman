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

#ifndef PACKMAN_UTILS_RECEIVER_TREE_MANIPULATION_GUARD
#define PACKMAN_UTILS_RECEIVER_TREE_MANIPULATION_GUARD

#include <memory>
#include <functional>
#include <vector>
#include <string>

#include "engine/types/Index_node.hpp"
#include "engine/events/Lambda_receiver.hpp"

#include "utils/typedefs.hpp"

namespace utils
{
    inline void add_lambda_receiver
    (
        std::weak_ptr < engine::types::Index_node < utils::Event_node > > tree,
        std::vector < std::string > keys,
        std::function < void ( utils::Event ) > lambda_function
    )
    {
        tree.lock ()->get_descendant ( keys )->get_wrapped ()->subscribe
        (
            std::make_shared < engine::events::Lambda_receiver < utils::Event > >
            (
                lambda_function
            )
        );
    }
    inline void add_lambda_receiver
    (
        std::shared_ptr < engine::types::Index_node < utils::Event_node > > tree,
        std::vector < std::string > keys,
        std::function < void ( utils::Event ) > lambda_function
    )
    {
        tree->get_descendant ( keys )->get_wrapped ()->subscribe
        (
            std::make_shared < engine::events::Lambda_receiver < utils::Event > >
            (
                lambda_function
            )
        );
    }
} /* namespace utils */

#endif // PACKMAN_UTILS_RECEIVER_TREE_MANIPULATION_GUARD
