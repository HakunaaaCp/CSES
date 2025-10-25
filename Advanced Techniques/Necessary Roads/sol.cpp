/**
 *    author:  Hakunaaa
 *    created: 25.10.2025 21:31:35
**/
#include <bits/stdc++.h>
using namespace std;

vector<array<int, 2>> bridges;

void IS_BRIDGE(int v,int to) {
    bridges.push_back({min(v, to), max(v, to)});
}

vector<vector<int>> adj;

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    bool parent_skipped = false;
    for (int to : adj[v]) {
        if (to == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                IS_BRIDGE(v, to);
        }
    }
}

void find_bridges(int n) {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
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
    find_bridges(n);
    cout << bridges.size() << '\n';
    for(auto [a, b] : bridges) {
        cout << a + 1 << ' ' << b + 1 << '\n';
    }
    return 0;
}