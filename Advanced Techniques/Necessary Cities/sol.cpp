/**
 *    author:  Hakunaaa
 *    created: 25.10.2025 21:31:35
**/
#include <bits/stdc++.h>
using namespace std;

unordered_set<int> ans;

int n; // number of nodes
vector<vector<int>> adj; // adjacency list of graph

void IS_CUTPOINT(int v) {
    ans.insert(v);
}

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children=0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p!=-1)
                IS_CUTPOINT(v);
            ++children;
        }
    }
    if(p == -1 && children > 1)
        IS_CUTPOINT(v);
}

void find_cutpoints(int n) {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs (i);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m; cin >> n >> m;
    adj.resize(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a -= 1, b -= 1;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    find_cutpoints(n);
    cout << ans.size() << '\n';
    for(int el : ans) cout << el + 1 << ' ';
    return 0;
}