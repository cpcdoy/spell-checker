#include "dawg/dawg.hh"

int main(int argc, char** argv)
{
  dawg<char, word_data> dawg;
  dawg.insert("blabla", { "blabla", 10 });
  dawg.insert("haha", { "haha", 10 });
  dawg.insert("lol", { "lol", 10 });
  dawg.insert("lolilol", { "lolilol", 10 });
  dawg.insert("test", { "test", 10 });
  dawg.insert("testing", { "testing", 10 });
  dawg.close();

  auto res = dawg.search(argv[1]);
  std::cout << "Result : " << res.word;

  return 0;
}
