#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "../src/types/types.hh"
#include "../src/dawg/dawg.hh"
#include "../src/trie/trie.hh"
#include "../src/utils/io.hh"

#include <iostream>
#include <typeinfo>
#include <fstream>

int main(int argc, char** argv)
{
  trie<char, word_data> trie_2(4);
  {
    std::ifstream ifs("index", std::fstream::binary | std::fstream::in);
    if (ifs.good())
    {
      boost::archive::text_iarchive ia(ifs);
      ia >> trie_2;
    }
  }

  auto res = trie_2.search("chadi");

  std::cout << "Result with deserialized trie : " << res.word << " with freq " << res.freq;

  /*std::vector<res_data> vv;
    std::vector<res_data>  v =  tri.search_dist(10, vv,tri.get_root(), "aa");
    std::sort(v.begin(), v.end(), trie<char, word_data>::sort_res_data); 
    for (auto it = v.begin() ; it != v.end(); ++it)
    std::cout << "dist : " <<  it->dist << " Result : "<< it->data.word << " freq : " << it->data.freq <<std::endl;

  //  std::cout << "Result : " << res.word << " with freq " << res.freq << std::endl;
  */

  return 0;
}
