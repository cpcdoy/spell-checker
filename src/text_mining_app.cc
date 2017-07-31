#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "../src/types/types.hh"
#include "../src/dawg/dawg.hh"
#include "../src/trie/trie.hh"
#include "../src/utils/io.hh"

#include <iostream>
#include <typeinfo>
#include <fstream>

/** 
 * @brief TextMiningApp entry point (main)
 * 
 * @param argc
 * @param argv
 * 
 * @return
 */
int main(int argc, char** argv)
{
  if (argc > 1)
  {
    std::string dic(argv[1]);
    trie<char, word_data> trie_2(4);
    {
      std::ifstream ifs(dic + "/index", std::fstream::binary | std::fstream::in);
      if (ifs.good())
      {
        boost::archive::text_iarchive ia(ifs);
        ia >> trie_2;
      }
    }

    io_handler<pipe_input_data> pipe_io;
    while (!pipe_io.is_finished())
    {
      pipe_input_data line;
      pipe_io >> line;

      if (line.dist != -1)
      {
        std::vector<res_data> vv;
        std::vector<res_data>  v = trie_2.search_dist(line.dist, vv, trie_2.get_root(), line.word);
        std::sort(v.begin(), v.end(), trie<char, word_data>::sort_res_data); 
        trie_2.print(std::cout, vv);
      }
    }
  }

  return 0;
}
