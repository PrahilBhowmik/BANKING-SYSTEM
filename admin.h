#include <bits/stdc++.h>
using namespace std;

class Admin
{
public:
    string Credit_Balance(string user_id, int balance)
    {

        int id = stoi(user_id);

        if (!(id >= 101 && id <= 110))
        {
            return "USER NOT EXIST\n";
        }

        ifstream in;
        in.open(user_id + ".txt");
        string balancer;
        while (in)
        {
            in >> balancer;
        }
        in.close();

        int amt = 0;
        bool check = false;
        if (!balancer.empty())
        {
            amt = stoi(balancer);
            check = true;
        }

        amt = amt + balance;

        balancer = to_string(amt);

        ofstream of;

        of.open(user_id + ".txt", ios::app);

        if (!of)
        {
            return "FILE NOT OPEN\n";
        }

        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        if (check)
            of << endl;
        of << std::put_time(&tm, "%d/%m/%Y") << " Credit " << balancer;
        of.close();

        return "SUCCESSFULLY CREDIT\n";
    }

    string Debit_Balance(string user_id, int balance)
    {

        int id = stoi(user_id);

        if (!(id >= 101 && id <= 110))
        {
            return "USER NOT EXIST\n";
        }

        ifstream in;
        in.open(user_id + ".txt");
        string balancer;
        while (in)
        {
            in >> balancer;
        }
        in.close();

        int amt = 0;
        bool check = false;
        if (!balancer.empty())
        {
            amt = stoi(balancer);
            check = true;
        }
        if (amt < balance)
        {
            return "NOT SUFFICIENT BALANCE\n";
        }

        amt = amt - balance;

        balancer = to_string(amt);

        ofstream of;

        of.open(user_id + ".txt", ios::app);

        if (!of)
        {
            return "FILE NOT OPEN\n";
        }

        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        if (check)
            of << endl;
        of << std::put_time(&tm, "%d/%m/%Y") << " Debit " << balancer;
        of.close();

        return "SUCCESSFULLY DEBIT\n";
    }
};

