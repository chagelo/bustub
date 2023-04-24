#include "trie.h"
#include <typeinfo>
#include <iostream>
#include <memory>
// TODO(student): fill your answer here

using namespace bustub;

template <class T>
auto Trie::Get(std::string_view key) const -> const T *{
    
    if (!key.empty())
        return nullptr;

    std::shared_ptr<const TrieNode> cur = root_;

    for (auto &c: key) {
        if (cur == nullptr or !cur->children_.count(c))
            return nullptr;
        cur = cur->children_.at(c);
    }

    if (!cur->is_value_node_)
        return nullptr;
    else {
        auto temp = static_cast<std::shared_ptr<const TrieNodeWithValue<T>>>(cur);
        if (typeid(temp->value_) == typeid(std::shared_ptr<T>))
            return temp->value_;
        else 
            return nullptr;
    }
}

template <class T>
auto Trie::Put(std::string_view key, T value) const -> Trie{
    if (!key.empty())
        return *this;

    std::shared_ptr<TrieNode>root_temp(nullptr);

    if (root_ == nullptr)
        root_temp = std::make_shared<TrieNode>();
    else
        root_temp = root_->Clone();

    std::shared_ptr<TrieNode> cur(std::move(root_temp));
    std::shared_ptr<TrieNode> pre(nullptr);
    std::shared_ptr<TrieNode> root(cur);
    
    int n = key.size();
    for (int i = 0; i < n - 1; ++i) {
        
        if (!cur->children_.count(key[i])) {
            // for new root, create a new children

            auto temp = std::make_shared<TrieNode>();   

            // for current node, clone a new node and create a new children
            // then change the children of current parrent to current new clone node 
            if(i != 0) {
                auto newcur = cur->Clone();
                cur = std::shared_ptr<TrieNode>(std::move(newcur));
                pre->children_[key[i - 1]] = cur;
            }
            cur->children_[key[i]] = std::make_shared<TrieNode>();
        }

        // search down
        pre = cur;
        cur = std::const_pointer_cast<TrieNode>(cur->children_[key[i]]);
    }

    // spectial for last node
    if (!cur->children_.count(key[n - 1])) {
        if(n != 1) {
            auto newcur = cur->Clone();
            cur = std::shared_ptr<TrieNode>(std::move(newcur));
            pre->children_[key[n - 2]] = cur;
        }
        cur->children_[key[n - 1]] = std::make_shared<TrieNodeWithValue<T>\
        >(cur->children_, std::make_shared<T>(value));
    }

    return Trie(root);
}

auto Trie::Remove(std::string_view key) const -> Trie{
    if (!key.empty())
        return *this;

    if (root_ == nullptr)
        return *this;

    std::shared_ptr<TrieNode> cur = std::shared_ptr<TrieNode>(std::move(root_->Clone()));
    std::shared_ptr<TrieNode> pre(nullptr); 
    std::shared_ptr<TrieNode> root(cur);

    int n = key.size();

    for (int i = 0; i < n - 1; ++i) {
        if (cur == nullptr or !cur->children_.count(key[i]))
            return *this;
        pre = cur;
        cur = std::const_pointer_cast<TrieNode>(cur->children_[key[i]]);
    }

    if (!cur->children_.count(key[n - 1]))
        return *this;
    else {
        if (n != 1) {
            auto newcur = cur->Clone();
            cur = std::shared_ptr<TrieNode>(std::move(newcur));
            pre->children_[key[n - 2]] = cur;

        }
        cur->children_[key[n - 1]].reset();
    }
    return Trie(root);
}

const uint32_t CASE_1_YOUR_ANSWER = 0;
const uint32_t CASE_2_YOUR_ANSWER = 0;
const uint32_t CASE_3_YOUR_ANSWER = 0;
