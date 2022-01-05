#ifndef A_STAR_H
#define A_STAR_H

#include <BearLibTerminal.h>
#include <queue> //priority queue
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include "gridgraph.h"
using namespace std;

class AStar {
    public:
    std::map<int, int> camefrom;
    std::map<int, int> dist;
    std::priority_queue<pair<int,int>, vector<pair<int,int>>, std::greater<pair<int,int> > > pq;
    AStar(Graph& G, int from, int to)
    {
        search(G, from, to);
    }
    int heuristic(Graph& G, int u, int v)
    {
        node a = G.verts[u];
        node b = G.verts[v];
        int distx = abs(a.x - b.x);
        int disty = abs(a.y - b.y);
        return 5 * (distx + disty);
    }
    void search(Graph& G, int from, int to)
    {
        int examined = 0;
        bool found = false;
        dist[from] = 0;
        camefrom[from] = -1;
        pq.push(make_pair(0, from));
        while (!pq.empty())
        {
            int current = pq.top().second;
            pq.pop();
            if (current == to)
            {
                found = true;
                break;
            }
            
            for (auto adj : G.adjList[current])
            {
                examined++;
                if (!G.verts[adj].blocking)
                {
                    int new_cost = dist[current] + G.verts[adj].cost;
                    if (dist.find(adj) == dist.end() || new_cost < dist[adj])
                    {
                        dist[adj] = new_cost;
                        camefrom[adj] = current;
                        int priority = new_cost + heuristic(G, adj, to);
                        pq.push(make_pair(priority, adj));
                        terminal_bkcolor(color_from_name("darker grey"));
                        terminal_put(G.verts[current].x, G.verts[current].y, ' ');
                        terminal_refresh();
                    }
                }
            }
        }
        if (found)
        {
            showPath(G, from, to);
        }
    }

    void showPath(Graph& G, int from, int to)
    {

            std::vector<int> path;
            int crawl = to;
            while (crawl != from)
            {

                path.push_back(crawl);
                crawl = camefrom[crawl];
            }
            path.push_back(from);
            reverse(path.begin(), path.end());

            for (auto p : path)
            {
                terminal_color(color_from_name("green"));
                terminal_put(G.verts[p].x, G.verts[p].y, '*');
             cout<<p<<" -> ";
              terminal_refresh();
            }
            cout<<"Found!\n";
    }
};

#endif