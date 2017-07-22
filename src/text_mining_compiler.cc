#include "types/types.hh"
#include "dawg/dawg.hh"
#include "utils/io.hh"

int main(int argc, char** argv)
{
  dawg<char, word_data> dawg;
  io_handler<word_data> io;
  io.open_file(argv[2]);
  while (!io.is_finished())
  {
    word_data line;
    io >> line;
    dawg.insert(line.word, line);
    //std::cout << line.word << std::endl;
  }
  /*dawg.insert(".net", { ".net", 16 });
  dawg.insert("0+", { "0+", 154 });
  dawg.insert("00", { "00", 126 });
  dawg.insert("000", { "000", 12323 });*/

  dawg.close();

  auto res = dawg.search(argv[1]);
  std::cout << "Result : " << res.word << " with freq " << res.freq;

  return 0;
}
