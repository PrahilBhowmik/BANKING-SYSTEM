#include<bits/stdc++.h>
using namespace std;

char clientType;

pair<bool,string> login(string userId, string password){
    // Request to Server
    clientType = 'C';
    return make_pair(true,"LOGGED IN SUCCESSFULLY\n");
}

void printMiniStatement(string userId){
    // Request to Server
    cout<<"PRINTING MINI STATEMENT"<<endl;
}

void printBalance(string userId){
    // Request to Server
    cout<<"PRINTING YOUR BALANCE"<<endl;
}

void printAllBalances(){
    // Request to Server
    cout<<"PRINTING ALL BALANCES"<<endl;
}

void credit_balance(){
    string userId;
    double amount;
    cout<<"Enter userId: ";
    cin>>userId;
    cout<<"Enter amount to credit: ";
    cin>>amount;
    // Request to Server
    cout<<"CREDITING AMOUNT"<<endl;
}

void debit_balance(){
    string userId;
    double amount;
    cout<<"Enter userId: ";
    cin>>userId;
    cout<<"Enter amount to debit: ";
    cin>>amount;
    // Request to Server
    cout<<"DEBITING AMOUNT"<<endl;
}

void handleAdmin(){
    while(true){
        cout<<"Please choose an action:\n1.Credit Balance\n2.Debit Balance\n3.Exit\nYour Choice: ";
        int choice;
        cin>>choice;
        system("clear");
        switch(choice){
            case 1: credit_balance();break;
            case 2: debit_balance();break;
            case 3: return;
            default: cout<<"INVALID CHOICE!!"<<endl;break;
        }
    }
}

void handleCustomer(string userId){
    while(true){
        cout<<"Please choose an action:\n1.See Available Balance\n2.Get mini statement\n3.Exit\nYour Choice: ";
        int choice;
        cin>>choice;
        system("clear");
        switch(choice){
            case 1: printBalance(userId);break;
            case 2: printMiniStatement(userId);break;
            case 3: return;
            default: cout<<"INVALID CHOICE!!"<<endl;break;
        }
    }
}

void handlePolice(){
    while(true){
        cout<<"Please choose an action:\n1.See Available Balances of all customers\n2.Get mini statement\n3.Exit\nYour Choice: ";
        int choice;
        string userId;
        cin>>choice;
        system("clear");
        switch(choice){
            case 1: printAllBalances();break;
            case 2: cout<<"Enter userId: ";
                    cin>>userId;
                    printMiniStatement(userId);break;
            case 3: return;
            default: cout<<"INVALID CHOICE!!"<<endl;break;
        }
    }
}

int main(){
    clientType = 'N';
    bool loggedIn=false;
    string userId;
    while(!loggedIn){
        string password;
        cout<<"Enter userId: ";
        cin>>userId;
        cout<<"Enter Password: ";
        cin>>password;
        auto loginInfo = login(userId,password);
        system("clear");
        loggedIn = loginInfo.first;
        cout<<loginInfo.second<<endl;
    } 
    switch (clientType)
    {
        case 'C': handleCustomer(userId);break;
        case 'A': handleAdmin();break;
        case 'P': handlePolice();break;
        default: break;
    }
    system("clear");
    cout<<"LOGGING OUT"<<endl;
    return 0;
}