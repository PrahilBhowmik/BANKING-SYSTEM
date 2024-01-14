#include <netinet/in.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/socket.h>  
#include <unistd.h>  
#include "server.h"
#define PORT 8080  
#include "user.h"
#include "admin.h"
#include "police.h"
int server_fd, new_socket, valread;  
struct sockaddr_in address;  
int opt = 1;  
int addrlen = sizeof(address);  
char buffer[1024] = { 0 };  
char* hello = "Request Handled";  



vector<string> tokenize(string data)
{
    vector <string> tokens;
     
    // stringstream class check1
    stringstream check(data);
     
    string intermediate;
     
    // Tokenizing w.r.t. space ' '
    while(getline(check, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

void do_login(vector<string>&token,string buffer)
{
        string res = login(token[1],token[2]);
        cout<<res<<endl; 
        const int length = res.length(); 
        char* char_array = new char[length + 1]; 
        strcpy(char_array, res.c_str()); 
        send(new_socket, char_array, strlen(char_array), 0);  
        printf("Request Handled\n"); 
}

void get_Balance_data(User user)
{
        string res = user.getBalance();
        const int length = res.length(); 
        char* char_array = new char[length + 1]; 
        strcpy(char_array, res.c_str()); 
        send(new_socket, char_array, strlen(char_array), 0); 
}

void get_MiniStatement_data(User user)
{
      string res = user.getMiniStatement();
      const int length = res.length(); 
      char* char_array = new char[length + 1]; 
      strcpy(char_array, res.c_str()); 
      send(new_socket, char_array, strlen(char_array), 0); 
}


void get_Credit(Admin admin,string id,string balance)
{  
    int amt = stoi(balance);    
    string res =  admin.Credit_Balance(id,amt);
    const int length = res.length(); 
    char* char_array = new char[length + 1]; 
    strcpy(char_array, res.c_str()); 
    send(new_socket, char_array, strlen(char_array), 0); 
}

void get_Debit(Admin admin,string id,string balance)
{  
    int amt = stoi(balance);    
    string res =  admin.Debit_Balance(id,amt);
    const int length = res.length(); 
    char* char_array = new char[length + 1]; 
    strcpy(char_array, res.c_str()); 
    send(new_socket, char_array, strlen(char_array), 0); 
}

void get_balance(Police police)
{
    string res = police.getBalance();
    const int length = res.length(); 
    char* char_array = new char[length + 1]; 
    strcpy(char_array, res.c_str()); 
    send(new_socket, char_array, strlen(char_array), 0); 
}

void get_ministatement(Police police,string id)
{
    string res = police.miniStatement(id);
    const int length = res.length(); 
    char* char_array = new char[length + 1]; 
    strcpy(char_array, res.c_str()); 
    send(new_socket, char_array, strlen(char_array), 0); 
}

int main(int argc, char const* argv[])  
{  

    // Creating socket file descriptor  
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  
            perror("socket failed");  
            exit(EXIT_FAILURE);  
    }  

    // Forcefully attaching socket to port 8080  
    if (setsockopt(server_fd, SOL_SOCKET,  
                            SO_REUSEADDR | SO_REUSEPORT, &opt,  
                            sizeof(opt))) {  
            perror("setsockopt");  
            exit(EXIT_FAILURE);  
    }  
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons(PORT);  

    // Forcefully attaching socket to port 8080  
    if (bind(server_fd, (struct sockaddr*)&address,  
                    sizeof(address))  
            < 0) {  
            perror("bind failed");  
            exit(EXIT_FAILURE);  
    }  
    if (listen(server_fd, 3) < 0) {  
            perror("listen");  
            exit(EXIT_FAILURE);  
    }  
    if ((new_socket  
            = accept(server_fd, (struct sockaddr*)&address,  
                            (socklen_t*)&addrlen))  
            < 0) {  
            perror("accept");  
            exit(EXIT_FAILURE);  
    }  
    while(true){
        valread = read(new_socket, buffer, 1024);  
        printf("%s\n", buffer);
        string info = buffer;
        memset(buffer,0,sizeof(buffer));
        vector<string> token = tokenize(info); 
        
        if(token[0]=="login")
        {
          do_login(token,info);
        }
        else if(token[0]=="C")
        {
                User user(token[2]);
                if(token[1]=="getBalance")
                {
                    get_Balance_data(user);
                }
                else if(token[1]=="miniStatement")
                {
                    get_MiniStatement_data(user);
                }
        }
        else if(token[0]=="A")
        {
           Admin admin;
           if(token[1]=="credit")
           {
                get_Credit(admin,token[2],token[3]);
           }
           else if(token[1]=="debit")
           {
                get_Debit(admin,token[2],token[3]);
           }
        }
        else if(token[0]=="P")
        {
            Police police;

            if(token[1]=="balance")
            {
                get_balance(police);
            }
            else if(token[1]=="miniStatement")
            {
                get_ministatement(police,token[2]);
            }

        }
        else if(token[0]=="exit"){
                break;
        }
    } 

    // closing the connected socket  
    close(new_socket);  
    // closing the listening socket  
    shutdown(server_fd, SHUT_RDWR);  
    return 0;  
}  