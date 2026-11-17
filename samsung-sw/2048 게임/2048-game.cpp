#include <iostream>
#include <vector>
using namespace std;
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 1};
// 
int n;
vector<vector<int>> mp;
// 
void input();
vector<vector<int>> rotate(vector<vector<int>> t_mp, int cnt);
void solve();

vector<int> merge(vector<int> tmp)
{
    vector<int> ret, t_mp;
    for (auto i : tmp) if(i) t_mp.push_back(i);
    tmp = t_mp;

    int i = 0;
    while (i < tmp.size())
    {
        if(i != tmp.size() - 1 && tmp[i] == tmp[i+1])
        {
            ret.push_back(tmp[i]*2);
            i+=2;
        }
        else
        {
            ret.push_back(tmp[i]);
            i++;
        }
    }
    while (ret.size() < n) ret.push_back(0);
    return ret;
}
// 
vector<vector<int>> rotate(vector<vector<int>> t_mp, int cnt)
{
    vector<vector<int>> ret;
    int r = n;
    int c = n;
    cnt %= 4;
    ret.resize(r, vector<int>(c, -1));
    while(cnt--)
    {
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                ret[i][j] = t_mp[n-1-j][i];
            }
        }
        t_mp = ret;
    }
    ret = t_mp;    
    return ret;
}
void input()
{
    cin >> n;
    mp.resize(n, vector<int>(n, 0));
    for (auto &i : mp) for (auto &j : i) cin >> j;
}

void solve()
{
    int p = 1 << 10;
    int res = 0;
    while (p--)
    {
        int pp = p;
        vector<vector<int>> tmp;
        tmp = mp;
        for (int i = 0; i < 5; i++)
        {
            int dir = pp % 4;
            pp /= 4;
            tmp = rotate(tmp, 4 - dir);
            for (int i = 0; i < n; i++)
            {            
                vector<int> row = merge(tmp[i]);
                for (int j = 0; j < n; j++) tmp[i][j] = row[j];
            }
            tmp = rotate(tmp, dir);
        }
        for (auto i : tmp) for (auto j : i) res = max(res, j);
    }
    cout << res;
}

int main() {
    input();
    solve();
    return 0;
}