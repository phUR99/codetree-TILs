#include <bits/stdc++.h>
#define fastio                       \
    ios_base::sync_with_stdio(NULL); \
    cin.tie(NULL);                   \
    cout.tie(NULL)
using namespace std;
vector<vector<pair<int, int>>> adj;
int Q;
int n, m;
int isValid[30005];
int rev[30005];
int dist[2005];
int destination[30005];

int st = 0;
void dijkstra()
{
    fill(dist, dist + n, 987654321);
    dist[st] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, st});
    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        int cost = cur.first;
        int dest = cur.second;
        if (dist[dest] < cost)
            continue;
        for (auto nxt : adj[dest])
        {
            int nxtCost = nxt.first;
            int nxtDest = nxt.second;
            if (dist[nxtDest] > nxtCost + dist[dest])
            {
                dist[nxtDest] = nxtCost + dist[dest];
                pq.push({dist[nxtDest], nxtDest});
            }
        }
    }
}
struct node
{
    int cost;
    int id;
    bool operator<(const node &a) const
    {
        if (a.cost == cost)
            return a.id < id;
        return cost < a.cost;
    }
};
priority_queue<node> pq;

int main()
{
    fastio;
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        int cmd;
        cin >> cmd;
        if (cmd == 100)
        {
            cin >> n >> m;
            adj.resize(n);
            for (int j = 0; j < m; j++)
            {
                int u, v, w;
                cin >> u >> v >> w;
                adj[u].push_back({w, v});
                adj[v].push_back({w, u});
            }
            dijkstra();
        }
        // 30000
        else if (cmd == 200)
        {
            int id, revenue, dest;
            cin >> id >> revenue >> dest;
            isValid[id] = true;
            rev[id] = revenue;
            destination[id] = dest;
            pq.push({revenue - dist[dest], id});
        }
        // 30000
        else if (cmd == 300)
        {
            int id;
            cin >> id;
            isValid[id] = false;
        }
        // 30000
        else if (cmd == 400)
        {
            int ret = -1;
            while (!pq.empty())
            {
                auto cur = pq.top();
                pq.pop();
                int cost = cur.cost;
                int id = cur.id;
                if (!isValid[id] || cost < 0)
                    continue;
                isValid[id] = false;
                ret = id;
                break;
            }
            cout << ret << '\n';
        }
        // 15
        else
        {
            int s;
            cin >> s;
            st = s;
            dijkstra();
            while (!pq.empty())
            {
                pq.pop();
            }
            for (int i = 1; i <= 30000; i++)
            {
                if (isValid[i])
                    pq.push({rev[i] - dist[destination[i]], i});
            }
        }
    }

    return 0;
}