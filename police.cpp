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

    map<string, string> getBalance()
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

        return mp;
    }

    vector<vector<string>> miniStatement(string user_id)
    {
        int id = stoi(user_id);

        if (!(id >= 101 && id <= 110))
        {
            return {{}};
        }

        return data[user_id];
    }
};

int main()
{
    Police police;
    map<string, string> data = police.getBalance();
    vector<vector<string>> miniStatement = police.miniStatement("102");
    for (auto i : miniStatement)
    {
        cout << i[0] << " " << i[1] << " " << i[2] << endl;
    }
    // return response
    return 0;
}