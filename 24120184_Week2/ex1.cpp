#include <iostream>

using namespace std;
/*
Hàm linearSearch : tìm kiếm tuyển tính
*/
int linearSearch(int* a,int n,int k)
{
    for (int i = 0; i < n ;i++)//Duyệt lần lượt các phần tử
    {
        if (a[i] == k)//Tìm được phần tử có giá trị bằng k
            return i;//Trả về index của phần tử
    }
    return -1;//Không tìm được phần tử thỏa trong mảng
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
    cout << linearSearch(a,n,k) << endl;
    return 0;
}