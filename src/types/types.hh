#pragma once

# include <string>

# include <boost/serialization/base_object.hpp>


/** 
 * @brief word_data is a struct containing informations about words (i.e. the word and its frequency)
 */
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


/** 
 * @brief pipe_input_data contains a search query's data (the word and the wanted distance)
 */
struct pipe_input_data
{
  std::string word;
  int dist;
};


/** 
 * @brief res_data contains a result's data which means, a word_data structure and a distance
 */
struct res_data
{
  struct word_data data;
  unsigned int dist;
};
