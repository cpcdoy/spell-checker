#pragma once

# include <string>
# include <ctype.h>
# include <fstream>

/** 
 * @brief Io_andler handles io using nice "<<"/">>" operators overloading
 * 
 **/
template<typename data_type>
class io_handler
{
  public:
    void open_file(std::string path);
    io_handler<data_type>& operator>>(data_type& data);

    bool is_finished();
    void close();

  private:
    std::ifstream file;

    bool finished = false;
};

# include "io.hxx"
