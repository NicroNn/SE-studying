#ifndef LABWORK8_NICRONN_LIB_BST_H_
#define LABWORK8_NICRONN_LIB_BST_H_
#include <memory>
#include <iostream>
#include <functional>

enum class TraversalOrder {
    InOrder,
    PreOrder,
    PostOrder
};

template<typename Type,
    class Comparator = std::less<Type>,
    class Allocator = std::allocator<Type>,
    TraversalOrder Order = TraversalOrder::InOrder>
class BstContainer {
  private:
    struct Node {
        Type key_;
        std::unique_ptr<Node, std::function<void(Node*)>> left_;
        std::unique_ptr<Node, std::function<void(Node*)>> right_;
        Node* parent;

        explicit Node(const Type& val, const Allocator& alloc, Node* parentNode = nullptr)
            : key_(val), left_(nullptr, [](Node*) {}), right_(nullptr, [](Node*) {}), parent(parentNode) {}

        // Node constructor with custom allocator_
        Node(const Type& val, const Allocator& alloc, std::function<void(Node*)> deleter, Node* parentNode = nullptr)
            : key_(val), left_(nullptr, deleter), right_(nullptr, deleter), parent(parentNode) {}
    };

    std::unique_ptr<Node, std::function<void(Node*)>> root_;
    Comparator comparator_;
    Allocator allocator_;

    struct InOrderTag {};
    struct PreOrderTag {};
    struct PostOrderTag {};

  public:
    // fields
    using value_type = Type;
    using reference = Type&;
    using const_reference = const Type&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    BstContainer() : root_(nullptr, [](Node*) {}), allocator_(Allocator()) {}

    // Constructor with custom allocator_
    explicit BstContainer(const Allocator& alloc) : root_(nullptr, [](Node*) {}), allocator_(alloc) {}

    ~BstContainer() {
        root_.reset();
    }

    BstContainer(const BstContainer& other) {
        root_ = deepCopy(other.root_.get(), nullptr);
    }

    BstContainer& operator=(const BstContainer& other) {
        if (this != &other) {
            clear();
            root_ = deepCopy(other.root_.get(), nullptr);
        }
        return *this;
    }

    BstContainer(BstContainer&& other) noexcept
        : root_(std::move(other.root_)), allocator_(std::move(other.allocator_)) {}

    BstContainer& operator=(BstContainer&& other) noexcept {
        if (this != &other) {
            root_ = std::move(other.root_);
            allocator_ = std::move(other.allocator_);
        }
        return *this;
    }

    void insert(const Type& key) {
        root_ = insertRecursive(std::move(root_), key);
    }

    class iterator : public std::iterator<std::bidirectional_iterator_tag, Type> {
        Comparator comparator;
      protected:
        Node* current;
      public:
        explicit iterator(Node* node) : current(node) {}

        Type& operator*() const {
            return current->key_;
        }

        iterator& operator++() {
            if (current == nullptr)
                return *this;

            if constexpr (Order == TraversalOrder::InOrder) {
                if (current->right_) {
                    current = current->right_.get();
                    while (current->left_)
                        current = current->left_.get();
                } else {
                    Node* parent = current->parent;
                    while (parent && current == parent->right_.get()) {
                        current = parent;
                        parent = parent->parent;
                    }
                    current = parent;
                }
            } else if constexpr (Order == TraversalOrder::PreOrder) {
                if (current->left_)
                    current = current->left_.get();
                else if (current->right_)
                    current = current->right_.get();
                else {
                    Node* parent = current->parent;
                    while (parent && (current == parent->right_.get() || !parent->right_)) {
                        current = parent;
                        parent = parent->parent;
                    }
                    if (parent)
                        current = parent->right_.get();
                    else
                        current = nullptr;
                }
            } else if constexpr (Order == TraversalOrder::PostOrder) {
                if (current->parent && current == current->parent->left_.get() && current->parent->right_) {
                    current = current->parent->right_.get();
                    while (current->left_ || current->right_) {
                        if (current->left_)
                            current = current->left_.get();
                        else
                            current = current->right_.get();
                    }
                } else {
                    current = current->parent;
                }
            }

            return *this;
        }

