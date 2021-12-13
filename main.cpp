#include<iostream>
#include<vector>
#include <cstdlib>
using namespace std;

class Date{
	public:
		int day;
		int month;
		int year;

	void printDate(){
		cout<<day<<"/"<<month<<"/"<<year<<"\n";
	}
	Date(){
		day = 1;
		month = 1;
		year = 2000;
	}
	Date(int a , int b, int c){
		day = a;
		month = b;
		year = c;
	}
};

class Employee{
	private:
		string first_Name;
		string sur_Name;
		Date date_Of_Birth;
		vector<Date> holiDays;
		int count_Holidays;
		int old_Age;

	public:
	    Employee(){
			first_Name = "";
			sur_Name = "";
			Date dob(0 , 0 ,0);
			date_Of_Birth = dob;
		}
		Employee(string s , string s1 , Date dob){
			sur_Name = s1;
			date_Of_Birth = dob;
			first_Name = s;
			if(dob.year < 1971)
				old_Age = 1;
			else
				old_Age = 0;

			count_Holidays = 0;
			cout<<"Employee called\n";
		}
		//adding Employee
		void setEmp(string s , string s1 , Date dob){
			first_Name = s;
			sur_Name = s1;
			date_Of_Birth = dob;
			if(dob.year < 1971)
				old_Age = 1;
			else
				old_Age = 0;

			cout<<"Employee Edited\n";
		}
		//output employee
		void printEmployee(){
			cout<<"Employee Name : ";
			cout<<first_Name<<" "<<sur_Name<<"\n";
			cout<<"Date of Birth :";
			date_Of_Birth.printDate();
			if(old_Age == 0)
				cout<<"Leaves left : "<<30-count_Holidays;
			else
				cout<<"Leaves left : "<<32-count_Holidays;
			cout<<"\n";
			cout<<"Total Leave Taken : "<<count_Holidays;
			cout<<"\n";
		}
		//printing all the dates of leaves
		void printAllLeaveDates(){
			cout<<"Dates on which Employee Taken the Leave\n";
			vector<Date> :: iterator i;
			for(i = holiDays.begin() ; i !=  holiDays.end() ; i++){
				(*i).printDate();
			}
		}

		//getters
		string getFirstName(){
			return first_Name;
		}

		string getLastName(){
			return sur_Name;
		}

		//leave checking and assiging
		int giveLeave(Date leaveDate){
			int total_Possible;
			if(old_Age == 0)
				total_Possible = 30;
			else
				total_Possible = 32;

			if(count_Holidays < total_Possible){
				holiDays.push_back(leaveDate);
				count_Holidays++;
				cout<<"\n";
				cout<<"Leave Granted\n";
				return 1;
			}
			else{
				cout<<"### MESSAGE ###\n";
				cout<<"You already Crossed the limit of maximum holidays\n";
				return 0;
			}
		}
};

//class hourlyEmployee inheriting Employee
class hourlyEmployee : public Employee{
    private:
        int hours_Worked;
        int hour_Wage;
    public:
        hourlyEmployee(int w, int h)
        {
            hours_Worked = h;
            hour_Wage = w;
        }
        hourlyEmployee(){}
        int getHoursWorked(){
            return hours_Worked;
        }
        int getHourWage(){
            return hour_Wage;
        }
};

//class salariedEmployee inheriting Employee
class salariedEmployee : public Employee{
    private:
        int annual_Salary;
    public:
        salariedEmployee(int as){
            annual_Salary = as;
        }
        salariedEmployee(){}
        int getAnnualSalary(){
            return annual_Salary;
        }
};

//class manager inheriting Employee
class Manager : public Employee{
    private:
        int profit_Sharing;
    public:
        Manager(){}
        Manager(int ps){
            profit_Sharing = ps;
        }
        int getProfitSharing(){
            return profit_Sharing;
        }
};

//creating employee
int createEmployee(vector<Employee> &Emp)
{
	string s , s1;
	int a , b, c;
	cout<<"Enter Employee First Name :  ";
	cin>>s;
	cout<<"Enter Employee Surname :  ";
	cin>>s1;
	cout<<"Enter Date Of Birth(format : 08 01 2001):  ";
	cin>>a;
	cin>>b;
	cin>>c;
	Date dob(a ,b ,c);

	Employee e1(s,s1,dob);
	Emp.push_back(e1);

	cout<<"Employee Created\n\n";
	return Emp.size();
}

//adding hourlyEmployee
void createHourlyEmployee(vector<Employee> &Emp)
{
    int h,w;
    hourlyEmployee HEmp[500];
    int n = 0;
    n = createEmployee(Emp);
    cout<<"Enter Number of Hours Worked\n";
    cin>>h;
    cout<<"Enter Hourly Wage\n";
    cin>>w;
    hourlyEmployee h1(w,h);
    HEmp[n]=h1;
}
//adding salariedEmployee
void createSalariedEmployee(vector<Employee> &Emp)
{
    int s;
    salariedEmployee SEmp[500];
    int n = 0;
    n = createEmployee(Emp);
    cout<<"Enter Salary\n";
    cin>>s;
    salariedEmployee s1(s);
    SEmp[n]=s1;
}
////adding Manager
void createManager(vector<Employee> &Emp)
{
    int p;
    Manager M[500];
    int n = 0;
    n = createEmployee(Emp);
    cout<<"Enter Profit Sharing Percentage\n";
    cin>>p;
    Manager m(p);
    M[n]=m;
}


