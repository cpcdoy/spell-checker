#include "io.hh"

template<typename data_type>
void
io_handler<data_type>::
open_file(std::string path)
{
  file.open(path.c_str(), std::ios::in);
}

template<>
io_handler<word_data>&
io_handler<word_data>::
operator>>(word_data& data)
{
  std::string line;
  std::getline(file, line);

  for (auto it = line.begin(); it != line.end(); it++)
    ;//if (*it != ' ')

  return *this;
}
