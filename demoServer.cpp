#include <netinet/in.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/socket.h>  
#include <unistd.h>  
#include "server.h"
#define PORT 8080  


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
        vector<string> token = tokenize(info); 
        
        if(token[0]=="login")
        {
          do_login(token,buffer);
        }
    } 

    // closing the connected socket  
    close(new_socket);  
    // closing the listening socket  
    shutdown(server_fd, SHUT_RDWR);  
    return 0;  
}  