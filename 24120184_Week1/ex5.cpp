#include <iostream>

using namespace std;

bool CheckIsSorted(int a[],int n)
{   
    //Trường hợp mảng chỉ có 1 hoặc 0 phần tử thì trả về true
    if (n == 1 || n == 0) return true;

    //Kiểm tra phần tử thứ n có lớn hơn phần tử thứ n - 1 hay không 
    if (a[n - 1] >= a[n - 2])
    {   
        // Có => Trả về kết quả n - 1 phần tử trước có sắp xếp hay không
        // Đệ quy cho đến khi duyệt qua so sánh tất cả phần tử còn sót lại 1 phần tử thì trả về true
        return CheckIsSorted(a, n - 1);
    }
    else
    {
        // Không => trả về false
        return false;
    }
}

int main()
{
    int a[100];
    int n;
    cin >> n;
    for (int i = 0;i < n ;i++)
    {
        cin >> a[i];
    }
    if (CheckIsSorted(a,n) == true)
    {
        cout << "Is Sorted" << endl; 
    }
    else
    {
        cout << "Not Sorted" << endl;
    }
}