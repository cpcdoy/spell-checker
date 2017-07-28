#include "trie.hh"
#include <fstream>
#include "../types/types.hh"
#include "../utils/io.hh"
template<typename key_type, typename data_type>
trie<key_type, data_type>::
trie(unsigned depth)
{
  this->depth_ = depth;
  this->count_ = 0;
  this->root_ = std::make_shared<trie_node<key_type>>(0);

  //this->words_datatypes.insert(std::pair<unsigned int, data_type>(a ,std::make_shared<trie_node<char>>(++this->count_)));
}
template<typename key_type, typename data_type>
data_type
trie<key_type, data_type>::
search(std::string word)
{
  std::cout << "not defined yet" <<std::endl;
 return data_type();
}
template<>
word_data
trie<char, word_data>::
search(std::string word)
{
  int cmp = 0;
  auto sp = this->root_;
  //std::cout << sp->get_childs()['a'] << std::endl;
 // std::cout << sp->get_childs().count(word[cmp]) << std::endl;
  while ((cmp < this->depth_) && (cmp < word.size()))
  {
    if (sp->get_childs().count(word[cmp]))
      sp = sp->get_childs()[word[cmp]];
    else
      break;
    cmp ++;
  }
  if (cmp < this->depth_) 
    if ((sp->get_final_node() == true) && (cmp == word.size() - 1))
    {
      std::cout <<  "word found : "<<  words_datatypes[sp->get_id()].word <<std::endl ; 
      return this->words_datatypes[sp->get_id()];
    }
     else
      return {"not found", 0};
  else
  {
    io_handler<word_data> io;
    io.open_file("dic/" + std::to_string(sp->get_id()));
    while (!io.is_finished())
    {
      word_data line;
      io >> line;
      if (word.substr(cmp) == line.word)
      {
        line.word = word;
        std::cout <<  "word found : "<<  word <<std::endl ; 
        return line;
      }
    }
    return {"not found", 0};
  }

}
template<typename key_type, typename data_type>
void
trie<key_type, data_type>::
insert(std::string word, data_type data)
{
}
template<>
void
trie<char, word_data>::
insert(std::string word, word_data data)
{
  if (!word.size())
    return;
  // auto sp = std::make_shared<int>(12); 
  //auto sp =  std::make_shared<trie_node<key_type>>(*this->root_);
  auto sp =  this->root_;
  unsigned int cmp = 0;

  while((cmp < word.size() - 1) && (cmp < this->depth_))
  {
    char a = word[cmp];
    typename std::map<char, trie_node_ptr<char>>::iterator it = sp->get_childs().find(a);
    if (!sp->get_childs().count(a))
      //if (it == sp->get_childs().end())
    {
      sp->get_childs().insert(std::pair<char, trie_node_ptr<char>>(a ,std::make_shared<trie_node<char>>(++this->count_)));
    }
    sp = sp->get_childs()[a];
    cmp++;
  }
  if (cmp < this->depth_)
  {
    sp->set_final_node(true);
    this->words_datatypes[sp->get_id()] = data;
  }
  else
  {
    std::ofstream dict;
    dict.open ("dic/" + std::to_string(sp->get_id()), std::ofstream::out | std::ofstream::app);
    dict << word.substr(cmp  )  << " " <<  data.freq << std::endl; //have to write data_type instead of word
    dict.close();
  }
}
