#include "types/types.hh"
#include "dawg/dawg.hh"
#include "trie/trie.hh"
#include "utils/io.hh"

int main(int argc, char** argv)
{
  /*dawg_node<char> node(0);
  std::vector<std::pair<char, dawg_node<char>>> v;
  std::cout << sizeof(v) << std::endl;
  std::exit(0);*/
  dawg<char, word_data> dawg;
  trie<char, word_data> trie(4);
  trie_node<char> node(3);
  io_handler<word_data> io;
  io.open_file(argv[2]);
  while (!io.is_finished())
  {
    word_data line;
    io >> line;
    dawg.insert(line.word, line);
  }

  dawg.close();

  auto res = dawg.search(argv[1], 0);
  std::cout << "Result : " << res.word << " with freq " << res.freq;

  return 0;
}
