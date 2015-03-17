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

#ifndef STATES_BASE_STATE_GUARD
#define STATES_BASE_STATE_GUARD

#include <memory>
#include <vector>
#include <algorithm>

#include "engine/types/Index_node.hpp"
#include "engine/events/Broadcaster.hpp"
#include "engine/events/Filter_node.hpp"

#include "utils/typedefs.hpp"
#include "utils/Tee.hpp"

namespace states
{
    class Base_state
    {
        public:
            Base_state ();

            std::shared_ptr < engine::types::Index_node < utils::Event_node > > get_index ();
            std::shared_ptr < utils::Event_receiver > get_receiver () const;

            void add_node ( std::vector < std::string > keys, std::shared_ptr < utils::Event_node > node );

            virtual ~Base_state () = default;

        protected:
            std::shared_ptr < engine::types::Index_node < utils::Event_node > > index;
            std::shared_ptr < engine::events::Broadcaster < utils::Event > > broadcaster;

        private:
            void add_sfml_type ( std::string type );
    };
} /* namespace states */

#endif // STATES_BASE_STATE_GUARD
