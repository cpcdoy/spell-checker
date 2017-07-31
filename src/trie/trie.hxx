#include "trie.hh"
#include <fstream>
#include "../types/types.hh"
#include "../utils/io.hh"

/** 
 * @brief 
 * 
 * @param depth
 * @param dic
 * 
 * @return 
 */
template<typename key_type, typename data_type>
trie<key_type, data_type>::
trie(unsigned depth, std::string dic)
{
  this->depth_ = depth;
  this->count_ = 0;
  this->root_ = std::make_shared<trie_node<key_type>>(0);
  this->dic = dic + "/";
}

/** 
 * @brief 
 * 
 * @return 
 */
template<typename key_type, typename data_type>
trie_node_ptr<key_type>
trie<key_type, data_type>::
get_root()
{
  return this->root_;
}

/** 
 * @brief 
 * 
 * @param out
 * @param v
 * 
 * @return 
 */
template<typename key_type, typename data_type>
void
trie<key_type, data_type>::
print(std::ostream& out, std::vector<res_data> &v)
{
  out <<"[";
  for (auto it = v.begin() ; it != (v.end() - 1); ++it)
    out<<"{\"word\":\"" << it->data.word << "\",\"freq\":"<<it->data.freq << ",\"distance\":"<<it->dist<<"},";
  auto it = (v.end() - 1);
  out<<"{\"word\":\"" << it->data.word << "\",\"freq\":"<<it->data.freq << ",\"distance\":"<<it->dist<<"}";
  out <<"]" <<std::endl;
}

/** 
 * @brief 
 * 
 * @param word
 * 
 * @return 
 */
template<typename key_type, typename data_type>
data_type
trie<key_type, data_type>::
search(std::string word)
{
  std::cout << "not defined yet" <<std::endl;
  return data_type();
}

/** 
 * @brief 
 * 
 * @param word
 * 
 * @return 
 */
template<>
word_data
trie<char, word_data>::
search(std::string word)
{
  int cmp = 0;
  auto sp = this->root_;
  while ((cmp < this->depth_) && (cmp < word.size()))
  {
    if (sp->get_childs().count(word[cmp]))
    {
      sp = sp->get_childs()[word[cmp]];
    }
    else
      break;
    cmp ++;
  }
  if (cmp <= this->depth_) 
    if ((sp->get_final_node() == true))
    {
      return this->words_datatypes[sp->get_id()];
    }
    else
      return {"not found", 0};
  else
  {
    io_handler<word_data> io;
    io.open_file(dic  + std::to_string(sp->get_id()));
    while (!io.is_finished())
    {
      word_data line;
      io >> line;
      if (word.substr(cmp) == line.word)
      {
        line.word = word;
        return line;
      }
    }
    return {"not found", 0};
  }
}

/** 
 * @brief 
 * 
 * @param dist
 * @param v
 * @param cur_node
 * @param word
 * @param tmp
 * 
 * @return 
 */
template<typename key_type, typename data_type>
template<typename T>
std::vector<T> & 
trie<key_type, data_type>::
search_dist(int dist, std::vector<T> &v, trie_node_ptr<key_type> cur_node,std::string word, std::string tmp)
{
  return std::vector<T>();
}

template<typename key_type, typename data_type>
bool
trie<key_type, data_type>::
sort_res_data(const res_data& lhs, const res_data& rhs)
{
  if (lhs.dist != rhs.dist)
    return lhs.dist < rhs.dist;

  else if (lhs.data.freq != rhs.data.freq)
    return lhs.data.freq > rhs.data.freq;

  else if (lhs.data.word != rhs.data.word)
    return lhs.data.word < rhs.data.word;
}


/** 
 * @brief 
 * 
 * @param dist
 * @param v
 * @param cur_node
 * @param word
 * @param tmp
 * 
 * @return 
 */
