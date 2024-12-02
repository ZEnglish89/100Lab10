#include<iostream>
#include<vector>
#include<stack>

#define MAX_N 20001//This was recommended to me online, when I had the issues with dynamic allocation(see line 81). It's an arbitrary value.

using namespace std;

struct Node {
    vector<int> Adjacent;
    vector<int> ReverseAdjacent;
};

/*
Node* g;
stack<int> S;
bool* visited;
int* component;
vector<int>* components;
int numComponents;
*/

Node g[MAX_N];
stack <int> S;
bool visited[MAX_N];
vector <int> components[MAX_N];
int numComponents;

void DFS(int x){
    visited[x]=true;
    for(int i=0;i<g[x].Adjacent.size();i++){
        if(!visited[g[x].Adjacent[i]]){
            DFS(g[x].Adjacent[i]);
        }
    }
    S.push(x);//Stack it in order of endtime.
}

void SpecialDFS(int x){
    components[numComponents].push_back(x);
    visited[x]=true;
    for(int i=0;i<g[x].ReverseAdjacent.size();i++){
        if(!visited[g[x].ReverseAdjacent[i]]){
            SpecialDFS(g[x].ReverseAdjacent[i]);
        }
    }
}

void Kosaraju(int n){
    for(int i=0;i<n;i++){
        if(!visited[i]){
            DFS(i);
        }
    }//First round of searches, stacking up the elements.
    for(int i=0;i<n;i++){
        visited[i]=false;
    }//resetting the bools to search again.
    while(!S.empty()){
        int v = S.top();
        S.pop();
        if(!visited[v]){
            SpecialDFS(v);
            numComponents++;//holding onto this because it's used in the second search.
        }
    }//Second round of searches, in the order the elements were stacked.
}

int main(){
    int n;
    int m;

    cin>>n;
    cin>>m;

/*
    g = new Node[n+1];
    visited = new bool[n+1];
    component = new int[n];
    components = new vector<int>[n];
*/
//I really wanted to avoid having to use pre-allocated global variables, but seemingly no matter what I did it just wouldn't work.
//The most interesting problem is that my dynamically-allocated version wasn't deterministic. It would sometimes be correct and
//sometimes be incorrect, even if run back-to-back with the same inputs.

    int u;
    int v;
    for(int i=0;i<m;i++){
        cin>>u;
        cin>>v;
        g[u].Adjacent.push_back(v);
        g[v].ReverseAdjacent.push_back(u);
    }//Setting up the graph based on inputs.

    Kosaraju(n);

    int ID[n];

    for(int i=0;i<numComponents;i++){//I'm assigning the IDs via something hashing-esque to avoid having to search components n times.
        int min=components[i][0];
        for(int j=0;j<components[i].size();j++){
            if(components[i][j]<min){
                min=components[i][j];//Finding the minimum within each SCC, because they aren't automatically sorted.
            }
        }
        for(int j=0;j<components[i].size();j++){
            ID[components[i][j]]=min;//Assigning the ID for each element.
        }
    }
    for(int i=0;i<n;i++){
        cout<<ID[i]<<endl;
    }//And print!

    return 1;
}