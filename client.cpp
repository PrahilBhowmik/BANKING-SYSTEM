#include "clientUtils.h"
 
int main(){
    if(!connect()){
        return 0;
    }
    clientType = 'C';
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
    close(client_fd);  
    return 0;
}