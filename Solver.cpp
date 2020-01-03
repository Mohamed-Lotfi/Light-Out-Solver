#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <bitset>
#include <stack>
#include <set>
#include "ExpandableGraph.cpp"

using namespace std;

//Solver that runs DFS and constructs the graph as it does so

typedef uint32_t cboard; //compressed board as a single integer

void ConstructiveDFS(cboard Board, stack<int> *Solution){
    Graph* graph = graph_new(Board);

    stack<cboard> moveStack;
    moveStack.push(Board);

    
    bool flipped[25];

    map<cboard,cboard> seen; //key = board, entry = board it was visited from
    seen.insert(pair<uint32_t,uint32_t>(Board, Board));

    while(!moveStack.empty()){
        cboard v = moveStack.top();
        moveStack.pop();
        
        for (int i = 0; i < 25; i++){
            flipped[i] = 0;
        }

        cboard iterator = v;
        int f_button = flipped_button(graph,iterator,seen[iterator]);
        while (f_button >= 0) {
            flipped[f_button] = 1;
            iterator = seen[iterator];
            f_button = flipped_button(graph,iterator,seen[iterator]);
        }



        uint32_t vnum = (graph->vNums)[v];
        add_neighbors(graph, v, flipped);

        for(nodelist* p = ((graph->vertices)[vnum])->next; p != NULL; p = p->next){
            //print_board(p->vertex);
            if(p->vertex == 0){ 
                flipped[p->button] = 1;
                goto done;  
            }
            //if board wasn't already seen, add it to the stack
            if(seen.count(p->vertex) != 1){   
                seen.insert( pair<uint32_t,uint32_t>(p->vertex, v) );
                moveStack.push(p->vertex);
            }
        }
    }
done:
    for(int i = 0; i < 25; i++){
        if(flipped[i] == 1) (*Solution).push(i);
    }
    //delete[] flipped;
    delete_graph(graph);
}



int main(){
    cboard Board = 2551084;
    stack<int>* Solution = new stack<int>;
    ConstructiveDFS(Board, Solution);

    while(!(*Solution).empty()){
        cout << (*Solution).top() << " ";
        (*Solution).pop();
    }
    cout << "" << endl;

    return 0;

}