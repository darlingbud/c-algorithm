#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
int a[300010];
int b[300010];
int main(){
    int n, m;
    cin >> n;
    cin >> m;
    for (int i = 0; i < n;i++)
        cin >> a[i];
    for (int i = 0; i < m;i++)
        cin >> b[i];
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;
    sort(b, b + m);
    int i = 0,j = 0;
    while(j<m ){
        //Get 操作
        if(b[j]==i ){
            cout << right.top() << endl;
            left.push(right.top());
            right.pop();
            j++;
        }
        if(b[j]>i){
            if(left.empty()||a[i]>left.top()){
                right.push(a[i]);
            }
            else{
                left.push(a[i]);
                right.push(left.top());
                left.pop();
            }
            i++;
        }
        cout << i << j << endl;
    }
    return 0;
}