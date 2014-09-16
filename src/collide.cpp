#include "collide.hpp"
#include "tagged.hpp"

void pkmn::collide(const composite &left, const composite &right) {
    auto big = std::make_pair(&left, equal_range<sensor>(left));
    auto small = std::make_pair(&right, equal_range<sensor>(right));

    if (big.second.first == big.second.second && small.second.first != small.second.second) {
        std::swap(big, small);
    }
    
    for (; big.second.first != big.second.second; ++big.second.first) {
        sf::FloatRect bigrect;
        
        if (auto geom = get<geometry>(*big.first)) {
            bigrect.left += geom->getPosition().x;
            bigrect.top += geom->getPosition().y;
        }
        
        if (auto move = get<movement>(*big.first)) {
            bigrect.left += move->vector.x;
            bigrect.top += move->vector.y;
        }
        
        bigrect.left += unwrap<sensor>(big.second.first).bounds.left;
        bigrect.top += unwrap<sensor>(big.second.first).bounds.top;
        bigrect.width += unwrap<sensor>(big.second.first).bounds.width;
        bigrect.height += unwrap<sensor>(big.second.first).bounds.height;
        
        bigrect.left = std::round(bigrect.left);
        bigrect.top = std::round(bigrect.top);
        bigrect.width = std::round(bigrect.width);
        bigrect.height = std::round(bigrect.height);
        
        sf::FloatRect smallrect;
        
        if (auto geom = get<geometry>(*small.first)) {
            smallrect.left += geom->getPosition().x;
            smallrect.top += geom->getPosition().y;
        }
        
        if (auto move = get<movement>(*small.first)) {
            smallrect.left += move->vector.x;
            smallrect.top += move->vector.y;
        }
        
        if (small.second.first == small.second.second) {
            smallrect.width = 1.0f;
            smallrect.height = 1.0f;
            
            smallrect.left = std::round(smallrect.left);
            smallrect.top = std::round(smallrect.top);
            
            if (bigrect.intersects(smallrect) && unwrap<sensor>(big.second.first).action) {
                unwrap<sensor>(big.second.first).action(*small.first);
            }
        } else {
            for (auto cursor = small.second.first; cursor != small.second.second; ++cursor) {
                sf::FloatRect sensorrect(smallrect);
                
                sensorrect.left += unwrap<sensor>(cursor).bounds.left;
                sensorrect.top += unwrap<sensor>(cursor).bounds.top;
                sensorrect.width += unwrap<sensor>(cursor).bounds.width;
                sensorrect.height += unwrap<sensor>(cursor).bounds.height;
                
                sensorrect.left = std::round(sensorrect.left);
                sensorrect.height = std::round(sensorrect.height);
                sensorrect.width = std::round(sensorrect.width);
                sensorrect.height = std::round(sensorrect.height);
                
                if (bigrect.intersects(sensorrect)) {
                    if (unwrap<sensor>(big.second.first).action) {
                        unwrap<sensor>(big.second.first).action(*small.first);
                    }
                    if (unwrap<sensor>(cursor).action) {
                        unwrap<sensor>(cursor).action(*big.first);
                    }
                }
            }
        }
    }
}

