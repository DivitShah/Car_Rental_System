//customers.csv, employees.csv, and managers.csv use data in the form of {name,id,password,user_type,record}
//cars.csv uses data in the form of {car_name,brand,price,serial_no,is_rented}
//rented_cars.csv uses data in the form of {id,car_name,car_price,car_serial_number,rent_date}


#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
using namespace std;
vector<vector<string>> my_vector;
vector<string> update_vector;
const int max_balance=100000;
void read(string file_name){     //reference : https://java2blog.com/read-csv-file-in-cpp/
    vector<string> row;
    string line, word;
    fstream file (file_name,ios::in);
    if(file.is_open()){
        while(getline(file, line)){
            row.clear();
            stringstream str(line);
            while(getline(str, word, ',')) row.push_back(word);
            my_vector.push_back(row);
        }
    }
    else cout<<"Could not open the required file"<<endl;
}
void write(vector<vector<string>> to_write, string file_name){  
    fstream fout(file_name,ios::out);
    for(auto lines:to_write){
        for(auto line:lines){
            fout<<line;
            if(line!=lines.back()) fout<<",";
        }
        fout<<endl;
    }

}
void append_to_file(vector<string> to_write, string file_name){  
    fstream fout(file_name,ios::out | ios::app);
    for(auto line:to_write){
        fout<<line;
        if(line!=to_write.back()) fout<<",";
    }
    fout<<endl;
}
void output_file(vector<vector<string>> to_write){
    int no_of_line=1;
    for(auto lines:to_write){
        cout<<no_of_line<<". ";
        for(auto line:lines){
            cout<<line;
            if(line!=lines.back()) cout<<" | ";
        }
        no_of_line++;
        cout<<endl;
    }
}
void output_file_without_pwd(vector<vector<string>> to_write){
    int no_of_line=1;
    for(auto lines:to_write){
        cout<<no_of_line<<". ";
        cout<<lines[0]<<" | "<<lines[1]<<" | "<<lines[3]<<" | "<<lines[4]<<endl;
        no_of_line++;
    }
}
class User{
    private:
        string password;
    public:
        string name;
        string id;
        string record;
        vector<string> car_serial_nos_rented;
        virtual void display_menu(string id){};
        void display_overall_menu();
        void login();
        void new_register();
        void browse_all_cars(string id);
        void browse_rented_cars(string id);
        virtual void rent_car(string id, string my_car_name){};
        virtual void return_car(string id,string my_car_serial_no){};
        virtual void check_available(string id, string my_car_name){};
        virtual void show_record(string id){};
        virtual void restore_account_balance(string id,string user_type){};
        void logout();
};

class Customer: public User{
    public:
    string customer_record;
    void display_menu(string id);
    void rent_car(string id, string my_car_name);
    void return_car(string id, string my_car_serial_no);
    void check_available(string id, string my_car_name);
    void show_record(string id);
    void restore_account_balance(string id,string user_type);

};
class Employee: public User{
    public:
    string employee_record;
    void display_menu(string id);
    void rent_car(string id, string my_car_name);
    void return_car(string id, string my_car_serial_no);
    void check_available(string id, string my_car_name);
    void show_record(string id);
    void restore_account_balance(string id,string user_type);
};
class Manager{
    public:
        void display_store_menu(string id);
        void browse_all_users(string id);
        void browse_all_cars(string id);
        void show_due_date(string my_car_serial_no);
        void add_user(string id);
        void update_user(string id);
        void delete_user(string id);
        void add_car(string id);
        void update_car(string id);
        void delete_car(string id);
        void browse_rented_to_user(string id,string user_id);
        void browse_all_rented_cars(string id);
};






