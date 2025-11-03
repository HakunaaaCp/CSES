#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 501, INF = LONG_MAX;

struct Edge {
    int from, to, cap, flow, cost;
};

struct MCMF {//0-indexed
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[N];
    int p[N],inq[N];
    int d[N];
    int a[N];
    MCMF(int n) {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from,int to,int cap,int cost) {
        edges.push_back((Edge){from, to, cap, 0, cost});
        edges.push_back((Edge){to, from, 0, 0, -cost});
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    pair<int,int> Mincost(int s,int t) {//SPFA
        int tot_cost = 0;
        int tot_flow = 0;
        while(true) {
            for(int i = 0; i < n; i++) d[i] = INF;
            memset(inq, 0, sizeof(inq));
            d[s] = 0;
            inq[s] = 1;
            p[s] = 0;
            a[s] = INF;
            queue<int> Q;
            srand(time(NULL));
            Q.push(s);
            while(!Q.empty()) {
                int u = Q.front();
                Q.pop();
                inq[u] = 0;
                for(int i = 0; i < G[u].size(); i++) {
                    Edge& e = edges[G[u][i]];
                    if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                        d[e.to] = d[u] + e.cost;
                        p[e.to] = G[u][i];
                        a[e.to] = min(a[u], e.cap - e.flow);
                        if(!inq[e.to]) {
                            Q.push(e.to);
                            inq[e.to] = 1;
                        }
                    }
                }
            }
            if(d[t] == INF) break;
            tot_cost += (int)d[t] * a[t];
            tot_flow += a[t];
            int u = t;
            while(u != s) {
                edges[p[u]].flow += a[t];
                edges[p[u]^1].flow -= a[t];
                u = edges[p[u]].from;
            }
        }

        return {tot_cost,tot_flow};
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k; cin >> n >> m >> k;
    MCMF mcmf(n + 1);
    int s = 0, t = n;
    for(int i = 0; i < m; i++) {
        int a, b, r, c; cin >> a >> b >> r >> c;
        mcmf.AddEdge(a, b, r, c);
    }
    mcmf.AddEdge(0, 1, k, 0);
    auto [c, f] = mcmf.Mincost(s,t);
    cout << (f == k ? c : -1);
    return 0;
}