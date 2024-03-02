# Car_Rental_System
Divit Shah's Repository for CS253 Object-Oriented Programming Assignment in C++


This Car Rental System comprises of the main C++ file, "car_rental_system.cpp", containing the source code, and 5 database files in total, which are:
"customers.csv", for maintaining the customer database and responding to any customer related queries.
"employees.csv", for maintaining the employee database and responding to any employee related queries.
"managers.csv", for maintaining the manager database and responding to any manager related queries.
"cars.csv", for maintaining the overall car database which keeps a record of every car in the system.
"rented_cars.csv", for keeping track of currently rented cars and their respective owners.

The structure of the 3 user databases is as follows:
"Name of User", "User ID", "Password", "Type of User", "User Record".

The structure of "cars.csv" is as follows:
"Car Name", "Car Brand", "Rental Price", "Car Serial No.", "is_rented".

is_rented signifies whether the car is currently rented or not.

The structure of "rented_cars.csv" is as follows:
"User ID", "Brand", "Rental Price", "Car Serial No.", "Time of Rental".

Time of Rental is updated by the system by itself and is used to calculate due date for return of the car.

Upon entering the system, the user is greeted with the Home page, wherein he is given the choice of logging in, registering as a new user, or exiting the system. Only existing users can log in using their user ID and password, and all others are expected to register by specifying the type of user they wish to register as.

To register as a customer or employee, the user can set any password they wish to and login using that password in the future, but to login as a manager, they must provide a specific password ("12345678") which is the same for all managers, to prevent intrusion by unauthorized users. This means that no "Set Password" option is available for managers during registration, since it is already preset by itself. All passwords must be atleast 8 characters long. 

Only customers and employees can rent cars, and all employees are given a 15% discount on the same.
