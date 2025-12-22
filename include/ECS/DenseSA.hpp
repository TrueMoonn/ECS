/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** DenseSA.hpp
*/

#pragma once

    #include <utility>
    #include <iostream>
    #include <vector>

    #include "ECS/Entity.hpp"
    #include "ECS/SparseArray.hpp"

namespace ECS {

#define MAX_PAGE_SIZE 1000
#define PAGE(e) e / MAX_PAGE_SIZE
#define PAGE_INDEX(e) e % MAX_PAGE_SIZE

template <typename Component>
class DenseSparseArray {
 public:
    using value_type = Component;

    DenseSparseArray() = default;

    template <typename ...Args>
    void createComponent(Entity e, Args&&... args) {
        if (PAGE(e) >= _spar.size()) {
            _spar.resize(PAGE(e) + 1);
        }
        _spar[PAGE(e)].insert_at(PAGE_INDEX(e), _dense.size());
        _dense.emplace_back(std::forward<Args>(args)...);
    }

    void addComponent(Entity e, Component&& cmpt) {
        if (PAGE(e) >= _spar.size()) {
            _spar.resize(PAGE(e) + 1);
        }
        _spar[PAGE(e)].insert_at(PAGE_INDEX(e), _dense.size());
        _dense.push_back(std::forward<Component>(cmpt));
    }

    void addComponent(Entity e, const Component& cmpt) {
        if (PAGE(e) >= _spar.size()) {
            _spar.resize(PAGE(e) + 1);
        }
        _spar[PAGE(e)].insert_at(e, _dense.size());
        _dense.push_back(cmpt);
    }

    void removeComponent(Entity e) {
        if (PAGE(e) < _spar.size() && PAGE_INDEX(e) < _spar[PAGE(e)].size() &&
            _spar[PAGE(e)][PAGE_INDEX(e)].has_value()) {
            std::size_t del_index = _spar[PAGE(e)][PAGE_INDEX(e)].value();
            Entity back_e = getBackEntity();
            std::swap(_dense[del_index], _dense.back());
            _spar[PAGE(e)][PAGE_INDEX(e)] = std::nullopt;
            _spar[PAGE(back_e)][PAGE_INDEX(back_e)] = del_index;
            _dense.pop_back();
        }
    }

    std::vector<SparseArray<std::size_t>>& getSpar() {
        return _spar;
    }

    const std::vector<SparseArray<std::size_t>>& getSpar() const {
        return _spar;
    }

    Component& getComponent(std::size_t index) {
        return _dense[index];
    }

    const Component& getComponent(std::size_t index) const {
        return _dense[index];
    }

 private:
    Entity getBackEntity() {
        for (std::size_t page = 0; page < _spar.size(); ++page) {
            for (std::size_t idx = 0; idx < _spar[page].size(); ++idx) {
                if (_spar[page][idx].has_value() &&
                    _spar[page][idx].value() == _dense.size() - 1) {
                    return page * MAX_PAGE_SIZE + idx;
                }
            }
        }
    }

    std::vector<Component> _dense;
    std::vector<SparseArray<std::size_t>> _spar;
};

}  // namespace ECS
