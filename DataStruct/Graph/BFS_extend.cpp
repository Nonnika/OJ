#include <iostream>
#include <queue>

#define MAX_VEX 10

using  namespace std;

struct Graph{
    int arcs[MAX_VEX][MAX_VEX]={0};
    int vexnum,arcnum;
};


bool visited[MAX_VEX] = {false};

void BFS(Graph g,int vexnum);

void fixBDF(Graph g){
    for(int i=0;i<g.vexnum;i++){
        if(!visited[i]){
            BFS(g, i);
        }
    }
}

void BFS(Graph g,int vex){
    queue<int> vexs;
    cout<<vex<<endl;
    visited[vex] = true;
    for(int i =0;i<g.vexnum;i++){
        if(g.arcs[vex][i]==1&&visited[i]==false){
            vexs.push(i);
        }
    }
    
    while(vexs.empty()==false){
        int next = vexs.front();
        BFS(g,next);
        vexs.pop();
    }
}

int main(void){
    Graph g;
    g.arcnum = 0;
    g.vexnum = 0;
    cin>>g.vexnum>>g.arcnum;

    for(int i =0;i<g.arcnum;i++){
        int vex1,vex2;
        cin>>vex1>>vex2;
        g.arcs[vex1][vex2]=1;

    }

    BFS(g, 0);
    fixBDF(g);
    return 0;
}