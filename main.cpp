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

vector<Order> OrderList;
vector<Menu*>  MenuList;
vector<People*> PeopleList;
vector<Employee*> EmployeeList;
vector<Customer*> CustomerList;

void addemployee() {
    string name;
    Date birthDate;
    int salary, typenum;
    EmployeeType type;

    cout << "Enter employee's name: ";
    cin >> name;    
    cout << "Enter employee's birth date (dd mm yyyy): ";
    cin >> birthDate.day >> birthDate.month >> birthDate.year;
    cout << "Enter employee's salary: ";
    cin >> salary;
    cout << "Enter employee's type (0 for Chef, 1 for Waiter): ";
    cin >> typenum;
    type = (EmployeeType)typenum;

    EmployeeList.push_back(new Employee(name, birthDate, type, salary));    
}

void ModifyEmployee() {
    string name, newName;
    Date birthDate;
    int salary, typenum;
    EmployeeType type;
    
    for(auto &employee : EmployeeList) {
        cout << "Enter employee's name: ";
        cin >> name;
        if (name == employee->getName()) {
            cout << "Enter new employee's name: ";
            cin >> newName;
            cout << "Enter new employee's birth date (dd mm yyyy): ";
            cin >> birthDate.day >> birthDate.month >> birthDate.year;
            cout << "Enter new employee's salary: ";
            cin >> salary;
            cout << "Enter new employee's type (0 for Chef, 1 for Waiter): ";
            cin >> typenum;
            type = (EmployeeType)typenum;

            employee->setName(newName);
            employee->setBirthDate(birthDate);
            employee->setSalary(salary);
            employee->setType(type);
        }
        else {
            cout << "Employee not found!" << endl;
        }
    }
}

void deleteEmployee() {
    string name;
    for(auto &employee : EmployeeList) {
        cout << "Enter employee's name: ";
        cin >> name;
        if (name == employee->getName()) {
            EmployeeList.erase(remove(EmployeeList.begin(), EmployeeList.end(), employee), EmployeeList.end());
        }
        else {
            cout << "Employee not found!" << endl;
        }
    }
}

void showEmployee() {
    for(auto &employee : EmployeeList) {
        cout << employee->intro() << endl;
    }
}

void addCostumer() {
    string name;
    Date birthDate;
    int typenum;
    MemberType type;

    cout << "Enter customer's name: ";
    cin >> name;    
    cout << "Enter customer's birth date (dd mm yyyy): ";
    cin >> birthDate.day >> birthDate.month >> birthDate.year;
    cout << "Enter customer's type (0 for Basic, 1 for Gold, 2 for Platinum, 3 for Diamond): ";
    cin >> typenum;
    type = (MemberType)typenum;

    CustomerList.push_back(new Customer(name, birthDate, type));    
}

void ModifyCustomer() {
    string name, newName;
    Date birthDate;
    int typenum;
    MemberType type;
    
    for(auto &customer : CustomerList) {
        cout << "Enter customer's name: ";
        cin >> name;
        if (name == customer->getName()) {
            cout << "Enter new customer's name: ";
            cin >> newName;
            cout << "Enter new customer's birth date (dd mm yyyy): ";
            cin >> birthDate.day >> birthDate.month >> birthDate.year;
            cout << "Enter new customer's type (0 for Basic, 1 for Gold, 2 for Platinum, 3 for Diamond): ";
            cin >> typenum;
            type = (MemberType)typenum;

            customer->setName(newName);
            customer->setBirthDate(birthDate);
            customer->setType(type);
        }
        else {
            cout << "Customer not found!" << endl;
        }
    }
}

void deleteCustomer() {
    string name;
    for(auto &customer : CustomerList) {
        cout << "Enter customer's name: ";
        cin >> name;
        if (name == customer->getName()) {
            CustomerList.erase(remove(CustomerList.begin(), CustomerList.end(), customer), CustomerList.end());
        }
        else {
            cout << "Customer not found!" << endl;
        }
    }
}

void showCustomer() {
    for(auto &customer : CustomerList) {
        cout << customer->intro() << endl;
    }
}

void addMenu() {
    string name;
    int price;

    cout << "Enter menu's name: ";
    cin >> name;
    cout << "Enter menu's price: ";
    cin >> price;

    MenuList.push_back(new Menu(name, price));
}

void ModifyMenu() {
    string name, newName;
    int price;
    
    for(auto &menu : MenuList) {
        cout << "Enter menu's name: ";
        cin >> name;
        if (name == menu->getName()) {
            cout << "Enter new menu's name: ";
            cin >> newName;
            cout << "Enter new menu's price: ";
            cin >> price;

            menu->setName(newName);
            menu->setPrice(price);
        }
        else {
            cout << "Menu not found!" << endl;
        }
    }
}

void deleteMenu() {
    string name;
    for(auto &menu : MenuList) {
        cout << "Enter menu's name: ";
        cin >> name;
        if (name == menu->getName()) {
            MenuList.erase(remove(MenuList.begin(), MenuList.end(), menu), MenuList.end());
        }
        else {
            cout << "Menu not found!" << endl;
        }
    }
}

void showMenu() {
    for(auto &menu : MenuList) {
        cout << menu->getName() << " - Rp " << menu->getPrice() << endl;
    }
}

