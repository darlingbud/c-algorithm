#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct line
{
    int x;
    int y1, y2, flag;
    };
    struct node
    {
        int l=0,r=0 ,flag=0, len=0;
        node * lchild = nullptr;
        node * rchild = nullptr;
        node(int l,int r):l(l),r(r){};
    }; 
    node* root;
    vector<int> Y;
    vector<line> edge;

    static bool cmp(line& l1,line & l2){
        if(l1.x<l2.x)
            return true;
        if(l1.x==l2.x)
            if(l1.y1<l2.y1)
                return true;
        if(l1.x==l2.x&&l1.y1==l2.y1)
            if(l1.flag<l2.flag)
                return true;
        return false;
        }

        void build(node *&p,int l,int r){
            p = new node(Y[l], Y[r]);
            if(l+1==r)
                return;
            int mid = (l + r) / 2;
            build(p->lchild, l, mid);
            build(p->rchild, mid, r);
        }
        void len(node *p){
            if(p->flag>0){
                p->len = p->r - p->l;
                return;
            }
            if(p->lchild==nullptr){
                p->len = 0;
            }
            else{
                p->len = p->lchild->len + p->rchild->len;
            }
        }
        
        void update(node *p, line e){
            if(p->l==e.y1&&p->r==e.y2){
                p->flag += e.flag;
                len(p);
                return;
            }
            if(e.y2<=p->lchild->r)
                update(p->lchild, e);
            else if(e.y1>=p->rchild->l)
                update(p->rchild, e);
            else{
                line tem = e;
                tem.y2 = p->lchild->r;
                update(p->lchild, tem);
                tem = e;
                tem.y1 = p->rchild->l;
                update(p->rchild, tem);
            }
            len(p);
        }
        
        

        int rectangleArea(vector<vector<int>> &rectangles)
        {
            int ans = 0;
            
            for (auto v : rectangles)
            {
                edge.push_back(line{v[0], v[1], v[3], 1});
                edge.push_back(line{v[2], v[1], v[3], -1});
                Y.push_back(v[1]);
                Y.push_back(v[3]);
            }
            sort(Y.begin(), Y.end());
            sort(edge.begin(), edge.end(), cmp);
            Y.erase(unique(Y.begin(), Y.end()), Y.end());
            build(root, 0, Y.size() - 1);
            update(root, edge[0]);
            for (int i = 1; i < edge.size();i++){
                ans += (edge[i].x - edge[i - 1].x) * root->len;
                update(root, edge[i]);
            }
            return ans;
    }


int main(){
    vector<vector<int>> recc{vector<int>{1, 1, 3, 3},
     vector<int>{3, 1, 4, 2}, vector<int>{3, 2, 4, 4},
     vector<int>{1, 3, 2, 4}, vector<int>{2, 3, 3, 4}};;
    rectangleArea(recc);
    system("pause");
}