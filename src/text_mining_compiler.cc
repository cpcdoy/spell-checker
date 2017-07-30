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
  trie<char, word_data> trie1(4);

  io_handler<word_data> io;
  io.open_file(argv[1]);
  while (!io.is_finished())
  {
    word_data line;
    io >> line;
    trie1.insert(line.word, line);
  }

  std::cout << "Serializing" << std::endl;

  {
    std::ofstream ofs("index", std::fstream::binary | std::fstream::out);
    boost::archive::text_oarchive oa(ofs);
    oa << trie1;
  }

  return 0;
}
