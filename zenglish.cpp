#include<iostream>
#include<vector>
#include<stack>

using namespace std;

struct Node {
    vector<int> Adjacent;
    vector<int> ReverseAdjacent;
};

    Node* g;
    stack<int> S;
    bool* visited;
    int* component;
    vector<int>* components;
    int numComponents;

void dfs_1(int x){
    visited[x]=true;
    for(int i=0;i<g[x].Adjacent.size();i++){
        if(!visited[g[x].Adjacent[i]]){
            dfs_1(g[x].Adjacent[i]);
        }
    }
    S.push(x);
}

void dfs_2(int x){
    cout<<x<<" ";
    component[x] = numComponents;
    components[numComponents].push_back(x);
    visited[x]=true;
    for(int i=0;i<g[x].ReverseAdjacent.size();i++){
        if(!visited[g[x].ReverseAdjacent[i]]){
            dfs_2(g[x].ReverseAdjacent[i]);
        }
    }
}

void Kosaraju(int n){
    for(int i=0;i<n;i++){
        if(!visited[i]){
            dfs_1(i);
        }
    }
    for(int i=0;i<n;i++){
        visited[i]=false;
    }
    while(!S.empty()){
        int v = S.top();
        S.pop();
        if(!visited[v]){
            cout<<"Component "<<numComponents<<": ";
            dfs_2(v);
            numComponents++;
            cout<<endl;
        }
    }
}

int main(){
    int n;
    int m;

    cin>>n;
    cin>>m;

    g = new Node[n];
    stack<int> S;
    visited = new bool[n];
    component = new int[n];
    components = new vector<int>[n];

    int u;
    int v;
    for(int i=0;i<m;i++){
        cin>>u;
        cin>>v;
        g[u].Adjacent.push_back(v);
        g[v].ReverseAdjacent.push_back(u);
    }

    Kosaraju(n);

    int ID[n];

    for(int i=0;i<numComponents;i++){
        for(int j=0;j<components[i].size();j++){
            ID[components[i][j]] = components[i][0];
        }
    }
    for(int i=0;i<n;i++){
        cout<<ID[i]<<endl;
    }

    return 1;
}