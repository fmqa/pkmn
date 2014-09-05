#include "sensor.hpp"
#include "tagged.hpp"

pkmn::sensor::sensor() = default;
pkmn::sensor::sensor(const sf::FloatRect &area) : bounds(area), action() {}
pkmn::sensor::sensor(const sf::FloatRect &area, const fn &trigger) : bounds(area), action(trigger) {}
pkmn::sensor::sensor(const sf::FloatRect &area, fn &&trigger) : bounds(area), action(std::move(trigger)) {}

