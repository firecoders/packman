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

#ifndef PACKMAN_CONTENT_PACKMAN_GUARD
#define PACKMAN_CONTENT_PACKMAN_GUARD

#include "engine/geometry/Rectangle.h"
#include "engine/geometry/Vector.hpp"
#include "engine/gamelogic/Pruning_world.hpp"
#include "engine/types/Index_node.hpp"
#include "engine/gui/Resource_manager.h"

#include "gamelogic/Actor.h"
#include "utils/typedefs.hpp"

namespace content
{
    class Packman : public gamelogic::Actor
    {
        public:
            Packman
            (
                std::weak_ptr < engine::gamelogic::Pruning_world < gamelogic::Entity > > world,
                utils::Entry_point entry_point,
                std::weak_ptr < engine::types::Index_node < utils::Event_node > > index,
                std::weak_ptr < engine::gui::Resource_manager > resource_manager,
                engine::geometry::Vector < int > position
            );

            bool is_obstacle_for ( std::string other_entity_type ) const;
            constexpr static char get_level_char () { return 'P'; };

            void die ();

        private:
            bool alive;

            void handle_key_event ( utils::Event event );
            void handle_custom_event ( utils::Event event );
    };
} /* namespace content */

#endif // PACKMAN_CONTENT_PACKMAN_GUARD
