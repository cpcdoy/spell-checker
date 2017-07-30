#include "../src/types/types.hh"
#include "../src/dawg/dawg.hh"
#include "../src/trie/trie.hh"
#include "../src/utils/io.hh"
#include <iostream>
#include <typeinfo>

int main(int argc, char** argv)
{
  trie<char, word_data> tri(4);

  io_handler<word_data> io;
  io.open_file(argv[1]);
  while (!io.is_finished())
  {
    word_data line;
    io >> line;
    tri.insert(line.word, line);
  }
   std::vector<res_data> vv;
  std::vector<res_data>  v =  tri.search_dist(10, vv,tri.get_root(), "aa");
  std::sort(v.begin(), v.end(), trie<char, word_data>::sort_res_data); 
  for (auto it = v.begin() ; it != v.end(); ++it)
    std::cout << "dist : " <<  it->dist << " Result : "<< it->data.word << " freq : " << it->data.freq <<std::endl;

//  std::cout << "Result : " << res.word << " with freq " << res.freq << std::endl;

  return 0;
}
