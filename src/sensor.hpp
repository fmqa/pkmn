#ifndef PKMN_SENSOR_HPP
#define PKMN_SENSOR_HPP

#include <functional>
#include <SFML/Graphics/Rect.hpp>
#include "composite.hpp"

namespace pkmn {
    struct sensor {
        using fn = std::function<void(const composite &)>;
        sensor();
        explicit sensor(const sf::FloatRect &);
        sensor(const sf::FloatRect &, const fn &);
        sensor(const sf::FloatRect &, fn &&);
        sf::FloatRect bounds;
        fn action;
    };
}

#endif /* #ifndef PKMN_SENSOR_HPP */
