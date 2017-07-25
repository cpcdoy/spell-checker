#include "trie_node.hh"
template<typename key_type>
trie_node<key_type>::
trie_node(unsigned int id)
{
  this->id_ = id;
  this->final_node_ = false;
}
template<typename key_type>
unsigned int 
trie_node<key_type>::get_id()
{
  return this->id_;
}
/*template<typename key_type>
void
trie_node<key_type>::set_id(unsigned int id);
{
  this->id_ = id;
}
*/