template<>
template<>
std::vector<res_data> &
trie<char, word_data>::
search_dist(int dist, std::vector<res_data> &v,trie_node_ptr<char> cur_node,std::string word, std::string tmp)
{
  //stille have to handle case when the word is tooo big for the trie
  size_t cal_dis = 0;
  if (dist == 0)
  {
    word_data d = search(word);
    if (d.freq)
      v.push_back({d, 0});
    return v;
  }
  if (tmp.size() < this->depth_)
  {
    if ((cur_node->get_final_node()) && ((cal_dis = lev_dam_dist(this->words_datatypes[cur_node->get_id()].word, word)) <= dist))
      v.push_back({this->words_datatypes[cur_node->get_id()], cal_dis});
    if (!cur_node->get_childs().empty())
      for(auto iter = cur_node->get_childs().begin(); iter != cur_node->get_childs().end(); ++iter)
      {
        char a = iter->first;
        std::string tmp2(tmp + a);
        search_dist(dist, v, cur_node->get_childs()[a], word, tmp2);
      }
    return v;
  }
  else
  {
    if ((cur_node->get_final_node()) && ((cal_dis = lev_dam_dist(this->words_datatypes[cur_node->get_id()].word, word)) <= dist))
      v.push_back({this->words_datatypes[cur_node->get_id()], cal_dis});
    if (! cur_node->has_child_)
      return v;
    io_handler<word_data> io;
    io.open_file(dic  + std::to_string(cur_node->get_id()));
    while (!io.is_finished())
    {
      word_data line;
      io >> line;
      if (((cal_dis =lev_dam_dist(tmp + line.word, word)) <= dist) && (line.freq > 0))
      {
        v.push_back({{tmp + line.word, line.freq}, cal_dis});
      }
      //i could add else break if i was sure that the words are in order
    }
    return v;
  }
}


/** 
 * @brief 
 * 
 * @param word
 * @param data
 * 
 * @return 
 */
template<typename key_type, typename data_type>
void
trie<key_type, data_type>::
insert(std::string word, data_type data)
{
}


/** 
 * @brief 
 * 
 * @param word
 * @param data
 * 
 * @return 
 */
template<>
void
trie<char, word_data>::
insert(std::string word, word_data data)
{
  if (!word.size())
    return;
  auto sp =  this->root_;
  unsigned int cmp = 0;

  while((cmp < word.size() /*- 1*/) && (cmp < this->depth_))
  {
    char a = word[cmp];
    auto it = sp->get_childs().find(a);
    if (!sp->get_childs().count(a))
      //if (it == sp->get_childs().end())
    {
      sp->get_childs().insert(std::pair<char, trie_node_ptr<char>>(a ,std::make_shared<trie_node<char>>(++this->count_)));
    }
    sp = sp->get_childs()[a];
    cmp++;
  }
  if ((cmp < this->depth_) || ((cmp == this->depth_) && (cmp == word.size())))
  {
    sp->set_final_node(true);
    this->words_datatypes[sp->get_id()] = data;
  }
  else
  {
    sp->has_child_ = true;
    std::ofstream dict;
    dict.open (dic  + std::to_string(sp->get_id()), std::ofstream::out | std::ofstream::app);
    dict << word.substr(cmp)  << " " <<  data.freq << std::endl; //have to write data_type instead of word
    dict.close();
  }
}

/** 
 * @brief 
 * 
 * @param s1
 * @param s2
 * 
 * @return 
 */
template<typename key_type, typename data_type>
unsigned int
trie<key_type, data_type>::
lev_dam_dist(std::string s1,  std::string s2)
{
  size_t size1 = s1.size();
  size_t size2 = s2.size();
  size_t d[size1 + 1][size2 + 1];
  for (int i = 0; i <= size1; i ++)
    d[i][0] = i;
  for (int i = 0; i <= size2; i ++)
    d[0][i] = i;

  int cost = 0; 
  for (int i = 1; i <= size1; i ++)
    for (int j = 1; j <= size2; j ++)
    {      
      cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1 ;
      size_t a = std::min(d[i - 1][j] + 1, d[i][j - 1] + 1);
      size_t b = std::min(d[i - 1 ][j - 1] + cost, a);
      d[i][j] = std::min(a, b);
      if ( (i > 1) && (j > 1) && (s1[i - 1] == s2[j - 2]) && (s1[i - 2] == s2[j - 1]))
      {
        d[i][j] = std::min(d[i][j], d[i -2][j - 2] + cost);
      }
    }
  return d[size1][size2];
}

