#ifndef CE_COMPONENTS_HPP
#define CE_COMPONENTS_HPP

namespace CE_Components {
    // Leave empty because this is just a header file and the actual namespace code is in different files
}

// Here is where we include all of the code that we want to be a part of the namespace
#include "icomponent.hpp"
#include "hitbox.hpp"
#include "ce_sprite.hpp"
#include "player_controller.hpp"
//#include "animated_sprite.hpp"

//TODO: Implement the animated_sprite component and let the player_controller component use either the sprite or animated_sprite component


#endif