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
 * @brief TextMiningCompiler entry point (main)
 * 
 * @param argc
 * @param argv
 * 
 * @return
 */
int main(int argc, char** argv)
{
  if (argc > 2)
  {
    std::string dic(argv[2]);
    std::cerr << "Removing " + dic << std::endl;
    std::string arg("rm -rf " + dic);
    std::system(arg.c_str());
    const int dir_err = mkdir(dic.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    std::cerr << "Creating " + dic << std::endl;

    trie<char, word_data> trie1(4, argv[2]);

    io_handler<word_data> io;
    io.open_file(argv[1]);
    while (!io.is_finished())
    {
      word_data line;
      io >> line;
      trie1.insert(line.word, line);
    }
    std::cerr << "Inserting " << argv[1] << std::endl;

    {
      std::ofstream ofs(dic + "/index", std::fstream::binary | std::fstream::out);
      boost::archive::text_oarchive oa(ofs);
      oa << trie1;
    }
  }
  else
    std::cerr << "Example usage: ./TextMiningCompiler /path/to/words.txt /path/to/dict.bin" << std::endl;

  return 0;
}
