#ifndef XSF_GRID_HPP
#define XSF_GRID_HPP

#include <SFML/System/Vector2.hpp>
#include <map>

namespace xsf {
    template <typename> struct less;
    
    template <typename T>
    struct less<sf::Vector2<T>> {
        bool operator()(const sf::Vector2<T> &lhs, const sf::Vector2<T> &rhs) const {
            return std::make_pair(lhs.y, lhs.x) < std::make_pair(rhs.y, rhs.x);
        }
    };
    
    template <typename T, typename U, template <typename> class A = std::allocator>
    using Grid = std::map<T,U,less<T>,A<std::pair<const T,U>>>;
    
    template <typename> struct Clustering;
    
    template <typename T, typename U, template <typename> class A>
    struct Clustering<Grid<T,U,A>> {
        using grid_type = Grid<T,U,A>;
        Grid<T,U,A> *grid;
        T cell;
        Clustering();
        Clustering(Grid<T,U,A> &, const T &);
        template <typename V> Clustering(Grid<T,U,A> &, const V &);
        template <typename V> U& operator[](const V &) const;
        template <typename V> typename Grid<T,U,A>::iterator find(const V &) const;
    };
    
    template <typename T, typename U, template <typename> class A>
    Clustering<Grid<T,U,A>>::Clustering() = default;
    
    template <typename T, typename U, template <typename> class A>
    Clustering<Grid<T,U,A>>::Clustering(Grid<T,U,A> &parent, const T &size) : grid(&parent), cell(size) {}
    
    template <typename T, typename U, template <typename> class A>
    template <typename V>
    Clustering<Grid<T,U,A>>::Clustering(Grid<T,U,A> &parent, const V &size) : grid(&parent), cell(size) {}
    
    template <typename T, typename U, template <typename> class A>
    template <typename V>
    U& Clustering<Grid<T,U,A>>::operator[](const V &k) const {
        return (*grid)[T(k.x / cell.x, k.y / cell.y)];
    }
    
    template <typename T, typename U, template <typename> class A>
    template <typename V>
    typename Grid<T,U,A>::iterator Clustering<Grid<T,U,A>>::find(const V &k) const {
        return grid->find(T(k.x / cell.x, k.y / cell.y));
    }
}

#endif /* #ifndef XSF_GRID_HPP */
