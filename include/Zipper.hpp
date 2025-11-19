/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** Zipper.hpp
** Copyright [2025] <DeepestDungeonGroup>
*/

#ifndef INCLUDE_ZIPPER_HPP_
    #define INCLUDE_ZIPPER_HPP_

    #include <tuple>
    #include <utility>
    #include <cstddef>
    #include <iterator>
    #include <algorithm>

namespace ECS {

template <class... Containers>
class Zipper {
 public:
    template <class... Cs>
    class ZipperIterator {
     public:
        template <class Container>
        using iterator_t = typename Container::iterator;
        template <class Container>
        using it_reference_t = typename iterator_t<Container>::reference;

        using value_type = std::tuple<it_reference_t<Cs>...>;
        using reference = value_type;
        using pointer = void;
        using size_type = size_t;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        using iterator_tuple = std::tuple<iterator_t<Cs>...>;

        ZipperIterator(iterator_tuple current, size_t max, size_t idx = 0)
            : _current(current), _max(max), _idx(idx) {
            if (!all_set(_seq) && _idx < _max) {
                incr_all(_seq);
            }
        }

        ZipperIterator(ZipperIterator const &z) = default;

        ZipperIterator& operator++() {
            incr_all(_seq);
            return *this;
        }
        ZipperIterator operator++(int) {
            auto prev = *this;
            ++(*this);
            return prev;
        }

        value_type operator*() {
            return to_value(_seq);
        }
        value_type operator->() {
            return to_value(_seq);
        }

        friend bool operator==(ZipperIterator const &lhs,
            ZipperIterator const& rhs) {
            return lhs._idx == rhs._idx;
        }

        friend bool operator!=(ZipperIterator const &lhs,
            ZipperIterator const& rhs) {
            return !(lhs._idx == rhs._idx);
        }

        size_t get_index() const {
            return _idx;
        }

     private:
        template <size_t... Is>
        void incr_all(std::index_sequence<Is...>) {
            do {
                (++std::get<Is>(_current), ...);
                ++_idx;
            } while (_idx < _max && !all_set(_seq));
        }

        template <size_t... Is>
        bool all_set(std::index_sequence<Is...>) {
            return (std::get<Is>(_current)->has_value() && ...);
        }

        template <size_t... Is>
        value_type to_value(std::index_sequence<Is...>) {
            return std::tie(*std::get<Is>(_current)...);
        }

        iterator_tuple _current;
        size_t _max;
        size_t _idx;
        static constexpr std::index_sequence_for<Cs...> _seq{};
    };

    using iterator = ZipperIterator<Containers...>;
    using iterator_tuple = typename iterator::iterator_tuple;

    explicit Zipper(Containers&... cs) :
        _size(_compute_size(cs...)),
        _begin(std::make_tuple(cs.begin()...)),
        _end(std::make_tuple(cs.end()...)) {}

    iterator begin() {
        return iterator(_begin, _size, 0);
    }
    iterator end() {
        return iterator(_begin, _size, _size);
    }

 private:
    static size_t _compute_size(Containers&... containers) {
        return std::min({containers.size()...});
    }

    iterator_tuple _begin;
    iterator_tuple _end;
    size_t _size;
};

template <class... Containers>
class IndexedZipper {
 public:
    class Iterator {
     public:
        using inner_iterator = typename Zipper<Containers...>::iterator;
        using value_type = std::tuple<size_t,
            typename inner_iterator::value_type>;
        using reference = value_type;

        explicit Iterator(inner_iterator it) : _it(it) {}

        Iterator& operator++() {
            ++_it;
            return *this;
        }
        Iterator operator++(int) {
            auto prev = *this;
            ++(*this);
            return prev;
        }
        auto operator*() {
            return std::tuple_cat(std::make_tuple(_it.get_index()), *_it);;
        }
        bool operator==(Iterator const& other) const {
            return _it == other._it;
        }
        bool operator!=(Iterator const& other) const {
            return !(*this == other);
        }

     private:
        inner_iterator _it;
    };

    explicit IndexedZipper(Containers&... cs) : _zipper(cs...) {}

    Iterator begin() {
        return Iterator(_zipper.begin());
    }

    Iterator end() {
        return Iterator(_zipper.end());
    }

 private:
    Zipper<Containers...> _zipper;
};

}  // namespace ECS

#endif  // INCLUDE_ZIPPER_HPP_
