#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <queue>
#include "Board.cpp"


using namespace std;

/********* Graph Type Declaration *****************
A graph is a vector where each element contains a vertex as well as a 
pointer to a linked list that includes all of its neighbors on the graph
*/

typedef uint32_t cboard; //compressed board as a single integer

typedef struct nodelist_header nodelist;

struct nodelist_header{  // simple linked list with the board as the data
  uint32_t vertex;
  int button; //buttin flipped to get from the vertex to this neighbor 
  nodelist* next;
};

typedef struct Graph_header Graph;

struct Graph_header{
  vector<nodelist*> vertices;    // adjacency list implementation of a graph
  map<uint32_t,uint32_t> vNums;   // map between a board(key) and its vertex number
};

// Basic Graph Functions

//creates a new graph with the single given node v 
Graph* graph_new(uint32_t v){
    Graph* g = new Graph;
    nodelist* fnode = new nodelist;

    fnode->next = NULL;
    fnode->vertex = v;
    fnode->button = -1;

    (g->vertices).push_back(fnode);
    (g->vNums).insert( pair<uint32_t,uint32_t>(v,0) );

    return g;
}

//adds a lone vertex to the graph
void add_vertex(Graph* g, uint32_t v){  
    nodelist* node = new nodelist;

    node->next = NULL;
    node->vertex = v;
    node->button = -1;

    (g->vertices).push_back(node);
    (g->vNums).insert( pair<uint32_t,uint32_t>(v, (uint32_t)(g->vertices).size() -1));
}

//checks if there is an edge between two vertices
bool has_edge(Graph* g, uint32_t v, uint32_t w){
    uint32_t vnum = (g->vNums)[v];
    for(nodelist* p = ((g->vertices)[vnum])->next; p != NULL; p = p->next){
        if(p->vertex == w) return true;
    }
    return false;
} 

//adds edge between two existing vertices
void add_edge(Graph* g, uint32_t v, uint32_t w, int button){ 
    uint32_t vnum = (g->vNums)[v];

    nodelist* wnode = new nodelist;
    
    wnode->vertex = w;
    wnode->button = button;
    wnode->next = ((g->vertices)[vnum])->next;
    ((g->vertices)[vnum])->next = wnode;

    uint32_t wnum = (g->vNums)[w];

    nodelist* vnode = new nodelist;
    
    vnode->vertex = v;
    vnode->button = button;
    vnode->next = ((g->vertices)[wnum])->next;
    ((g->vertices)[wnum])->next = vnode;
}

int numOnes(cboard b){
    int count = 0;
    for(int i = 0; i < 25; i++){
        if(((b >> i) & 1) == 1) count++;
    }
    return count;
}

struct boardMove{
    cboard board;
    int move;
};

struct CompareNumOn{ 
    bool operator()(boardMove b1, boardMove b2)
    { 
        return numOnes(b1.board) > numOnes(b2.board); 
    } 
};



//Expands the graph by adding the neigbors of the given vertex
void add_neighbors(Graph* g, cboard Board, bool* flipped){ 
    priority_queue<boardMove, vector<boardMove>, CompareNumOn> pq;
    for(int i = 0; i < 25; i++){
        if(flipped[i] != 1){
          boardMove bm;
          cboard b = make_move(Board, i);
          bm.board = b;
          bm.move = i;
          pq.push(bm);       
        } 
    }

    while(!pq.empty()){
        boardMove bm = pq.top();
        pq.pop();
        if((g->vNums).count(bm.board) != 1){
            add_vertex(g, bm.board);
            add_edge(g,Board, bm.board,bm.move);
        }
        else{
            add_edge(g,Board, bm.board,bm.move);
        }    
    }
}

int flipped_button(Graph* g, cboard v, cboard w){
    uint32_t vnum = (g->vNums)[v];
    for(nodelist* p = ((g->vertices)[vnum])->next; p != NULL; p = p->next){
        if(p->vertex == w) return p->button;
    }
    return -1;
}

void delete_nodelist(nodelist* n){ 
    while(n->next != NULL){
        nodelist* TMP = n->next;
        n->next = n->next->next;
        delete TMP;
    }
    delete n;
}

void delete_graph(Graph* g){
    for(int i = 0; i < (g->vertices).size(); i++){
        delete_nodelist((g->vertices)[i]);
    }
    delete g;
}



