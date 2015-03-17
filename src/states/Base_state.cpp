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

#include "states/Base_state.h"

#include <iostream>

using namespace states;

const std::string sfml_event_type_prefix = "converted sf::Event of type ";
const int sfml_event_type_prefix_len = sfml_event_type_prefix.length ();

Base_state::Base_state () :
    broadcaster ( std::make_shared < utils::Event_broadcaster > () ),
    index ( std::make_shared < engine::types::Index_node < utils::Event_node > > () )
{
    index->set_wrapped ( broadcaster );
    index->at ( "draw"   )->set_wrapped ( std::make_shared < utils::Event_broadcaster > () );
    index->at ( "sfml"   )->set_wrapped ( std::make_shared < utils::Event_broadcaster > () );
    index->at ( "custom" )->set_wrapped ( std::make_shared < utils::Event_broadcaster > () );
    auto notdraw = std::make_shared < utils::Event_broadcaster > ();

    {
        std::shared_ptr < utils::Tee < utils::Event > > tee =
            std::make_shared < utils::Tee < utils::Event > >
        (
            [] ( utils::Event event )
            {
                try
                {
                    return event->at ( "type.string" ).get < std::string > () == "converted engine::gui::Draw_event";
                }
                catch (...)
                {
                    return false;
                }
            },
            index->at ( "draw" )->get_wrapped (),
            notdraw
        );
        broadcaster->subscribe ( tee );
    }

    {
        std::shared_ptr < utils::Tee < utils::Event > > tee =
            std::make_shared < utils::Tee < utils::Event > >
        (
            [] ( utils::Event event )
            {
                try
                {
                    std::string typestring = event->at ( "type.string" ).get < std::string > ();
                    return typestring.substr ( 0, sfml_event_type_prefix_len ) == sfml_event_type_prefix;
                }
                catch (...)
                {
                    return false;
                }
            },
            index->at ( "sfml"   )->get_wrapped (),
            index->at ( "custom" )->get_wrapped ()
        );
        notdraw->subscribe ( tee );
    }

    add_sfml_type ( "MouseButtonPressed" );
    add_sfml_type ( "MouseButtonReleased" );
    add_sfml_type ( "MouseWheelMoved");
    add_sfml_type ( "MouseMoved" );
    add_sfml_type ( "MouseEntered" );
    add_sfml_type ( "MouseLeft"   );
    add_sfml_type ( "KeyPressed" );
    add_sfml_type ( "KeyReleased" );
    add_sfml_type ( "LostFocus" );
    add_sfml_type ( "GainedFocus" );
    add_sfml_type ( "TextEntered" );
    add_sfml_type ( "Resized" );
}

std::shared_ptr < engine::types::Index_node < utils::Event_node > > Base_state::get_index ()
{
    return index;
}

std::shared_ptr < utils::Event_receiver > Base_state::get_receiver () const
{
    return broadcaster;
}

void Base_state::add_node ( std::vector < std::string > keys, std::shared_ptr < utils::Event_node > node )
{
    index->get_descendant ( keys )->set_wrapped ( node );
    index->get_descendant ( keys.begin (), --keys.end () )->get_wrapped ()->subscribe ( node );
}

void Base_state::add_sfml_type ( std::string type )
{
    add_node
    (
        { "sfml", type },
        std::make_shared < engine::events::Filter_node < utils::Event > >
        (
            [ type ] ( utils::Event event )
            {
                auto event_type = event->at ( "type.string" ).get < std::string > ();
                return type == event_type.substr ( sfml_event_type_prefix_len );
            }
        )
    );
}
