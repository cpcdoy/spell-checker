#pragma once

# include <string>

# include <boost/serialization/base_object.hpp>

struct word_data
{
  std::string word;
  unsigned long freq;

  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      (void)version;
      ar & word;
      ar & freq;
    }
};

struct pipe_input_data
{
  std::string word;
  int dist;
};

struct res_data
{
  struct word_data data;
  unsigned int dist;
};
