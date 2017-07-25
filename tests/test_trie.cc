#include "../src/types/types.hh"
#include "../src/dawg/dawg.hh"
#include "../src/trie/trie.hh"
#include "../src/utils/io.hh"

int main(int argc, char** argv)
{
  trie<char, word_data> trie(4);
  trie_node<char> node(3);
  auto a = node.get_id();
  //io_handler<word_data> io;
  //io.open_file(argv[2]);
  /*while (!io.is_finished())
  {
    word_data line;
    io >> line;
    dawg.insert(line.word, line);
  }*/


//  auto res = dawg.search(argv[1], 0);
 // std::cout << "Result : " << res.word << " with freq " << res.freq;

  return 0;
}
