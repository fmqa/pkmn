#include "collide.hpp"
#include "tagged.hpp"

static void collide_ordered(
    const pkmn::composite &big, 
    std::pair<pkmn::composite::const_iterator,
              pkmn::composite::const_iterator> bigger, 
    const pkmn::composite &small, 
    std::pair<pkmn::composite::const_iterator,
              pkmn::composite::const_iterator> smaller) 
{
    for (; bigger.first != bigger.second; ++bigger.first) {
        sf::FloatRect rbig(
            (pkmn::get<pkmn::geometry>(big) 
                 ? pkmn::get<pkmn::geometry>(big)->getPosition()
                 : sf::Vector2f(0.0f, 0.0f)) +
            (pkmn::get<pkmn::movement>(big)
                 ? pkmn::get<pkmn::movement>(big)->vector
                 : sf::Vector2f(0.0f, 0.0f)),
            sf::Vector2f(pkmn::unwrap<pkmn::sensor>(bigger.first).bounds.width,
                         pkmn::unwrap<pkmn::sensor>(bigger.first).bounds.height));
        
        rbig.left = std::round(rbig.left);
        rbig.top = std::round(rbig.top);
        rbig.width = std::round(rbig.width);
        rbig.height = std::round(rbig.height);
        
        if (smaller.first == smaller.second) {
            sf::FloatRect rsmall(
                (pkmn::get<pkmn::geometry>(small)
                     ? pkmn::get<pkmn::geometry>(small)->getPosition()
                     : sf::Vector2f(0.0f, 0.0f)) +
                (pkmn::get<pkmn::movement>(small)
                     ? pkmn::get<pkmn::movement>(small)->vector
                     : sf::Vector2f(0.0f, 0.0f)),
                sf::Vector2f(1.0f, 1.0f));
            
            rsmall.left = std::round(rsmall.left);
            rsmall.top = std::round(rsmall.top);
            rsmall.width = std::round(rsmall.width);
            rsmall.height = std::round(rsmall.height);
            
            if (rbig.intersects(rsmall) && pkmn::unwrap<pkmn::sensor>(bigger.first).action) {
                pkmn::unwrap<pkmn::sensor>(bigger.first).action(small);
            }
        } else {
            for (auto cursor = smaller.first; cursor != smaller.second; ++cursor) {
                sf::FloatRect rsmall(
                    (pkmn::get<pkmn::geometry>(small) 
                        ? pkmn::get<pkmn::geometry>(small)->getPosition()
                        : sf::Vector2f(0.0f, 0.0f)) +
                    (pkmn::get<pkmn::movement>(small)
                        ? pkmn::get<pkmn::movement>(small)->vector
                        : sf::Vector2f(0.0f, 0.0f)),
                    sf::Vector2f(pkmn::unwrap<pkmn::sensor>(cursor).bounds.width,
                                 pkmn::unwrap<pkmn::sensor>(cursor).bounds.height));
                
                rsmall.left = std::round(rsmall.left);
                rsmall.top = std::round(rsmall.top);
                rsmall.width = std::round(rsmall.width);
                rsmall.height = std::round(rsmall.height);
                
                if (rbig.intersects(rsmall)) {
                    if (pkmn::unwrap<pkmn::sensor>(bigger.first).action) {
                        pkmn::unwrap<pkmn::sensor>(bigger.first).action(small);
                    }
                    if (pkmn::unwrap<pkmn::sensor>(cursor).action) {
                        pkmn::unwrap<pkmn::sensor>(cursor).action(big);
                    }
                }
            }
        }
    }
}

void pkmn::collide(const composite &left, const composite &right) {
    auto big = equal_range<pkmn::sensor>(left);
    auto small = equal_range<pkmn::sensor>(right);
    
    if (std::distance(big.first, big.second) < std::distance(small.first, small.second)) {
        collide_ordered(right, small, left, big);
    } else {
        collide_ordered(left, big, right, small);
    }
}

