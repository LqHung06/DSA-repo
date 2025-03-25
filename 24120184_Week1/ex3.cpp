#include <iostream>

using namespace std;

/*
Hàm tạo và in ra chuỗi nhị phân có độ dài n lần lượt theo thứ tự tăng dần
*/

void generateBinaryStrings(int n, string str)
{   
    //Điều kiện để dừng
    if (n == 0) 
    {
        cout << str << endl;
        return;
    }
    //Các chuỗi có n phần tử được tạo chuỗi có n - 1 phần tử + '0' , và + '1'
    /*
    VD: n = 2 => chuỗi có độ dài 1 + '0' và + '1'
        n = 1 => chuỗi có độ dài 0 + '0' và '1'
        Tại chuỗi bằng không thì trả về 2 (0 và 1)
        Tương ứng chuỗi 0 có độ dài 1 lần lượt thêm 0 và 1: 00 và 01
        Tương ứng chuỗi 1 có độ dài 1 lần lượt thêm 0 và 1: 10 và 11
        => Chuỗi có 2 phần tử: 00 01 10 11
    */
    generateBinaryStrings(n - 1, str + '0');
    generateBinaryStrings(n - 1, str + '1');
}

int main()
{
    int n;
    cin >> n;
    //Khởi tạo chuỗi rỗng
    generateBinaryStrings(n,"");
}