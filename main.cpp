#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <list>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

void bfs(string start, string finsh, vector<vector<short int>> &index);
void dfs(string cur, string goal, vector<vector<short int>> &index, map<string, short int> &tree, bool &found, int &count, int &max);
void infs(string start, string finish, vector<vector<short int>> &index);
int infsManDis(string cur, string finish);
void printPath(map<string, short int> &visited, vector<vector<short int>> &index, string cur, int &nodes_count);
void printFormated(string cur);

// void printQueue(priority_queue<pair<string, int>, vector<pair<string, int>>, less_then_greater> queue){
//     for (int i = 0; i < priority_queue.size(); i++) {

//     }
// }

struct less_then_greater
{
    template <typename T, typename U>
    bool operator()(T const &lhs, U const &rhs) const
    {
        // cout << "left:" << lhs.second << " right:" << rhs.second << endl;
        return lhs.second > rhs.second;
    }
};

int main()
{
    string start;
    string finish;
    cin >> start;
    cin >> finish;

    vector<vector<short int>> index{
        {1, 3},
        {0, 2, 4},
        {1, 5},
        {0, 4, 6},
        {1, 3, 5, 7},
        {2, 4, 8},
        {3, 7},
        {4, 6, 8},
        {5, 7}};

    cout << "BFS:" << endl;
    bfs(start, finish, index);

    cout << "DFS:" << endl;
    bool found = false;
    int count = 0;
    int max = 0;
    map<string, short int> tree;
    tree.insert(pair<string, short int>(start, -1));
    dfs(start, finish, index, tree, found, count, max);

    cout << "BFS-star:" << endl;
    infs(start, finish, index);
}

void bfs(string start, string finish, vector<vector<short int>> &index)
{
    map<string, short int> visited;

    // push start to the visited
    visited.insert(pair<string, short int>(start, -1));

    // Create a queue for BFS
    list<string> queue;

    // Mark the current node as visited and enqueue it
    // tree.insert(pair<string, short int>(start, start.find('-')));
    queue.push_back(start);

    // 'i' will be used to get all adjacent
    // vertices of a vertex
    // list<string>::iterator i;

    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        string cur = queue.front();
        queue.pop_front();

        vector<short int> pos_swaps = index[cur.find('-')];

        for (auto i = 0; i < pos_swaps.size(); i++)
        {
            auto temp_cur = visited.find(finish);
            if (temp_cur != visited.end())
            {
                break;
            }
            string swapped = cur;
            swap(swapped[swapped.find('-')], swapped[pos_swaps[i]]);

            if (visited.find(swapped) == visited.end())
            {
                visited.insert(pair<string, short int>(swapped, cur.find('-')));
                queue.push_back(swapped);
            }
        }
    }

    int nodes_count = 0;
    printPath(visited, index, finish, nodes_count);
    cout << "Total nodes: " << visited.size() << ", max depth is: " << nodes_count << endl;
}

void dfs(string cur, string goal, vector<vector<short int>> &index, map<string, short int> &tree, bool &found, int &count, int &max)
{
    count++;
    if (tree.size()-1 > max)
    {
      max = tree.size()-1;
    }
    if (cur == goal)
    {
        found = true;
        int nodes_count = 0;
        printPath(tree, index, cur, nodes_count);
        /*
        for (int j = 0; j < 3; j++)
        {
            int u = j * 3;
            int stop = (j + 1) * 3;
            for (; u < stop; u++)
                cout << setw(2) << cur[u];
            cout << endl;
        }
        cout << endl;
        */
        cout << "Total nodes: " << count << ", max depth is: " << max << endl;
        
        return;
    }
    // cout<<index[cur.find('-')].size()<<endl;
    for (int i = 0; i < (int)index[cur.find('-')].size(); i++)
    {
        // cout<<"i "<<i<<endl;
        if (found == false)
        {
            string newCur = cur;
            swap(newCur[newCur.find('-')], newCur[index[newCur.find('-')][i]]);
            if (tree.find(newCur) == tree.end())
            {
                /*
                for (int j = 0; j < 3; j++)
                {
                    int u = j * 3;
                    int stop = (j + 1) * 3;
                    for (; u < stop; u++)
                        cout << setw(2) << cur[u];
                    cout << endl;
                }
                cout << endl;
                */
                tree.insert(pair<string, short int>(newCur, cur.find('-')));
                dfs(newCur, goal, index, tree, found, count, max);
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
    tree.erase(cur);
    return;
}

void infs(string start, string finish, vector<vector<short int>> &index)
{
    map<string, short int> visited;

    // push start to the visited
    visited.insert(pair<string, short int>(start, -1));

    // Create a queue for BFS
    // priority_queue<string> queue;
    priority_queue<pair<string, int>, vector<pair<string, int>>, less_then_greater> queue;

    // Mark the current node as visited and enqueue it
    // tree.insert(pair<string, short int>(start, start.find('-')));
    queue.push(pair<string, int>(start, infsManDis(start, finish)));

    // 'i' will be used to get all adjacent
    // vertices of a vertex
    // list<string>::iterator i;
    // int count = 0;
    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        pair<string, int> cur = queue.top();
        //cout << "string:" << cur.first << " sum:" << cur.second << " queueSize:" << queue.size() << endl;
        queue.pop();

        // count += 1;
        vector<short int> pos_swaps = index[cur.first.find('-')];

        for (auto i = 0; i < pos_swaps.size(); i++)
        {
            auto temp_cur = visited.find(finish);
            if (temp_cur != visited.end())
            {
                break;
            }
            string swapped = cur.first;
            swap(swapped[swapped.find('-')], swapped[pos_swaps[i]]);

            if (visited.find(swapped) == visited.end())
            {
                visited.insert(pair<string, short int>(swapped, cur.first.find('-')));
                queue.push(pair<string, int>(swapped, infsManDis(swapped, finish)));
            }
        }
        //cout << endl;
    }
    // cout << "Count: " << count << endl;
    int nodes_count = 0;
    printPath(visited, index, finish, nodes_count);
    cout << "Total nodes: " << visited.size() << ", max depth is: " << nodes_count << endl;
}

int infsManDis(string cur, string finish)
{
    int sum = 0;
    for (int i = 0; i < cur.length(); i++)
    {
        int finIndex = finish.find(cur[i]);
        int m1 = i / 3;
        int m2 = finIndex / 3;
        int r1 = i % 3;
        int r2 = finIndex % 3;
        sum += abs(m1 - m2) + abs(r1 - r2);
    }
    // cout << "Cur: " << cur << " Finish: " << finish << " Sum: " << sum << endl;
    return sum;
}

void printPath(map<string, short int> &visited, vector<vector<short int>> &index, string cur, int &nodes_count)
{
    auto temp_cur = visited.find(cur);
    string swapped = cur;
    swap(swapped[swapped.find('-')], swapped[temp_cur->second]);

    if (temp_cur->second < 0)
    {
        printFormated(cur);
        return;
    }
    nodes_count++;
    printPath(visited, index, swapped, nodes_count);
    printFormated(cur);
}

void printFormated(string cur)
{
    for (auto i = 0; i < 3; i++)
    {
        for (auto j = 0; j < 3; j++)
        {
            cout << " " << cur[i * 3 + j];
        }
        cout << endl;
    }
    cout << endl;
}