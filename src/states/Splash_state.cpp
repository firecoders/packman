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

#include "states/Splash_state.h"

#include "engine/events/Lambda_receiver.hpp"
#include "utils/typedefs.hpp"

using namespace states;

Splash_state::Splash_state ( utils::Globals globals )
{
    std::shared_ptr < sf::Sprite > splash_sprite = std::make_shared < sf::Sprite > ();
    splash_sprite->setTexture ( globals.resource_manager->get_texture ( "splash.welcome" ) );

    index->at ( "draw" )->get_wrapped ()->subscribe
    (
        std::make_shared < engine::events::Lambda_receiver < utils::Event > >
        (
            [ splash_sprite ] ( utils::Event event )
            {
                event->at ( "rendertarget" ).get < sf::RenderTarget* > ()->draw ( *splash_sprite );
            }
        )
    );

    index->get_descendant ( { "sfml", "KeyPressed" } )->get_wrapped ()->subscribe
    (
        std::make_shared < engine::events::Lambda_receiver < utils::Event > >
        (
            [ globals ] ( utils::Event event )
            {
                if ( event->at ( "key.code" ).get < std::string > () == "Space" )
                    globals.state_manager->switch_state ( { "splash", "post" } );
            }
        )
    );
}
