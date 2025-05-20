#include <iostream>

using namespace std;

/*
Hàm tính giai thừa
*/

int factorial(int n)
{   
    //Cần 3 trường hợp ban đầu để đảm bảo tính đúng đắn trong việc tính toán
    if (n == 0) return 1;
    // if (n == 1) return 1;

    //n! = n * (n - 1)!
    return n * factorial(n - 1);
}

int main()
{   
    int n;
    cin >> n;
    cout << factorial(n);
    return 0;
}