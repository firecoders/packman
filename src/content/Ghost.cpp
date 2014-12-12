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

#include "content/Ghost.h"

using namespace content;

#include <cstdlib> // for std::rand

#include "engine/events/Lambda_receiver.hpp"

#include "utils/tile_rectangle.hpp"
#include "utils/receiver_tree_manipulation.hpp"

Ghost::Ghost
(
    std::weak_ptr < engine::gamelogic::Pruning_world < gamelogic::Entity > > world,
    utils::Entry_point entry_point,
    std::weak_ptr < engine::types::Index_node < utils::Event_node > > index,
    std::weak_ptr < engine::gui::Resource_manager > resource_manager,
    engine::geometry::Vector < int > position
) :
    Actor
    (
        world,
        entry_point,
        index,
        resource_manager,
        position,
        "actor.ghost"
    )
{
    utils::add_lambda_receiver ( index, { "custom" },
        [ this ] ( utils::Event event ) { handle_custom_event ( event ); }
    );
}


bool Ghost::is_obstacle_for ( std::string other_entity_type ) const
{
    return other_entity_type == "actor.ghost";
}

void Ghost::handle_custom_event ( utils::Event event )
{
    if ( event->at ( "type.string" ).get < std::string > () != "movement.done" )
        return;
    std::string actor_type = event->at ( "actor.type" ).get < std::string > ();
    if ( actor_type == "actor.packman" )
    {
        int x = event->at ( "new.x" ).get < int > ();
        int y = event->at ( "new.y" ).get < int > ();
        step ( { x, y } );
    }
}

void Ghost::step ( engine::geometry::Vector < int > target )
{
    int x = 0;
    int y = 0;
    if ( std::rand () % 2 )
    {
        engine::geometry::Vector < int > target_offset = target - get_position ();
        if ( target_offset.get_x () > 0 ) x = 1;
        if ( target_offset.get_x () < 0 ) x = -1;
        if ( target_offset.get_y () > 0 ) y = 1;
        if ( target_offset.get_y () < 0 ) y = -1;
    }
    else
    {
        x = ( std::rand () % 3 ) - 1;
        y = ( std::rand () % 3 ) - 1;
    }
    if ( x != 0 || y != 0 )
    {
        propose_move_offset ( { x, y } );
    }
}