void User :: display_overall_menu(){
    char c;
    cout<<"---------------------------------------------------------------------"<<endl;
    cout<<endl<<endl<<"Welcome to Divit's Car Rental System!"<<endl<<endl;
    cout<<"1. Press 1 to log in : "<<endl;
    cout<<"2. Press 2 to register as a new user : "<<endl;
    cout<<"3. Press 3 to exit"<<endl;
    cout<<"---------------------------------------------------------------------"<<endl;
    cin>>c;
    while(c!='1'&&c!='2'&&c!='3'){
        cout<<"Please enter a valid input!"<<endl;
        cout<<"Enter your choice again (1 or 2 or 3): "<<endl;
        cin>>c;
    }
    if(c=='1'){ //logs in a user 
        User u;
        u.login();
    }else if(c=='2'){
        User u;
        u.new_register();
    }
    else if(c=='3'){
        cout<<"Thanks for using the system !";
        exit(1);
    }
}
void User :: login(){
    User u;
    int flag=0;
    string id, user_name, pwd, _type;
    cout<<"Enter your User ID : ";
    cin>>id;
    my_vector.clear();
    read("customers.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==id){
            flag=1;
            user_name=my_vector[i][0];
            _type=my_vector[i][3];
        }
    }
    my_vector.clear();
    read("employees.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==id){
            flag=1;
            user_name=my_vector[i][0];
            _type=my_vector[i][3];
        }
    }
    my_vector.clear();
    read("managers.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==id){
            flag=1;
            user_name=my_vector[i][0];
            _type=my_vector[i][3];
        }
    }
    my_vector.clear();
    if(flag==0){
        cout<<"The user ID "<<id<<" does not exist."<<endl;
        cout<<"Please enter an existing user ID, or register as a new user with a new user ID."<<endl<<endl;
        u.display_overall_menu();
        return;
    }
    cout<<"Welcome "<<user_name<<" . Please enter your password : ";
    cin>>pwd;
    vector<string> row;
    string line,word;

    if(_type=="1"){

        fstream file("customers.csv",ios::in);
    int ct=0;
    if(file.is_open()){
        while(getline(file,line)){
            row.clear();
            stringstream str(line);
            while(getline(str,word,',')){
                row.push_back(word);
            }
            if(row[1]==id){
                ct=1;
                if(row[2]==pwd){
                    ct++;
                    break;
                }
                else{
                    while(pwd!=row[2]){
                        cout<<"You entered the wrong password. Press 1 to reenter the password and 2 to exit"<<endl;
                        char c;
                        cin>>c;
                        if(c=='1'){
                            cout<<"Enter the password : ";
                            cin>>pwd;
                            if(pwd==row[2]) ct++;
                        }
                        else if(c=='2'){
                            cout<<"Exiting..."<<endl;
                            User u;
                            u.display_overall_menu();
                            return;
                        }
                        else{
                            cout<<"Please enter a valid input."<<endl;
                        }
                    }
                    if(ct==2) break;
                }
            }
            if(ct==2) break;            
        }
        if(ct==0){
            cout<<"Error: Customer with user ID"<<id<<" was not found"<<endl;
            User u;
            u.display_overall_menu();
            return;
        }
        if(ct==2){
            Customer cst;
            cst.display_menu(row[1]);
            
        }
    }




    }else if(_type=="2"){

        fstream file("employees.csv",ios::in);
    int ct=0;
    if(file.is_open()){
        while(getline(file,line)){
            row.clear();
            stringstream str(line);
            while(getline(str,word,',')){
                row.push_back(word);
            }
            if(row[1]==id){
                ct=1;
                if(row[2]==pwd){
                    ct++;
                    break;
                }
                else{
                    while(pwd!=row[2]){
                        cout<<"You entered the wrong password. Press 1 to reenter the password and 2 to exit"<<endl;
                        char c;
                        cin>>c;
                        if(c=='1'){
                            cout<<"Enter the password : ";
                            cin>>pwd;
                            if(pwd==row[2]) ct++;
                        }
                        else if(c=='2'){
                            cout<<"Exiting...";
                            return;
                        }
                        else{
                            cout<<"Please enter a valid input."<<endl;
                        }
                    }
                    if(ct==2) break;
                }
            }
            if(ct==2) break;            
        }
        if(ct==0){
            cout<<"Error: Employee with user ID"<<id<<" was not found"<<endl;
            User u;
            u.display_overall_menu();
            return;
        }
        if(ct==2){
            
            Employee e;
            e.display_menu(row[1]);
            
        }
    }

    }else{

        fstream file("managers.csv",ios::in);
    int ct=0;
    if(file.is_open()){
        while(getline(file,line)){
            row.clear();
            stringstream str(line);
            while(getline(str,word,',')){
                row.push_back(word);
            }
            if(row[1]==id){
                ct=1;
                if(row[2]==pwd){
                    ct++;
                    break;
                }
                else{
                    while(pwd!=row[2]){
                        cout<<"You entered the wrong password. Press 1 to reenter the password and 2 to exit"<<endl;
                        char c;
                        cin>>c;
                        if(c=='1'){
                            cout<<"Enter the password : ";
                            cin>>pwd;
                            if(pwd==row[2]) ct++;
                        }
                        else if(c=='2'){
                            cout<<"Exiting...";
                            return;
                        }
                        else{
                            cout<<"Please enter a valid input."<<endl;
                        }
                    }
                    if(ct==2) break;
                }
            }
            if(ct==2) break;            
        }
        if(ct==0){
            cout<<"Error: Manager with user ID"<<id<<" was not found"<<endl;
            User u;
            u.display_overall_menu();
            return;
        }
        if(ct==2){
            
            Manager m;
            
            m.display_store_menu(row[1]);
            
        }
    }

    }
    

    
    
}
void User :: new_register(){
    User u;
    string _type;
    cout<<"Please enter the type of user you wish to register as : "<<endl;
    cout<<"Enter 1 for Customer, 2 for Employee, 3 for Manager: "<<endl;
    cin>>_type;
    while(_type!="1"&&_type!="2"&&_type!="3"){
        cout<<"Please enter a valid input (1, 2 or 3): "<<endl;
        cin>>_type;
    }

    string _name,_id,_password;
    string _record="100000";
    cout<<"Enter user name: ";
    cin.ignore();
    getline(cin,_name);
    cout<<"Enter user ID : ";
    cin>>_id;

    my_vector.clear();
    read("customers.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==_id){
            cout<<"This user ID has already been assigned to another user. Please re-enter user details with a different user ID."<<endl;
            cout<<"You will now be redirected to the Home page."<<endl;
            my_vector.clear();
            u.display_overall_menu();
            return;
        }
    }
    write(my_vector,"customers.csv");
    my_vector.clear();
    read("employees.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==_id){
            cout<<"This user ID has already been assigned to another user. Please re-enter user details with a different user ID."<<endl;
            cout<<"You will now be redirected to the Home page."<<endl;
            my_vector.clear();
            u.display_overall_menu();
            return;
        }
    }
    write(my_vector,"employees.csv");
    my_vector.clear();
    read("managers.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==_id){
            cout<<"This user ID has already been assigned to another user. Please re-enter user details with a different user ID."<<endl;
            cout<<"You will now be redirected to the Home page."<<endl;
            my_vector.clear();
            u.display_overall_menu();
            return;
        }
    }
    write(my_vector,"managers.csv");
    my_vector.clear();
    cout<<"Enter password (minimum length of password is 8 characters) : ";
    cin>>_password;
    while(_password.length()<=7){
        cout<<"Password length should be atleast 8 characters. Please re-enter a valid password."<<endl;
        cout<<"Enter password : ";
        cin>>_password;
    }
    if(_type=="3"&&_password!="12345678"){
        cout<<"You cannot be assigned as a manager since you have not entered the required password. Please retry with a valid password."<<endl;
        cout<<"You will now be redirected to the Home page."<<endl;
        u.display_overall_menu();
        return;
    }
    if(_type=="1"){
        fstream fout("customers.csv",ios::out | ios::app);
        fout<<_name<<","<<_id<<","<<_password<<","<<_type<<","<<_record<<endl;
        cout<<"You have been registered as a new customer with customer record = 100000."<<endl;
        cout<<"You may now login with your credentials."<<endl;
    }else if(_type=="2"){
        fstream fout("employees.csv",ios::out | ios::app);
        fout<<_name<<","<<_id<<","<<_password<<","<<_type<<","<<_record<<endl;
        cout<<"You have been registered as a new employee with employee record = 100000."<<endl;
        cout<<"You may now login with your credentials."<<endl;
    }else{
        fstream fout("managers.csv",ios::out | ios::app);
        fout<<_name<<","<<_id<<","<<_password<<","<<_type<<","<<_record<<endl;
        cout<<"You have been registered as a manager."<<endl;
        cout<<"You may now login with your credentials."<<endl;
    }
    u.display_overall_menu();
}
void User :: browse_all_cars(string id){
    my_vector.clear();
    cout<<"In the data below, 0 signifies that the car is not currently rented and 1 means that it is rented to someone."<<endl;
    read("cars.csv");
    output_file(my_vector);
    my_vector.clear();
}
void User :: browse_rented_cars(string id){
    int count=1;
    my_vector.clear();
    read("rented_cars.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][0]==id){
            cout<<count<<". ";
            count++;
            for(int k=0;k<my_vector[i].size()-1;k++)
                cout<<my_vector[i][k]<<" | ";
            time_t stamp = stoi(my_vector[i][4]);
            tm *dateformat = localtime(&stamp);  
            cout<< dateformat->tm_mday<<"/"<<1 + dateformat->tm_mon<<"/"<<1900 + dateformat->tm_year<<endl;
        }
    }
    if(count==0) cout<<"You have not rented any cars as of now"<<endl<<endl;
    my_vector.clear();
}
void User :: logout(){
    cout<<"Logging out..."<<endl;
    User u;
    u.display_overall_menu();
}


