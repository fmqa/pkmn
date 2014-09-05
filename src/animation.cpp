#include "animation.hpp"
#include "timer.hpp"
#include "sequence.hpp"
#include "geometry.hpp"

pkmn::animation::animation() = default;
pkmn::animation::animation(geometry &container, const sequence &seq, std::size_t i) : frames(&seq), index(i), m_geometry(&container) {}
void pkmn::animation::operator()(timer &t) {
    index = (index + 1) % frames->count();
    m_geometry->value = &frames->at(index);
}

void pkmn::animation::reset(bool resetindex) {
    if (resetindex) {
        index = 0;
    }
    m_geometry->value = &frames->at(index);
}
