#include "trie_node.hh"
template<typename key_type>
trie_node<key_type>::
trie_node(unsigned int id)
{
  this->id_ = id;
  this->final_node_ = false;
  this->childs_ = std::map<key_type, trie_node_ptr<key_type>>();
}
template<typename key_type>
unsigned int 
trie_node<key_type>::get_id()
{
  return this->id_;
}
template<typename key_type>
std::map<key_type, trie_node_ptr<key_type>>&
trie_node<key_type>::get_childs()
{
  return this->childs_;
}
template<typename key_type>
void
trie_node<key_type>::set_final_node(bool val)
{
  this->final_node_ = val;
}

