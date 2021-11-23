#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
const int N = 10010;
typedef long long ll;
typedef pair<ll, int> pli;
ll lt[N];
int pre[N];
int nex[N];
set<pli> st;
void del(ll pf ,int ps){
    //删除左右结点，更改中间结点值
    pre[ps]--;
    nex[ps]++;
    st.erase(pli(lt[ps - 1], ps - 1));
    st.erase(pli(lt[ps + 1], ps + 1));
    lt[ps] = lt[ps - 1] + lt[ps + 1] - pf;
    st.erase(pli(pf, ps));
    st.emplace(pli(lt[ps], ps));
}


int main(){

    //用一个双链表和一个小根堆，不断选择堆顶元素，对链表和堆进行修改
    //因为要不断地定向查找，删除，添加元素，使用数组双链表，set堆
    int n, K;
    cin >> n >> K;
    for (int i = 0; i < n;i++){
        cin >> lt[i];
        pre[i] = i - 1;
        nex[i] = i + 1;
    }

    

    for (int i = n-1; i>0 ;i--){
        lt[i] -= lt[i - 1];
        st.emplace(lt[i], i);
    }
    lt[0] = INT_MAX;
    st.emplace(lt[0], 0);
    lt[n] = INT_MAX;
    st.emplace(lt[n], n);

    int ans = 0;
    for (int i = 0; i < K;i++){
        auto p = st.begin();
        ans += p->first;
        del(p->first,p->second);
    }
    cout<< ans;
    system("pause");
}
