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

#ifndef UTILS_TEE_GUARD
#define UTILS_TEE_GUARD

#include <functional>

#include "engine/events/interfaces/Receiver.h"
#include "engine/events/Receiver_forwarder.hpp"

namespace utils
{
    template < typename Event_type >
        class Tee : public engine::events::Receiver < Event_type >
        {
            public:
                Tee
                (
                    std::function < bool ( Event_type ) > predicate,
                    std::shared_ptr < engine::events::Receiver < Event_type > > if_true,
                    std::shared_ptr < engine::events::Receiver < Event_type > > if_false
                );

                ~Tee () noexcept {};

                virtual void receive ( Event_type event );

                void set_predicate ( std::function < bool ( Event_type ) > predicate );
                void redirect_true  ( std::shared_ptr < engine::events::Receiver < Event_type > > receiver );
                void redirect_false ( std::shared_ptr < engine::events::Receiver < Event_type > > receiver );

            private:
                std::function < bool ( Event_type ) > predicate;
                engine::events::Receiver_forwarder < Event_type > if_true;
                engine::events::Receiver_forwarder < Event_type > if_false;
        };

    template < typename Event_type >
        Tee < Event_type >::Tee
        (
            std::function < bool ( Event_type ) > predicate,
            std::shared_ptr < engine::events::Receiver < Event_type > > if_true,
            std::shared_ptr < engine::events::Receiver < Event_type > > if_false
        ) :
            predicate ( predicate ),
            if_true ( if_true ),
            if_false ( if_false )
        {}

    template < typename Event_type >
        void Tee < Event_type >::receive ( Event_type event )
        {
            if ( predicate ( event ) )
                if_true.receive  ( event );
            else
                if_false.receive ( event );
        }

    template < typename Event_type >
        void Tee < Event_type >::set_predicate ( std::function < bool ( Event_type ) > predicate )
        {
            this->predicate = predicate;
        }

    template < typename Event_type >
        void Tee < Event_type >::redirect_true  ( std::shared_ptr < engine::events::Receiver < Event_type > > receiver )
        {
            if_true.redirect ( receiver );
        }

    template < typename Event_type >
        void Tee < Event_type >::redirect_false ( std::shared_ptr < engine::events::Receiver < Event_type > > receiver )
        {
            if_false.redirect ( receiver );
        }
} /* namespace utils */

#endif // UTILS_TEE_GUARD