        iterator& operator--() {
            if (current == nullptr)
                return *this;

            if constexpr (Order == TraversalOrder::InOrder) {
                if (current->left_) {
                    current = current->left_.get();
                    while (current->right_)
                        current = current->right_.get();
                } else {
                    Node* parent = current->parent;
                    while (parent && current == parent->left_.get()) {
                        current = parent;
                        parent = parent->parent;
                    }
                    current = parent;
                }
            } else if constexpr (Order == TraversalOrder::PreOrder) {
                if (current->parent == nullptr) {
                    current = nullptr;
                } else if (comparator(current->parent->key_, current->key_)) {
                    if (current->parent->left_ == nullptr) {
                        current = current->parent;
                    } else {
                        current = current->parent->left_.get();
                        while (true) {
                            if (current->right_) {
                                current = current->right_.get();
                            } else if (current->left_) {
                                current = current->left_.get();
                            } else {
                                break;
                            }
                        }
                    }
                } else {
                    current = current->parent;
                }
            } else if constexpr (Order == TraversalOrder::PostOrder) {
                if (current->right_ != nullptr) {
                    current = current->right_.get();
                } else if (current->left_ != nullptr) {
                    current = current->left_.get();
                } else {
                    while (true) {
                        if (current->parent == nullptr) {
                            current = nullptr;
                            break;
                        }
                        if (comparator(current->parent->key_, current->key_) && current->parent->left_ != nullptr) {
                            current = current->parent->left_.get();
                            break;
                        } else {
                            current = current->parent;
                        }
                    }
                }
            }

            return *this;
        }

        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };

    class reverse_iterator : public iterator {
      public:
        explicit reverse_iterator(Node* node) : iterator(node) {}

        reverse_iterator& operator++() {
            iterator::operator--();
            return *this;
        };

        reverse_iterator& operator--() {
            iterator::operator++();
            return *this;
        }
    };

    class const_iterator : public iterator {
      public:
        explicit const_iterator(Node* node) : iterator(node) {}

        const Type& operator*() const {
            return this->current->key_;
        }

        const_iterator& operator++() {
            iterator::operator++();
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp = *this;
            iterator::operator++();
            return tmp;
        }

        const_iterator& operator--() {
            iterator::operator--();
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator tmp = *this;
            iterator::operator--();
            return tmp;
        }
    };

    class const_reverse_iterator : public reverse_iterator {
      public:
        explicit const_reverse_iterator(Node* node) : reverse_iterator(node) {}

        const Type& operator*() const {
            return this->current->key_;
        }

        const_reverse_iterator& operator++() {
            reverse_iterator::operator++();
            return *this;
        }

        const_reverse_iterator operator++(int) {
            const_reverse_iterator tmp = *this;
            reverse_iterator::operator++();
            return tmp;
        }

        const_reverse_iterator& operator--() {
            reverse_iterator::operator--();
            return *this;
        }

        const_reverse_iterator operator--(int) {
            const_reverse_iterator tmp = *this;
            reverse_iterator::operator--();
            return tmp;
        }
    };

    Node* first(Node* node, InOrderTag) {
        if (!node) return nullptr;
        while (node->left_) node = node->left_.get();
        return node;
    }

    Node* first(Node* node, PreOrderTag) {
        return node;
    }

    Node* first(Node* node, PostOrderTag) {
        if (!node) return nullptr;
        while (node->left_ || node->right_) {
            if (node->left_)
                node = node->left_.get();
            else
                node = node->right_.get();
        }
        return node;
    }

    Node* first(Node* node, InOrderTag) const {
        if (!node) return nullptr;
        while (node->left_) node = node->left_.get();
        return node;
    }

    Node* first(Node* node, PreOrderTag) const {
        return node;
    }

    Node* first(Node* node, PostOrderTag) const {
        if (!node) return nullptr;
        while (node->left_ || node->right_) {
            if (node->left_)
                node = node->left_.get();
            else
                node = node->right_.get();
        }
        return node;
    }

    Node* rfirst(Node* node, InOrderTag) {
        if (!node) return nullptr;
        while (node->right_) node = node->right_.get();
        return node;
    }

    Node* rfirst(Node* node, PreOrderTag) {
        if (!node) return nullptr;
        while (node->left_ || node->right_) {
            if (node->right_)
                node = node->right_.get();
            else
                node = node->left_.get();
        }
        return node;
    }

