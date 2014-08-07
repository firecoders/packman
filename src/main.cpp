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

#include <memory>

#include <SFML/Graphics.hpp>

#include "engine/gui/Resource_manager.h"
#include "engine/gui/Window.h"

#include "engine/converters/Dict.hpp"
#include "engine/events/Lambda_receiver.hpp"

#include "states/Splash_state.h"
#include "states/State_manager.h"

#include "utils/typedefs.hpp"
#include "utils/Globals.hpp"

int main ()
{
    auto resource_manager = std::make_shared < engine::gui::Resource_manager > ( "res/", ".png" );
    auto state_manager = std::make_shared < states::State_manager > ();

    utils::Globals globals { resource_manager, state_manager };

    auto splash = std::make_shared < states::Splash_state > ( globals );

    state_manager->add_state ( { "splash" }, splash->get_receiver () );
    state_manager->switch_state ( { "splash" } );

    std::shared_ptr < engine::gui::Window > window = state_manager->wrap_window
    (
        std::make_shared < sf::RenderWindow >
        (
            sf::VideoMode { 1280,1024 }, "2D-engine packman"
        )
    );

    window->loop ( 30 );
}
