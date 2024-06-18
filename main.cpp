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

class inventory {
    protected:
        string name;
        int stock;
    
    public:
        inventory(string inpName, int inpStock) {
            name = inpName;
            stock = inpStock;
        }

        // Getter
        string getName() {return name;}
        int getStock() {return stock;}

        // Setter
        void setName(string inpName) {name = inpName;}
        void setStock(int inpStock) {stock = inpStock;}
};

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
            return "Name: " + name + ", Age: " + to_string(getAge()) + " years old";
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
        string getStringType() {
            if (type == Chef) {
                return "Chef";
            }
            else {
                return "Waiter";
            }
        }

        // Setter
        void setType(EmployeeType inpType) {type = inpType;}
        void setSalary(int inpSalary) {salary = inpSalary;}

        // Method
        string intro() override {
            return People::intro() + ", Emp Type: " + getStringType() + ", Salary: " + to_string(salary) + ".";
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
        string getStringType() {
            if (type == Basic) {
                return "Basic";
            }
            else if (type == Gold) {
                return "Gold";
            }
            else if (type == Platinum) {
                return "Platinum";
            }
            else {
                return "Diamond";
            }
        }

        // Setter
        void setType(MemberType inpType) {type = inpType;}

        // Method
        string intro() override {
            return People::intro() + ", Membership: " + getStringType() + ".";
        }
};

class Menu {
    protected:
        string name;
        int price;
        string ingredient;
        int amount;
    
    public:
        Menu(string inpName, int inpPrice, string inpIngredient, int inpAmount) {
            name = inpName;
            price = inpPrice;
            ingredient = inpIngredient; 
            amount = inpAmount;
        }

        // Getter
        string getName() {return name;}
        int getPrice() {return price;}
        string getIngredient() {return ingredient;}
        int getAmount() {return amount;}

        // Setter
        void setName(string inpName) {name = inpName;}
        void setPrice(int inpPrice) {price = inpPrice;}
        void setIngredient(string inpIngredient) {ingredient = inpIngredient;}
        void setAmount(int inpAmount) {amount = inpAmount;}
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
        double getTotalPriceAfterDisc() {
            vector<double> discountList = {0.0, 8.0, 16.0, 20.0};
            MemberType memberType = getType();

            return totalPrice - (totalPrice * (discountList[memberType] / 100.0));
        } 
        int getTotalPrice() {return totalPrice;}

        // Setter
        void addItem(Menu item) {
            items.push_back(item);
            totalPrice += item.getPrice();
        }

