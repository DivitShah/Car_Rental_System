# Car_Rental_System
Divit Shah's Repository for CS253 Object-Oriented Programming Assignment in C++


+ This Car Rental System comprises of the main C++ file, [`car_rental_system_220995.cpp`](/car_rental_system_220995.cpp), containing the source code, and 5 database files in total, which are:

+ [`customers.csv`](/customers.csv), for maintaining the customer database and responding to any customer related queries.

+ [`employees.csv`](/employees.csv), for maintaining the employee database and responding to any employee related queries.

+ [`managers.csv`](/managers.csv), for maintaining the manager database and responding to any manager related queries.

+ [`cars.csv`](/cars.csv), for maintaining the overall car database which keeps a record of every car in the system.

+ [`rented_cars.csv`](/rented_cars.csv), for keeping track of currently rented cars and their respective owners.



+ The structure of the 3 user databases is as follows:

"Name of User", "User ID", "Password", "Type of User", "User Record".

+ The structure of [`cars.csv`](/cars.csv) is as follows:

"Car Name", "Car Brand", "Rental Price", "Car Serial No.", "is_rented".

is_rented signifies whether the car is currently rented or not.

+ The structure of [`rented_cars.csv`](/rented_cars.csv) is as follows:

"User ID", "Brand", "Rental Price", "Car Serial No.", "Time of Rental".

Time of Rental is updated by the system by itself and is used to calculate due date for return of the car.

+ Upon entering the system, the user is greeted with the Home page, wherein he is given the choice of logging in, registering as a new user, or exiting the system. Only existing users can log in using their user ID and password, and all others are expected to register by specifying the type of user they wish to register as.

+ To register as a customer or employee, the user can set any password they wish to and login using that password in the future, but to login as a manager, they must provide a specific password ("12345678") which is the same for all managers, to prevent intrusion by unauthorized users. This means that no "Set Password" option is available for managers during registration, since it is already preset by itself. All passwords must be atleast 8 characters long. 

+ Only customers and employees can rent cars, and all employees are given a 15% discount on the same. All customers and employees have a customer record and employee record respectively, which is used as a credit score to judge whether a user can be deemed fit for renting a car or not, as given in the problem statement.

+ While returning a car, the user is asked to update the damage done to the car in percentage. A higher damage % leads to a proportionate reduction in the user's user record. Also, the system automatically detects the date of return and calculates the fine accordingly if the date of return is past the due date as fine = days_late * fine_per_day. This fine is then again reflected in the user's record, which is updated accordingly. Thus, both damage caused and late returns can make a difference to the user's record. 

+ If the user's record drops below a certain car's price, he will not be allowed to rent that car, as mentioned in the problem statement. However, the user has an option to update his/her customer record to any specific level (below the maximum balance) by paying the required amount and it will get reflected accordingly.

+ Additionally, customers and employees can browse all cars in the store and check whether they can rent a particular car or not, and the price required for renting it. Managers can view all cars in the store, view all user details (except passwords), view which car is rented to whom, and add, delete and update details of any car or user. 

+ Lastly, at runtime, care has been taken to ensure that invalid inputs are handled by the system accordingly using defensive programming, and only valid inputs will be considered by the system at each and every step of execution.


