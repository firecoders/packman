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

#include "gamelogic/Actor.h"

#include "utils/receiver_tree_manipulation.hpp"
#include "utils/tile_rectangle.hpp"

using namespace gamelogic;

Actor::Actor
(
    std::weak_ptr < engine::gamelogic::Pruning_world < gamelogic::Entity > > world,
    utils::Entry_point entry_point,
    std::weak_ptr < engine::types::Index_node < utils::Event_node > > index,
    std::weak_ptr < engine::gui::Resource_manager > resource_manager,
    engine::geometry::Vector < int > position,
    std::string type_string
) :
    world ( world ),
    entry_point ( entry_point ),
    index ( index ),
    resource_manager ( resource_manager ),
    position ( position ),
    sprite ( resource_manager.lock ()->get_texture ( type_string ) ),
    type_string ( type_string ),
    visible ( true )
{
    move_to ( position );
    sprite.setScale ( 2.f, 2.f );

    utils::add_lambda_receiver ( index, { "draw" },
        [ this ] ( utils::Event event )
        {
            if ( visible )
                event->at ( "rendertarget" ).get < sf::RenderTarget* > ()->draw ( sprite );
        }
    );

    utils::add_lambda_receiver ( index, { "custom" },
        [ this ] ( utils::Event event ) { handle_custom_event ( event ); }
    );
}

void Actor::move_to ( engine::geometry::Vector < int > position )
{
    this->position = position;
    sprite.setPosition ( 32 * position.get_x (), 32 * position.get_y () );
    try
    {
        world.lock ()->update_pruning ( this );
    }
    catch ( std::out_of_range )
    {}
}

void Actor::move_offset ( engine::geometry::Vector < int > offset )
{
    move_to ( position + offset );
}

void Actor::propose_move_to ( engine::geometry::Vector < int > position )
{
    utils::Event propose_event = std::make_shared < engine::types::Dict > ();
    ( * propose_event ) [ "type.string" ] = std::string ( "movement.proposal" );
    ( * propose_event ) [ "new.x" ] = position.get_x ();
    ( * propose_event ) [ "new.y" ] = position.get_y ();
    ( * propose_event ) [ "actor.type" ] = get_type_string ();
    ( * propose_event ) [ "actor.address" ] = get_address ();
    entry_point.lock ()->receive ( propose_event );
}

void Actor::propose_move_offset ( engine::geometry::Vector < int > offset )
{
    propose_move_to ( position + offset );
}

engine::geometry::Vector < int > Actor::get_position () const
{
    return position;
}

engine::geometry::Rectangle Actor::get_collision_box () const
{
    return utils::tile_rectangle ( get_position () );
}

std::string Actor::get_type_string () const
{
    return type_string;
}

std::string Actor::get_address () const
{
    std::stringstream address;
    address << this;
    return address.str ();
}

void Actor::handle_custom_event ( utils::Event event )
{
    std::string type_string, address;
    int x, y;
    try
    {
        type_string = event->at ( "type.string" ).get < std::string > ();
        x = event->at ( "new.x" ).get < int > ();
        y = event->at ( "new.y" ).get < int > ();
        address = event->at ( "actor.address" ).get < std::string > ();
    }
    catch ( ... )
    {}

    if ( address == get_address () )
    {
        if ( type_string == "movement.success" )
        {
            move_to ( { x, y } );
            send_movement_done_event ( true, { x, y } );
        }
        else if ( type_string == "movement.obstructed" )
        {
            send_movement_done_event ( false, { x, y } );
        }
    }
}

void Actor::send_movement_done_event ( bool success, engine::geometry::Vector < int > target )
{
    utils::Event done_event = std::make_shared < engine::types::Dict > ();
    ( * done_event ) [ "type.string" ] = std::string ( "movement.done" );
    ( * done_event ) [ "new.x" ] = target.get_x ();
    ( * done_event ) [ "new.y" ] = target.get_y ();
    ( * done_event ) [ "actor.type" ] = get_type_string ();
    ( * done_event ) [ "actor.address" ] = get_address ();
    ( * done_event ) [ "success" ] = success;
    entry_point.lock ()->receive ( done_event );
}

void Actor::set_visibility ( bool visibility )
{
    visible = visibility;
}

bool Actor::get_visibility () const
{
    return visible;
}
