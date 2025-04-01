#include <iostream>

using namespace std;
/*
Hàm sentinelLinearSearch
*/
int sentinelLinearSearch(int* a,int n,int k)
{
    if (a[n - 1] == k)//Kiểm tra phần tử cuối
        return n - 1;//Trả về index

    int last = a[n - 1];//Lưu giá trị của phần tử cuối
    a[n - 1] = k;//Đặt lính
    int i = 0;
    while (a[i] != k)//Duyệt
    {
        i++;
    }
    a[n - 1] = last;//Trả về mảng ban đầu

    if (i < n - 1)//Tìm được phần tử thỏa
        return i;//Trả về index
    return -1;//Không tìm được phần tử thỏa
}

int main()
{   
    int n, k;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n ;i++)
    {
        cin >> a[i];
    }
    cin >> k;
    cout << sentinelLinearSearch(a,n,k) << endl;
    return 0;
}