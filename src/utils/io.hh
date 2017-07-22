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
    bool is_finished();

  private:
    std::ifstream file;
};

# include "io.hxx"
