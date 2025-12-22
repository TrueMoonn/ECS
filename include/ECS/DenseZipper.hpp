/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** DenseZipper.hpp
** Copyright [2025] <DeepestDungeonGroup>
*/

#pragma once

    #include <tuple>
    #include <utility>
    #include <cstddef>
    #include <iterator>

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

        DenseZipIt(std::tuple<Cs*...> containers, size_t page, size_t idx = 0) :
            _currents(containers), _page(page), _idx(idx), _is_end(false) {
            if (!_is_end && !all_set(_seq)) {
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
                return lhs._is_end == rhs._is_end &&
                    (lhs._is_end ||
                    (lhs._page == rhs._page && lhs._idx == rhs._idx));
        }
        friend bool operator!=(const DenseZipIt& lhs,
            const DenseZipIt& rhs) {
            return !(lhs == rhs);
        }

        size_t get_page() const {
            return _page;
        }

        size_t get_index() const {
            return _idx;
        }

     private:
        void incr_all() {
            auto& fcontainer = *std::get<0>(_currents);
            auto& fspar = fcontainer.getSpar();

            ++_idx;
            while (_page < fspar.size()) {
                while (_idx < fspar[_page].size()) {
                    if (fspar[_page][_idx].has_value() && all_set(_seq)) {
                        return;
                    }
                    ++_idx;
                }
                ++_page;
                _idx = 0;
            }
            _is_end = true;
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
            auto& spar = container.getSpar();

            return _page < spar.size() &&
                    _idx < spar[_page].size() &&
                    spar[_page][_idx].has_value();
        }

        template <size_t I>
        auto& get_component() {
            auto& container = *std::get<I>(_currents);
            auto& spar = container.getSpar();
            size_t dense_idx = spar[_page][_idx].value();
            return container.getComponent(dense_idx);
        }

        std::tuple<Cs*...> _currents;
        size_t _page;
        size_t _idx;
        bool _is_end;
        static constexpr std::index_sequence_for<Cs...> _seq{};
    };

    using iterator = DenseZipIt<Containers...>;

    explicit DenseZipper(Containers&... cs) :
        _currents(std::make_tuple(&cs...)) {}

    iterator begin() {
        return iterator(_currents, 0, 0);
    }
    iterator end() {
        auto& first_container = *std::get<0>(_currents);
        size_t max_page = first_container.getSpar().size();
        return iterator(_currents, max_page, 0);
    }

 private:
    std::tuple<Containers*...> _currents;
    size_t _size;
};

}  // namespace ECS
