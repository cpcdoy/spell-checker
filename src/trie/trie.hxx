#include "trie.hh"
template<typename key_type, typename data_type>
trie<key_type, data_type>::
trie(unsigned depth)
{
  this->depth_ = depth;
  this->count_ = 0;
}
template<typename key_type, typename data_type>
void
trie<key_type, data_type>::
insert(std::string word, data_type data)
{
 // auto sp = std::make_shared<int>(12); 
  auto sp =  std::make_shared<  std::map<key_type, trie_node_ptr<key_type>>>(this->childs_);
  unsigned int cmp = 0;
  while((cmp < word.size() - 1) && (cmp < this->depth))
  {
    typename std::map<key_type, trie_node_ptr<key_type>>::const_iterator it = sp->find(word[cmp]);
    if (it == this->childs_.end())
    {
    (*sp).insert(std::pair<key_type, trie_node_ptr<key_type>>(word[cmp], ++this->count));
    //sp = (*sp)[word[cmp]].get_childs()
    //this->count ++;
    }
    cmp++;
  }
  /*
  if (cmp == depth - 1)
    (*sp).segond->set_final_node(true);
    instansiate data_type then puch_back trie with the node id  
    */
  //else traitement io
}
