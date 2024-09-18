#include <bits/stdc++.h>
#define fastio                       \
    ios_base::sync_with_stdio(NULL); \
    cin.tie(NULL);                   \
    cout.tie(NULL)
using namespace std;
vector<pair<int, int>> arr;
int n, m;
int board[25][25];
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

void makeShape(pair<int, int> st)
{
    int cnt = 0;
    int nx = st.first;
    int ny = st.second;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cnt %= 4;
            for (int r = 1; r <= i; r++)
            {
                nx = nx + dx[cnt];
                ny = ny + dy[cnt];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                    return;
                arr.push_back({nx, ny});
            }
            cnt++;
        }
    }
}
// R D L U
int returnDir(int dir)
{
    if (dir == 0)
        return 2;
    else if (dir == 1)
        return 1;
    else if (dir == 2)
        return 0;
    else
        return 3;
}
void fill()
{
    vector<int> cur;
    for (auto e : arr)
    {
        int x = e.first;
        int y = e.second;
        if (board[x][y] != 0)
            cur.push_back(board[x][y]);
    }
    memset(board, 0, sizeof(board));
    for (int i = 0; i < cur.size(); i++)
    {
        int x = arr[i].first;
        int y = arr[i].second;
        board[x][y] = cur[i];
    }
}
int find()
{
    int ret = 0;
    vector<pair<int, int>> now;
    int num = -1;
    for (auto e : arr)
    {
        int x = e.first;
        int y = e.second;

        if (num == -1)
        {
            now.push_back({x, y});
            num = board[x][y];
        }
        else
        {
            if (num != board[x][y])
            {
                if (now.size() > 3)
                {

                    for (auto i : now)
                    {
                        int xx = i.first;
                        int yy = i.second;
                        board[xx][yy] = 0;
                    }
                    ret += num * now.size();
                }
                now.clear();
                num = board[x][y];
            }
            now.push_back({x, y});
        }
    }
    if (now.size() >= 4)
    {
        for (auto i : now)
        {
            int xx = i.first;
            int yy = i.second;
        }
    }
    ret += num * now.size();
    return ret;
}
void copy()
{
    vector<int> nxt;
    int num = -1;
    int cnt = 0;

    for (auto e : arr)
    {
        int x = e.first;
        int y = e.second;
        if (board[x][y] == 0)
            break;
        if (num == -1)
        {
            num = board[x][y];
            cnt++;
            continue;
        }
        if (num != board[x][y])
        {
            nxt.push_back(cnt);
            nxt.push_back(num);
            cnt = 1;
            num = board[x][y];
        }
        else
            cnt++;
    }
    nxt.push_back(cnt);
    nxt.push_back(num);
    int l = min(arr.size(), nxt.size());
    for (int i = 0; i < l; i++)
    {
        int x = arr[i].first;
        int y = arr[i].second;
        int c = nxt[i];
        board[x][y] = c;
    }
}
void print()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

int main()
{
    fastio;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> board[i][j];
        }
    }
    int answer = 0;
    pair<int, int> st = {n / 2, n / 2};
    makeShape(st);
    for (int i = 0; i < m; i++)
    {
        int dir, movement;
        cin >> dir >> movement;
        dir = returnDir(dir);
        int nx = st.first;
        int ny = st.second;
        for (int j = 0; j < movement; j++)
        {
            nx = nx + dx[dir];
            ny = ny + dy[dir];
            answer += board[nx][ny];
            board[nx][ny] = 0;
        }

        fill();
        while (true)
        {
            int now = find();
            if (now == 0)
                break;
            answer += now;
            fill();
        }
        copy();
        // print();
    }
    cout << answer << '\n';

    return 0;
}