    Node* rfirst(Node* node, PostOrderTag) {
        return node;
    }

    Node* rfirst(Node* node, InOrderTag) const {
        if (!node) return nullptr;
        while (node->right_) node = node->right_.get();
        return node;
    }

    Node* rfirst(Node* node, PreOrderTag) const {
        if (!node) return nullptr;
        while (node->left_ || node->right_) {
            if (node->right_)
                node = node->right_.get();
            else
                node = node->left_.get();
        }
        return node;
    }

    Node* rfirst(Node* node, PostOrderTag) const {
        return node;
    }

    iterator begin() {
        if constexpr (Order == TraversalOrder::InOrder)
            return iterator{first(root_.get(), InOrderTag{})};
        else if constexpr (Order == TraversalOrder::PreOrder)
            return iterator{first(root_.get(), PreOrderTag{})};
        else if constexpr (Order == TraversalOrder::PostOrder)
            return iterator{first(root_.get(), PostOrderTag{})};
    }

    iterator end() {
        return iterator{nullptr};
    }

    const_iterator cbegin() const {
        if constexpr (Order == TraversalOrder::InOrder)
            return const_iterator{first(root_.get(), InOrderTag{})};
        else if constexpr (Order == TraversalOrder::PreOrder)
            return const_iterator{first(root_.get(), PreOrderTag{})};
        else if constexpr (Order == TraversalOrder::PostOrder)
            return const_iterator{first(root_.get(), PostOrderTag{})};
    }

    const_iterator cend() const {
        return const_iterator{nullptr};
    }

    reverse_iterator rbegin() {
        if constexpr (Order == TraversalOrder::InOrder)
            return reverse_iterator{rfirst(root_.get(), InOrderTag{})};
        else if constexpr (Order == TraversalOrder::PreOrder)
            return reverse_iterator{rfirst(root_.get(), PreOrderTag{})};
        else if constexpr (Order == TraversalOrder::PostOrder)
            return reverse_iterator{rfirst(root_.get(), PostOrderTag{})};
    }

    reverse_iterator rend() {
        return reverse_iterator{nullptr};
    }

    const_reverse_iterator crbegin() const {
        if constexpr (Order == TraversalOrder::InOrder)
            return const_reverse_iterator{rfirst(root_.get(), InOrderTag{})};
        else if constexpr (Order == TraversalOrder::PreOrder)
            return const_reverse_iterator{rfirst(root_.get(), PreOrderTag{})};
        else if constexpr (Order == TraversalOrder::PostOrder)
            return const_reverse_iterator{rfirst(root_.get(), PostOrderTag{})};
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator{nullptr};
    }

    bool empty() const noexcept {
        return root_ == nullptr;
    }

    size_type size() const noexcept {
        return size_helper(root_.get());
    }

    size_type max_size() const noexcept {
        return std::allocator_traits<Allocator>::max_size(allocator_);
    }

    void clear() {
        root_.reset();
    }

    void swap(BstContainer& other) noexcept(std::allocator_traits<Allocator>::is_always_equal::value) {
        std::swap(root_, other.root_);
        std::swap(allocator_, other.allocator_);
    }

    iterator find(const Type& key) {
        Node* node = findRecursive(root_.get(), key);
        return iterator{node};
    }

    size_t count(const Type& key) {
        return countRecursive(root_.get(), key);
    }

    iterator lower_bound(const Type& key) {
        Node* node = lowerBoundRecursive(root_.get(), key);
        return iterator{node};
    }

    iterator upper_bound(const Type& key) {
        Node* node = upperBoundRecursive(root_.get(), key);
        return iterator{node};
    }

    std::pair<iterator, iterator> equal_range(const Type& key) {
        Node* node = findRecursive(root_.get(), key);
        auto lower = iterator{node};
        auto upper = iterator{upperBoundRecursive(node, key)};
        return std::make_pair(lower, upper);
    }

    void erase(const Type& key) {
        root_ = eraseRecursive(std::move(root_), key);
    }

    Node* findMin(Node* node) {
        while (node->left_) node = node->left_.get();
        return node;
    }

    bool insert_unique(const Type& key) {
        if (find(key) != end()) return false;
        insert(key);
        return true;
    }

