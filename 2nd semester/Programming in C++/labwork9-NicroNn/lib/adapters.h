#ifndef LABWORK9_NICRONN_LIB_ADAPTERS_H_
#define LABWORK9_NICRONN_LIB_ADAPTERS_H_
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <functional>

template<typename Container>
concept ContainerConcept = requires(Container c) {
    { c.begin() } -> std::same_as<typename Container::iterator>;
    { c.end() } -> std::same_as<typename Container::iterator>;
};

template<ContainerConcept Container, typename UnaryFunction>
struct TransformAdapter {
    const Container& container;
    UnaryFunction function;

    TransformAdapter(const Container& container, UnaryFunction&& function) : container(container), function(std::forward<UnaryFunction>(function)) {}

    template<typename T>
    friend auto operator|(const T& container, const TransformAdapter<T, UnaryFunction>& adapter) {
        return adapter.transform(container);
    }

    template<typename T>
    auto transform(const T& container) const {
        using ValueType = typename T::value_type;
        std::vector<decltype(function(std::declval<ValueType>()))> result;
        for (const auto& element : container) {
            result.push_back(function(element));
        }
        return result;
    }
};

template<typename Container, typename UnaryFunction>
auto transform(const Container& container, UnaryFunction&& func) {
    return TransformAdapter<Container, UnaryFunction>(container, std::forward<UnaryFunction>(func));
}

template<typename UnaryPredicate, typename T>
concept UnaryPredicateConcept = std::predicate<UnaryPredicate, T>;

template<ContainerConcept Container, UnaryPredicateConcept<typename Container::value_type> UnaryPredicate>
struct FilterAdapter {
    const Container& container;
    UnaryPredicate predicate;

    FilterAdapter(const Container& container, UnaryPredicate&& predicate) : container(container), predicate(std::forward<UnaryPredicate>(predicate)) {}

    template<typename T>
    friend auto operator|(const T& container, const FilterAdapter<T, UnaryPredicate>& adapter) {
        return adapter.filter(container);
    }

    template<typename T>
    auto filter(const T& container) const {
        std::vector<typename T::value_type> result;
        for (const auto& element : container) {
            if (predicate(element)) {
                result.push_back(element);
            }
        }
        return result;
    }
};

template<typename Container, typename UnaryPredicate>
auto filter(const Container& container, UnaryPredicate&& pred) {
    return FilterAdapter<Container, UnaryPredicate>(container, std::forward<UnaryPredicate>(pred));
}


template<ContainerConcept Container>
struct TakeAdapter {
    const Container& container;
    size_t n;

    TakeAdapter(const Container& container, size_t n) : container(container), n(n) {}

    template<typename T>
    friend auto operator|(const T& container, const TakeAdapter<T>& adapter) {
        return adapter.take(container);
    }

    template<typename T>
    auto take(const T& container) const {
        using ValueType = typename T::value_type;
        std::vector<ValueType> result;
        size_t count = 0;
        for (const auto& element : container) {
            if (count++ < n) {
                result.push_back(element);
            } else {
                break;
            }
        }
        return result;
    }
};

template<typename Container>
auto take(const Container& container, size_t n) {
    return TakeAdapter<Container>(container, n);
}

template<ContainerConcept Container>
struct DropAdapter {
    const Container& container;
    size_t n;

    DropAdapter(const Container& container, size_t n) : container(container), n(n) {}

    template<typename T>
    friend auto operator|(const T& container, const DropAdapter<T>& adapter) {
        return adapter.drop(container);
    }

    template<typename T>
    auto drop(const T& container) const {
        using ValueType = typename T::value_type;
        std::vector<ValueType> result;
        size_t count = 0;
        for (const auto& element : container) {
            if (count++ >= n) {
                result.push_back(element);
            }
        }
        return result;
    }
};

template<typename Container>
auto drop(const Container& container, size_t n) {
    return DropAdapter<Container>(container, n);
}

template<typename Container>
concept ContainerConceptReverse = requires(Container c) {
    { c.begin() } -> std::same_as<typename Container::iterator>;
    { c.end() } -> std::same_as<typename Container::iterator>;
    { c.rbegin() } -> std::same_as<typename Container::reverse_iterator>;
    { c.rend() } -> std::same_as<typename Container::reverse_iterator>;
};

template<ContainerConceptReverse Container>
struct ReverseAdapter {
    const Container& container;

    ReverseAdapter(const Container& container) : container(container) {}

    template<typename T>
    friend auto operator|(const T& container, const ReverseAdapter<T>& adapter) {
        return adapter.reverse(container);
    }

    template<typename T>
    auto reverse(const T& container) const {
        using ValueType = typename T::value_type;
        std::vector<ValueType> result;
        for (auto it = container.rbegin(); it != container.rend(); ++it) {
            result.push_back(*it);
        }
        return result;
    }
};

template<typename Container>
auto reverse(const Container& container) {
    return ReverseAdapter<Container>(container);
}

template<ContainerConcept Container>
struct KeysAdapter {
    const Container& container;

    KeysAdapter(const Container& container) : container(container) {}

    template<typename T>
    friend auto operator|(const T& container, const KeysAdapter<T>& adapter) {
        return adapter.keys(container);
    }

    template<typename T>
    auto keys(const T& container) const {
        using KeyType = typename std::remove_reference_t<T>::key_type;
        std::vector<KeyType> result;
        for (const auto& pair : container) {
            result.push_back(pair.first);
        }
        return result;
    }
};

template<typename Container>
auto keys(const Container& container) {
    return KeysAdapter<Container>(container);
}

template<ContainerConcept Container>
struct ValuesAdapter {
    const Container& container;

    ValuesAdapter(const Container& container) : container(container) {}

    template<typename T>
    friend auto operator|(const T& container, const ValuesAdapter<T>& adapter) {
        return adapter.values(container);
    }

    template<typename T>
    auto values(const T& container) const {
        using ValueType = typename std::remove_reference_t<T>::mapped_type;
        std::vector<ValueType> result;
        for (const auto& pair : container) {
            result.push_back(pair.second);
        }
        return result;
    }
};

template<typename Container>
auto values(const Container& container) {
    return ValuesAdapter<Container>(container);
}

#endif //LABWORK9_NICRONN_LIB_ADAPTERS_H_
