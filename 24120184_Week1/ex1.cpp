#include <iostream>

using namespace std;

/*
Hàm đệ quy tính số fibonacci thứ n
*/

int fibonacci(int n)
{   
    //Trường hợp cơ bản số fibonacci thứ 1 và thứ 2
    if (n == 0) return 0;
    if (n == 1) return 1;
    //Số fibonacci thứ n bằng tổng của số fibonacci thứ n - 1 + số fibonacci thứ n - 2
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/*
Hàm in n số fibonacci
*/

void print(int n)
{
    for (int i = 0; i < n ;i++)
    {
        cout << fibonacci(i) << " ";
    }
}

int main()
{   
    int n;
    cin >> n;
    print(n);
    return 0;
}