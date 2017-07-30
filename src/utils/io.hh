#pragma once

# include <string>
# include <ctype.h>
# include <fstream>

template<typename data_type>
class io_handler
{
  public:
    void open_file(std::string path);
    io_handler<data_type>& operator>>(data_type& data);
    template<typename T>
      io_handler<data_type>& operator<<(std::vector<T> v);
    bool is_finished();
    void close();

  private:
    std::ifstream file;
};

# include "io.hxx"
