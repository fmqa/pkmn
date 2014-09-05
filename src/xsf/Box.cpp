#include "Box.hpp" 
#include <SFML/Graphics/RenderTarget.hpp>

xsf::Box::Box() : sf::Drawable(), sf::Transformable(), value() {}
xsf::Box::Box(const sf::Drawable &boxed) : sf::Drawable(), sf::Transformable(), value(&boxed) {}
void xsf::Box::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (value) {
        states.transform *= getTransform();
        target.draw(*value, states);
    }
}