        // Method
        string intro() override {
            return Customer::intro() + " with total price " + "Rp " + to_string(getTotalPriceAfterDisc());
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
vector<Employee*> EmployeeList;
vector<Customer*> CustomerList;
vector<inventory*> InventoryList;

// !INVENTORY
void addinventory() {
    string name;
    int stock;

    cin.ignore();
    cout << "Enter inventory's name: ";
    getline(cin, name);
    cout << "Enter inventory's stock: ";
    cin >> stock;

    InventoryList.push_back(new inventory(name, stock));
}

bool inventoryenough(string name, int amount) {
    for(auto &inventory : InventoryList) {
        if (name == inventory->getName()) {
            if (inventory->getStock() >= amount) {
                return true;
            }
            else {
                cout << "Inventory not enough!" << endl;
                return false;
            }
        }
        else {
            cout << "Inventory not found!" << endl;
            return false;
        }
    }
    return false;
}

void useinventory(string name, int amount) {
    for(auto &inventory : InventoryList) {
        if (name == inventory->getName()) {
            inventory->setStock(inventory->getStock() - amount);
        }
        else {
            cout << "Inventory not found!" << endl;
        }
    }
}

// !EMPLOYEE
void addemployee() {
    string name;
    Date birthDate;
    int salary, typenum;
    EmployeeType type;

    cin.ignore();
    cout << "Enter employee's name: ";
    getline(cin, name);    
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
        cin.ignore();
        cout << "Enter employee's name: ";
        getline(cin, name);
        if (name == employee->getName()) {
            cout << "Enter new employee's name: ";
            getline(cin, newName);
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
        cin.ignore();
        cout << "Enter employee's name: ";
        getline(cin, name);
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

// !CUSTOMER
void addCostumer() {
    string name;
    Date birthDate;
    int typenum;
    MemberType type;

    cin.ignore();
    cout << "Enter customer's name: ";
    getline(cin, name);    
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
        cin.ignore();
        cout << "Enter customer's name: ";
        getline(cin, name);
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
        cin.ignore();
        cout << "Enter customer's name: ";
        getline(cin, name);
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

// !MENU
void addMenu() {
    string name;
    int price;
    string ingredient;
    int amount;    

    cin.ignore();
    cout << "Enter menu's name: ";
    getline(cin, name);
    cout << "Enter menu's price: ";
    cin >> price;
    cin.ignore();
    cout << "Enter menu's ingredient: ";
    getline(cin, ingredient);
    cout << "Enter ingredients's amount: ";
    cin >> amount;
    cin.ignore();

    MenuList.push_back(new Menu(name, price, ingredient, amount));
}

void ModifyMenu() {
    string name, newName;
    int price;
    string newingredient;
    int newamount;
    
    for(auto &menu : MenuList) {
        cin.ignore();
        cout << "Enter menu's name: ";
        getline(cin, name);
        if (name == menu->getName()) {
            cout << "Enter new menu's name: ";
            getline(cin, newName);
            cout << "Enter new menu's price: ";
            cin >> price;
            cin.ignore();
            cout << "Enter new menu's ingredient: ";
            getline(cin, newingredient);
            cout << "Enter new ingredients's amount: ";
            cin >> newamount;
            cin.ignore();

            menu->setName(newName);
            menu->setPrice(price);
            menu->setIngredient(newingredient);
            menu->setAmount(newamount);

        }
        else {
            cout << "Menu not found!" << endl;
        }
    }
}

void deleteMenu() {
    string name;
    for(auto &menu : MenuList) {
        cin.ignore();
        cout << "Enter menu's name: ";
        getline(cin, name);
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
        cout << "# " << menu->getName() << " - Rp " << menu->getPrice() << ", Ingredients: " << endl << menu->getIngredient() << "(" << menu->getAmount() << ")" << endl;
    }
}

// !ORDER
void addOrder() {
    string customerName, menuName;
    int customerIndex = -1, menuIndex = -1;
    
    // Get customer name
    cin.ignore();
    cout << "Enter customer's name: ";
    getline(cin, customerName);
    
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
    getline(cin, menuName);
    
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
    
    if (!inventoryenough(MenuList[menuIndex]->getIngredient(), MenuList[menuIndex]->getAmount())) {
        cout << "Inventory not enough!" << endl;
        return;
    } else {
        useinventory(MenuList[menuIndex]->getIngredient(), MenuList[menuIndex]->getAmount());
    }
    // Create new order and add menu item
    OrderList.push_back(Order(CustomerList[customerIndex]->getName(), CustomerList[customerIndex]->getBirthDate(), CustomerList[customerIndex]->getType()));
    OrderList.back().addItem(*MenuList[menuIndex]);


    for (int i = 0; i < OrderList.size(); i++) {
        cout << i + 1 << ". " << OrderList[i].intro() << endl;
    }
}

int main() {
    cout << "-----------------------------------------------------------" << endl;
    cout << "---------------- Sistem Manajemen Restoran ----------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "------ Daffa Rajendra, Kevin Anugerah, Dimas Andhika ------" << endl;

    while(true) {
        cout << "-----------------------------------------------------------" << endl;
        cout << "1. Inventory Management" << endl;
        cout << "2. Employee Management" << endl;
        cout << "3. Customer Management" << endl;
        cout << "4. Menu Management" << endl;
        cout << "5. Order" << endl;
        cout << "6. Exit" << endl;

        cout << "-----------------------------------------------------------" << endl;
        cout << "Choose: ";
        int choose;
        cin >> choose;
        cout << "-----------------------------------------------------------" << endl;

        if (choose == 1) {
            cout << "1. Add Inventory" << endl;
            cout << "2. Show Inventory" << endl;
            cout << "-----------------------------------------------------------" << endl;
            cout << "Choose: ";
            int choose;
            cin >> choose;
            cout << "-----------------------------------------------------------" << endl;

            if (choose == 1) {
                addinventory();
            } else if (choose == 2) {
                for(auto &inventory : InventoryList) {
                    cout << inventory->getName() << " - " << inventory->getStock() << endl;
                }
            }
        }
        else if (choose == 2) {
            cout << "1. Add Employee" << endl;
            cout << "2. Modify Employee" << endl;
            cout << "3. Delete Employee" << endl;
            cout << "4. Show Employee" << endl;
            cout << "---------------------------------------------------------------------------" << endl;
            cout << "Choose: ";
            int choose;
            cin >> choose;
            cout << "---------------------------------------------------------------------------" << endl;

            if (choose == 1) {
                addemployee();
            } else if (choose == 2) {
                ModifyEmployee();
            } else if (choose == 3) {
                deleteEmployee();
            } else if (choose == 4) {
                showEmployee();
            }
        }
        else if (choose == 3) {
            cout << "1. Add Customer" << endl;
            cout << "2. Modify Customer" << endl;
            cout << "3. Delete Customer" << endl;
            cout << "4. Show Customer" << endl;
            cout << "---------------------------------------------------------------------------" << endl;
            cout << "Choose: ";
            int choose;
            cin >> choose;
            cout << "---------------------------------------------------------------------------" << endl;

            if (choose == 1) {
                addCostumer();
            }
            else if (choose == 2) {
                ModifyCustomer();
            }
            else if (choose == 3) {
                deleteCustomer();
            }
            else if (choose == 4) {
                showCustomer();
            }
        }
        else if (choose == 4) {
            cout << "1. Add Menu" << endl;
            cout << "2. Modify Menu" << endl;
            cout << "3. Delete Menu" << endl;
            cout << "4. Show Menu" << endl;
            cout << "---------------------------------------------------------------------------" << endl;
            cout << "Choose: ";
            int choose;
            cin >> choose;
            cout << "---------------------------------------------------------------------------" << endl;

            if (choose == 1) {
                addMenu();
            }
            else if (choose == 2) {
                ModifyMenu();
            }
            else if (choose == 3) {
                deleteMenu();
            }
            else if (choose == 4) {
                showMenu();
            }
            else if (choose == 5) {
                break;
            }
        } else if (choose == 5) {
            addOrder();
        } else if (choose == 6) {
            break;
        } else {
            cout << "Invalid input!" << endl;
        }
    }
}
