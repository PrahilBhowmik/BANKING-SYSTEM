#include "clientUtils.h"
 
int main(int argc, char* argv[]){
    string ip = argv[1];
    string port = argv[2];
    if(!connect(stoi(port),ip)){
        return 0;
    }
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
    switch (clientType[0])
    {
        case 'C': handleCustomer(userId);break;
        case 'A': handleAdmin();break;
        case 'P': handlePolice();break;
        default: break;
    }
    system("clear");
    cout<<"LOGGING OUT"<<endl;
    close(client_fd);  
    return 0;
}