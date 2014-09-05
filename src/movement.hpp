#ifndef PKMN_MOVEMENT_HPP
#define PKMN_MOVEMENT_HPP

#include <functional>
#include <SFML/System/Vector2.hpp>
#include "fwd/timer.hpp"

namespace pkmn {
    struct movement {
        using fn = std::function<void(const sf::Vector2f &)>;
        movement();
        movement(const sf::Vector2f &, float, const fn &);
        movement(const sf::Vector2f &, float, fn &&);
        void operator()(timer &);
        sf::Vector2f vector;
        float velocity;
        fn action;
    };
}

#endif /* #ifndef PKMN_MOVEMENT_HPP */
