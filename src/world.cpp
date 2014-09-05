#include "world.hpp" 
#include "geometry.hpp"
#include "tagged.hpp"

bool pkmn::insert(world &w, composite &c) {
    if (const geometry *geom = get<geometry>(c)) {
        return w[geom->getPosition()].insert(&c).second;
    }
    return false;
}

bool pkmn::reseat(world &w, composite &c) {
    if (const geometry *geom = get<geometry>(c)) {
        grid::iterator cursor = w.find(geom->getPosition());
        bool removed = (cursor != w.grid->end()) && cursor->second.erase(&c);
        
        if (!removed) {
            cursor = w.find(sf::Vector2i(geom->getPosition().x - w.cell.x,
                                         geom->getPosition().y));
            removed = (cursor != w.grid->end()) && cursor->second.erase(&c);
        }
        
        if (!removed) {
            cursor = w.find(sf::Vector2i(geom->getPosition().x + w.cell.x,
                                         geom->getPosition().y));
            removed = (cursor != w.grid->end()) && cursor->second.erase(&c);
        }
        
        if (!removed) {
            cursor = w.find(sf::Vector2i(geom->getPosition().x,
                                         geom->getPosition().y - w.cell.y));
            removed = (cursor != w.grid->end()) && cursor->second.erase(&c);
        }
        
        if (!removed) {
            cursor = w.find(sf::Vector2i(geom->getPosition().x,
                                         geom->getPosition().y + w.cell.y));
            removed = (cursor != w.grid->end()) && cursor->second.erase(&c);
        }
        
        if (removed) {
            return insert(w, c);
        }
    }
    return false;
}

