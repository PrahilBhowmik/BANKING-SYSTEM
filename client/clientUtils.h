#include<bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/socket.h> 
using namespace std;

string clientType;
int sock = 0, valread, client_fd;  
struct sockaddr_in serv_addr; 

char buffer[1024] = { 0 }; 

vector<string> tokenize(string data){
    vector<string> tokens;
    stringstream check(data);   
    string intermediate;
    while(getline(check, intermediate, ' ')){
        tokens.push_back(intermediate);
    }
    return tokens;
}

bool connect(int port,string ip){ 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  
        printf("\n ERROR: Failed Creating Socket \n");  
        return false;  
    } 
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_port = htons(port);  
    const int length = ip.length(); 
    char* ip_ = new char[length + 1];  
    strcpy(ip_, ip.c_str());
    if (inet_pton(AF_INET, ip_, &serv_addr.sin_addr)  
            <= 0) {  
            printf(  
                    "\nInvalid/Unsupported Address\n");  
            return false;  
    }  
    if ((client_fd  
            = connect(sock, (struct sockaddr*)&serv_addr,  
                            sizeof(serv_addr)))  
            < 0) {  
            printf("\nConnection Failed \n");  
            return false;  
    }
    return true;  
}

pair<bool,string> login(string userId, string password){
    // Request to Server
    string s = "login " + userId + " " + password;
    const int length = s.length(); 
    char* request = new char[length + 1];  
    strcpy(request, s.c_str());
    send(sock, request, strlen(request), 0); 
    valread = read(sock, buffer, 1024);  
    s=buffer;
    memset(buffer,0,sizeof(buffer));
    vector<string> vec = tokenize(s);
    if(vec[0]=="Success"){
        clientType = vec[1];
        return make_pair(true,"logged in");
    }
    return make_pair(false,vec[1]);
}

void printMiniStatement(string userId){
    // Request to Server
    string s = clientType+" miniStatement " + userId;
    const int length = s.length(); 
    char* request = new char[length + 1];  
    strcpy(request, s.c_str());
    send(sock, request, strlen(request), 0);
    valread = read(sock, buffer, 1024);
    cout<<"Your mini statement is:\n"<<buffer<<endl<<endl<<endl;
    memset(buffer,0,sizeof(buffer));
}

void printBalance(string userId){
    // Request to Server
    string s = clientType+" getBalance " + userId;
    const int length = s.length(); 
    char* request = new char[length + 1];  
    strcpy(request, s.c_str());
    send(sock, request, strlen(request), 0); 
    valread = read(sock, buffer, 1024);
    cout<<"Your account balance is:\nRs."<<buffer<<endl<<endl<<endl;
    memset(buffer,0,sizeof(buffer));
}

void printAllBalances(){
    // Request to Server
    string s = clientType+" balance";
    const int length = s.length(); 
    char* request = new char[length + 1];  
    strcpy(request, s.c_str());
    send(sock, request, strlen(request), 0); 
    valread = read(sock, buffer, 1024);
    cout<<"All Account Balances:\n"<<buffer<<endl<<endl<<endl;
    memset(buffer,0,sizeof(buffer));
}

void credit_balance(){
    string userId;
    int amount;
    cout<<"Enter userId: ";
    cin>>userId;
    cout<<"Enter amount to credit: ";
    cin>>amount;
    // Request to Server
    string s = clientType+" credit " + userId+" "+to_string(amount);
    const int length = s.length(); 
    char* request = new char[length + 1];  
    strcpy(request, s.c_str());
    send(sock, request, strlen(request), 0); 
    valread = read(sock, buffer, 1024);
    cout<<buffer<<endl<<endl<<endl;
    memset(buffer,0,sizeof(buffer));
}

void debit_balance(){
    string userId;
    int amount;
    cout<<"Enter userId: ";
    cin>>userId;
    cout<<"Enter amount to debit: ";
    cin>>amount;
    // Request to Server
    string s = clientType+" debit " + userId+" "+to_string(amount);
    const int length = s.length(); 
    char* request = new char[length + 1];  
    strcpy(request, s.c_str());
    send(sock, request, strlen(request), 0); 
    valread = read(sock, buffer, 1024);
    cout<<buffer<<endl<<endl<<endl;
    memset(buffer,0,sizeof(buffer));
}

void exit(){
    // Request to Server
    string s = "exit";
    const int length = s.length(); 
    char* request = new char[length + 1];  
    strcpy(request, s.c_str());
    send(sock, request, strlen(request), 0); 
    memset(buffer,0,sizeof(buffer));
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
            case 3: exit();return;
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
            case 3: exit();return;
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
            case 3: exit();return;
            default: cout<<"INVALID CHOICE!!"<<endl;break;
        }
    }
}
