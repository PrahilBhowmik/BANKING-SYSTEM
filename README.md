SERVER SIDE

* In server side we are maintaining the bussiness logic part and the database part of the application.
* There are three file in which we have written the bussiness logic code.

1. Admin.h -> contain all the bussiness logic of admin like credit and debit balance of the customer.
2. User.h -> contain all the bussiness logic of user like get available balance or mini statement.
3. Police.h -> contain all the bussiness logic of police like get available balance of all the customer or get the mini statement of particular customer.

* There is also a serverUtils file which contain all the authentication part (LOGIN)

* Server.cpp is the main file where the socket code is written, to accept the request of the user and provide the functionality according to the user type.


