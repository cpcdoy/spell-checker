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
  if (word == prev_word || word.size() == 0)
    return;

  if (word < prev_word)
  {
    std::cerr << "At comparaison : " << word << "(" << word.size() << ") <= " << prev_word << "(" << prev_word.size() << ") \n-> Words must be inserted in alphabetical order." << std::endl;
    std::exit(0);
    return;
  }

  unsigned long common_prefix = 0;

  auto word_min_size = std::min(word.size(), prev_word.size());

  for (unsigned long i = 0; i < word_min_size; i++)
  {
    if (word[i] != prev_word[i])
      break;
    common_prefix++;
  }

  minimize(common_prefix);

  data.push_back(word_data);

  dawg_node_ptr<key_type> node;
  
  if (!unchecked_nodes.size()) //not hunderstood
    node = root;
  else
    node = unchecked_nodes.back().next_node;

  for (auto& l : word.substr(common_prefix))
  {
    auto next_node = std::make_shared<dawg_node<key_type>>(dawg_node_id++);
    next_node->set_depth(node); /*added*/
    node->add_edge(l, next_node);
    unchecked_nodes.push_back({node, next_node, l});
    node = next_node;
  }

  node->set_final();
  prev_word = word;
}
template<typename key_type, typename data_type>
void
dawg<key_type, data_type>::
minimize2(long limit)
{
  //std::cout << "Minimizing " << unchecked_nodes.size() - 1 << " " << limit - 1 <<std::endl;
  for (long i = (long)(unchecked_nodes.size() - 1); i > limit - 1; i--)
  {
    unchecked_node& u_node = unchecked_nodes[i];
    auto& parent = u_node.node;
    auto& letter = u_node.letter;
    auto& child = u_node.next_node;
    auto child_it = minimized_nodes.find(child);
    auto& child_it_val = *child_it;

    //std::cout << "--------------------------- " << parent->id << " " << letter <<  " " << child->id << std::endl;

    if (child_it != minimized_nodes.end())
      parent->get_edges()[letter] = child_it_val.second;
    else
      minimized_nodes[child] = child;

    unchecked_nodes.pop_back();
  }
  //std::cout << "End minimizing" << std::endl;
}
template<typename key_type, typename data_type>
void
dawg<key_type, data_type>::
minimize(long limit)
{
  //std::cout << "Minimizing " << unchecked_nodes.size() - 1 << " " << limit - 1 <<std::endl;
  for (long i = (long)(unchecked_nodes.size() - 1); i > limit - 1; i--)
  {
    unchecked_node& u_node = unchecked_nodes[i];
    auto& parent = u_node.node;
    auto& letter = u_node.letter;
    auto& child = u_node.next_node;
    auto child_it = minimized_nodes.find(child);
    /*std::cout << prev_word << " For letter " << letter << std::endl;
    typename std::map<dawg_node_ptr<key_type>, dawg_node_ptr<key_type>>::iterator child_it;
    for (child_it = minimized_nodes.begin(); child_it != minimized_nodes.end(); child_it++)
    {
      std::cout << child_it->first->letter << " ";
      if (child_it->first->letter == letter)
      {
        std::cout << "letter is present" << std::endl;
        break;
      }
    }
    std::cout << std::endl << "---------" << std::endl;*/

    auto& child_it_val = *child_it;

    //std::cout << "--------------------------- " << parent->id << " " << letter <<  " " << child->id << std::endl;

    if (child_it != minimized_nodes.end())
      parent->get_edges()[letter] = child_it_val.second;
    else
      minimized_nodes[child] = child;

    unchecked_nodes.pop_back();
  }
  //std::cout << "End minimizing" << std::endl;
}

template<typename key_type, typename data_type>
data_type
dawg<key_type, data_type>::
search(std::string word, unsigned long cost)
{
  auto node = root;

  unsigned long skipped = 0;

  auto columns = word.size() + 1;

  std::vector<std::string> results;

  std::vector<int> prev_row(word.size());
  std::iota(std::begin(prev_row), std::end(prev_row), 0);

  std::vector<int> curr_row(columns);
  curr_row[0] = prev_row[0] + 1;

  for (auto& l : word)
  {
    if (!node->is_an_edge(l))
    {
      //std::cout << "Not found" << std::endl;
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
      //std::cout << "Skipping " << skipped << std::endl;
    }
  }

  //std::cout << "Might be found" << std::endl;

  if (node->is_final())
    return data[skipped];


  //std::cout << "Not found at all :'(" << std::endl;
  return data_type();
}

template<typename key_type, typename data_type>
void
dawg<key_type, data_type>::
close()
{
  minimize(0);

  root->get_reacheable_nodes_count();

  /*for (auto it = root->get_edges().begin(); it != root->get_edges().end(); it++)
    for (auto it2 = it->second->get_edges().begin(); it2 != it->second->get_edges().end(); it2++)
    std::cout << "key "  << it2->first << std::endl;*/
}


template<typename key_type, typename data_type>
void
dawg<key_type, data_type>::
debug_display()
{
}
