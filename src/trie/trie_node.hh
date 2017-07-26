#pragma once

#include <string>
#include <map>
#include <memory>

template<typename key_type>
class trie_node
{
  public:
    template<typename T>
      using trie_node_ptr = std::shared_ptr<trie_node<T>>;
    unsigned int get_id();
    trie_node(unsigned int id);
    std::map<key_type, trie_node_ptr<key_type>>& get_childs();
    void set_final_node(bool val);
  private:
    unsigned int id_;
    std::map<key_type, trie_node_ptr<key_type>> childs_;
    bool  final_node_;
};
template<typename T>
using trie_node_ptr = std::shared_ptr<trie_node<T>>;

#include "trie_node.hxx"
