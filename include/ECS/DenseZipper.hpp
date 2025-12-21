/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** DenseZipper.hpp
** Copyright [2025] <DeepestDungeonGroup>
*/

#pragma once

    #include <iostream>
    #include <tuple>
    #include <utility>
    #include <cstddef>
    #include <iterator>
    #include <algorithm>

    #include "DenseSA.hpp"

namespace ECS {

template <class... Containers>
class DenseZipper {
 public:
    template <class... Cs>
    class DenseZipIt {
     public:
        template <class Container>
        using component_t = typename Container::value_type;

        using value_type = std::tuple<component_t<Cs>&...>;
        using reference = value_type;
        using pointer = void;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        DenseZipIt(std::tuple<Cs*...> containers, size_t max, size_t idx = 0)
            : _currents(containers), _max(max), _idx(idx) {
            if (_idx < _max && !all_set(_seq)) {
                incr_all();
            }
        }

        DenseZipIt& operator++() {
            incr_all();
            return *this;
        }
        DenseZipIt operator++(int) {
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

        friend bool operator==(const DenseZipIt& lhs,
            const DenseZipIt& rhs) {
            return lhs._idx == rhs._idx;
        }
        friend bool operator!=(const DenseZipIt& lhs,
            const DenseZipIt& rhs) {
            return !(lhs == rhs);
        }

        size_t get_index() const {
            return _idx;
        }

     private:
        void incr_all() {
            do {
                ++_idx;
            } while (_idx < _max && !all_set(_seq));
        }

        template <size_t... Is>
        bool all_set(std::index_sequence<Is...>) {
            return (has_component<Is>() && ...);
        }

        template <size_t... Is>
        value_type to_value(std::index_sequence<Is...>) {
            return std::tie(get_component<Is>()...);
        }

        template <size_t I>
        bool has_component() {
            auto& container = *std::get<I>(_currents);
            auto& spar = container.getSparComponents();
            size_t page = PAGE(_idx);
            size_t page_idx = PAGE_INDEX(_idx);

            return page < spar.size() &&
                    page_idx < spar[page].size() &&
                    spar[page][page_idx].has_value();
        }

        template <size_t I>
        auto& get_component() {
            auto& container = *std::get<I>(_currents);
            auto& spar = container.getSparComponents();
            size_t page = PAGE(_idx);
            size_t page_idx = PAGE_INDEX(_idx);
            size_t dense_idx = spar[page][page_idx].value();
            return container.getComponent(dense_idx);
        }

        std::tuple<Cs*...> _currents;
        size_t _max;
        size_t _idx;
        static constexpr std::index_sequence_for<Cs...> _seq{};
    };

    using iterator = DenseZipIt<Containers...>;

    explicit DenseZipper(Containers&... cs) :
        _currents(std::make_tuple(&cs...)),
        _size(_compute_size(cs...)) {}

    iterator begin() {
        return iterator(_currents, _size, 0);
    }
    iterator end() {
        return iterator(_currents, _size, _size);
    }

 private:
    static size_t _compute_size(Containers&... containers) {
        return std::max({
            (containers.getSparComponents().size() * MAX_PAGE_SIZE)...
        });
    }

    std::tuple<Containers*...> _currents;
    size_t _size;
};

}  // namespace ECS
