// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


using namespace std;
const int maxn = 210;
struct line{
	//line维护一条与y轴平行的线段，此线段方程为X=x1，长度是y2-y1
	double x1, y1, y2;
	int flag;
	line(double x_1=0, double y_1=0, double y_2=0, int _flag=0) {
		x1 = x_1, y1 = y_1, y2 = y_2, flag=_flag;
	}
	//对x进行排序，使得在线段树叶节点中，线段与其在坐标系中的排列顺序相同
	bool operator < (const line a) const {
		return x1 < a.x1;
	}
};
struct Node {
	//线段树的len，维护的是目前所到位置线段在y轴方向的总长度
	
	double ll, lr, len;
	int l, r;
	int flag;
};
line _data[310];
Node sum[1500];
double y[300];
void build(int l, int r, int num) {
	//l，r表示当前区间维护的是y[l-r]
	//线段树lr，ll表示目前区间所维护的线段开始和结束的端点，用来后期update确定区间用
	//有人通过binarysearch在区间先查找目前线段左右端点在y的哪个下标（i，j）然后update时用i，j就行
	//那样就不用维护ll和lr
	sum[num].l = l, sum[num].r = r;
	sum[num].ll = y[l], sum[num].lr = y[r];
	sum[num].flag = 0; sum[num].len = 0;
	if (l + 1 == r)return;
	int mid = (l + r) >> 1;
	build(l, mid, num << 1);
	//mid不可以加一，不然[mid, mid+1]这个区间就会被漏掉
	build(mid, r, num << 1 | 1);
}
void len(int num) {
	//前提：必然存在flag>=0
	//flag>0，则确定现在扫描线在某些矩形之间，所以现在线段的长度就是线段上端点（lr）减去下端点（ll）
	//不会出现因为出现某两个矩形的左上端点横坐标相同而出现缺漏，因为这种情况本来就是分为两步去计算，今晚就卡在这里很久
	//由于进入一个矩形时（设端点为i，j），则i<=sum[ALL].ll, sum[ALL].lr<=j，这个区间所有flag+1
	//出矩阵时i<=sum[ALL].ll, sum[ALL]<=j，flag-1
	//所以当flag为0时，则必定表示当前扫描线没有穿过一个矩形，此时如果区间l和r相连，则y[i-j]区间内必定没有线段，所以len=0；
	//如果ij不相邻，则该区间的线段长度就由[i,j]之间所有子区间的线段长度之和（flag==0只能确定[i,i+1]之间没有线段）
	if (sum[num].flag > 0) {
		sum[num].len = sum[num].lr - sum[num].ll;
		return;
	}
	if (sum[num].l + 1 == sum[num].r) {
		sum[num].len = 0;
	}
	else {
		sum[num].len = sum[num << 1].len + sum[num << 1 | 1].len;
	}
}
void update(line a, int num) {
	//必定刚好存在一个区间，使得该区间左右端点与新增线段端点相同
	if (a.y1 == sum[num].ll&&a.y2 == sum[num].lr) {
		sum[num].flag += a.flag;
		len(num);
		return;
	}
	if (a.y2<=sum[num<<1].lr)//新增线段完全落在左子树所维护的区间
		update(a, num << 1);
	else if (a.y1>=sum[num<<1|1].ll)//新增线段完全落在右子树所维护的区间
		update(a, num << 1 | 1);
	else {
		//左右区间都有部分线段，所以要把线段拆成[y1,leftson.lr]和[rightson.ll,y2]两个区间，然后维护左右区间
		//其中，leftson.lr==rightson.ll，这与build时右子树mid不加一有关
		line tmp = a;
		tmp.y2 = sum[num << 1].lr;
		update(tmp, num << 1);
		tmp = a;
		tmp.y1 = sum[num << 1|1].ll;
		update(tmp, num << 1|1);
	}
	len(num);
}
int main()
{
	double a, b, c, d, ans;
	int n, t=1;
	while (~scanf("%d", &n)&&n) {
		for (int i = 1; i <= n; i++) {
			scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
			_data[i] = line(a, b, d, 1);
			_data[i + n] = line(c, b, d, -1);
			y[i] = b, y[i + n] = d;
		}
		sort(y + 1, y + 1 + 2*n);
		sort(_data + 1, _data + 2*n + 1);
		build(1, n * 2, 1);
		update(_data[1], 1);
		ans = 0;
		for (int i = 2; i <= n * 2; i++) {
			ans += sum[1].len*(_data[i].x1 - _data[i - 1].x1);
			update(_data[i], 1);
		}
		printf("Test case #%d\nTotal explored area: %.2f\n\n", t++, ans);
	}
    return 0;
}