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

#ifndef PACKMAN_GAMELOGIC_LEVEL_GUARD
#define PACKMAN_GAMELOGIC_LEVEL_GUARD

#include <string>
#include <memory>

#include "engine/gamelogic/Pruning_world.hpp"

#include "utils/Globals.hpp"
#include "gamelogic/Entity.h"
#include "states/Ingame_state.h"

namespace gamelogic
{
    class Level
    {
        public:
            Level ( std::string path, utils::Globals );

            void load_level ();

            std::shared_ptr < engine::gamelogic::Pruning_world < Entity > > get_world () const;
            std::shared_ptr < states::Ingame_state > get_ingame_state () const;

        private:
            std::string path;
            utils::Globals globals;
            std::shared_ptr < engine::gamelogic::Pruning_world < Entity > > world;
            std::shared_ptr < states::Ingame_state > ingame_state;
    };
} /* namespace gamelogic */

#endif // PACKMAN_GAMELOGIC_LEVEL_GUARD
