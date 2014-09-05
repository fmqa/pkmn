#include "movement.hpp"
#include "timer.hpp"

pkmn::movement::movement() = default;
pkmn::movement::movement(const sf::Vector2f &movementVector, float movementVelocity, const fn &movementAction) : vector(movementVector), velocity(movementVelocity), action(movementAction) {}
pkmn::movement::movement(const sf::Vector2f &movementVector, float movementVelocity, fn &&movementAction) : vector(movementVector), velocity(movementVelocity), action(std::move(movementAction)) {}
void pkmn::movement::operator()(timer &t) {
    if (action && (vector != sf::Vector2f(0.0f, 0.0f))) {
        float dx = (vector.x < 0 ? -1 : (vector.x > 0 ? 1 : 0)) * velocity * t.delta;
        float dy = (vector.y < 0 ? -1 : (vector.y > 0 ? 1 : 0)) * velocity * t.delta;
        
        if ((vector.x - dx > 0) == (vector.x > 0)) {
            vector.x -= dx;
        } else {
            dx = vector.x;
            vector.x = 0;
        }
        
        if ((vector.y - dy > 0) == (vector.y > 0)) {
            vector.y -= dy;
        } else {
            dy = vector.y;
            vector.y = 0;
        }
        
        action(sf::Vector2f(dx, dy));
    }
}
