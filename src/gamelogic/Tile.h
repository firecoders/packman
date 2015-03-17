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

#ifndef PACKMAN_GAMELOGIC_TILE_GUARD
#define PACKMAN_GAMELOGIC_TILE_GUARD

#include <memory>
#include <string>

#include "engine/types/Index_node.hpp"
#include "engine/gui/Resource_manager.h"
#include "engine/geometry/Vector.hpp"

#include "gamelogic/Entity.h"
#include "utils/typedefs.hpp"

namespace gamelogic
{
    class Tile : public gamelogic::Entity
    {
        public:
            Tile
            (
                std::weak_ptr < engine::types::Index_node < utils::Event_node > > index,
                std::weak_ptr < engine::gui::Resource_manager > resource_manager,
                engine::geometry::Vector < int > position,
                std::string type_string
            );

            engine::geometry::Rectangle get_collision_box () const;
            engine::geometry::Vector < int > get_position () const;
            std::string get_type_string () const;
            std::string get_address () const;

            void set_visibility ( bool visibility );
            bool get_visibility () const;

        protected:
            std::weak_ptr < engine::types::Index_node < utils::Event_node > > index;
            std::weak_ptr < engine::gui::Resource_manager > resource_manager;
            engine::geometry::Vector < int > position;
            std::string type_string;
            bool visible;
    };
} /* namespace gamelogic */

#endif // PACKMAN_GAMELOGIC_TILE_GUARD
