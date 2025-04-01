#include <iostream>
#include <algorithm>

using namespace std;

void TheTriplets(int *a,int n)
{   
    sort(a,a + n);//Sắp xếp thành mảng tăng
    bool check = false;
    for (int i = 0; i < n - 2;i++)//Duyệt qua từng phần tử
    {   
        if (i > 0 && a[i] == a[i - 1]) continue;//Bỏ qua trường hợp bị trùng lặp
        int temp = -a[i];
        int j = i + 1 , z = n - 1;//Khai báo lần lượt 2 con trỏ
        while (j < z)//Điều kiện chạy vòng lặp
        {
            if (a[j] + a[z] == temp)//Tìm được
            {   
                check = true;
                cout << a[i] << " " << a[j] << " " << a[z] << endl;//Xuất kết quả
            }
            if (a[j] + a[z] > temp)
            {
                z--;//Giảm để tìm phần tử phù hợp khi tổng 2 phần tử lớn hơn targer(tính chất mảng tăng)
            }
            else
            {
                j++;//Tăng để tìm phần tử phù hợp
            }
        }
    }
    if (!check)
        cout << "Không có bộ ba nào thõa mãn";
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
    TheTriplets(a,n);
    return 0;
}