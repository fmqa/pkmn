#ifndef XSF_BOX_HPP
#define XSF_BOX_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace sf {
    class RenderTarget;
}

namespace xsf {
    struct Box : sf::Drawable, sf::Transformable {
        Box();
        explicit Box(const sf::Drawable &);
        const sf::Drawable *value;
    private:
        void draw(sf::RenderTarget &, sf::RenderStates) const override;
    };
}

#endif /* #ifndef XSF_BOX_HPP */
