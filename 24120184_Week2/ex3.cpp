#include <iostream>

using namespace std;

int findMinRotated(int* a,int n)
{
    int left = 0;//trỏ vị trí biên trái
    int right = n - 1;//trỏ vị trí biên phải
    int mid;
    while (left < right - 1)
    {
        mid = (left + right) / 2;//vị trí giữa

        if (a[mid] <= a[right])//Nếu ở vị trí giữa < vị trí phải
        {
            right = mid;//Xét tiếp tìm min từ left -> mid
        }
        else
        {
            left = mid;//Ngược lại, xét tìm min từ mid -> right
        }
    }
    //Vòng lặp kết thuc khi xét chỉ còn 2 phần tử
    if (a[left] <  a[right])//Chọn phần tử nhỏ hơn
        return a[left];
    return a[right];
}

int main()
{   
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n ;i++)
    {
        cin >> a[i];
    }
    cout << findMinRotated(a,n);
    return 0;
}