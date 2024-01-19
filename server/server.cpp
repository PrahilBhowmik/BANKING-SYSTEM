// close
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <bits/stdc++.h>
#include "serverUtils.h"
#include "user.h"
#include "admin.h"
#include "police.h"
using namespace std;
#define TRUE 1
#define FALSE 0

int opt = TRUE;
int master_socket, addrlen, new_socket, client_socket[30],
    max_clients = 30, activity, i, valread, sd;
int max_sd;
struct sockaddr_in address;

vector<string> tokenize(string data)
{
    vector<string> tokens;

    // stringstream class check1
    stringstream check(data);

    string intermediate;

    // Tokenizing w.r.t. space ' '
    while (getline(check, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

void do_login(vector<string> &token, string buffer, int sd)
{
    string res = login(token[1], token[2]);
    cout << res << endl;
    const int length = res.length();
    char *char_array = new char[length + 1];
    strcpy(char_array, res.c_str());
    send(sd, char_array, strlen(char_array), 0);
    printf("Request Handled\n");
}

void get_Balance_data(User user, int sd)
{
    string res = user.getBalance();
    const int length = res.length();
    char *char_array = new char[length + 1];
    strcpy(char_array, res.c_str());
    send(sd, char_array, strlen(char_array), 0);
}

void get_MiniStatement_data(User user, int sd)
{
    string res = user.getMiniStatement();
    const int length = res.length();
    char *char_array = new char[length + 1];
    strcpy(char_array, res.c_str());
    send(sd, char_array, strlen(char_array), 0);
}

void get_Credit(Admin admin, string id, string balance, int sd)
{
    int amt = stoi(balance);
    string res = admin.Credit_Balance(id, amt);
    const int length = res.length();
    char *char_array = new char[length + 1];
    strcpy(char_array, res.c_str());
    send(sd, char_array, strlen(char_array), 0);
}

void get_Debit(Admin admin, string id, string balance, int sd)
{
    int amt = stoi(balance);
    string res = admin.Debit_Balance(id, amt);
    const int length = res.length();
    char *char_array = new char[length + 1];
    strcpy(char_array, res.c_str());
    send(sd, char_array, strlen(char_array), 0);
}

void get_balance(Police police, int sd)
{
    string res = police.getBalance();
    const int length = res.length();
    char *char_array = new char[length + 1];
    strcpy(char_array, res.c_str());
    send(sd, char_array, strlen(char_array), 0);
}

void get_ministatement(Police police, string id, int sd)
{
    string res = police.miniStatement(id);
    const int length = res.length();
    char *char_array = new char[length + 1];
    strcpy(char_array, res.c_str());
    send(sd, char_array, strlen(char_array), 0);
}

int main(int argc, char *argv[])
{
    char buffer[1025]; // data buffer of 1K

    fd_set readfds;

    // initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++)
    {
        client_socket[i] = 0;
    }

    // create a master socket
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // set master socket to allow multiple connections ,
    // this is just a good habit, it will work without this
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(stoi(argv[1]));

    // bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while (TRUE)
    {
        // clear the socket set
        FD_ZERO(&readfds);

        // add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        // add child sockets to set
        for (i = 0; i < max_clients; i++)
        {
            // socket descriptor
            sd = client_socket[i];

            // if valid socket descriptor then add to read list
            if (sd > 0)
                FD_SET(sd, &readfds);

            // highest file descriptor number, need it for the select function
            if (sd > max_sd)
                max_sd = sd;
        }

        // wait for an activity on one of the sockets , timeout is NULL ,
        // so wait indefinitely
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR))
        {
            printf("select error");
        }

        // If something happened on the master socket ,
        // then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket,
                                     (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            // add new socket to array of sockets
            for (i = 0; i < max_clients; i++)
            {
                // if position is empty
                if (client_socket[i] == 0)
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);

                    break;
                }
            }
        }

        // else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)
        {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds))
            {
                // Check if it was for closing , and also read the
                // incoming message
                valread = read(sd, buffer, 1024);
                buffer[valread] = '\0';
                string info = buffer;
                memset(buffer, 0, sizeof(buffer));
                vector<string> token = tokenize(info);
                if (token[0] == "exit")
                {
                    // Somebody disconnected , get his details and print
                    getpeername(sd, (struct sockaddr *)&address,
                                (socklen_t *)&addrlen);

                    // Close the socket and mark as 0 in list for reuse
                    close(sd);
                    client_socket[i] = 0;
                }

                // Echo back the message that came in
                else
                {
                    // valread = read(sd, buffer, 1024);
                    // printf("%s\n", buffer);
                    // string info = buffer;
                    // memset(buffer,0,sizeof(buffer));
                    // vector<string> token = tokenize(info);

                    if (token[0] == "login")
                    {
                        do_login(token, info, sd);
                    }
                    else if (token[0] == "C")
                    {
                        User user(token[2]);
                        if (token[1] == "getBalance")
                        {
                            get_Balance_data(user, sd);
                        }
                        else if (token[1] == "miniStatement")
                        {
                            get_MiniStatement_data(user, sd);
                        }
                    }
                    else if (token[0] == "A")
                    {
                        Admin admin;
                        if (token[1] == "credit")
                        {
                            get_Credit(admin, token[2], token[3], sd);
                        }
                        else if (token[1] == "debit")
                        {
                            get_Debit(admin, token[2], token[3], sd);
                        }
                    }
                    else if (token[0] == "P")
                    {
                        Police police;

                        if (token[1] == "balance")
                        {
                            get_balance(police, sd);
                        }
                        else if (token[1] == "miniStatement")
                        {
                            get_ministatement(police, token[2], sd);
                        }
                    }
                }
            }
        }
    }

    return 0;
}