void Customer :: display_menu(string id){
    cout<<"---------------------------------------------------------------------"<<endl;
    cout<<endl<<"You have been logged in as a Customer"<<endl;
    cout<<"Press 1 to browse all the cars in the store"<<endl;
    cout<<"Press 2 to view cars currently rented by you"<<endl;
    cout<<"Press 3 to check if a car is available to rent or not"<<endl;
    cout<<"Press 4 to view your customer record"<<endl;
    cout<<"Press 5 to update your customer record"<<endl;
    cout<<"Press 6 to rent a car"<<endl;
    cout<<"Press 7 to return a car"<<endl;
    cout<<"Press 8 to logout"<<endl;
    cout<<"---------------------------------------------------------------------"<<endl;
    char c;
    cin>>c;
    string my_car_name,my_car_serial_no;
    Customer cst;
    switch(c){
        case '1':
            cst.browse_all_cars(id);
            cst.display_menu(id);
            break;
        case '2':
            cst.browse_rented_cars(id);
            cst.display_menu(id);
            break;
        case '3':
            cout<<"Enter the name of the car you wish to check : ";
            cin.ignore();
            getline(cin,my_car_name);
            cst.check_available(id,my_car_name);
            cst.display_menu(id);
            break;
        case '4':
            cst.show_record(id);
            cst.display_menu(id);
            break;
        case '5':
            cst.restore_account_balance(id,"1");
            cst.display_menu(id);
        case '6':
            cout<<"Enter the name of the car you wish to rent : ";
            cin.ignore();
            getline(cin,my_car_name);
            cst.rent_car(id,my_car_name);
            cst.display_menu(id);        
            break;
        case '7':
            cout<<"Enter the serial number of the car you wish to return : ";
            cin>>my_car_serial_no;
            cst.return_car(id,my_car_serial_no);
            cst.display_menu(id);
            break;    
        case '8':
            logout();
            break;
    }
}
void Customer :: rent_car(string id,string my_car_name){
    int customer_record;
    my_vector.clear();
    read("customers.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==id) customer_record=stoi(my_vector[i][4]);
    }
    my_vector.clear();
    int flag=0;
    //if starts
    
    read("cars.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][0]==my_car_name && my_vector[i][4]=="0" && customer_record>=stoi(my_vector[i][2])){
            flag=1;
            cout<<"Car is available to you to rent for "<<(int)stoi(my_vector[i][2])<<" rupees!"<<endl;
            my_vector[i][4]="1";
            update_vector.clear();
            update_vector.push_back(id); //for customer id
            update_vector.push_back(my_car_name); //for car name
            update_vector.push_back(my_vector[i][2]); //for car price
            update_vector.push_back(my_vector[i][3]); //for car serial number
            update_vector.push_back(to_string(time(0))); //for rent date
            append_to_file(update_vector,"rented_cars.csv");
            cout<<"Your requested car has been successfully rented to you!"<<endl;
            break;
        }else if(my_vector[i][0]==my_car_name && my_vector[i][4]=="0" && customer_record<stoi(my_vector[i][2])){
            flag=1;
            cout<<"Requested car is available but cannot be rented due to bad customer record"<<endl;
        }
    }
    if(flag==0) cout<<"Requested car is not available to rent!"<<endl;
    write(my_vector,"cars.csv");
    my_vector.clear();
    
    //if ends
    
}
void Customer :: return_car(string id,string my_car_serial_no){
    my_vector.clear();
    int flag=0;
    int damage=0;
    int fine=damage*100;
    read("rented_cars.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][3]==my_car_serial_no && my_vector[i][0]==id){
            flag=1;
            my_vector.erase(my_vector.begin()+i,my_vector.begin()+i+1);
            cout<<"Car was rented to you and is now being returned by you"<<endl;
            cout<<"Please enter the damage done to the car in percentage: "<<endl;
            cin>>damage;
            while(damage<0||damage>100){
                cout<<"Please enter a valid amount between 0 to 100: "<<endl;
                cin>>damage;
            }
            fine=damage*100;
            int current_time=time(0);
            int rented_time=stoi(my_vector[i][4]);
            if(((int)((current_time-rented_time)/86400))>30){
                int late_days=((int)((current_time-rented_time)/86400))-30;
                fine+=late_days*stoi(my_vector[i][2])*0.01;
                cout<<"You are returning the car late by "<<late_days<<" days, and will hence face a fine of "<<fine<<" rupees"<<endl;
            }
            write(my_vector,"rented_cars.csv");
            my_vector.clear();
            read("cars.csv");
            for(int i=0;i<my_vector.size();i++){
                if(my_vector[i][3]==my_car_serial_no) my_vector[i][4]="0";
            }
            write(my_vector,"cars.csv");
            my_vector.clear();
            read("customers.csv");
            for(int i=0;i<my_vector.size();i++){  //for updating fine in the customer's record
                if(my_vector[i][1]==id){
                    int customer_record=stoi(my_vector[i][4]);
                    customer_record-=fine;
                    my_vector[i][4]=to_string(customer_record); //changes the value of customer record in my_vector to reflect fine
                }
            }
            write(my_vector,"customers.csv"); //writes back updated my_vector to the csv
            break;
        }
    }
    if(!flag) cout<<"This car has not been rented to you! Please retry with valid details."<<endl;
    else if(flag) cout<<"Car has been returned successfully!"<<endl;

    my_vector.clear();
}
void Customer :: show_record(string id){
    int flag=0;
    my_vector.clear();
    read("customers.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==id&&my_vector[i][3]=="1"){
            flag=1;
            cout<<"Your customer record stands at "<<my_vector[i][4]<<" as of now."<<endl;
        }
    }
    if(flag==0) cout<<"Requested customer was not found. Please retry with valid customer details."<<endl;
    my_vector.clear();
}
void Customer :: restore_account_balance(string id,string user_type){
    my_vector.clear();
    int customer_record,amount_to_be_paid;
    int flag=0;
    read("customers.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==id){
            flag=1;
            customer_record=stoi(my_vector[i][4]);
            cout<<"Please enter the amount you wish to pay towards your customer record: "<<endl;
            cin>>amount_to_be_paid;
            while(amount_to_be_paid<0){
                cout<<"Please enter a positive integer: "<<endl;
                cin>>amount_to_be_paid;
            }
            while(amount_to_be_paid>(max_balance-customer_record)){
                cout<<"You cannot exceed maximum customer record of 100000 rupees! Please re-enter amount: "<<endl;
                cin>>amount_to_be_paid;
            }
            cout<<"Now restoring your customer record to "<<customer_record+amount_to_be_paid<<" rupees...."<<endl;
            my_vector[i][4]=to_string(customer_record+amount_to_be_paid);
            break;
        }
    }
    write(my_vector,"customers.csv");
    my_vector.clear();
    
}
void Customer :: check_available(string id,string my_car_name){
    my_vector.clear();
    int flag=0;
    read("cars.csv");
    int ct=1;
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][0]==my_car_name && my_vector[i][4]=="0"){
            flag=1;
            cout<<ct<<". ";
            ct++;
            cout<<"Car is available to you for: "<<my_vector[i][2]<<" rupees!"<<endl;
            for(auto j:my_vector[i])
                cout<<j<<" | ";
            cout<<endl;
            break;
        }
    }
    if(flag==0) cout<<"Requested car is not available"<<endl;
    my_vector.clear();
}

