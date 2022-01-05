#include <BearLibTerminal.h>
#include <iostream>

#include "gridgraph.h"
#include "astar.h"
#include "dfs.h"

using namespace std;


void draw(Grid& grid)
{
    terminal_clear();
    char symbol;
    for (int i = 0; i < grid.N; i++)
    {
       for (int j = 0; j < grid.M; j++)
       {
            node vert = grid.grid[i][j];
            if (vert.blocking) symbol = '#';
            else symbol = ' ';

            terminal_color(color_from_name("draker grey"));
            if (vert.cost > 9)
                terminal_bkcolor(color_from_name("lighter blue"));
            if (vert.cost > 19)
                terminal_bkcolor(color_from_name("light blue"));
            
            terminal_put(vert.x, vert.y, symbol);
       }
    }
    terminal_refresh();
}

int main()
{
    srand(time(0));
    char k;
    terminal_open();
    terminal_set("window: size=80x40");
    Grid grid(80, 40);
    Graph G(grid);
    bool found = false;
    int start = 0;
    start = G.verts[G.verts.size()-1].label;
    while (true)
    {
        if (terminal_has_input())
        {
            if ((k = terminal_read()) == TK_Q)
            {
                break;
            }
        }
        draw(grid);
        cout<<"Starting from: "<<start<<endl;
        AStar ast(G, start, 1);
        int i;
        cin>>i;
    }
    terminal_close();
    return 0;
}