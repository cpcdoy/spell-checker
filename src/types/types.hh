#pragma once

# include <string>

struct word_data
{
  std::string word;
  unsigned long freq;
};
struct res_data
{
  struct  word_data;
  unsigned int dist;
};


