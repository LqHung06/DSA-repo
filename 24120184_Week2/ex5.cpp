#include <iostream>

using namespace std;

int MinimalLength(int *a,int n,int target)
{
    int left = 0, right = 0;//2 con trỏ
    bool check = false;//check xem có mảng con nào thỏa điều kiện nhỏ hơn hoặc bằng target hay không
    int min = INT_MAX;
    int sum = a[0];//Nhận giá trị ban đầu
    while (left <= right && right < n)
    {
        if (sum >= target)//Đk đề bài thõa
        {
            check = true;//Đã tìm được mảng con thỏa
            if (left == right)//Mảng con có độ dài nhỏ nhất => trả về 1
            {
                return right - left + 1;
            }
            int temp = right - left + 1;
            if (temp < min)//So sánh với mảng con trước để tìm mảng con có độ dài nhỏ nhất thỏa điều kiện
            {
                min = temp;
            }
            sum -= a[left];//Trừ bớt
            left++;//Giảm độ dài mảng con
        }
        else
        {
            right++;//Tăng độ dài mảng con
            if (right < n)//Tránh trường hợp right trỏ đến n
            {
                sum += a[right];//Cộng thêm vào
            }
        }
    }
    if (check)//Đã tìm được mảng con thỏa
        return min;//Trả về độ dài min
    return 0;//Không tìm được trả về 0
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
    cout << MinimalLength(a,n,target);
    return 0;
}