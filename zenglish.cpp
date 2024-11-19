#include<iostream>
#include<vector>

using namespace std;
struct Graph{
    vector<vector<int>> adj_matrix;
    Vertex* Verteces;
    
    Graph(int n){
        adj_matrix = vector<vector<int>>(n,vector<int>(n,0));
        Verteces = new Vertex[n];
        for(int i=0;i<n;i++){
            Verteces[i].ID=i;
        }
    }

    void AddEdge(int u,int v){
        adj_matrix[u][v]=1;
        Verteces[u].OutDegree++;
        Verteces[u].Neighbors.push_back(&Verteces[v]);
        Verteces[v].InDegree++;
        
    }
};

struct Vertex{
    bool visited = false;
    bool complete = false;
    int ID=0;
    int InDegree=0;
    int OutDegree=0;
    vector<Vertex*> Neighbors;
};

int main(){
    int n;
    int nEdges;
    cin>>n;
    cin>>nEdges;
    Graph* g = new Graph(n);//Creating the graph as a struct

    for(int i=0;i<n;i++){
        g->Verteces[i].ID=i;//Giving the verteces their IDs in order.
    }

    int u=0;
    int v=0;

    for(int i=0;i<nEdges;i++){//Assigning all of the edges
        cin>>u;
        cin>>v;
        g->AddEdge(u,v);
    }//At this point the graph is now fully set up.

    return 1;
}