    void merge(BstContainer&& other) {
        if (other.empty()) return;
        if (empty()) {
            *this = std::move(other);
            return;
        }

        auto it = other.begin();
        auto it_end = other.end();

        while (it != it_end) {
            insert(std::move(*it));
            ++it;
        }

        other.clear();
    }



    // fields
    using iterator = BstContainer::iterator;
    using const_iterator = BstContainer::const_iterator;
    using reverse_iterator = BstContainer::reverse_iterator;
    using const_reverse_iterator = BstContainer::const_reverse_iterator;

  private:
    std::unique_ptr<Node, std::function<void(Node*)>> insertRecursive(std::unique_ptr<Node,
                                                                                      std::function<void(Node*)>> node,
                                                                      const Type& key,
                                                                      Node* parent = nullptr) {
        if (!node) {
            node = std::make_unique<Node>(key, allocator_, [this](Node* n) { allocator_.destroy(n); }, parent);
        } else if (comparator_(key, node->key_)) {
            node->left_ = insertRecursive(std::move(node->left_), key, node.get());
        } else if (comparator_(node->key_, key)) {
            node->right_ = insertRecursive(std::move(node->right_), key, node.get());
        }
        return node;
    }

    size_type size_helper(Node* node) const noexcept {
        if (!node)
            return 0;
        return 1 + size_helper(node->left_.get()) + size_helper(node->right_.get());
    }

    Node* findRecursive(Node* node, const Type& key) {
        if (!node) return nullptr;
        if (comparator_(key, node->key_)) {
            return findRecursive(node->left_.get(), key);
        } else if (comparator_(node->key_, key)) {
            return findRecursive(node->right_.get(), key);
        } else {
            return node;
        }
    }

    size_t countRecursive(Node* node, const Type& key) {
        if (!node) return 0;
        if (comparator_(key, node->key_)) {
            return countRecursive(node->left_.get(), key);
        } else if (comparator_(node->key_, key)) {
            return countRecursive(node->right_.get(), key);
        } else {
            return 1 + countRecursive(node->left_.get(), key) + countRecursive(node->right_.get(), key);
        }
    }

    Node* lowerBoundRecursive(Node* node, const Type& key) {
        if (!node) return nullptr;
        if (comparator_(key, node->key_)) {
            Node* left = lowerBoundRecursive(node->left_.get(), key);
            return left ? left : node;
        } else if (comparator_(node->key_, key)) {
            return lowerBoundRecursive(node->right_.get(), key);
        } else {
            return node;
        }
    }

    Node* upperBoundRecursive(Node* node, const Type& key) {
        if (!node) return nullptr;
        if (comparator_(key, node->key_)) {
            Node* right = upperBoundRecursive(node->left_.get(), key);
            return right ? right : node;
        } else {
            return upperBoundRecursive(node->right_.get(), key);
        }
    }


    std::unique_ptr<Node, std::function<void(Node*)>> eraseRecursive(std::unique_ptr<Node,
                                                                                     std::function<void(Node*)>> node,
                                                                     const Type& key) {
        if (!node) return nullptr;
        if (comparator_(key, node->key_)) {
            node->left_ = eraseRecursive(std::move(node->left_), key);
        } else if (comparator_(node->key_, key)) {
            node->right_ = eraseRecursive(std::move(node->right_), key);
        } else {
            if (!node->left_ && !node->right_) {
                return nullptr;
            } else if (!node->left_) {
                return std::move(node->right_);
            } else if (!node->right_) {
                return std::move(node->left_);
            } else {
                Node* minNode = findMin(node->right_.get());
                node->key_ = minNode->key_;
                node->right_ = eraseRecursive(std::move(node->right_), minNode->key_);
            }
        }
        return node;
    }
    std::unique_ptr<Node, std::function<void(Node*)>> deepCopy(const Node* node, Node* parent) {
        if (!node) return nullptr;
        auto newNode = std::make_unique<Node>(node->key_, allocator_, parent);
        newNode->left_ = deepCopy(node->left_.get(), newNode.get());
        newNode->right_ = deepCopy(node->right_.get(), newNode.get());
        return newNode;
    }

};

#endif //LABWORK8_NICRONN_LIB_BST_H_
