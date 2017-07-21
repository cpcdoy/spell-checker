#include "dawg_node.hh"

template<typename node_type>
dawg_node<node_type>::
dawg_node(unsigned long id)
{
  this->id = id;
}

template<typename node_type>
std::string
dawg_node<node_type>::
to_string()
{
  return std::string("");
}

template<typename node_type>
inline void
dawg_node<node_type>::
add_edge(node_type key, dawg_node_ptr<node_type> value)
{
  edges.insert(std::make_pair(key, value));
  std::cout << "Inserting " << key << std::endl;
}

template<typename node_type>
inline bool
dawg_node<node_type>::
is_an_edge(node_type node)
{
  return edges.find(node) != edges.end();
}

template<typename node_type>
inline std::/*unordered_*/map<node_type, dawg_node_ptr<node_type>>&
dawg_node<node_type>::
get_edges()
{
  return edges;
}

template<typename node_type>
unsigned long
dawg_node<node_type>::
get_count()
{
  return count;
}

template<typename node_type>
inline void
dawg_node<node_type>::
set_final()
{
  final = true;
}

template<typename node_type>
inline bool
dawg_node<node_type>::
is_final()
{
  return final;
}

template<typename node_type>
unsigned long
dawg_node<node_type>::
get_reacheable_nodes_count()
{
  if (count)
    return count;

  count = 0;
  if (final)
    count += 1;

  for (auto i = edges.begin(); i != edges.end(); i++)
  {
    count += i->second->get_reacheable_nodes_count();
    std::cout << "count " << count << std::endl;
  }

  return count;
}
