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

#ifndef PACKMAN_STATES_INGAME_STATE_GUARD
#define PACKMAN_STATES_INGAME_STATE_GUARD

#include <memory>

#include "engine/gamelogic/Pruning_world.hpp"

#include "states/Base_state.h"
#include "utils/Globals.hpp"
#include "utils/typedefs.hpp"
#include "gamelogic/Entity.h"

namespace states
{
    class Ingame_state : public Base_state
    {
        public:
            Ingame_state
            (
                utils::Globals globals,
                std::shared_ptr < engine::gamelogic::Pruning_world < gamelogic::Entity > > world
            );

        private:
            utils::Globals globals;
            std::shared_ptr < engine::gamelogic::Pruning_world < gamelogic::Entity > > world;

            void handle_custom_event ( utils::Event event );
            void handle_move_proposal_event ( utils::Event event );
    };
} /* namespace states */

#endif // PACKMAN_STATES_INGAME_STATE_GUARD