//display all employee
void displayAllEmployee(vector<Employee> &Emp){
	int count =  Emp.size();
	if(count == 0)
		cout<<"No Employee available!!!!!!\n";

	else{
		for(int i = 0 ; i <= count-1 ; i++){
			cout<<i+1<<".\n";
			Emp[i].printEmployee();
			cout<<"\n\n";
		}
	}
}

//delete employee
void deleteEmployee(vector<Employee> &Emp){
	int count = Emp.size();
	if(count == 0){
		cout<<"There is no Employee to Delete\n";
		return;
	}

	string s,s1;
	cout<<"Enter the first name of employee : ";
	cin>>s;
	cout<<"Enter the surname of employee : ";
	cin>>s1;

	vector<Employee> :: iterator p = Emp.begin();
	vector<Employee> :: iterator i;
	for(i = Emp.begin() ; i != Emp.end() ; i++){
		if((*i).getFirstName() == s && (*i).getLastName() == s1){
			p = i;
			break;
		}
	}
	if(p == Emp.begin()){
		cout<<"Employee NOT FOUND !!!!!\n";
	}
	else{
		Emp.erase(p);
		cout<<"Employee Deleted!!!\n";
	}
}

// display one employee with dates of leave
void displayOneEmployee(vector<Employee> &Emp){
	string s , s1;
	cout<<"Enter the details of that Employee\n";
	cout<<"First Name : ";
	cin>>s;
	cout<<"Surname : ";
	cin>>s1;

	vector<Employee> :: iterator i;
	for(i = Emp.begin() ; i != Emp.end() ; i++){
		if((*i).getFirstName() == s && (*i).getLastName() == s1){
			cout<<"\n";
			(*i).printEmployee();
			(*i).printAllLeaveDates();
			break;
		}
	}
	if(i==Emp.end())
		cout<<"Employee not Found....\n";
}

//Give a Leave
void giveALeave(vector <Employee> &Emp){
	string s , s1;
	bool a = true;
	cout<<"Enter the Details of Employee\n";
	cout<<"First Name : ";
	cin>>s;
	cout<<"Surname : ";
	cin>>s1;
	while(a){
	cout<<"Enter the date Employee Want Leave For(format : 01 01 2000) : ";
	int a,b,c;
	cin>>a>>b>>c;
	Date leaveDate (a,b,c);

	vector<Employee> :: iterator i;
	for(i = Emp.begin() ; i !=  Emp.end(); i++){
		if((*i).getFirstName() == s && (*i).getLastName() == s1){
			(*i).giveLeave(leaveDate);
			break;
		}
	}
	int cc;
	cout<<"Want to give more leaves\n";
	cout<<"0. No\n";
	cout<<"1. Yes\n";
	cin>>b;
	if(b==0){
        a=false;
        break;
	}
	}
}

//main
int main(){
	int c = 1;
	int counter = 0;
	vector<Employee> Emp;
	while(c != 0){
        cout<<"*************************LEAVE MANAGEMENT SYSTEM*************************\n";
		cout<<"0 . EXIT\n";
		cout<<"1 . Create Employee\n";
		cout<<"2 . Delete Employee\n";
		cout<<"3 . Display All Employee\n";
		cout<<"4 . Show Specific Employee\n";
		cout<<"5 . Give a Leave\n";
        cout<<"*************************************************************************\n";
		cout<<"Enter your Choice\n";
		cin>>c;

		if(c == 1 && counter<501){
            system("cls");
            int u;
            cout<<"*************************************************************************\n";
            cout<<"1 . Manager\n";
            cout<<"2 . Salaried Employee\n";
            cout<<"3 . Hourly Employee\n";
            cout<<"*************************************************************************\n";
            cout<<"Enter your Choice\n";
            cin>>u;
            if(u == 1){
                system("cls");
                createManager(Emp);
                counter++;
            }

            else if(u == 2){
                system("cls");
                createSalariedEmployee(Emp);
                counter++;
            }

            else if(u==3){
                system("cls");
                createHourlyEmployee(Emp);
                counter++;
            }

            else
                cout<<"Wrong Selection";


		}
		else if(c == 2){
            system("cls");
			deleteEmployee(Emp);
			counter--;
		}
		else if(c == 3){
            system("cls");
			displayAllEmployee(Emp);
		}
		else if(c == 4){
            system("cls");
			displayOneEmployee(Emp);
		}
		else if(c ==5){
            system("cls");
			giveALeave(Emp);
		}
        else if(c ==0){
			system("cls");
			cout<<"Exiting Program";
			return 0;
        }
		else
			cout<<"Incorrect Choice!!!!\n";
		system("PAUSE");
        system("cls");

	}


}
