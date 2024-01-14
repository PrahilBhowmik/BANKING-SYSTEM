#include <bits/stdc++.h>
using namespace std;

class Police
{
private:
    map<string, vector<vector<string>>> data;

public:
    Police()
    {

        ifstream in;

        for (int i = 101; i <= 110; i++)
        {
            in.open(to_string(i) + ".txt");

            while (in)
            {
                string date, c_or_d, balance;
                in >> date >> c_or_d >> balance;
                if (!date.empty() || !c_or_d.empty() || !balance.empty())
                {
                    data[to_string(i)].push_back({date, c_or_d, balance});
                }
            }

            in.close();
        }
    }

    string getBalance()
    {
        map<string, string> mp;
        for (int i = 101; i <= 110; i++)
        {
            string id = to_string(i);
            int size = data[id].size();
            if (size == 0)
            {
                mp[id] = "0";
            }
            else
            {
                mp[id] = data[id][size - 1][2];
            }
        }

        string res = "";
        for(auto i : mp)
        {
           res = res + i.first + " ------> " + i.second + "\n"; 
        }
        return res;
    }

    string miniStatement(string user_id)
    {
        int id = stoi(user_id);

        if (!(id >= 101 && id <= 110))
        {
            return "NO USER EXIST\n";
        }

        string res = "";
        
        for(auto i : data[user_id])
        {
            res = res+i[0]+"_____"+i[1]+"_____"+i[2]+"\n";
        }

        if(res.size()==0)
        {
            return "NO DATA FOUND\n";
        }

        return res;
    }
};

