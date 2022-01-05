#ifndef DFS_H
#define DFS_H

#include <BearLibTerminal.h>
#include <vector>
#include "gridgraph.h"
using namespace std;

class DepthFirstSearch {
    public:
    std::vector<bool> visited;
    bool found;
    int examined;
    DepthFirstSearch(Graph& G, int from, int to)
    {
        examined = 0;
        visited.resize(G.V(), false);
        found = false;
        search(G, from, to);
        cout<<"Nodes Examined: "<<examined<<"\n";
    }
    void search(Graph& G, int from, int to)
    {
        if (found) return;
        terminal_color(color_from_name("red"));
        terminal_put(G.verts[from].x, G.verts[from].y, '%');
        terminal_refresh();
        cout<<from<<" -> ";
        if (from == to)
        {
            found = true;
            return;
        }
        examined++;
        visited[from] = true;
        for (auto u : G.adjList[from])
          if (!visited[u] && !G.verts[u].blocking)
           search(G, u, to);
    }
};


#endif