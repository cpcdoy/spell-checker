#include "io.hh"
# include "../types/types.hh"
template<typename data_type>
void
io_handler<data_type>::
open_file(std::string path)
{
  file.open(path.c_str(), std::ios::in);
}

template<typename data_type>
bool
io_handler<data_type>::
is_finished()
{
  return file.eof();
}

template<>
bool
io_handler<pipe_input_data>::
is_finished()
{
  return finished;
}

template<typename data_type>
io_handler<data_type>&
io_handler<data_type>::
operator>>(data_type& line)
{
  return *this;
}

template<>
io_handler<std::string>&
io_handler<std::string>::
operator>>(std::string& line)
{
  std::getline(file, line);
  return *this;
}

template<>
io_handler<word_data>&
io_handler<word_data>::
operator>>(word_data& data)
{
  std::string line;
  std::getline(file, line);

  std::string word;
  std::string::iterator it;
  for (it = line.begin(); it != line.end() && !isspace(*it); it++)
    word += *it;

  data.word = word;

  std::string nb;
  for (; it != line.end(); it++)
    if (!isspace(*it))
      nb += *it;

  try
  {
    data.freq = std::stol(nb, nullptr, 10);
  }
  catch (...)
  {
    data.freq = 0;
  }
  //std::cout << data.word << " " << data.freq << std::endl;

  return *this;
}

template<>
io_handler<pipe_input_data>&
io_handler<pipe_input_data>::
operator>>(pipe_input_data& data)
{
  std::string line;
  if (!std::getline(std::cin, line))
  {
    finished = true;
    data.word = "";
    data.dist = -1;

    return *this;
  }

  std::string::iterator it;

  std::string dist;
  for (it = line.begin() + 7; it != line.end() && isspace(*it); it++);

  for (; it != line.end() && !isspace(*it); it++)
    dist += *it;

  std::string word;
  for (; it != line.end(); it++)
    if (!isspace(*it))
      word += *it;

  data.word = word;

  try
  {
    data.dist = std::stol(dist, nullptr, 10);
  }
  catch (...)
  {
    data.dist = -1;
  }
  //std::cout << "word " <<  data.word << "----" << data.dist << std::endl;

  return *this;
}

template<typename data_type>
void
io_handler<data_type>::
close()
{
  file.close();
}
