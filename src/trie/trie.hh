#pragma once

# include <vector>
# include <algorithm>
# include <cmath>
# include <iostream>
# include <numeric>
# include <sys/stat.h>

# include <boost/serialization/base_object.hpp>
# include <boost/serialization/shared_ptr.hpp>
# include <boost/serialization/map.hpp>

# include "trie_node.hh"

template<typename key_type, typename data_type>
class trie
{
  public:
    // using map_key_node = std::shared_ptr<trie_node<T>>;
    trie(unsigned int depth);

    void 
      insert(std::string word, data_type data);

    data_type 
      search(std::string word);
    template<typename T>
      std::vector<T> & 
      search_dist(int dist, std::vector<T> &v, trie_node_ptr<key_type> cur_node,std::string word, std::string tmp = "");
    unsigned int 
      lev_dam_dist(std::string s1,  std::string s2);

    trie_node_ptr<key_type>
      get_root();
    unsigned int count_;
  private:
    static bool sort_res_data(const res_data& lhs, const res_data& rhs);

    trie_node_ptr<key_type> root_;
    //std::map<key_type, trie_node_ptr<key_type>> childs_;
    std::map<unsigned int, data_type> words_datatypes; //unsigned int will be the id of the node
    unsigned int depth_;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      (void)version;
      ar & root_;
      ar & words_datatypes;
      ar & depth_;
      ar & count_;
    }
};

#include "trie.hxx"
