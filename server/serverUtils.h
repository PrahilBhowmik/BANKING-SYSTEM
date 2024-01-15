#include <bits/stdc++.h>
using namespace std;
string login(string id,string key)
{
    ifstream in;
    in.open("login.txt");

    if (!in)
    {
       return "Fail File_Not_Opened";
    }
    else
    {
        map<string, pair<string, string>> data;
        while (in)
        {
            string user_id, password, type;
            in >> user_id >> password >> type;
            data[user_id] = make_pair(password, type);
        }

        in.close();

        // USER EXIST
        if (data.find(id) == data.end())
        {
            return "Fail USER_NOT_EXIST\n";
        }

        // PASSWORD MATCH
        if (data[id].first != key)
        {
            return "Fail PASSWORD_NOT_MATCHED\n";
        }

        return "Success "  + data[id].second;
    }

    return 0;
}