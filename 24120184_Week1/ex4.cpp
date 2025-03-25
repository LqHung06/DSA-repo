#include <iostream>

using namespace std;

/*
Viết hàm số cách di chuyển n chiếc đĩa từ cộc A sang cộc C thông qua cộc trung gian B(Tháp Hà Nội)
*/

long long TowerOfHanoi(int n)
{   
    //Trường hợp ban đầu khi có 1 dĩa thì chỉ cần 1 cách
    if (n == 1) return 1;
    if (n == 0) return 0;
    //Để di chuyển n bằng cách 2 lần di chuyển n - 1 dĩa trước + thêm 1 bước di chuyển đĩa cuối
    //Di chuyển (n - 1) đĩa từ A sang B, sau đó di chuyển đĩa cuối , di chuyển (n - 1) đĩa từ B sang C
    return 2*TowerOfHanoi(n - 1) + 1;
}

int main()
{   
    int n;
    cin >> n;
    cout << TowerOfHanoi(n);
    return 0;
}