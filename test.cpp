#include <bits/stdc++.h>

#define MAX_N 20001

using namespace std;

int n, m;

struct Node {
    vector <int> adj;
    vector <int> rev_adj;
};

Node g[MAX_N];
stack <int> S;
bool visited[MAX_N];
int component[MAX_N];
vector <int> components[MAX_N];
int numComponents;
/*
Node* g;
stack <int> S;
bool* visited;
int* component;
vector<int>* components;
int numComponents;
*/
void dfs_1(int x) {
    visited[x] = true;
    for (int i = 0; i < g[x].adj.size(); i++) {
        if (!visited[g[x].adj[i]])
            dfs_1(g[x].adj[i]);
    }
    S.push(x);
}

void dfs_2(int x) {
    cout<<x<<" ";
//    printf("%d ", x);
    component[x] = numComponents;
    components[numComponents].push_back(x);
    visited[x] = true;
    for (int i = 0; i < g[x].rev_adj.size(); i++) {
        if (!visited[g[x].rev_adj[i]])
            dfs_2(g[x].rev_adj[i]);
    }
}
void Kosaraju() {
    for (int i = 0; i < n; i++)
        if (!visited[i]) dfs_1(i);

    for (int i = 0; i < n; i++)
        visited[i] = false;
    
    while (!S.empty()) {
        int v = S.top();
        S.pop();
        if (!visited[v]) {
            cout<<"Component "<<numComponents<<": ";
//            printf("Component %d: ", numComponents);
            dfs_2(v);
            numComponents++;
            cout<<endl;
//            printf("\n");
        }
    }
}

int main() {
    cin >> n >> m;
/*    g = new Node[n+1];
    visited = new bool[n+1];
    component = new int[n+1];
    components = new vector<int>[n+1];*/
    int a, b;
    for(int i=0;i<m;i++){
        cin >> a >> b;
        g[a].adj.push_back(b);
        g[b].rev_adj.push_back(a);
    }

    Kosaraju();
    
    cout<<"Total number of components: "<<numComponents<<endl;
//    printf("Total number of components: %d\n", numComponents);
    
    return 0;
}
