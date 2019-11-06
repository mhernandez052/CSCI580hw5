#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <list>
#include <algorithm>

using namespace std;

void bfs(string start, string finsh, vector<vector<short int>> &index);
void printPath(map<string, short int> &visited, vector<vector<short int>> &index, string &start, string cur, int &nodes_count);
void printFormated(string cur);

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
}

void bfs(string start, string finish, vector<vector<short int>> &index)
{
    map<string, short int> visited;

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
    printPath(visited, index, start, finish, nodes_count);
    cout << "Total nodes: " << visited.size() << ", max depth is: " << nodes_count << endl;
}

void printPath(map<string, short int> &visited, vector<vector<short int>> &index, string &start, string cur, int &nodes_count)
{
    auto temp_cur = visited.find(cur);
    string swapped = cur;
    swap(swapped[swapped.find('-')], swapped[temp_cur->second]);

    if (cur == start)
    {
        printFormated(cur);
        return;
    }
    nodes_count++;
    printPath(visited, index, start, swapped, nodes_count);
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