void Employee :: display_menu(string id){
    cout<<"---------------------------------------------------------------------"<<endl;
    cout<<endl<<"You have been logged in as an Employee"<<endl;
    cout<<"Press 1 to browse all the cars in the store"<<endl;
    cout<<"Press 2 to view cars currently rented by you"<<endl;
    cout<<"Press 3 to check if a car is available to rent or not"<<endl;
    cout<<"Press 4 to view your employee record"<<endl;
    cout<<"Press 5 to update your employee record"<<endl;
    cout<<"Press 6 to rent a car"<<endl;
    cout<<"Press 7 to return a car"<<endl;
    cout<<"Press 8 to logout"<<endl;
    cout<<"---------------------------------------------------------------------"<<endl;
    char c;
    cin>>c;
    string my_car_name,my_car_serial_no;
    Employee e;
    switch(c){
        case '1':
            e.browse_all_cars(id);
            e.display_menu(id);
            break;
        case '2':
            e.browse_rented_cars(id);
            e.display_menu(id);
            break;
        case '3':
            cout<<"Enter the name of the car you wish to check : ";
            cin.ignore();
            getline(cin,my_car_name);
            e.check_available(id,my_car_name);
            e.display_menu(id);
            break;
        case '4':
            e.show_record(id);
            e.display_menu(id);
            break;
        case '5':
            e.restore_account_balance(id,"2");
            e.display_menu(id);
        case '6':
            cout<<"Enter the name of the car you wish to rent : ";
            cin.ignore();
            getline(cin,my_car_name);
            e.rent_car(id,my_car_name);
            e.display_menu(id);        
            break;
        case '7':
            cout<<"Enter the serial number of the car you wish to return : ";
            cin>>my_car_serial_no;
            e.return_car(id,my_car_serial_no);
            e.display_menu(id);
            break;        
        case '8':
            logout();
            break;
    }
}
void Employee :: rent_car(string id,string my_car_name){
    int employee_record;
    my_vector.clear();
    read("employees.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==id) employee_record=stoi(my_vector[i][4]);
    }
    my_vector.clear();
    int flag=0;
    //if starts
    
    read("cars.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][0]==my_car_name && my_vector[i][4]=="0" && employee_record>=stoi(my_vector[i][2])){
            flag=1;
            cout<<"Car is available to you for "<<(int)(stoi(my_vector[i][2])*0.85)<<" rupees, giving a discount of "<<(stoi(my_vector[i][2])-(int)(stoi(my_vector[i][2])*0.85))<<" rupees!"<<endl;
            my_vector[i][4]="1";
            update_vector.clear();
            update_vector.push_back(id); //for employee id
            update_vector.push_back(my_car_name); //for car name
            update_vector.push_back(my_vector[i][2]); //for car price
            update_vector.push_back(my_vector[i][3]); //for car serial number
            update_vector.push_back(to_string(time(0))); //for rent date
            append_to_file(update_vector,"rented_cars.csv");
            cout<<"Your requested car has been successfully rented to you!"<<endl;
            break;
        }
        else if(my_vector[i][0]==my_car_name && my_vector[i][4]=="0" && employee_record<stoi(my_vector[i][2])){
            flag=1;
            cout<<"Requested car is available but cannot be rented due to bad employee record"<<endl;
        }
    }
    if(flag==0) cout<<"Requested car is not available to rent!"<<endl;
    write(my_vector,"cars.csv");
    my_vector.clear();
    
    //if ends
    
}
void Employee :: return_car(string id,string my_car_serial_no){
    my_vector.clear();
    int flag=0;
    int damage=0;
    int fine=damage*100;
    read("rented_cars.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][3]==my_car_serial_no && my_vector[i][0]==id){
            flag=1;
            my_vector.erase(my_vector.begin()+i,my_vector.begin()+i+1);
            cout<<"Car was rented to you and is now being returned by you"<<endl;
            cout<<"Please enter the damage done to the car in percentage: "<<endl;
            cin>>damage;
            while(damage<0||damage>100){
                cout<<"Please enter a valid amount between 0 to 100: "<<endl;
                cin>>damage;
            }
            fine=damage*100;
            int current_time=time(0);
            int rented_time=stoi(my_vector[i][4]);
            if(((int)((current_time-rented_time)/86400))>30){
                int late_days=((int)((current_time-rented_time)/86400))-30;
                fine+=late_days*stoi(my_vector[i][2])*0.01;
                cout<<"You are returning the car late by "<<late_days<<" days, and will hence face a fine of "<<fine<<" rupees"<<endl;
            }
            write(my_vector,"rented_cars.csv");
            my_vector.clear();
            read("cars.csv");
            for(int i=0;i<my_vector.size();i++){
                if(my_vector[i][3]==my_car_serial_no) my_vector[i][4]="0";
            }
            write(my_vector,"cars.csv");
            my_vector.clear();
            read("employees.csv");
            for(int i=0;i<my_vector.size();i++){  //for updating fine in the employee's record
                if(my_vector[i][1]==id){
                    int employee_record=stoi(my_vector[i][4]);
                    employee_record-=fine;
                    my_vector[i][4]=to_string(employee_record); //changes the value of employee record in my_vector to reflect fine
                }
            }
            write(my_vector,"employees.csv"); //writes back updated my_vector to the csv
            break;
        }
    }
    if(!flag) cout<<"This car has not been rented to you! Please retry with valid details."<<endl;
    else if(flag) cout<<"Car has been returned successfully!"<<endl;

    my_vector.clear();
}
void Employee :: show_record(string id){
    int flag=0;
    my_vector.clear();
    read("employees.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==id&&my_vector[i][3]=="2"){
            flag=1;
            cout<<"Your employee record stands at "<<my_vector[i][4]<<" as of now."<<endl;
        }
    }
    if(flag==0) cout<<"Requested employee was not found. Please retry with valid employee details."<<endl;
    
    my_vector.clear();
}
void Employee :: restore_account_balance(string id,string user_type){
    my_vector.clear();
    int employee_record,amount_to_be_paid;
    int flag=0;
    read("employees.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==id){
            flag=1;
            employee_record=stoi(my_vector[i][4]);
            cout<<"Please enter the amount you wish to pay towards your employee record: "<<endl;
            cin>>amount_to_be_paid;
            while(amount_to_be_paid<0){
                cout<<"Please enter a positive integer: "<<endl;
                cin>>amount_to_be_paid;
            }
            while(amount_to_be_paid>(max_balance-employee_record)){
                cout<<"You cannot exceed maximum employee record of 100000 rupees! Please re-enter amount: "<<endl;
                cin>>amount_to_be_paid;
            }
            cout<<"Now restoring your employee record to "<<employee_record+amount_to_be_paid<<" rupees...."<<endl;
            my_vector[i][4]=to_string(employee_record+amount_to_be_paid);
            break;
        }
    }
    write(my_vector,"employees.csv");
    my_vector.clear();
    
}
void Employee :: check_available(string id,string my_car_name){
    my_vector.clear();
    int flag=0;
    read("cars.csv");
    int ct=1;
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][0]==my_car_name && my_vector[i][4]=="0"){
            flag=1;
            cout<<ct<<". ";
            ct++;
            cout<<"Car is available to you for: "<<(int)(stoi(my_vector[i][2])*0.85)<<" rupees!"<<endl;
            for(auto j:my_vector[i])
                cout<<j<<" | ";
            cout<<endl;
            break;
        }
    }
    if(flag==0) cout<<"Requested car is not available"<<endl;
    my_vector.clear();
}


