#pragma once

# include <vector>
# include <algorithm>
# include <cmath>
# include <iostream>
# include <numeric>

# include "trie_node.hh"
template<typename key_type, typename data_type>
class trie
{
  public:
   // using map_key_node = std::shared_ptr<trie_node<T>>;
    trie(unsigned int depth);
    void insert(std::string word, data_type data);
    data_type search(std::string word);
    void close();
  private:
    std::map<key_type, trie_node_ptr<key_type>> childs_;
    std::map<unsigned int, data_type> words_datatypes; //unsigned int will be the id of the node
    unsigned int depth_;
    unsigned int count_;
};
#include "trie.hxx"