void addOrder() {
    string customerName, menuName;
    int customerIndex = -1, menuIndex = -1;
    
    // Get customer name
    cout << "Enter customer's name: ";
    cin >> customerName;
    
    // Find customer index
    for (int i = 0; i < CustomerList.size(); i++) {
        if (CustomerList[i]->getName() == customerName) {
            customerIndex = i;
            break;
        }
    }
    
    // Check if customer exists
    if (customerIndex == -1) {
        cout << "Customer not found!" << endl;
        return;
    }
    
    // Get menu name
    cout << "Enter menu's name: ";
    cin >> menuName;
    
    // Find menu index
    for (int i = 0; i < MenuList.size(); i++) {
        if (MenuList[i]->getName() == menuName) {
            menuIndex = i;
            break;
        }
    }
    
    // Check if menu exists
    if (menuIndex == -1) {
        cout << "Menu not found!" << endl;
        return;
    }
    
    // Create new order and add menu item
    OrderList.push_back(Order(CustomerList[customerIndex]->getName(), CustomerList[customerIndex]->getBirthDate(), CustomerList[customerIndex]->getType()));
    OrderList.back().addItem(*MenuList[menuIndex]);
}

void modifyOrder() {
    string customerName, menuName;
    int customerIndex = -1, menuIndex = -1;
    
    // Get customer name
    cout << "Enter customer's name: ";
    cin >> customerName;
    
    // Find customer index
    for (int i = 0; i < OrderList.size(); i++) {
        if (OrderList[i].getName() == customerName) {
            customerIndex = i;
            break;
        }
    }
    
    // Check if customer exists
    if (customerIndex == -1) {
        cout << "Customer not found!" << endl;
        return;
    }
    
    // Get menu name
    cout << "Enter menu's name: ";
    cin >> menuName;
    
    // Find menu index
    for (int i = 0; i < MenuList.size(); i++) {
        if (MenuList[i]->getName() == menuName) {
            menuIndex = i;
            break;
        }
    }
    
    // Check if menu exists
    if (menuIndex == -1) {
        cout << "Menu not found!" << endl;
        return;
    }
    
    // Add menu item
    OrderList[customerIndex].addItem(*MenuList[menuIndex]);
}

void deleteOrder() {
    string customerName;
    int customerIndex = -1;
    
    // Get customer name
    cout << "Enter customer's name: ";
    cin >> customerName;
    
    // Find customer index
    for (int i = 0; i < OrderList.size(); i++) {
        if (OrderList[i].getName() == customerName) {
            customerIndex = i;
            break;
        }
    }
    
    // Check if customer exists
    if (customerIndex == -1) {
        cout << "Customer not found!" << endl;
        return;
    }
    
    // Delete order
    OrderList.erase(OrderList.begin() + customerIndex);
}

void showOrder() {
    for (int i = 0; i < OrderList.size(); i++) {
        cout << i + 1 << ". " << OrderList[i].intro() << endl;
    }
}

int main() {
    while(true){
        int choice;
        cout << "1.Employee Management\n2.Customer Management\n3.Menu Management\n4.Order Management\n5.Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            int choice2;
            cout << "1.Add Employee\n2.Modify Employee\n3.Delete Employee\n4.Show Employee\n5.Back" << endl;
            cout << "Enter your choice: ";
            cin >> choice2;
            if (choice2 == 1) {
                addemployee();
            }
            else if (choice2 == 2) {
                ModifyEmployee();
            }
            else if (choice2 == 3) {
                deleteEmployee();
            }
            else if (choice2 == 4) {
                showEmployee();
            }
            else if (choice2 == 5) {
                continue;
            }
        }
        else if (choice == 2) {
            int choice2;
            cout << "1.Add Customer\n2.Modify Customer\n3.Delete Customer\n4.Show Customer\n5.Back" << endl;
            cout << "Enter your choice: ";
            cin >> choice2;
            if (choice2 == 1) {
                addCostumer();
            }
            else if (choice2 == 2) {
                ModifyCustomer();
            }
            else if (choice2 == 3) {
                deleteCustomer();
            }
            else if (choice2 == 4) {
                showCustomer();
            }
            else if (choice2 == 5) {
                continue;
            }
        }
        else if (choice == 3) {
            int choice2;
            cout << "1.Add Menu\n2.Modify Menu\n3.Delete Menu\n4.Show Menu\n5.Back" << endl;
            cout << "Enter your choice: ";
            cin >> choice2;
            if (choice2 == 1) {
                addMenu();
            }
            else if (choice2 == 2) {
                ModifyMenu();
            }
            else if (choice2 == 3) {
                deleteMenu();
            }
            else if (choice2 == 4) {
                showMenu();
            }
            else if (choice2 == 5) {
                continue;
            }
        }
        else if (choice == 4) {
            int choice2;
            cout << "1.Add Order\n2.Modify Order\n3.Delete Order\n4.Show Order\n5.Back" << endl;
            cout << "Enter your choice: ";
            cin >> choice2;
            if (choice2 == 1) {
                addOrder();
            }
            else if (choice2 == 2) {
                modifyOrder();
            }
            else if (choice2 == 3) {
                deleteOrder();
            }
            else if (choice2 == 4) {
                showOrder();
            }
            else if (choice2 == 5) {
                continue;
            }
        }
    }
}