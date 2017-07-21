#include "dawg.hh"

template<typename key_type, typename data_type>
dawg<key_type, data_type>::
dawg()
{
  dawg_node_id = 0;
  root = std::make_shared<dawg_node<key_type>>(dawg_node_id++);
  prev_word = "";
}

template<typename key_type, typename data_type>
void
dawg<key_type, data_type>::
insert(std::string word, data_type word_data)
{
  if (word <= prev_word)
  {
    std::cerr << "At comparaison : " << word << " <= " << prev_word << " \n-> Words must be inserted in alphabetical order." << std::endl;
    return;
  }

  unsigned long common_prefix = 0;

  std::cout << "For: " << word << " " << prev_word << std::endl;
  for (unsigned long i = 0; i < std::min(word.size(), prev_word.size()); i++)
  {
    std::cout << word[i] << " " << prev_word[i] << " " << common_prefix << std::endl;
    if (word[i] != prev_word[i])
      break;
    common_prefix++;
  }

  std::cout << "size : " << unchecked_nodes.size() << std::endl;
  minimize(common_prefix);
  std::cout << "size : " << unchecked_nodes.size() << std::endl;

  data.push_back(word_data);

  dawg_node_ptr<key_type> node;
  if (!unchecked_nodes.size())
    node = root;
  else
    node = unchecked_nodes.back().next_node;

  for (auto& l : word.substr(common_prefix))
  {
    auto next_node = std::make_shared<dawg_node<key_type>>(dawg_node_id++);
    node->add_edge(l, next_node);
    std::cout << "node id " << l << " " << node->id << std::endl;
    unchecked_nodes.push_back({ node, next_node, l});
    node = next_node;
  }

  node->set_final();
  prev_word = word;
}

template<typename key_type, typename data_type>
void
dawg<key_type, data_type>::
minimize(unsigned long limit)
{
  std::cout << "Minimizing " << unchecked_nodes.size() - 1 << " " << limit - 1<<std::endl;
  for (long i = (long)unchecked_nodes.size() - 1; i < limit - 1; i--)
  {
    unchecked_node& u_node = unchecked_nodes[i];
    auto& parent = u_node.node;
    auto& letter = u_node.letter;
    auto& child = u_node.next_node;
    auto child_it = minimized_nodes.find(child);
    auto& child_it_val = *child_it;

    std::cout << "--------------------------- " << parent->id << " " << letter << std::endl;
    if (child_it != minimized_nodes.end())
      parent->get_edges()[letter] = child_it_val.second;
    else
      minimized_nodes[child] = child;

    unchecked_nodes.pop_back();
  }
}

template<typename key_type, typename data_type>
data_type
dawg<key_type, data_type>::
search(std::string word)
{
  auto node = root;

  unsigned long skipped = 0;

  for (auto& l : word)
  {
    std::cout << l << std::endl;
    if (!node->is_an_edge(l))
    {
      std::cout << "Not found" << std::endl;
      return data_type();
    }

    for (auto& e : node->get_edges())
    {
      if (e.first == l)
      {
        if (node->is_final())
          skipped++;
        node = e.second;
        break;
      }
      skipped += e.second->get_count();
      std::cout << "Skipping " << skipped << std::endl;
    }
  }
  std::cout << "Might be found" << std::endl;
  if (node->is_final())
  {
    std::cout << "Data content" << std::endl;
    for (int i = 0; i < data.size(); i++)
      std::cout << i << " " << data[i].word << " | " << std::endl;
    return data[skipped];
  }

  std::cout << "Not found at all" << std::endl;
  return data_type();
}

template<typename key_type, typename data_type>
void
dawg<key_type, data_type>::
close()
{
  minimize(0);

  root->get_reacheable_nodes_count();
  
  for (auto it = root->get_edges().begin(); it != root->get_edges().end(); it++)
    std::cout << "key "  << it->first << std::endl;
}


template<typename key_type, typename data_type>
void
dawg<key_type, data_type>::
debug_display()
{
}
