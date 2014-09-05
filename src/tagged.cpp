#include "tagged.hpp"

pkmn::tagged<pkmn::timer>::tagged() = default;
pkmn::tagged<pkmn::timer>::tagged(const timer &t) : unknown(), timer(t) {}
pkmn::tagged<pkmn::timer>::tagged(timer &&t) : unknown(), timer(std::move(t)) {}

pkmn::tagged<pkmn::movement>::tagged() = default;
pkmn::tagged<pkmn::movement>::tagged(const movement &m) : unknown(), movement(m) {}
pkmn::tagged<pkmn::movement>::tagged(movement &&m) : unknown(), movement(std::move(m)) {}

pkmn::tagged<pkmn::geometry>::tagged() = default;
pkmn::tagged<pkmn::geometry>::tagged(const geometry &s) : unknown(), geometry(s) {}
pkmn::tagged<pkmn::geometry>::tagged(geometry &&s) : unknown(), geometry(std::move(s)) {}

pkmn::tagged<pkmn::animation>::tagged() = default;
pkmn::tagged<pkmn::animation>::tagged(const animation &a) : unknown(), animation(a) {}
pkmn::tagged<pkmn::animation>::tagged(animation &&a) : unknown(), animation(std::move(a)) {}

pkmn::tagged<pkmn::sensor>::tagged() = default;
pkmn::tagged<pkmn::sensor>::tagged(const sensor &s) : unknown(), sensor(s) {}
pkmn::tagged<pkmn::sensor>::tagged(sensor &&s) : unknown(), sensor(std::move(s)) {}
