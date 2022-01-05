#ifndef GRIDGRAPH_H
#define GRIDGRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

//for grid representation
struct node {
    int label;
    int x, y;
    bool blocking;
    int cost;
    node(int X, int Y, int L, int C, bool B) : x(X), y(Y), label(L), cost(C), blocking(B) { }
    node(int X, int Y, int L) : x(X), y(Y), label(L) { }
    node(int X, int Y) : x(X), y(Y), label(0) { }
    node() : x(0), y(0), label(0) { }
};


class Grid {
    public:
    vector<vector<node> > grid;
    int M;
    int N;
    Grid(int m, int n)
    {
        M = m;
        N = n;
        grid.resize(N,vector<node>(M));
        int _node = 0;
        for (int i = 0; i < N; i++) {
           for (int j = 0; j < M; j++) {
                grid[i][j] = node(j, i, _node++); //assign x, y, and label to graph
                
                if (rand() % 100 > 90)
                   grid[i][j].blocking = true; //place a wall

                grid[i][j].cost = ((rand() % 100) > 65) ? 20 : 10; 
           }
        }
    }
};

//for graph representation
struct Edge {
    int from;
    int to;
    Edge(int f, int t) : from(f), to(t) { }
    Edge() { from = 0; to = 0; }
};

class Graph {
    public:
    std::map<int, set<int> > adjList;
    std::map<int, node> verts;

    Graph(Grid& gridRep)
    {
        int m = gridRep.M * gridRep.N;
        for (int i = 0; i < m; i++)
        {
            adjList[i] = std::set<int>();
        }
        
        std::vector<node> dirs = { node{-1, 0}, node{1, 0}, node{0, 1}, node{0, -1} };
        for (int i =  0; i < gridRep.N; i++)
        {
          for (int j = 0; j < gridRep.M; j++)
          {
              for (auto d : dirs)
              {
                  verts[gridRep.grid[i][j].label] = node(j, i, gridRep.grid[i][j].label, gridRep.grid[i][j].cost, gridRep.grid[i][j].blocking);
                  node gridPos(d.x + j, d.y + i);
                  if (gridPos.x >= 0 && gridPos.x < gridRep.M && gridPos.y >= 0 && gridPos.y < gridRep.N)
                  {
                      adjList[gridRep.grid[i][j].label].insert(gridRep.grid[gridPos.y][gridPos.x].label);
                  }
              }
          }
        }
    }
    void addEdge(int f, int t)
    {
        adjList[f].insert(t);
        adjList[t].insert(f);
    }
    void showGraph()
    {
        for (auto vert : adjList) {
            cout<<vert.first<<": ";
            for (auto n : vert.second)
            {
                cout<<n<<" ";
            }
            cout<<endl;
        }     
    }
    int V()
    {
        return adjList.size();
    }
};


#endif