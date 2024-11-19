#include<iostream>
#include<vector>

using namespace std;

struct Graph{

    vector<vector<int>> adj_matrix;
    Vertex* Verteces;
    int n;
    
    Graph(int numVerteces){//Sets up a blank matrix of the appropriate dimensions, and creates the appropriate number of verteces.
        n=numVerteces;
        adj_matrix = vector<vector<int>>(n,vector<int>(n,0));
        Verteces = new Vertex[n];
        for(int i=0;i<n;i++){
            Verteces[i].ID=i;//Numbers each vertex.
        }
    }

    void AddEdge(int u,int v){//Adds the edge both in the matrix representation and in each vertex's information.
        adj_matrix[u][v]=1;
        Verteces[u].OutDegree++;
        Verteces[u].Neighbors.push_back(&Verteces[v]);
        Verteces[v].InDegree++;
    }

    void ResetEdges(){//Resets all of the edge data within the verteces to match the information contained within the matrix.
        for(int i=0;i<n;i++){
            Verteces[i].Reset();
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(adj_matrix[i][j]==1){
                    AddEdge(i,j);
                }
            }
        }
    }

    int DFSHelper(Vertex* w,int currentTime){//Allows each vertex to be unmarked when the search is completed.
        int val = DFS(w,currentTime);
        
        for(int i=0;i<n;i++){
            Verteces[i].DoneWithSearch();
        }
        return val;
    }

    int DFS(Vertex* w,int currentTime){//Depth-first-search babyyy
        w->StartTime=currentTime;
        currentTime++;
        w->visited=true;
        int n = w->Neighbors.size();
        Vertex* v;
        for(int i=0;i<n;i++){
            v=w->Neighbors[i];
            if(!v->visited){
                currentTime=DFS(v,currentTime);
                currentTime++;
            }
        }
        w->FinishTime=currentTime;
        w->complete=true;
        return currentTime; 
    }

    vector<vector<int>> findSCC(){
        vector<vector<int>> SCCs;
        
        Graph* transpose = new Graph(n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                transpose->adj_matrix[j][i] = adj_matrix[i][j];
            }
        }
        transpose->ResetEdges();

        return SCCs;
    }
};

struct Vertex{
    
    int StartTime;
    int FinishTime;
    bool visited = false;
    bool complete = false;
    int ID=0;
    int InDegree=0;
    int OutDegree=0;

    vector<Vertex*> Neighbors;
    
    void Reset(){
        StartTime=0;
        FinishTime=0;
        visited=false;
        complete=false;
        InDegree=0;
        OutDegree=0;
        Neighbors.clear();
    }

    void DoneWithSearch(){
        visited=false;
        complete=false;
    }

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
