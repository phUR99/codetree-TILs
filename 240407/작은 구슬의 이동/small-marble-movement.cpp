#include <iostream>
using namespace std;

int dx[4] = {0, 1, -1, 0};
int dy[4] = {1, 0, 0, -1};
int n, t, r, c;
char d;
bool inRange(int x, int y){
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

int GetDir(char a) {
    if(a == 'R')
        return 0;
    else if(a == 'D')
        return 1;
    else if(a == 'U')
        return 2;
    else
        return 3;
}


int main() {
    cin >> n >> t  >> r >> c >> d;
    //t %= 2 *(n);
    int dir = GetDir(d);    
    int delatx = dx[dir];
    int delaty = dy[dir];

    while(t--){
        if(inRange(r+delatx, c+delaty)){
            r += delatx;
            c += delaty;
        }
        else{
            delatx = -delatx;
            delaty = -delaty;            
        }
    }
    cout << r << ' ' << c;

    return 0;
}