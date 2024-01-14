#include <bits/stdc++.h>
using namespace std;

class User
{
private:
    vector<vector<string>> data;

public:
    User(string user_id)
    {

        ifstream in;

        in.open(user_id + ".txt");

        if (!in)
        {
            cout << "FILE NOT OPENED \n";
            exit(0);
        }

        while (in)
        {
            string date, c_or_d, balance;
            in >> date >> c_or_d >> balance;
            if (!date.empty() || !c_or_d.empty() || !balance.empty())
            {
                data.push_back({date, c_or_d, balance});
            }
        }

        in.close();
    }

    string getBalance()
    {
        if (data.size() == 0)
        {
            return "NO DATA FOUND";
        }
        int size = data.size() - 1;
        string balance = data[size][2];
        return balance;
    }
    vector<vector<string>> getMiniStatement()
    {
        return data;
    }
};

int main()
{
    User user("101");
    string balance = user.getBalance();
    vector<vector<string>> getMiniStatement = user.getMiniStatement();
    // return response
    return 0;
}