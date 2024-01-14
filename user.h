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
    string getMiniStatement()
    {
        string res = "";
        for(auto i : data)
        {
            res = res+i[0]+"_____"+i[1]+"_____"+i[2]+"\n";
        }
        if (res.size() == 0)
        {
            return "NO DATA FOUND";
        }
        return res;
    }
};
