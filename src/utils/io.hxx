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
template<>
io_handler<word_data>& 
io_handler<word_data>:: 
operator<<(const std::vector<res_data> &v)
{
  std::cout <<"[";
  for (auto it = v.begin() ; it != v.end(); ++it)
    std::cout << "\"word\":\"" <<  it->data.word << "\",\"freq:\""<< it->data.freq  <<"\",\"distance:\"" << it->dist << <<std::endl;
  std::cout <<"]";
  return *this;
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

  std::transform(word.begin(), word.end(), word.begin(), ::tolower);
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

template<typename data_type>
void
io_handler<data_type>::
close()
{
  file.close();
}
