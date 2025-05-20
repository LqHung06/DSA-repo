#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

const int p = 31;
const int m = 2000;

struct Company
{
    string name;
    string profit_tax;
    string address;
};

struct HashTable
{
    vector<Company> Company_Table;
    HashTable()
    {
        Company_Table.resize(2000);
    }
};

vector<Company> readCompanyList(string file_name)
{
    ifstream In(file_name);
    if (!In.is_open())
    {
        cout << "Không thể mở file input MST.txt" << endl;
        return {};
    }
    vector<Company> result;
    string companyInfo;
    getline(In,companyInfo);
    while (getline(In,companyInfo))
    {   
        Company c;
        string company_name, company_profit , company_address;
        int i = 0;
        while (companyInfo[i] != '|')
        {   
            company_name.push_back(companyInfo[i]);
            i++;
        }
        i++;
        c.name = company_name;
        while (companyInfo[i] != '|')
        {
            company_profit.push_back(companyInfo[i]);
            i++;
        }
        c.profit_tax = company_profit;
        i++;
        while (companyInfo[i] != '|' && i < companyInfo.size())
        {
            company_address.push_back(companyInfo[i]);
            i++;
        }
        c.address = company_address;
        result.push_back(c);
    }
    In.close();
    return result;
}

int modPow(int a, int b,int c)
{   
    if (b == 0)
        return 1;
    int temp = 1;
    for (int i = 1; i <= b; i++)
    {
        temp = temp * a;
        temp = temp % c;
    }
    return temp;
}

long long hashString(string company_name)
{
    long long temp = 0;
    string c;
    if (company_name.size() >= 20)
    {
        c = company_name.substr(company_name.size() - 20);
    }
    else
    {
        c = company_name;
    }
    for (int i = 0; i < c.size(); i++)
    {   
        temp += (c[i] * modPow(p,i,m)) % m;
    }
    temp = temp % m;
    return temp;
}

void insert(HashTable &hash_table, Company company)
{
    int posAdd = hashString(company.name);
    int firstpos = posAdd;
    while (hash_table.Company_Table[posAdd].name != "")
    {   
        posAdd = (posAdd + 1) % 2000;
        if (firstpos == posAdd)
        {
            cout << "Mảng băm đã đầy phần tử" << endl;
            return;
        }
    }
    hash_table.Company_Table[posAdd].name = company.name;
    hash_table.Company_Table[posAdd].profit_tax = company.profit_tax;
    hash_table.Company_Table[posAdd].address = company.address;
}

HashTable createHashTable(vector<Company> list_company)
{   
    HashTable newHashTable;
    for (int i = 0; i < list_company.size() ;i++)
    {
        insert(newHashTable, list_company[i]);
    }
    return newHashTable;
}

Company search(HashTable &hash_table, string company_name)
{   
    Company c;
    int pos = hashString(company_name);
    int Firstpos = pos;
    while (hash_table.Company_Table[pos].name != company_name)
    {
        pos = (pos + 1) % 2000;
        if (pos == Firstpos)
        {
            c.name = "";
            c.profit_tax = "";
            c.address = "";
            return c;
        }
    }
    c.name = hash_table.Company_Table[pos].name;
    c.profit_tax = hash_table.Company_Table[pos].profit_tax;
    c.address = hash_table.Company_Table[pos].address;
    return c;
}

int main(int argc, char* argv[])
{
    string file_name = argv[1];
    string inputFile = argv[2];
    string outputFile = argv[3];

    vector<Company> Company_List = readCompanyList(file_name);
    HashTable Company_Table = createHashTable(Company_List);
    vector<string> CompanyName_List;
    ifstream fIn(inputFile);
    if (!fIn.is_open())
    {
        cout << "Không thể mở file input" << endl;
        return 0;
    }
    string s;
    while (getline(fIn,s))
    {
        CompanyName_List.push_back(s);
    }
    fIn.close();

    ofstream fOut(outputFile);
    if (!fOut.is_open())
    {
        cout << "Không thể mở file output" << endl;
    }
    for (int i = 0; i < CompanyName_List.size() ;i++)
    {
        Company temp;
        temp = search(Company_Table, CompanyName_List[i]);
        if (temp.name != "")
        {
            fOut << temp.name << "|" << temp.profit_tax << "|" << temp.address << endl;
        }
        // fOut << Company_Table.Company_Table[i].name << " " << Company_Table.Company_Table[i].profit_tax << " " << Company_Table.Company_Table[i].address << endl;
    }
    fOut.close();
}

