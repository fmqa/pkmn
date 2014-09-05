#ifndef PKMN_WORLD_HPP
#define PKMN_WORLD_HPP

#include <unordered_set>
#include "xsf/Grid.hpp"
#include "composite.hpp"

namespace pkmn {
    using grid = xsf::Grid<sf::Vector2i,std::unordered_set<composite*>>;
    using world = xsf::Clustering<grid>;
    
    bool insert(world &, composite &);
    bool reseat(world &, composite &);
}

#endif /* #ifndef PKMN_WORLD_HPP */
