#include "../src/types/types.hh"
#include "../src/dawg/dawg.hh"
#include "../src/trie/trie.hh"
#include "../src/utils/io.hh"
#include <iostream>
#include <typeinfo>
unsigned int lev_dam_distop(std::string s1,  std::string s2)
{
  size_t size1 = s1.size();
  size_t size2 = s2.size();
  size_t v0[size2  + 1] ;
  size_t v1[size2  + 1] ;
  size_t v2[size2  + 1] ;
  unsigned int cost = 0;
  for (int i = 0; i <= size2; i ++)
    v1[i] = i;
  for (int i = 0; i < size2; i ++)
  {
    v2[0] = i + 1;
    for (int j = 0; j < size2; j ++)
    {      
      cost = (s1[i + 1] == s2[j + 1]) ? 0 : 1 ;
      v2[j + 1] = std::min(std::min(v2[j] + 1, v1[j + 1] + 1), v1[j] + cost);
      if ( (i > 1) && (j > 1) && (s1[i + 1] == s2[j]) && (s1[i] == s2[j + 1]))
        v2[j  + 1] = std::min(v2[j + 1], v0[j - 1] + cost);
    }
    for (int j = 0; j <= size2; j ++)
    {
      v0[j] = v1[j] ;
      v1[j] = v2[j] ;
    }
  }
  return v1[size2];
}

int main(int argc, char** argv)
{
  trie<char, word_data> trie(4);

  io_handler<word_data> io;
  io.open_file(argv[1]);
  while (!io.is_finished())
  {
    word_data line;
    io >> line;
    trie.insert(line.word, line);
  }
  std::vector<word_data>  vv;
  std::cout << "hello" <<std::endl; 
  std::vector<word_data>  v =  trie.search_dist(10, vv,trie.get_root(), "aa");
  std::sort(v.begin(), v.end(), sort_res_data); 
  for (auto it = v.begin() ; it != v.end(); ++it)
    std::cout << it->word <<std::endl;
  return 0;
}
