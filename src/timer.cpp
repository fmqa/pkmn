#include "timer.hpp"

pkmn::timer::timer() = default;
pkmn::timer::timer(bool active, int interv, const fn &timeout) : enabled(active), interval(interv), action(timeout), elapsed(), delta() {}
pkmn::timer::timer(bool active, int interv, fn &&timeout) : enabled(active), interval(interv), action(std::move(timeout)), elapsed(), delta() {}
void pkmn::timer::update(int dt) {
    if (enabled) {
        delta = dt;
        elapsed += dt;
        if (elapsed >= interval) {
            if (action) {
                action(*this);
            }
            elapsed = 0;
        }
    }
}
