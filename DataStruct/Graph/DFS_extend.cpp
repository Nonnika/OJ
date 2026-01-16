#include<iostream>

const int max_1 = 10;

using namespace std;

struct Graph{
    int arcs[max_1][max_1]={0};
    int vexnum;
    int arcnum;
};

bool visited[max_1] = {false};
void DFS(Graph g,int vex){
    cout<<vex<<endl;
    visited[vex]=true;
    for(int i = 0;i<g.vexnum;i++){
        if(g.arcs[vex][i]&&visited[i]==false){
            DFS(g,i);
        }
    }
}


void fixDFS(Graph g){
    for(int i=0;i<g.vexnum;i++){
        if(!visited[i]){
            DFS(g,i);
        }
    }
}

int main(void){
    Graph g;
    g.vexnum = 0;
    g.arcnum = 0;

    cin>>g.vexnum>>g.arcnum;
    for(int i = 0;i<g.arcnum;i++){
        int vex1,vex2;
        cin>>vex1>>vex2;
        g.arcs[vex1][vex2]=1;
        g.arcs[vex2][vex1]=1;
    }

    DFS(g,0);
    fixDFS(g);
    return 0;
}