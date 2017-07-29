#include "../src/types/types.hh"
#include "../src/dawg/dawg.hh"
#include "../src/trie/trie.hh"
#include "../src/utils/io.hh"
#include <iostream>
#include <typeinfo>

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
  trie.search("chadi");
  //word_data a =  {"hhh", 1};

  //  auto res = dawg.search(argv[1], 0);
  // std::cout << "Result : " << res.word << " with freq " << res.freq;

  return 0;
}
