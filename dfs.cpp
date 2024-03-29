#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

void dfs(string cur, string goal, vector<vector<short int>> &index, map<string, short int> &tree, bool &found, int &count);

int main()
{
    // string test = "abcdefgh-";
    // string goal = "-abdecghf";
    // string test = "abcdefg-h";
    // string goal = "abcdefgh-";
    // string test = "dgaebfhc-";
    // string goal = "-abcdefgh";
    string test;
    string goal;
    cin>>test;
    cin>>goal;
    cout<<test<<endl;
    cout<<goal<<endl;
    map<string, short int> tree;
    tree.insert(pair<string, short int>(test, test.find('-')));

    vector<vector<short int>> index{
        {1, 3},
        {0, 2, 4},
        {1, 5},
        {0, 4, 6},
        {1, 3, 5, 7},
        {2, 4, 8},
        {3, 7},
        {4, 6, 8},
        {5, 7}
      };

      bool found = false;
      int count = 0;
      dfs(test, goal, index, tree, found, count);

}


void dfs(string cur, string goal, vector<vector<short int>> &index, map<string, short int> &tree, bool &found, int &count)
{
  if(cur == goal)
  {
    found = true;
    for(int	j	=	0;	j	<	3;	j++){
      int	u	=	j	*	3;
      int	stop	=	(j	+	1)	*	3;
      for(;	u	<	stop; u++)
      cout	<<	setw(2)	<<	cur[u];
      cout	<<	endl;
    }
    cout<<endl;
    cout<<"Total nodes: "<<tree.size()<<", max depth is: "<<count<<endl;
    return;
  }
  count++;
  // cout<<index[cur.find('-')].size()<<endl;
  for(int i = 0; i < (int)index[cur.find('-')].size(); i++)
  {
    // cout<<"i "<<i<<endl;
    if(found == false)
    {
      string newCur = cur;
      swap(newCur[newCur.find('-')], newCur[index[newCur.find('-')][i]]);
      if(tree.find(newCur) == tree.end())
      {
        for(int	j	=	0;	j	<	3;	j++){
					int	u	=	j	*	3;
					int	stop	=	(j	+	1)	*	3;
					for(;	u	<	stop; u++)
          cout	<<	setw(2)	<<	cur[u];
					cout	<<	endl;
        }
        cout	<<	endl;
        tree.insert(pair<string, short int>(newCur, cur.find('-')));
        dfs(newCur, goal, index, tree, found, count);
      }
      else
      {
        // cout<<"already in tree"<<endl;
      }
    }
    else
    {
      //print
      // cout<<cur<<endl;
      return;
    }
  }
  count--;
  return;
}
