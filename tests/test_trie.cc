#include "../src/types/types.hh"
#include "../src/dawg/dawg.hh"
#include "../src/trie/trie.hh"
#include "../src/utils/io.hh"
#include <iostream>
#include <typeinfo>
using namespace std;
int  editdist(string s,string t,int n,int m) 
{
  int d1,d2,d3,cost;
  int i,j;
  int d[n + 1][m + 1];
  for(i=0;i<=n;i++) 
  {
    for(j=0;j<=m;j++)
    {
      if(s[i - 1]==t[j - 1]) 
        cost=0;
      else
        cost=1;
      d1=d[i][j+1]+1;
      d2=d[i+1][j]+1;
      d3=d[i][j]+cost;
      d[i+1][j+1]=min(min(d1,d2),d3);
      if(i>0 && j>0 && s[i+1]==t[j] && s[i]==t[j+1] )   //transposition
      {
        d[i+1][j+1]=min(d[i+1][j+1],d[i-1][j-1]+cost);
      }
    }
  }
  return d[n+1][m+1]; 
}
unsigned int lev_dam_dist(std::string s1,  std::string s2)
{
  size_t size1 = s1.size();
  size_t size2 = s2.size();
  size_t d[size1 + 1][size2 + 1];
  for (int i = 0; i <= size1; i ++)
    d[i][0] = i;
  for (int i = 0; i <= size2; i ++)
    d[0][i] = i;

  int cost = 0; 
  for (int i = 1; i <= size1; i ++)
    for (int j = 1; j <= size2; j ++)
    {      
      cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1 ;
      if ( (i > 1) && (j > 1) && (s1[i] == s2[j - 1]) && (s1[i - 1] == s2[j]))
      {
        size_t a = std::min(d[i - 1][j], d[i][j - 1] + 1);
        size_t b = std::min(d[i][j] + cost, d[i - 2][j - 2]);
        d[i][j] = std::min(a, b);
      }
      else
      {
        d[i][j] = std::min(std::min(d[i][j -1] + 1, d[i - 1][j] + 1), d[i - 1][j - 1] + cost);
      }
    }
  return d[size1][size2];
}

int main(int argc, char** argv)
{
  trie<char, word_data> tri(4);
  io_handler<word_data> io;
  io.open_file(argv[1]);
  while (!io.is_finished())
  {
    word_data line;
    io >> line;
    tri.insert(line.word, line);
  }
  std::vector<res_data>  vv;
  std::vector<res_data>  v =  tri.search_dist(4, vv,tri.get_root(), "testing");
  std::sort(v.begin(), v.end(),trie<char, word_data>::sort_res_data); 
  tri.print(std::cout, v);
  
  //std::cout << lev_dam_dist("testing", "testing") <<std::endl;
  //std::cout << editdist("pantera","aorta",7,5) <<std::endl;
  return 0;
}
