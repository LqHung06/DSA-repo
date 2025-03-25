#include <iostream>

using namespace std;

const int N = 8;
int board[N][N] = { 0 };
int solutions = 0;

bool CheckSave(int row,int col)
{   
    for (int i = 0; i < row ;i++)
    {   
        for (int i = 0 ; i < row ;i++)
        {
            if (board[i][col] == 1) //Kiểm tra đã có quân hậu nào nằm trên cột chưa nếu có trả về false
                return false;

            int k = (row - i);

            //Kiểm tra đường chéo trái, tổng quát các điểm của đường chéo trái có tọa độ [row - k][col - k] hay [i][col - k]
            //Với k tùy ý sao cho (col - k) >= 0 tức là vị trí của 1 phần tử đường chéo nằm trong bàn cờ
            if (col - k >= 0 && board[i][col - k] == 1) 
                return false;//Phát hiện quân hậu nằm trên đường chéo trái

            //Kiểm tra đường chéo phải, tổng quát các điểm của đường chéo trái có tọa độ [row - k][col + k] hay [i][col + k]
            //Với k tùy ý sao cho (col + k) < N tức là vị trí của 1 phần tử đường chéo nằm trong bàn cờ
            if (col + k < N && board[i][col + k] == 1)
                return false;//Phát hiện quân hậu nằm trên đường chéo phải
        }
        return true;//Đã kiểm tra an toàn
    }
    return true;
}

void SolveQueen(int row)
{   
    if (row == N)//Điều kiện thỏa
    {
        solutions++;//Tăng thêm số cách
        return;
    }

    for (int col = 0; col < N ;col++) //Duyệt qua từng cột của hàng
    {
        if (CheckSave(row,col) == true)//Nếu kiểm tra an toàn
        {
            board[row][col] = 1;//Đặt vị trí hậu
            SolveQueen(row + 1);//Đệ quy cho đến khi row = N thì số cách đặt +1
            board[row][col] = 0;//Nếu bước sau không tìm được thì quay về xóa quân hậu vừa đặt để thử các vị trí khác
        }
    }
}

int main()
{
    SolveQueen(0);
    cout << solutions;
    return 0;
}