void Manager :: display_store_menu(string id){

    cout<<"---------------------------------------------------------------------"<<endl;
    cout<<endl<<"Welcome "<<id<<"! You are logged in as a Manager."<<endl<<endl;
    cout<<"Press 1 to add a user"<<endl;
    cout<<"Press 2 to update a user"<<endl;
    cout<<"Press 3 to delete a user"<<endl;
    cout<<"Press 4 to add a car"<<endl;
    cout<<"Press 5 to update a car"<<endl;
    cout<<"Press 6 to delete a car"<<endl;
    cout<<"Press 7 to see all cars rented to a particular user"<<endl;
    cout<<"Press 8 to see which car is rented to which user"<<endl;
    cout<<"Press 9 to view all users"<<endl;
    cout<<"Press 0 to view all cars"<<endl;
    cout<<"Press d to show due date of a car"<<endl;
    cout<<"Press l to logout"<<endl;
    cout<<"---------------------------------------------------------------------"<<endl;
    char c;
    cin>>c;
    Manager m;
    User u;
    string my_car_serial_no,user_id;
    switch(c){
        case '1':
            m.add_user(id);
            m.display_store_menu(id);
            break;
        case '2':
            m.update_user(id);
            m.display_store_menu(id);
            break;
        case '3':
            m.delete_user(id);
            m.display_store_menu(id);
            break;
        case '4':
            m.add_car(id);
            m.display_store_menu(id);
            break;
        case '5':
            m.update_car(id);
            m.display_store_menu(id);
            break;
        case '6':
            m.delete_car(id);
            m.display_store_menu(id);
            break;
        case '7':
            cout<<"Enter the id of the user : ";
            cin>>user_id;
            m.browse_rented_to_user(id,user_id);
            m.display_store_menu(id);
            break;
        case '8':
            m.browse_all_rented_cars(id);
            m.display_store_menu(id);
            break;
        case '9':
            m.browse_all_users(id);
            m.display_store_menu(id);
            break;
        case '0':
            m.browse_all_cars(id);
            m.display_store_menu(id);
            break;
        case 'd':
            cout<<"Enter the serial number of the car : ";
            cin>>my_car_serial_no;
            m.show_due_date(my_car_serial_no);
            m.display_store_menu(id);
            break;
        case 'l':
            u.logout();
            u.display_overall_menu();
            break;
        default:
            cout<<"Please enter a valid input and try again."<<endl;
            m.display_store_menu(id);
            return;
    }
}
void Manager :: browse_all_users(string id){
    my_vector.clear();
    cout<<"Below are all the users, in the order of all customers first, followed by all employees, and finally all managers. "<<endl;
    cout<<"The data is given in the form of username, user_id, type of user (1 for customer, 2 for employee, and 3 for manager), and user record."<<endl;
    cout<<"NOTE: Kindly be informed that user record for managers will always be fixed at 100000 and cannot be updated."<<endl<<endl;
    read("customers.csv");
    output_file_without_pwd(my_vector);
    my_vector.clear();
    read("employees.csv");
    output_file_without_pwd(my_vector);
    my_vector.clear();
    read("managers.csv");
    output_file_without_pwd(my_vector);
    my_vector.clear();
}
void Manager :: browse_all_cars(string id){
    my_vector.clear();
    read("cars.csv");
    cout<<"Given below is the data all the cars belonging to the store. 1 at the end signifies that it is currently rented to someone, while 0 signifies that it is available in store."<<endl<<endl;
    cout<<"The data is given in the form of car name, brand, rental price, serial number, and a number to signify whether it is rented or not."<<endl<<endl;
    output_file(my_vector);
    my_vector.clear();
}
void Manager :: show_due_date(string my_car_serial_no){
    my_vector.clear();
    string user_id;
    time_t stamp;
    read("rented_cars.csv");
    int flag=0;
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][3]==my_car_serial_no){
            flag=1;
            user_id = my_vector[i][0];
            stamp = stoi(my_vector[i][4]);
            break;
        }
    }
    my_vector.clear();
    int days=30;
    stamp+=days*86400;
    tm *return_time = localtime(&stamp);  
    if(flag==0) cout<<"Car was not rented!"<<endl;
    else{
        cout<<"Return date of the car is : ";
        cout<< return_time->tm_mday<<"/"<<1 + return_time->tm_mon<<"/"<<1900 + return_time->tm_year<<endl;
    }
}
void Manager :: add_user(string id){
    Manager m;
    cout<<"Please enter the details of the new user as follows: "<<endl<<endl;
    string _name,user_id,_password,_type;
    string _record="100000";
    cout<<"Enter type of the user you wish to add : 1 for customer, 2 for employee, 3 for manager : ";
    cin>>_type;
    while(_type!="1"&&_type!="2"&&_type!="3"){
        cout<<"Please enter a valid type of user!"<<endl;
        cout<<"Enter type of the user : 1 for customer, 2 for employee, 3 for manager : ";
        cin>>_type;
    }

    cout<<"Enter user name: ";
    cin.ignore();
    getline(cin,_name);
    cout<<"Enter user ID : ";
    cin>>user_id;

    my_vector.clear();

    read("customers.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==user_id){
            cout<<"This user ID has already been assigned to another user. Please re-enter user details with a different user ID."<<endl;
            cout<<"You will now be redirected to the store menu."<<endl;
           
            my_vector.clear();
            m.display_store_menu(id);
            return;
        }
    }
    my_vector.clear();

    read("employees.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==user_id){
            cout<<"This user ID has already been assigned to another user. Please re-enter user details with a different user ID."<<endl;
            cout<<"You will now be redirected to the store menu."<<endl;
            
            my_vector.clear();
            m.display_store_menu(id);
            return;
        }
    }
    my_vector.clear();

    read("managers.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==user_id){
            cout<<"This user ID has already been assigned to another user. Please re-enter user details with a different user ID."<<endl;
            cout<<"You will now be redirected to the store menu."<<endl;
            my_vector.clear();
            m.display_store_menu(id);
            return;
        }
    }
    my_vector.clear();

    
    
    if(_type=="1"){
        cout<<"Enter password (minimum length of password is 8 characters) : ";
        cin>>_password;
        while(_password.length()<=7){
            cout<<"Password length should be atleast 8 characters. Please re-enter a valid password."<<endl;
            cout<<"Enter password : ";
            cin>>_password;
        }
        fstream fout("customers.csv",ios::out | ios::app);
        fout<<_name<<","<<user_id<<","<<_password<<","<<_type<<","<<_record<<endl;
        cout<<"New customer has been added with customer record = 100000."<<endl;
    }else if(_type=="2"){
        cout<<"Enter password (minimum length of password is 8 characters) : ";
        cin>>_password;
        while(_password.length()<=7){
            cout<<"Password length should be atleast 8 characters. Please re-enter a valid password."<<endl;
            cout<<"Enter password : ";
            cin>>_password;
        }
        fstream fout("employees.csv",ios::out | ios::app);
        fout<<_name<<","<<user_id<<","<<_password<<","<<_type<<","<<_record<<endl;
        cout<<"New employee has been added with employee record = 100000."<<endl;
    }else{
        cout<<"Since you have selected manager, password will be auto-set with manager password."<<endl;
        fstream fout("managers.csv",ios::out | ios::app);
        _password="12345678";
        fout<<_name<<","<<user_id<<","<<_password<<","<<_type<<","<<_record<<endl;
        cout<<"New manager has been added."<<endl;
        
    }
    
}
void Manager :: update_user(string id){
    int flag1=0;
    int flag2=0;
    int flag3=0;
    string user_id;
    Manager m;
    cout<<"Enter the user ID of the user you wish to update : ";
    cin>>user_id;
    cout<<"Enter the serial number of the field you wish to update : "<<endl;
    cout<<"1. Password"<<endl;
    cout<<"2. Name of the User"<<endl;
    char c;
    cin>>c;
    my_vector.clear();
    read("customers.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==user_id){
            flag1=1;
            if(c=='1'){
                string new_password;
                cout<<"Enter the new password for the user (minimum 8 characters) : ";
                cin.ignore();
                getline(cin,new_password);
                while(new_password.size()<=7){
                    cout<<"Please enter a valid password which is minimum 8 characters in length: "<<endl;
                    cin.ignore();
                    getline(cin,new_password);
                }
                my_vector[i][2]=new_password;
            }
            else if(c=='2'){
                string new_name;
                cout<<"Enter the new name of the user : ";
                cin.ignore();
                getline(cin,new_name);
                my_vector[i][0]=new_name;
            }
            else{
                cout<<"Invalid input! Please choose between 1 or 2 only."<<endl<<endl;
            }
            break;
        }
    }
    if(flag1) cout<<"User has been updated successfully."<<endl;
    write(my_vector,"customers.csv");
    my_vector.clear();

    
    read("employees.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==user_id){
            flag2=1;
            if(c=='1'){
                string new_password;
                cout<<"Enter the new password for the user (minimum 8 characters) : ";
                cin.ignore();
                getline(cin,new_password);
                while(new_password.size()<=7){
                    cout<<"Please enter a valid password which is minimum 8 characters in length: "<<endl;
                    cin.ignore();
                    getline(cin,new_password);
                }
                my_vector[i][2]=new_password;
            }
            else if(c=='2'){
                string new_name;
                cout<<"Enter the new name of the user : ";
                cin.ignore();
                getline(cin,new_name);
                my_vector[i][0]=new_name;
            }
            else{
                cout<<"Invalid input! Please choose between 1 or 2 only."<<endl<<endl;
            }
            break;
        }
    }
    if(flag2) cout<<"User has been updated successfully."<<endl;
    write(my_vector,"employees.csv");
    my_vector.clear();

   
    read("managers.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==user_id){
            flag3=1;
            if(c=='1'){
                cout<<"You can only update the name of managers and cannot update the password for managers due to security issues. Please try again."<<endl;
                my_vector.clear();
                m.display_store_menu(id);
                return;
            }
            else if(c=='2'){
                string new_name;
                cout<<"Enter the new name of the user : ";
                cin.ignore();
                getline(cin,new_name);
                my_vector[i][0]=new_name;
            }
            else{
                cout<<"Invalid input! Please choose between 1 or 2 only."<<endl<<endl;
            }
            break;
        }
    }
    if(flag3) cout<<"User has been updated successfully."<<endl;
    write(my_vector,"managers.csv");
    my_vector.clear();
    if(flag1==0&&flag2==0&&flag3==0) cout<<"Requested user was not found. Please retry again with valid user details."<<endl;
}
void Manager :: delete_user(string id){
    string user_id;
    cout<<"Enter the user id of the user : ";
    cin>>user_id;
    my_vector.clear();
    int flag=0;
    read("customers.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==user_id){
            flag=1;
            my_vector.erase(my_vector.begin()+i,my_vector.begin()+i+1);
            break;
        }
    }
    write(my_vector,"customers.csv");
    my_vector.clear();
    read("employees.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==user_id){
            flag=1;
            my_vector.erase(my_vector.begin()+i,my_vector.begin()+i+1);
            break;
        }
    }
    write(my_vector,"employees.csv");
    my_vector.clear();
    read("managers.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][1]==user_id){
            flag=1;
            my_vector.erase(my_vector.begin()+i,my_vector.begin()+i+1);
            break;
        }
    }
    write(my_vector,"managers.csv");
    my_vector.clear();



    vector<string> car_serial_nos;
    read("rented_cars.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][0]==user_id){
            car_serial_nos.push_back(my_vector[i][3]);
            my_vector.erase(my_vector.begin()+i,my_vector.begin()+i+1);
            break;
        }
    }
    write(my_vector,"rented_cars.csv");
    my_vector.clear();

    read("cars.csv");
    for(int i=0;i<my_vector.size();i++){
        for(int j=0;j<car_serial_nos.size();j++){
            if(car_serial_nos[j]==my_vector[i][3]){
                my_vector[i][4]="0";
            }
        }
    }
    write(my_vector,"cars.csv");

    if(flag) cout<<"User has been deleted successfully. You may view the user database to confirm your changes."<<endl;
    if(flag==0) cout<<"Requested user has not been found. Please retry with valid user details."<<endl;
}
void Manager :: add_car(string id){
    Manager m;
    cout<<"Please enter the details of the new car as follows: "<<endl;
    string my_car_name,brand,price,my_car_serial_number;
    cout<<"Enter serial number of the car : ";
    cin>>my_car_serial_number;
    my_vector.clear();
    read("cars.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][3]==my_car_serial_number){
            cout<<"This serial number has already been assigned to another car. Please re-enter car details with a different serial number."<<endl;
            cout<<"You will now be redirected to the store menu."<<endl;
            my_vector.clear();
            m.display_store_menu(id);
            return;
        }
    }
    my_vector.clear();
    cout<<"Enter the name of the car: ";
    cin.ignore();
    getline(cin, my_car_name);
    cout<<"Enter car brand : ";
    cin>>brand;
    cout<<"Enter the price you wish to set for this car: ";
    cin>>price;
    fstream fout("cars.csv",ios::out | ios::app);
    fout<<my_car_name<<","<<brand<<","<<price<<","<<my_car_serial_number<<",0"<<endl;
    cout<<"New car has been added successfully."<<endl;
}
void Manager :: update_car(string id){
    Manager m;
    string my_car_serial_no;
    cout<<"Enter the serial number of the car you wish to update : ";
    cin>>my_car_serial_no;
    cout<<"Enter the number of the field you wish to update : "<<endl;
    cout<<"1. Name of the car"<<endl;
    cout<<"2. Brand of the car"<<endl;
    cout<<"3. Price of the car"<<endl;
    char c;
    cin>>c;
    my_vector.clear();
    int flag=0;
    string new_car_name;
    string new_brand;
    int new_price;
    read("cars.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][3]==my_car_serial_no){
            flag=1;
            if(c=='1'){
                cout<<"Enter the new name of the car : ";
                cin.ignore();
                getline(cin,new_car_name);
                my_vector[i][0]=new_car_name;
            }
            else if(c=='2'){
                cout<<"Enter the new brand of the car : ";
                cin.ignore();
                getline(cin,new_brand);
                my_vector[i][1]=new_brand;
            }
            else if(c=='3'){
                cout<<"Enter the new rental price of the car : ";
                cin>>new_price;
                while(new_price<0||new_price>100000){
                    cout<<"Please enter a valid number between 0 and 100000"<<endl;
                    cin>>new_price;
                }
                my_vector[i][2]=to_string(new_price);
            }
            else{
                cout<<"Invalid input! Please retry with valid choice (1, 2 or 3)."<<endl;
                my_vector.clear();
                m.update_car(id);
            }
            break;
        }
    }
    write(my_vector,"cars.csv");
    my_vector.clear();
    
    read("rented_cars.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][3]==my_car_serial_no){
            flag=1;
            if(c=='1'){
                my_vector[i][1]=new_car_name;
            }else if(c=='3'){
                my_vector[i][2]=to_string(new_price);
            }
            break;
        }
    }
    write(my_vector,"rented_cars.csv");
    if(flag) cout<<"Requested car has been updated."<<endl;
    if(flag==0) cout<<"Requested car was not found. Please retry with valid car details."<<endl<<endl;
}
void Manager :: delete_car(string id){
    string my_car_serial_no;
    cout<<"Enter the serial number of the car : ";
    cin>>my_car_serial_no;
    my_vector.clear();
    int flag=0;
    read("cars.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][3]==my_car_serial_no){
            flag=1;
            my_vector.erase(my_vector.begin()+i,my_vector.begin()+i+1);
            break;
        }
    }
    write(my_vector,"cars.csv");
    my_vector.clear();
    read("rented_cars.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][3]==my_car_serial_no){
            my_vector.erase(my_vector.begin()+i,my_vector.begin()+i+1);
            break;
        }
    }
    write(my_vector,"rented_cars.csv");
    my_vector.clear();
    if(flag) cout<<"Car has successfully been deleted. You may view the car database to confirm the changes."<<endl;
    if(flag==0) cout<<"Requested car has not been found. Please retry with valid car details."<<endl;
}

