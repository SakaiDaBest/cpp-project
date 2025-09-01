#include <iostream>
using namespace std;

class AbstractEmp {
	virtual void AskForPromotion()=0;//abstract class, if use abstracemp then must have this
};

class Employee:AbstractEmp {
protected:
string Name;//if in protected:, then developer can use
string Company;
int Age;
//cannot use this anymore
	/*employee1.Name = "Sakai";
	employee1.Company = "Best Comp";
	employee1.Age = 69;*/
public:
	void setName(string name){//setter (set private info)
		Name = name;
	}
	string getName(){//getter (for private info)
		return Name;
	}
	void setComp(string comp){
		Company = comp;
	}
	string getComp(){
		return Company;
	}
	void setAge(int age){
		if(age>=18)Age = age;

	}
	int getAge(){
		return Age;
	}

	void Intro() {
		cout << "Name - " << Name << endl;
		cout << "Company - " << Company << endl;
		cout << "Age - " << Age << endl;
	}
	Employee(string name, string company, int age){//removes default constructor(this is a constructor)
		Name = name;
		Company = company;
		Age = age;
	}
	void AskForPromotion(){
		if(Age>30){
			cout << Name << " got Promoted"<<endl;
		}else{
			cout << Name << " tak ada promotion"<<endl;
		}
	}
	virtual void Work(){ //virtual checks if parent got same fuction
		cout << Name << " is checking email, task backlog, performing task... " << endl;
	}
};

class Developer:public Employee {
public:
	string FavLanguage;
	Developer(string name, string company, int age, string favLanguage)
		:Employee(name,company,age){FavLanguage=favLanguage;}
	void FixBug(){
		cout << getName()<< " fixed bug using " << FavLanguage <<endl; 
	}
	void Work(){
		cout << Name << " is writing "<< FavLanguage << endl;
	}

};

class Teacher: public Employee{
public:
	string Subject;
	Teacher(string name, string company, int age, string subject):Employee(name,company,age){Subject = subject;}
	void PrepareLesson(){
		cout << Name << " is preparing " << Subject << " Lesson"<<endl;
	}

	void Work(){
		cout << Name << " is Teaching "<< Subject << endl;
	}
};

int main() {
	Employee employee1= Employee("Sakai", "Best Comp", 69);//need default constructor
	/*employee1.Name = "Sakai";
	employee1.Company = "Best Comp";
	employee1.Age = 69;*/
	employee1.Intro();

    Employee employee2 = Employee("John", "Microsoft", 21);
    /*employee2.Name = "John";
    employee2.Company = "Microsoft";
    employee2.Age = 21;*/
    employee2.Intro();

	Developer d = Developer("Chicken", "Boring", 19, "C++");
	d.FixBug();
	d.AskForPromotion();
	d.Work();

	Teacher t = Teacher("Max", "Banana", 35, "Math");
	t.PrepareLesson();
	t.AskForPromotion();
	t.Work();

	//employee1.setAge(70);
	//cout << employee1.getAge() << endl << employee1.getName();
	employee1.AskForPromotion();

	Employee *e1 = &d;
	Employee *e2 = &t;
	e1->Work();
	e2->Work();
} 