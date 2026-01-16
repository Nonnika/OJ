#include <iostream>

#define NUM_MAX 10

using namespace std;

struct Graph{
    int arcs[NUM_MAX][NUM_MAX]={0};
    int vexnum;
    int arcnum; 
};

struct arc{
    int vex;
    int lowcost;
} closedge[NUM_MAX];


int findMin(int vexnum){
    int index = -1;
    int mini = -1;
    for(int i=0;i<vexnum;i++){
        if(closedge[i].lowcost>0){
            if(mini==-1||mini>closedge[i].lowcost){
                index = i;
                mini = closedge[i].lowcost;
            }
        }
    }
    return index;
}

void prime(Graph g,int vex){
     for(int i=0;i<g.vexnum;i++){
        if(i!=vex){
            closedge[i] = {vex,g.arcs[vex][i]};
        }
     }
     closedge[vex].lowcost=0;
     for(int i =1;i<g.vexnum;i++){
        int k = findMin(g.vexnum);
        int u0 = closedge[k].vex;
        int v0 = k;
        cout<<u0<<v0<<endl;
        closedge[k].lowcost = 0;
        for(int j =0;j<g.vexnum;j++){
            if(g.arcs[k][j]<closedge[j].lowcost){
                closedge[j]={k,g.arcs[k][j]};
            }
        }
     }
}

int main(void){
    Graph g;
    cin>>g.vexnum>>g.arcnum;

    for(int i=0;i<g.arcnum;i++){
        int vex1,vex2,power;
        cin>>vex1>>vex2>>power;

        g.arcs[vex1][vex2]=power;
        g.arcs[vex2][vex1]=power;
    }

    prime(g, 0);

    return 0;
}