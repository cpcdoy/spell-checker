#include "trie.hh"
#include <fstream>
template<typename key_type, typename data_type>
trie<key_type, data_type>::
trie(unsigned depth)
{
  this->depth_ = depth;
  this->count_ = 0;
  this->root_ = std::make_shared<trie_node<key_type>>(0);
}
template<typename key_type, typename data_type>
void
trie<key_type, data_type>::
insert(std::string word, data_type data)
{
  if (!word.size())
    return;
  // auto sp = std::make_shared<int>(12); 
  //auto sp =  std::make_shared<trie_node<key_type>>(*this->root_);
  auto sp =  this->root_;
  unsigned int cmp = 0;

  std::cout << "word " << word << std::endl;
  while((cmp < word.size() - 1) && (cmp < this->depth_))
  {
    char a = word[cmp];
    typename std::map<key_type, trie_node_ptr<key_type>>::iterator it = sp->get_childs().find(a);
    /*FIXME*/
    /*pb1 when i call the method .find('char a') on the map sp->get_childs() 
     * for a char that i have never added it doesnt return map sp->get_childs().end()
     * pb2 when i use sp->get_childs().count(key) it work the first time
     * then it segfault, the childs_ are initialized, i dont know where is the problem
     * */
    if (!sp->get_childs().count(a))
    //if (it == sp->get_childs().end())
    {
      std::cout << "hello" << std::endl;
      sp->get_childs().insert(std::pair<key_type, trie_node_ptr<key_type>>(a ,std::make_shared<trie_node<key_type>>(++this->count_)));
    }
    sp = sp->get_childs()[a];
    cmp++;
  }
  if (cmp < this->depth_)
  {
    sp->set_final_node(true);
  }
  else
  {
    std::ofstream dict;
    dict.open ("dic/" + std::to_string(sp->get_id()), std::ofstream::out | std::ofstream::app);
    dict << word.substr(cmp -1 ) << std::endl; //have to write data_type instead of word
    dict.close();
  }
}
