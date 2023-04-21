#include "trie.h"
#include <typeinfo>
#include <iostream>
#include <memory>
// TODO(student): fill your answer here

using namespace bustub;

template <class T>
auto Trie::Get(std::string_view key) const -> const T *{
    
    if (key.size() == 0)
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
            return temp->val;
        else 
            return nullptr;
    }
}

template <class T>
auto Trie::Put(std::string_view key, T value) const -> Trie{
    if (key.size() == 0)
        return *this;

    std::shared_ptr<const TrieNode>root_temp(nullptr);

    if (root_ == nullptr)
        root_temp = std::make_shared<TrieNode>();
    else
        root_temp = root_;

    Trie cuitrie(root_temp);

    std::shared_ptr<const TrieNode> cur(root_temp);
    std::shared_ptr<const TrieNode> pre(nullptr);

    int n = key.size();
    for (int i = 0; i < n - 1; ++i) {
        
        if (!cur.children_.count(key[i])) {
            // for new root, create a new children
            if (i == 0) 
                cur.children_.at(key[i]) = std::make_shared<TrieNode>();
            // for current node, clone a new node and create a new children
            // then change the children of current parrent to current new clone node 
            else {
                auto newcur = cur.clone();
                cur = std::shared_ptr<T>(std::move(newcur));
                cur.children_.at(key[i]) = std::make_shared<TrieNode>();
                pre.children_.at(key[i - 1]) = cur;
            }
        }
        // search down
        pre = cur;
        cur = cur.children_.at(key[i]);
    }

    // spectial for last node
    if (!cur.children_.count(key[n - 1])) {
        if(n == 1)
            cur.children_.at(key[n - 1]) = std::make_shared<TrieNodeWithValue>(&value);
        else {
            auto newcur = cur.clone();
            cur = std::shared_ptr<T>(std::move(newcur));
            cur.children_.at(key[i]) = std::make_shared<TrieNodeWithValue>(&value);
            pre.children_.at(key[i - 1]) = cur;
        }
    }

    return cuitrie;
}

auto Trie::Remove(std::string_view key) const -> Trie{

}

const uint32_t CASE_1_YOUR_ANSWER = 0;
const uint32_t CASE_2_YOUR_ANSWER = 0;
const uint32_t CASE_3_YOUR_ANSWER = 0;
