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

#include "content/Dot.h"

using namespace content;

#include "utils/receiver_tree_manipulation.hpp"

Dot::Dot
(
    std::weak_ptr < engine::types::Index_node < utils::Event_node > > index,
    std::weak_ptr < engine::gui::Resource_manager > resource_manager,
    engine::geometry::Vector < int > position,
    utils::Entry_point entry_point
) :
    Tile
    (
        index,
        resource_manager,
        position,
        "powerup.dot"
    ),
    entry_point ( entry_point )
{
    utils::add_lambda_receiver ( index, { "custom" },
        [ this ] ( utils::Event event ) { handle_custom_event ( event ); }
    );
}


bool Dot::is_obstacle_for ( std::string other_entity_type ) const
{
    return false;
}

void Dot::handle_custom_event ( utils::Event event )
{
    if ( event->at ( "type.string" ).get < std::string > () != "collision" )
        return;
    if
    (
        event->at ( "passive.address" ).get < std::string > () == get_address () &&
        event->at ( "active.type" ).get < std::string > () == "actor.packman"
    )
    {
        set_visibility ( false );
        utils::Event powerup_event = std::make_shared < engine::types::Dict > ();
        ( * powerup_event ) [ "type.string" ] = std::string ( "powerup" );
        ( * powerup_event ) [ "pos.x" ] = get_position ().get_x ();
        ( * powerup_event ) [ "pos.y" ] = get_position ().get_y ();
        ( * powerup_event ) [ "actor.type" ] = std::string ( "actor.packman" );
        ( * powerup_event ) [ "actor.address" ] = event->at ( "active.address" );
        ( * powerup_event ) [ "powerup.type" ] = get_type_string ();
        ( * powerup_event ) [ "powerup.address" ] = get_address ();
        entry_point.lock ()->receive ( powerup_event );
    }
}
