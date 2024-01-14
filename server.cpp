#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[])
{
    ifstream in;
    in.open("login.txt");

    if (!in)
    {
        cout << "LOGIN FILE NOT OPENED\n";
        return 0;
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
        if (data.find(argv[1]) == data.end())
        {
            cout << "USER NOT EXIST\n";
            // return response
            return 0;
        }

        // PASSWORD MATCH
        if (data[argv[1]].first != argv[2])
        {
            cout << "PASSWORD NOT MATCHED\n";
            // return response
            return 0;
        }

        cout << "USER LOGGED IN SUCCESSFULLY OF TYPE : " << data[argv[1]].second << endl;
        // return response
        return 1;
    }

    return 0;
}