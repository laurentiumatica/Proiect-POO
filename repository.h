#pragma once
#include <functional>
#include <string>
#include <vector>

template<typename T>
class Repository {
private:
    std::vector<T>items;
    std::function<std::string(const T&)> id_extractor;

public:
    explicit Repository(std::function<std::string(const T&)> extractor) : id_extractor(extractor) {};

    void add(const T& item) {
        items.push_back(item);
    }

    T* find_by_id(const std::string &id) {
        for (auto& item : items)
            if (id_extractor(item) == id)
                return &item;
        return nullptr;
    }

    const T* find_by_id(const std::string &id) const {
        for (const auto& item : items)
            if (id_extractor(item) == id)
                return &item;
        return nullptr;
    }

    void remove_by_id(const std::string &id) {
        for (auto it = items.begin(); it != items.end(); ++it)
            if (id_extractor(*it) == id) {
                items.erase(it);
                return;
            }
    }

    void clear() {
        items.clear();
    }

    const std::vector<T>& get_items() const {
        return items;
    }

    int count() const {
        return static_cast<int>(items.size());
    }
};