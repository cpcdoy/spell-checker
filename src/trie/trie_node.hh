#pragma once

#include <string>
#include <map>
#include <memory>

# include <boost/serialization/base_object.hpp>
# include <boost/serialization/shared_ptr.hpp>
# include <boost/serialization/map.hpp>


/** 
 * @brief Contains a trie's node
 */
template<typename key_type>
class trie_node
{
  public:
    template<typename T>
      using trie_node_ptr = std::shared_ptr<trie_node<T>>;
    unsigned int get_id();
    trie_node();
    trie_node(unsigned int id);
    std::map<key_type, trie_node_ptr<key_type>>& get_childs();
    void set_final_node(bool val);
    bool  get_final_node();
  private:
    unsigned int id_;
    std::map<key_type, trie_node_ptr<key_type>> childs_;
    bool  final_node_;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      (void)version;
      ar & id_;
      ar & childs_;
      ar & final_node_;
    }
};
template<typename T>
using trie_node_ptr = std::shared_ptr<trie_node<T>>;

#include "trie_node.hxx"
