#ifndef PKMN_TAGGED_HPP
#define PKMN_TAGGED_HPP

#include "geometry.hpp"
#include "unknown.hpp"
#include "timer.hpp"
#include "movement.hpp"
#include "animation.hpp"
#include "sensor.hpp"

namespace pkmn {
    template <typename> struct tagged;
    
    template <>
    struct tagged<timer> : unknown, timer {
        tagged();
        tagged(const timer &);
        tagged(timer &&);
    };
    
    template <>
    struct tagged<movement> : unknown, movement {
        tagged();
        tagged(const movement &);
        tagged(movement &&);
    };
    
    template <>
    struct tagged<geometry> : unknown, geometry {
        tagged();
        tagged(const geometry &);
        tagged(geometry &&);
    };
    
    template <>
    struct tagged<animation> : unknown, animation {
        tagged();
        tagged(const animation &);
        tagged(animation &&);
    };
    
    template <>
    struct tagged<sensor> : unknown, sensor {
        tagged();
        tagged(const sensor &);
        tagged(sensor &&);
    };
}

#endif /* #ifndef PKMN_TAGGED_HPP */
