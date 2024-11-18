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
        Verteces[v].InDegree++;
        
    }
};

struct Vertex{
    int ID;
    int InDegree;
    int OutDegree;
    vector<Vertex*> Out;
};
int main(){
    int n;
    int nEdges;
    cin>>n;
    cin>>nEdges;
    Vertex* Verteces = new Vertex[n];
    for(int i=0;i<n;i++){
        Verteces[i].ID=i;
    }
    return 1;
}