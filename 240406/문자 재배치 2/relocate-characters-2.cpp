#include <iostream>
using namespace std;
char arr[55];
int n;

int main() {
    cin >> n;
    for(int i =0; i < n; i ++){
        cin >> arr[i];
    }
    for(int i =n-1; i>=0; i--){
        cout << arr[i] << ' ';
    }
    return 0;
}