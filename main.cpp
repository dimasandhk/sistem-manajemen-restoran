#include <bits/stdc++.h>
using namespace std;

enum EmployeeType { Chef, Waiter };
struct Date {int day, month, year;};

Date current_time() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    Date date;
    date.day = ltm->tm_mday;
    date.month = 1 + ltm->tm_mon;
    date.year = 1900 + ltm->tm_year;

    return date;
}

class People {
    protected:
        string name;
        Date birthDate;
    
    public:
        People(string inpName, Date inpBirthDate) {
            name = inpName;
            birthDate = inpBirthDate;
        }

        // Getter
        string getName() {return name;}
        Date getBirthDate() {return birthDate;}
        int getAge() {
            Date now = current_time();
            int age = now.year - birthDate.year;
            if (now.month < birthDate.month || (now.month == birthDate.month && now.day < birthDate.day)) {
                age--;
            }
            return age;
        }

        // Setter
        void setName(string inpName) {name = inpName;}
        void setBirthDate(Date inpBirthDate) {birthDate = inpBirthDate;}

        // Method
        virtual string intro() {
            return "Hello, my name is " + name + " and I'm " + to_string(getAge()) + " years old.";
        }

        bool isAdult() {
            return getAge() >= 18;
        }
};

class Employee : public People {
    protected:
        EmployeeType type;
        int salary;
    
    public:
        Employee(string inpName, Date inpBirthDate, EmployeeType inpType, int inpSalary) 
        : People(inpName, inpBirthDate) {
            type = inpType;
            salary = inpSalary;
        }

        // Getter
        EmployeeType getType() {return type;}
        int getSalary() {return salary;}

        // Setter
        void setType(EmployeeType inpType) {type = inpType;}
        void setSalary(int inpSalary) {salary = inpSalary;}

        // Method
        string intro() override {
            return People::intro() + " I'm an employee with type " + to_string(type) + " and salary " + to_string(salary) + ".";
        }
};

enum MemberType { Basic, Gold, Platinum, Diamond };

class Customer : public People {
    protected:
        MemberType type;
    
    public:
        Customer(string inpName, Date inpBirthDate, MemberType inpType) 
        : People(inpName, inpBirthDate) {
            type = inpType;
        }

        // Getter
        MemberType getType() {return type;}

        // Setter
        void setType(MemberType inpType) {type = inpType;}

        // Method
        string intro() override {
            return People::intro() + " I'm a customer with type " + to_string(type);
        }
};

class Menu {
    protected:
        string name;
        int price;
    
    public:
        Menu(string inpName, int inpPrice) {
            name = inpName;
            price = inpPrice;
        }

        // Getter
        string getName() {return name;}
        int getPrice() {return price;}

        // Setter
        void setName(string inpName) {name = inpName;}
        void setPrice(int inpPrice) {price = inpPrice;}
};

class Order : public Customer {
    protected:
        vector<Menu> items;
        int totalPrice;
    
    public:
        Order(string inpName, Date inpBirthDate, MemberType inpType) 
        : Customer(inpName, inpBirthDate, inpType) {
            totalPrice = 0;
        }

        // Getter
        int getTotalPriceAfterDisc() {
            vector<int> discountList = {0, 8, 16, 20};
            MemberType memberType = getType();

            return totalPrice - totalPrice * (discountList[memberType] / 100);
        }
        int getTotalPrice() {return totalPrice;}

        // Setter
        void addItem(Menu item) {
            items.push_back(item);
            totalPrice += item.getPrice();
        }

        // Method
        string intro() override {
            return Customer::intro() + " with total price " + to_string(totalPrice);
        }

        void printReceipt() {
            cout << "Receipt for " << getName() << ":\n";
            for (int i = 0; i < items.size(); i++) {
                cout << i + 1 << ". " << items[i].getName() << " - Rp " << items[i].getPrice() << endl;
            }

            cout << "Total price: Rp " << getTotalPrice() << endl;
            cout << "Total price after discount: Rp " << getTotalPriceAfterDisc() << endl;
        }
};

int main() {
    return 0;
}