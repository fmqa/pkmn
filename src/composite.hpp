#ifndef PKMN_COMPOSITE_HPP
#define PKMN_COMPOSITE_HPP

#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include "unknown.hpp"

namespace pkmn {
    using composite = std::unordered_multimap<std::type_index,std::unique_ptr<unknown>>;
    
    template <typename> struct tagged;
    
    template <typename T>
    composite::iterator insert(composite &e, std::unique_ptr<tagged<T>> component) {
        return e.emplace(typeid(tagged<T>), std::move(component));
    }
    
    template <typename T>
    composite::iterator insert(composite &e, const tagged<T> &component) {
        return insert(e, std::unique_ptr<tagged<T>>(new tagged<T>(component)));
    }
    
    template <typename T>
    composite::iterator insert(composite &e, tagged<T> &&component) {
        return insert(e, std::unique_ptr<tagged<T>>(new tagged<T>(std::move(component))));
    }
    
    template <typename T>
    composite::iterator insert(composite &e, T &&component) {
        return insert(e, std::unique_ptr<tagged<T>>(new tagged<T>(std::forward<T>(component))));
    }
    
    template <typename T>
    composite::iterator find(composite &e) {
        return e.find(typeid(tagged<T>));
    }
    
    template <typename T>
    composite::const_iterator find(const composite &e) {
        return e.find(typeid(tagged<T>));
    }
    
    template <typename T>
    T& unwrap(const composite::const_iterator &cursor) {
        return static_cast<tagged<T>&>(*cursor->second);
    }
    
    template <typename T>
    T *get(const composite &e) {
        auto cursor = find<T>(e);
        if (cursor == e.end()) {
            return nullptr;
        } else {
            return static_cast<tagged<T>*>(&*cursor->second);
        }
    }
    
    template <typename T>
    std::pair<composite::iterator,composite::iterator> equal_range(composite &e) {
        return e.equal_range(typeid(tagged<T>));
    }
    
    template <typename T>
    std::pair<composite::const_iterator,composite::const_iterator> equal_range(const composite &e) {
        return e.equal_range(typeid(tagged<T>));
    }
    
    template <typename T>
    composite::size_type count(const composite &e) {
        return e.count(typeid(tagged<T>));
    }
}

#endif /* #ifndef PKMN_COMPOSITE_HPP */
