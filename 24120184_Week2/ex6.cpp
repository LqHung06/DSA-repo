#include <iostream>

using namespace std;

bool check(int *a,int n,int target)
{
    int left = 0;
    int right = n - 1;
    //Khai báo 2 con trỏ
    while (left < right)//Điều kiện chạy vòng lặp
    {   
        if (a[left] + a[right] == target)//Trả về true khi gặp trường hợp thỏa mãn
            return true;
        if (a[left] + a[right] > target)
        {
            right--;//Giảm để tìm phần tử phù hợp khi tổng 2 phần tử lớn hơn targer(tính chất mảng tăng)
        }
        else
        {
            left++;//Tăng để tìm phần tử thích hợp
        }
    }
    return false;
}

int main()
{
    int n, target;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n ;i++)
    {
        cin >> a[i];
    }
    cin >> target;
    if (check(a,n,target) == true)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}