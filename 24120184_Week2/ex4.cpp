#include <iostream>

using namespace std;

int findLeastWeight(int* a,int n,int days)
{   
    int LeastWeight;
    for (int i = 1; i < n; i++) {
        LeastWeight = max(LeastWeight, a[i]); //Tìm kiện hàng có khối lượng lớn nhất
    }
    int i = 0;
    while (true)//Bắt đầu chạy vòng lặp
    {   
        int daytemp = 1;//Ngày đếm tạm nhằm thỏa điều kiện các kiện hạng đc chất lên đúng ngày
        int temp = 0, j = 0;
        while (j < n)//Duyệt qua tất cả kiện hàng
        {
            temp += a[j];//Khối lượng tạm thời dùng để so sánh có vượt mức khối lượng tối thiểu hay không
            if (temp > LeastWeight)//Nếu vượt quá
            {   
                daytemp++;//+ thêm ngày
                temp = 0;//Trà về khối lượng ban đầu , tiếp tục so sánh
                j--;//Kiện hàng chưa được vận chuyển do vượt quá khối lượng cho phép
            }
            j++;
            if (daytemp > days)//Vượt quá số ngày quy định
            {
                break;//Thoát vòng lặp để kiểm tra các trường hợp khác
            }
        }
        if (daytemp == days && temp != 0)//Điều kiện ngày đã thõa, 
                                            //temp != nhằm đảm bảo kiện hàng ngày cuối vẫn không vượt quá mức khối lương cho phé
            return LeastWeight;//Trả về khối lượng tối thiểu
        if (daytemp < days)
            break;
        LeastWeight++;//Tăng lên để duyệt tìm kiếm khối lượng cần thiết
    }
    return -1;//Không tìm đc khối lượng tối thiểu thỏa các điều kiện
}

int main()
{
    int n, days;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n ;i++)
    {
        cin >> a[i];
    }
    cin >> days;
    cout << findLeastWeight(a,n,days);
    return 0;
}