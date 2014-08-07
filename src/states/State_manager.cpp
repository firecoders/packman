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

#include "states/State_manager.h"

using namespace states;

State_manager::State_manager () :
    entry_point ( std::make_shared < engine::events::Receiver_forwarder < utils::Event > > ( nullptr ) ),
    index       ( std::make_shared < engine::types::Index_node < utils::Event_receiver > > () )
{}

utils::Entry_point State_manager::get_entry_point () const
{
    return entry_point;
}

std::shared_ptr < engine::types::Index_node < utils::Event_receiver > > State_manager::get_index () const
{
    return index;
}

void State_manager::set_state ( std::shared_ptr < utils::Event_receiver > new_state )
{
    entry_point->redirect ( new_state );
}

void State_manager::add_state ( std::vector < std::string > index_keys, std::shared_ptr < utils::Event_receiver > state )
{
    index->get_descendant ( index_keys )->set_wrapped ( state );
}

void State_manager::switch_state ( std::vector < std::string > index_keys )
{
    auto new_state = index->get_descendant ( index_keys )->get_wrapped ();
    if ( new_state == nullptr )
    {
        std::cerr << "[FAILED] State_manager::switch_state was called with invalid index keys:" << std::endl;
        std::copy ( index_keys.begin (), index_keys.end (), std::ostream_iterator < std::string > ( std::cerr, "\n" ) );
        std::exit ( EXIT_FAILURE );
    }
    set_state ( new_state );
}

std::shared_ptr < engine::gui::Window > State_manager::wrap_window ( std::shared_ptr < sf::RenderWindow > render_window )
{
    std::shared_ptr < engine::events::Receiver < std::shared_ptr < engine::gui::Draw_event > > > draw_receiver =
        std::make_shared < engine::converters::Draw_event_to_dict > ( entry_point.get () );

    std::shared_ptr < engine::events::Receiver < std::shared_ptr < sf::Event > > > sfml_receiver =
        std::make_shared < engine::converters::Sfml_event_to_dict > ( entry_point.get () );

    return std::make_shared < engine::gui::Window > ( render_window, draw_receiver, sfml_receiver );
}
