#include "trie.h"
#include <typeinfo>
#include <iostream>
// TODO(student): fill your answer here

using namespace bustub;

template <class T>
auto Trie::Get(std::string_view key) const -> const T *{
    
    std::shared_ptr<const TrieNode> cur = root_;

    for (int i = 0; i < key.size(); ++i) {
        if (cur == nullptr or !cur->children_.count(key[i]))
            return nullptr;
        cur = cur->children_.at(key[i]);
    }

    if (!cur->is_value_node_)
        return nullptr;
    else {
        std::shared_ptr<const TrieNodeWithValue<T>> temp = static_cast<std::shared_ptr<const TrieNodeWithValue<T>>>(cur);
        if (typeid(temp->value_) == typeid(std::shared_ptr<T>))
            return temp->val;
        else 
            return nullptr;
    }
}

template <class T>
auto Trie::Put(std::string_view key, T value) const -> Trie{
    
}

auto Trie::Remove(std::string_view key) const -> Trie{
}

const uint32_t CASE_1_YOUR_ANSWER = 0;
const uint32_t CASE_2_YOUR_ANSWER = 0;
const uint32_t CASE_3_YOUR_ANSWER = 0;
