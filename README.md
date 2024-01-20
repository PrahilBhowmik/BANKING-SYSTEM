![Screenshot from 2024-01-20 17-01-34](https://github.com/saluja19/BANKING-SYSTEM/assets/69160216/bfbeedb6-666b-4229-9b56-cf4127ee787e)

**CLIENT SIDE**

* In client side we provide UI to the user to access the bank services.
* The **client.cpp** is the main program in client side.
* The **clientUtils.h** contains all the necessary functions to communicate with server(from establishing TCP connection to sending requests and receiving responses.

![Screenshot from 2024-01-20 16-20-15](https://github.com/saluja19/BANKING-SYSTEM/assets/100374007/4d3e0636-548c-4a2c-a35b-3470698f6a8a)

**SERVER SIDE**

* In server side we are maintaining the bussiness logic part and the database part of the application.
* There are three file in which we have written the bussiness logic code.

1. admin.h -> contain all the bussiness logic of admin like credit and debit balance of the customer.
2. user.h -> contain all the bussiness logic of customer like get available balance or mini statement.
3. police.h -> contain all the bussiness logic of police like get available balance of all the customer or get the mini statement of particular customer.

* There is also a serverUtils file which contain all the authentication part (LOGIN)

* server.cpp is the main file where the socket code is written, to accept the request of the client and provide the functionality according to the client type.


