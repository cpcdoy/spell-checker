#include "trie_node.hh"

/** 
 * @brief 
 * 
 * @return 
 */
template<typename key_type>
trie_node<key_type>::
trie_node()
{
}


/** 
 * @brief 
 * 
 * @param id
 * 
 * @return 
 */
template<typename key_type>
trie_node<key_type>::
trie_node(unsigned int id)
{
  this->id_ = id;
  this->final_node_ = false;
  this->has_child_ = false;
  this->childs_ = std::map<key_type, trie_node_ptr<key_type>>();
}

/** 
 * @brief 
 * 
 * @return 
 */
template<typename key_type>
unsigned int 
trie_node<key_type>::get_id()
{
  return this->id_;
}

/** 
 * @brief 
 * 
 * @return 
 */
template<typename key_type>
std::map<key_type, trie_node_ptr<key_type>>&
trie_node<key_type>::get_childs()
{
  return this->childs_;
}

/** 
 * @brief 
 * 
 * @param val
 */
template<typename key_type>
void
trie_node<key_type>::set_final_node(bool val)
{
  this->final_node_ = val;
}

/** 
 * @brief 
 * 
 * @return 
 */
template<typename key_type>
bool
trie_node<key_type>::get_final_node()
{
 return this->final_node_ ;
}
