#ifndef PKMN_SEQUENCE_HPP
#define PKMN_SEQUENCE_HPP

#include <cstddef>

namespace sf {
    class Drawable;
}

namespace pkmn {
    struct sequence {
        virtual const sf::Drawable& at(std::size_t) const = 0;
        virtual std::size_t count() const = 0;
        virtual ~sequence() = 0;
    };
    
    template <typename T>
    struct seq : sequence {
        seq();
        seq(const T *, const T *);
        const sf::Drawable& at(std::size_t) const override;
        std::size_t count() const override;
    private:
        const T *begin, *end;
    };
    
    template <typename T>
    seq<T>::seq() = default;
    
    template <typename T>
    seq<T>::seq(const T *seqbegin, const T *seqend) : begin(seqbegin), end(seqend) {}
    
    template <typename T>
    const sf::Drawable& seq<T>::at(std::size_t index) const {
        return begin[index];
    }
    
    template <typename T>
    std::size_t seq<T>::count() const {
        return end - begin;
    }
    
    template <typename T>
    seq<T> makeseq(const T *begin, const T *end) {
        return seq<T>(begin, end);
    }
}

#endif /* #ifndef PKMN_SEQUENCE_HPP */
