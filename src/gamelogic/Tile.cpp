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

#include "gamelogic/Tile.h"

#include <sstream>

#include "utils/receiver_tree_manipulation.hpp"
#include "utils/tile_rectangle.hpp"

using namespace gamelogic;

Tile::Tile
(
    std::weak_ptr < engine::types::Index_node < utils::Event_node > > index,
    std::weak_ptr < engine::gui::Resource_manager > resource_manager,
    engine::geometry::Vector < int > position,
    std::string type_string
) :
    index ( index ),
    resource_manager ( resource_manager ),
    position ( position ),
    type_string ( type_string ),
    visible ( true )
{
    sf::Sprite sprite { resource_manager.lock ()->get_texture ( type_string ) };
    sprite.setScale ( 2.f, 2.f );
    sprite.setPosition ( 32 * position.get_x (), 32 * position.get_y () );

    utils::add_lambda_receiver ( index, { "draw" },
        [ this, sprite ] ( utils::Event event )
        {
            if ( visible )
                event->at ( "rendertarget" ).get < sf::RenderTarget* > ()->draw ( sprite );
        }
    );
}

engine::geometry::Rectangle Tile::get_collision_box () const
{
    return utils::tile_rectangle ( position );
}

engine::geometry::Vector < int > Tile::get_position () const
{
    return position;
}

std::string Tile::get_type_string () const
{
    return type_string;
}

std::string Tile::get_address () const
{
    std::stringstream address;
    address << this;
    return address.str ();
}

void Tile::set_visibility ( bool visibility )
{
    visible = visibility;
}

bool Tile::get_visibility () const
{
    return visible;
}