void Manager ::browse_rented_to_user(string id,string user_id){
    vector<string> car_serial_nos;
    my_vector.clear();
    int ct=1;
    read("rented_cars.csv");
    for(int i=0;i<my_vector.size();i++){
        if(my_vector[i][0]==user_id){
            car_serial_nos.push_back(my_vector[i][3]);
        }
    }
    write(my_vector,"rented_cars.csv");
    my_vector.clear();
    if(car_serial_nos.size()==0) cout<<"No car is rented to this user as of now."<<endl;
    else{
        cout<<"The following cars have been rented to the user: "<<endl;
        read("cars.csv");
        for(int d=0;d<car_serial_nos.size();d++){
            for(int i=0;i<my_vector.size();i++){
                if(my_vector[i][3]==car_serial_nos[d]){
                    cout<<ct<<". ";
                    ct++;
                    for(auto word:my_vector[i]){
                        if(word!=my_vector[i].back()) cout<<word<<" | ";
                        else cout<<word<<endl;
                    }
                }
            }
        }
        my_vector.clear();
    }
}

void Manager :: browse_all_rented_cars(string id){
    my_vector.clear();
    read("rented_cars.csv");
    if(my_vector.size()==0) cout<<"There are no cars rented to any user as of now."<<endl;
    for(int i=0;i<my_vector.size();i++){
        cout<<"Car with serial number "<<my_vector[i][3]<<" and name "<<my_vector[i][1]<<" is rented to user with ID : "<<my_vector[i][0]<<endl;
        
    }
    my_vector.clear();
}
int main(){
    User u;
    u.display_overall_menu();
    return 0;
}


