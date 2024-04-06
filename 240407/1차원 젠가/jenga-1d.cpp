#include <iostream>
#include <cstring>
using namespace std;
int board[105];
int tmp_board[105];

int n;

int main() {
    cin >> n;
    for (int i =1; i <=n; i++) cin >> board[i];
    int t = 2;
    while(t--){
        memset(tmp_board, 0, sizeof(tmp_board));
        int st, ed;
        cin >> st >> ed;
        int idx = n;
        int s;
        for (int i = 1; i <=n; i++){
            if (board[i] == 0) continue;
            s = i;
            break;
        }
        for (int i = s + st -1; i < s + ed; i++){
            board[i] = 0;
        }

        for (int i = n; i >=1; i--){
            if (board[i] == 0) continue;
            tmp_board[idx] = board[i];
            idx--;
        }
        for (int i = n; i >= 1; i--){
            board[i] = tmp_board[i];
        } 
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++){
        if(board[i]) cnt++;
    }
    cout << cnt << '\n';
    for (int i = 1; i <= n; i++){
        if(board[i]) cout << board[i] << '\n';
    }

    return 0;
}