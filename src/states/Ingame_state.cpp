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

#include "states/Ingame_state.h"

#include <algorithm>

#include "engine/events/Lambda_receiver.hpp"
#include "utils/typedefs.hpp"
#include "utils/tile_rectangle.hpp"
#include "utils/receiver_tree_manipulation.hpp"

using namespace states;

Ingame_state::Ingame_state
(
    utils::Globals globals,
    std::shared_ptr < engine::gamelogic::Pruning_world < gamelogic::Entity > > world
) :
    globals ( globals ),
    world ( world )
{
    utils::add_lambda_receiver ( index, { "custom" },
        [ this ] ( utils::Event event ) { handle_custom_event ( event ); }
    );
}

void Ingame_state::handle_custom_event ( utils::Event event )
{
    std::string type_string;
    try
    {
        type_string = event->at ( "type.string" ).get < std::string > ();
    }
    catch ( ... )
    {}
    if ( type_string == "movement.proposal" )
    {
        handle_move_proposal_event ( event );
    }
}

void Ingame_state::handle_move_proposal_event ( utils::Event event )
{
    int x = event->at ( "new.x" ).get < int > ();
    int y = event->at ( "new.y" ).get < int > ();
    std::string actor_type = event->at ( "actor.type" ).get < std::string > ();
    auto collisions = this->world->get_collisions ( utils::tile_rectangle ( { x, y } ) );

    for ( std::shared_ptr < gamelogic::Entity > passive : collisions )
    {
        utils::Event new_event = std::make_shared < engine::types::Dict > ();
        ( * new_event ) [ "type.string" ] = std::string ( "collision" );
        ( * new_event ) [ "pos.x" ] = x;
        ( * new_event ) [ "pos.y" ] = y;
        ( * new_event ) [ "active.type" ] = actor_type;
        ( * new_event ) [ "active.address" ] = event->at ( "actor.address" );
        ( * new_event ) [ "passive.type" ] = passive->get_type_string ();
        ( * new_event ) [ "passive.address" ] = passive->get_address ();
        this->globals.state_manager->get_entry_point ().lock ()->receive ( new_event );
    }

    utils::Event new_event = std::make_shared < engine::types::Dict > ();
    ( * new_event ) [ "new.x" ] = x;
    ( * new_event ) [ "new.y" ] = y;
    ( * new_event ) [ "actor.type" ] = actor_type;
    ( * new_event ) [ "actor.address" ] = event->at ( "actor.address" );
    if
    (
        std::none_of
        (
            collisions.begin (),
            collisions.end (),
            [ actor_type ] ( std::shared_ptr < gamelogic::Entity > entity )
            { return entity->is_obstacle_for ( actor_type ); }
        )
    )
    {
        ( * new_event ) [ "type.string" ] = std::string ( "movement.success" );
    }
    else
    {
        ( * new_event ) [ "type.string" ] = std::string ( "movement.obstructed" );
    }
    this->globals.state_manager->get_entry_point ().lock ()->receive ( new_event );
}
