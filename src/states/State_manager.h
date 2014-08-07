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

#ifndef STATES_STATE_MANGER_GUARD
#define STATES_STATE_MANGER_GUARD

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "engine/types/Index_node.hpp"
#include "engine/events/Receiver_forwarder.hpp"
#include "engine/gui/Window.h"

#include "engine/converters/Sfml_event_to_dict.h"
#include "engine/converters/Draw_event_to_dict.h"

#include "utils/typedefs.hpp"

namespace states
{
    class State_manager
    {
        public:
            State_manager ();

            utils::Entry_point get_entry_point () const;
            std::shared_ptr < engine::types::Index_node < utils::Event_receiver > > get_index () const;

            void set_state ( std::shared_ptr < utils::Event_receiver > new_state );
            void add_state ( std::vector < std::string > index_keys, std::shared_ptr < utils::Event_receiver > state );
            void switch_state ( std::vector < std::string > index_keys );
            std::shared_ptr < engine::gui::Window > wrap_window ( std::shared_ptr < sf::RenderWindow > render_window );

        private:
            std::shared_ptr < engine::events::Receiver_forwarder < utils::Event > > entry_point;
            std::shared_ptr < engine::types::Index_node < utils::Event_receiver > > index;
    };
} /* namespace states */

#endif // STATES_STATE_MANGER_GUARD
