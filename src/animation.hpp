#ifndef PKMN_ANIMATION_HPP
#define PKMN_ANIMATION_HPP

#include <cstddef>
#include "fwd/geometry.hpp"
#include "fwd/timer.hpp"
#include "fwd/sequence.hpp"

namespace pkmn {
    struct animation {
        animation();
        animation(geometry &, const sequence &, std::size_t = 0);
        const sequence *frames;
        std::size_t index;
        void operator()(timer &);
        void reset(bool = false);
    private:
        geometry *m_geometry;
    };
    
    void reset(animation &);
}

#endif /* #ifndef PKMN_ANIMATION_HPP */
