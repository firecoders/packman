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

#include "content/Packman.h"

using namespace content;

#include "utils/receiver_tree_manipulation.hpp"

Packman::Packman
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
        "actor.packman"
    )
{
    utils::add_lambda_receiver ( index, { "sfml", "KeyPressed" },
        [ this ] ( utils::Event event ) { handle_key_event ( event ); }
    );
}

bool Packman::is_obstacle_for ( std::string other_entity_type ) const
{
    return false;
}

void Packman::handle_key_event ( utils::Event event )
{
    if ( event->at ( "type.string" ).get < std::string > () != "converted sf::Event of type KeyPressed" )
        return;
    std::string key_code = event->at ( "key.code" ).get < std::string > ();
    if ( key_code == "W" || key_code == "Up" )
        propose_move_offset ( { 0, -1 } );
    if ( key_code == "A" || key_code == "Left" )
        propose_move_offset ( { -1, 0 } );
    if ( key_code == "S" || key_code == "Down" )
        propose_move_offset ( { 0, 1 } );
    if ( key_code == "D" || key_code == "Right" )
        propose_move_offset ( { 1, 0 } );
}
