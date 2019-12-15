#include <iostream>
#include<time.h>
#include <algorithm>
using namespace std;
#define MAX 100

template<class Type>
int Partition(Type a[], int p, int r,int k) {
	int i = p-1, j = r + 1;
	Type x = k;//设置排序基准
	while (true){
		while (a[++i] < x && i < r);
		while (a[--j] > x);
		if (i >= j) {
			break;
		}
		swap(a[i], a[j]);//将左边不小于基准的与右边不大于基准的交换
	}
	return i;//返回基准在数组的下标值
}

template<class Type>
Type Select(Type a[], int p, int r, int k) {
	if (r - p < 75) {
		sort(a + p, a + r);
		return a[p + k - 1];
	}
	for (int i = 0; i <= (r - p - 4) / 5; i++) {
		sort(a + p + 5 * i, a + p + 5 * i + 4);//对每组进行排序找出找出中位数
		swap(a[p + i], a[p + 5 * i + 2]);//将每组的中位数放在数组前
		Type x = Select(a, p, p + (r - p - 4) / 5, (r - p - 4) / 10);//找出中位数中的中位数
		int l = Partition(a, p, r, x), j = l - p + 1;//将x作为基准来做排序，将大于x的放在右边，将小于x的放在左边，并返回x在数组中的下标
		if (k <= j) {
			return Select(a, p, l, k);//k<=j时那么说明要找的第几小的数下标在j之前，即左边
		}
		else {
			return Select(a, l + 1, r, k - j);//k>j时那么说明要找的第几小的数下标在j之后，即右边
		}
	}
}

int main()
{
	int k=5;
	int a[MAX];
	FILE* fp;
	fopen_s(&fp, "D:\\算法\\线性时间选择\\random.txt","w");
	srand(unsigned(time(NULL)));
	for (int i = 0; i < MAX; i++) {
		a[i] = rand();
		cout << a[i]<<ends;
		fprintf_s(fp, "%d ", a[i]);
		if ((i+1)% 30 == 0){
			cout << endl;
			fprintf_s(fp, "\n");
		}
	}
	cout << "\n-----------------------------------------\n";
	cout << "请输入要查找第几小的数：";
	cin >> k;
	int b = Select(a, 0, MAX-1, k);
	cout << "第" << k << "小的元素为" << b << endl;
	sort(a, a + MAX - 1);
	cout << "-----------------------------------------\n";
	cout << "排序后的结果为\n";
	for (int i = 0; i < MAX; i++) {
		cout << a[i] << ends;
		if ((i + 1) % 30 == 0) {
			cout << endl;
		}
	}
	return 0;
}