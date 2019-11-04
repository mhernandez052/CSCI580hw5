#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <list>
#include <algorithm>

using namespace std;

void bfs(string start, string finsh, vector<vector<short int>> &index);
void printPath(map<string, short int> visited, string finish);

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
            string swapped = cur;
            swap(swapped[swapped.find('-')], swapped[pos_swaps[i]]);

            if (visited.find(swapped) == visited.end())
            {
                visited.insert(pair<string, short int>(swapped, cur.find('-')));
                queue.push_back(swapped);
            }
        }
        if (visited.find(finish) != visited.end()) {
            cout << "Found it <<<<<\n";
            break;
        }
    }
    printPath(visited, finish);
}

void printPath(map<string, short int> visited, string finish)
{
    // if ( == )
    // {
    //     return;
    // }
}