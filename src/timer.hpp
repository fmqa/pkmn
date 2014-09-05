#ifndef PKMN_TIMER_HPP
#define PKMN_TIMER_HPP

#include <functional>

namespace pkmn {
    struct timer {
        using fn = std::function<void(timer &)>;
        timer();
        timer(bool, int, const fn &);
        timer(bool, int, fn &&);
        void update(int);
        bool enabled;
        int interval;
        fn action;
        int elapsed;
        int delta;
    };
}

#endif /* #ifndef PKMN_TIMER_HPP */
