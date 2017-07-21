#pragma once

#include <string>
#include <map>
#include <memory>

template<typename node_type>
class dawg_node
{
  public:
  template<typename T>
    using dawg_node_ptr = std::shared_ptr<dawg_node<T>>;

    dawg_node(unsigned long id);

    std::string to_string();

    unsigned long get_reacheable_nodes_count();

    void add_edge(node_type key, dawg_node_ptr<node_type> value);
    bool is_an_edge(node_type node);
    std::/*unordered_*/map<node_type, dawg_node_ptr<node_type>>& get_edges();

    unsigned long get_count();

    void set_final();
    bool is_final();

    long id = 0;
    long count = 0;
  private:

    bool final = false;


    std::/*unordered_*/map<node_type, dawg_node_ptr<node_type>> edges;
};

template<typename T>
using dawg_node_ptr = std::shared_ptr<dawg_node<T>>;

#include "dawg_node.hxx"
