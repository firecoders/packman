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

#include "gamelogic/Level.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

#include "engine/gui/Resource_manager.h"

#include "content/Packman.h"
#include "content/Wall.h"

using namespace gamelogic;

Level::Level ( std::string path, utils::Globals globals ) :
    path ( path ),
    globals ( globals )
{}

void Level::load_level ()
{
    std::ifstream file ( path );
    if ( !file.is_open () )
    {
        throw std::runtime_error { "[FAILED] to open level: " + path };
    }

    std::cout << "Loading level: " << path << std::endl;

    world = std::make_shared < engine::gamelogic::Pruning_world < Entity > > ( 10 );
    ingame_state = std::make_shared < states::Ingame_state > ( globals, world );

    std::cout << "[STUBBED] throw runtime_error on invalid tile descriptors" << std::endl;

    std::string line;
    for ( int y = 1; std::getline ( file, line ); ++y )
    {
        for ( int x = 0; x < line.size (); ++x )
        {
            char tile_descriptor = line.at ( x );
            switch ( tile_descriptor )
            {
                case content::Packman::get_level_char ():
                    world->add_entity
                    (
                        std::make_shared < content::Packman >
                        (
                            std::weak_ptr < engine::gamelogic::Pruning_world < Entity > > { world },
                            globals.state_manager->get_entry_point (),
                            std::weak_ptr < engine::types::Index_node < utils::Event_node > > { ingame_state->get_index () },
                            std::weak_ptr < engine::gui::Resource_manager > { globals.resource_manager },
                            engine::geometry::Vector < int > { x, y }
                        )
                    );
                    break;

                case content::Wall::get_level_char ():
                    world->add_entity
                    (
                        std::make_shared < content::Wall >
                        (
                            std::weak_ptr < engine::types::Index_node < utils::Event_node > > { ingame_state->get_index () },
                            std::weak_ptr < engine::gui::Resource_manager > { globals.resource_manager },
                            engine::geometry::Vector < int > { x, y }
                        )
                    );
                    break;

                case ' ': // air
                    break;

                default:
                    //TODO STUBBED: throw runtime_error on invalid tile descriptors
                    //throw std::runtime_error { std::string ( "Tile descriptor `" ) + tile_descriptor + "` is not valid." };
                    break;
            }
        }
    }
}

std::shared_ptr < engine::gamelogic::Pruning_world < Entity > > Level::get_world () const
{
    return world;
}

std::shared_ptr < states::Ingame_state > Level::get_ingame_state () const
{
    return ingame_state;
}
