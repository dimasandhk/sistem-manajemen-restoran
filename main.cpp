#include <bits/stdc++.h>
using namespace std;

enum EmployeeType { Chef, Waiter };
enum MemberType { Basic, Gold, Platinum, Diamond };

struct Date {
    int day, month, year;
};

Date current_time() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    Date date;
    date.day = ltm->tm_mday;
    date.month = 1 + ltm->tm_mon;
    date.year = 1900 + ltm->tm_year;

    return date;
}

string formatPrice(int price) {
    stringstream ss;
    ss << "Rp " << price;
    return ss.str();
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
    string getName() const { return name; }
    Date getBirthDate() const { return birthDate; }
    int getAge() const {
        Date now = current_time();
        int age = now.year - birthDate.year;
        if (now.month < birthDate.month || (now.month == birthDate.month && now.day < birthDate.day)) {
            age--;
        }
        return age;
    }

    // Setter
    void setName(string inpName) { name = inpName; }
    void setBirthDate(Date inpBirthDate) { birthDate = inpBirthDate; }

    // Method
    virtual string intro() const {
        return "Name: " + name + ", Age: " + to_string(getAge()) + " years old";
    }

    bool isAdult() const {
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
    EmployeeType getType() const { return type; }
    int getSalary() const { return salary; }
    string getStringType() const {
        if (type == Chef) {
            return "Chef";
        } else {
            return "Waiter";
        }
    }

    // Setter
    void setType(EmployeeType inpType) { type = inpType; }
    void setSalary(int inpSalary) { salary = inpSalary; }

    // Method
    string intro() const override {
        return People::intro() + ", Emp Type: " + getStringType() + ", Salary: " + formatPrice(salary) + ".";
    }
};

class Customer : public People {
protected:
    MemberType type;

public:
    Customer(string inpName, Date inpBirthDate, MemberType inpType)
        : People(inpName, inpBirthDate) {
        type = inpType;
    }

    // Getter
    MemberType getType() const { return type; }
    string getStringType() const {
        if (type == Basic) {
            return "Basic";
        } else if (type == Gold) {
            return "Gold";
        } else if (type == Platinum) {
            return "Platinum";
        } else {
            return "Diamond";
        }
    }

    // Setter
    void setType(MemberType inpType) { type = inpType; }

    // Method
    string intro() const override {
        return People::intro() + ", Membership: " + getStringType() + ".";
    }
};

class Menu {
protected:
    string name;
    int price;
    vector<string> ingredients;
    vector<int> amounts;
    bool halal;

public:
    Menu(string inpName, int inpPrice, vector<string> inpIngredients, vector<int> inpAmounts) {
        name = inpName;
        price = inpPrice;
        ingredients = inpIngredients;
        amounts = inpAmounts;
        halal = true;
        for (const auto &ingredient : ingredients) {
            if (ingredient == "pork" || ingredient == "vodka") {
                halal = false;
                break;
            }
        }
    }

    string getName() const { return name; }
    int getPrice() const { return price; }
    vector<string> getIngredients() const { return ingredients; }
    vector<int> getAmounts() const { return amounts; }
    bool isHalal() const { return halal; }

    void setName(string inpName) { name = inpName; }
    void setPrice(int inpPrice) { price = inpPrice; }
    void setIngredients(vector<string> inpIngredients) { ingredients = inpIngredients; }
    void setAmounts(vector<int> inpAmounts) { amounts = inpAmounts; }
};

class Inventory {
protected:
    string name;
    int stock;

public:
    Inventory(string inpName, int inpStock) {
        name = inpName;
        stock = inpStock;
    }

    string getName() const { return name; }
    int getStock() const { return stock; }

    void setName(string inpName) { name = inpName; }
    void setStock(int inpStock) { stock = inpStock; }
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
    double getTotalPriceAfterDisc() const {
        vector<double> discountList = {0.0, 8.0, 16.0, 20.0};
        MemberType memberType = getType();

        return totalPrice - (totalPrice * (discountList[memberType] / 100.0));
    }
    int getTotalPrice() const { return totalPrice; }

    // Setter
    void addItem(Menu item) {
        items.push_back(item);
        totalPrice += item.getPrice();
    }

    // Method
    string intro() const override {
        return Customer::intro() + " with total price " + formatPrice(getTotalPriceAfterDisc());
    }

    void printReceipt() const {
        cout << "Receipt for " << getName() << ":\n";
        for (int i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i].getName() << " - " << formatPrice(items[i].getPrice()) << endl;
        }

        cout << "Total price: " << formatPrice(getTotalPrice()) << endl;
        cout << "Total price after discount: " << formatPrice(getTotalPriceAfterDisc()) << endl;
    }
};

vector<Menu*> MenuList;
vector<Employee*> EmployeeList;
vector<Customer*> CustomerList;
vector<Inventory*> InventoryList;
vector<Order> OrderList;

// Predefined menus and ingredients
void initializeMenuAndInventory() {
    vector<pair<string, vector<pair<string, int>>>> menuData = {
        {"Spaghetti", {{"spaghetti", 1}, {"white onion", 1}, {"red onion", 2}, {"tomato", 2}, {"herbs", 3}}},
        {"Spaghetti with roasted pork", {{"spaghetti", 1}, {"pork", 1}, {"white onion", 1}, {"red onion", 2}, {"milk", 1}, {"herbs", 2}}},
        {"Chicken karaage", {{"chicken meat", 1}, {"herbs", 2}, {"chili", 2}}},
        {"Chicken Ricebowl Sambal Matah", {{"chicken meat", 1}, {"red onion", 1}, {"chili", 4}, {"herbs", 3}}},
        {"Pisang Goreng", {{"banana", 1}}},
        {"Strawberry Smoothies", {{"strawberry", 1}, {"ice cubes", 2}, {"milk", 1}}},
        {"Cappuccino", {{"espresso shot", 1}, {"milk", 1}}},
        {"Oreo Milkshake", {{"oreo", 2}, {"milk", 1}, {"ice cubes", 2}, {"ice cream", 1}}},
        {"Lemon Tea", {{"tea", 1}, {"lemon", 1}, {"ice cubes", 2}}},
        {"Lemon Cocktail", {{"vodka", 1}, {"lemon", 1}, {"syrup", 1}, {"ice cubes", 2}}}
    };

    map<string, int> fixedPrices = {
        {"Spaghetti", 30000},
        {"Spaghetti with roasted pork", 60000},
        {"Chicken karaage", 27500},
        {"Chicken Ricebowl Sambal Matah", 27500},
        {"Pisang Goreng", 16500},
        {"Strawberry Smoothies", 24500},
        {"Cappuccino", 19500},
        {"Oreo Milkshake", 22500},
        {"Lemon Tea", 19500},
        {"Lemon Cocktail", 50000}
    };

    for (const auto &menu : menuData) {
        vector<string> ingredients;
        vector<int> amounts;
        for (const auto &ingredient : menu.second) {
            ingredients.push_back(ingredient.first);
            amounts.push_back(ingredient.second);
        }
        int price = fixedPrices[menu.first];
        MenuList.push_back(new Menu(menu.first, price, ingredients, amounts));
    }

    vector<string> ingredients = {"spaghetti", "red onion", "white onion", "chicken meat", "pork", "tomato", "herbs", "chili", "milk", "ice cream", "syrup", "ice cubes", "lemon", "oreo", "banana", "strawberry", "espresso shot", "tea", "vodka"};

    for (const auto &ingredient : ingredients) {
        InventoryList.push_back(new Inventory(ingredient, 30)); // Set default stock to 30
    }
}

// !INVENTORY
void addInventory() {
    string name;
    int stock;

    cin.ignore();
    cout << "Enter inventory's name: ";
    getline(cin, name);
    cout << "Enter inventory's stock: ";
    cin >> stock;

    InventoryList.push_back(new Inventory(name, stock));
}

bool inventoryEnough(Menu* menu) {
    for (int i = 0; i < menu->getIngredients().size(); i++) {
        string ingredient = menu->getIngredients()[i];
        int amountNeeded = menu->getAmounts()[i];

        bool found = false;
        for (auto &inventory : InventoryList) {
            if (inventory->getName() == ingredient) {
                if (inventory->getStock() < amountNeeded) {
                    return false;
                }
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

void useInventory(Menu* menu) {
    for (int i = 0; i < menu->getIngredients().size(); i++) {
        string ingredient = menu->getIngredients()[i];
        int amountNeeded = menu->getAmounts()[i];

        for (auto &inventory : InventoryList) {
            if (inventory->getName() == ingredient) {
                inventory->setStock(inventory->getStock() - amountNeeded);
                break;
            }
        }
    }
}

// !EMPLOYEE
void addEmployee() {
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

void modifyEmployee() {
    string name, newName;
    Date birthDate;
    int salary, typenum;
    EmployeeType type;

    cin.ignore();
    cout << "Enter employee's name: ";
    getline(cin, name);

    for (auto &employee : EmployeeList) {
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
            return;
        }
    }
    cout << "Employee not found!" << endl;
}

void deleteEmployee() {
    string name;
    cin.ignore();
    cout << "Enter employee's name: ";
    getline(cin, name);

    for (auto it = EmployeeList.begin(); it != EmployeeList.end(); ++it) {
        if ((*it)->getName() == name) {
            delete *it;
            EmployeeList.erase(it);
            return;
        }
    }
    cout << "Employee not found!" << endl;
}

void showEmployee() {
    for (auto &employee : EmployeeList) {
        cout << employee->intro() << endl;
    }
}

// !CUSTOMER
void addCustomer() {
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

void modifyCustomer() {
    string name, newName;
    Date birthDate;
    int typenum;
    MemberType type;

    cin.ignore();
    cout << "Enter customer's name: ";
    getline(cin, name);

    for (auto &customer : CustomerList) {
        if (name == customer->getName()) {
            cout << "Enter new customer's name: ";
            getline(cin, newName);
            cout << "Enter new customer's birth date (dd mm yyyy): ";
            cin >> birthDate.day >> birthDate.month >> birthDate.year;
            cout << "Enter new customer's type (0 for Basic, 1 for Gold, 2 for Platinum, 3 for Diamond): ";
            cin >> typenum;
            type = (MemberType)typenum;

            customer->setName(newName);
            customer->setBirthDate(birthDate);
            customer->setType(type);
            return;
        }
    }
    cout << "Customer not found!" << endl;
}

void deleteCustomer() {
    string name;
    cin.ignore();
    cout << "Enter customer's name: ";
    getline(cin, name);

    for (auto it = CustomerList.begin(); it != CustomerList.end(); ++it) {
        if ((*it)->getName() == name) {
            delete *it;
            CustomerList.erase(it);
            return;
        }
    }
    cout << "Customer not found!" << endl;
}

void showCustomer() {
    for (auto &customer : CustomerList) {
        cout << customer->intro() << endl;
    }
}

// !MENU
void addMenu() {
    string name;
    int price;
    vector<string> ingredients;
    vector<int> amounts;

    cin.ignore();
    cout << "Enter menu's name: ";
    getline(cin, name);
    cout << "Enter menu's price: ";
    cin >> price;
    cin.ignore();

    int ingredientCount;
    cout << "Enter number of ingredients: ";
    cin >> ingredientCount;

    for (int i = 0; i < ingredientCount; i++) {
        string ingredient;
        int amount;

        cin.ignore();
        cout << "Enter ingredient " << (i + 1) << ": ";
        getline(cin, ingredient);
        cout << "Enter amount for " << ingredient << ": ";
        cin >> amount;

        ingredients.push_back(ingredient);
        amounts.push_back(amount);
    }

    MenuList.push_back(new Menu(name, price, ingredients, amounts));
}

void modifyMenu() {
    string name;
    cout << "Enter menu's name to modify: ";
    cin.ignore();
    getline(cin, name);

    for (auto &menu : MenuList) {
        if (name == menu->getName()) {
            string newName;
            int newPrice;
            vector<string> newIngredients;
            vector<int> newAmounts;

            cout << "Enter new menu's name: ";
            getline(cin, newName);
            cout << "Enter new menu's price: ";
            cin >> newPrice;
            cin.ignore();

            int ingredientCount;
            cout << "Enter number of ingredients: ";
            cin >> ingredientCount;

            for (int i = 0; i < ingredientCount; i++) {
                string ingredient;
                int amount;

                cin.ignore();
                cout << "Enter ingredient " << (i + 1) << ": ";
                getline(cin, ingredient);
                cout << "Enter amount for " << ingredient << ": ";
                cin >> amount;

                newIngredients.push_back(ingredient);
                newAmounts.push_back(amount);
            }

            menu->setName(newName);
            menu->setPrice(newPrice);
            menu->setIngredients(newIngredients);
            menu->setAmounts(newAmounts);
            return;
        }
    }
    cout << "Menu not found!" << endl;
}

void deleteMenu() {
    string name;
    cout << "Enter menu's name to delete: ";
    cin.ignore();
    getline(cin, name);

    for (auto it = MenuList.begin(); it != MenuList.end(); ++it) {
        if ((*it)->getName() == name) {
            delete *it;
            MenuList.erase(it);
            return;
        }
    }
    cout << "Menu not found!" << endl;
}

void showMenu() {
    for (auto &menu : MenuList) {
        cout << "# " << menu->getName() << " - " << formatPrice(menu->getPrice()) << (menu->isHalal() ? " (Halal)" : " (Non-Halal)") << endl;
    }
}

void showHalalMenu() {
    for (auto &menu : MenuList) {
        if (menu->isHalal()) {
            cout << "# " << menu->getName() << " - " << formatPrice(menu->getPrice()) << endl;
        }
    }
}

void showNonHalalMenu() {
    for (auto &menu : MenuList) {
        if (!menu->isHalal()) {
            cout << "# " << menu->getName() << " - " << formatPrice(menu->getPrice()) << endl;
        }
    }
}

// Cashier function to calculate change and return money sheets
bool cashier(int totalPrice) {
    int customerMoney;
    cout << "Total price: " << formatPrice(totalPrice) << endl;
    cout << "Enter customer's money: Rp ";
    cin >> customerMoney;

    if (customerMoney < totalPrice) {
        cout << "The order can't be done, insufficient amount of money by the customers!" << endl;
        return false;
    }

    int change = customerMoney - totalPrice;
    cout << "Change Money = " << formatPrice(change) << endl;

    if (change == 0) {
        cout << "Money Sheets = -" << endl;
        return true;
    }

    map<int, int> moneySheets = {
        {100000, 10}, {50000, 10}, {20000, 15}, {10000, 20},
        {5000, 25}, {2000, 25}, {1000, 25}, {500, 25}
    };

    vector<int> denominations = {100000, 50000, 20000, 10000, 5000, 2000, 1000, 500};

    cout << "Money Sheets = ";
    bool first = true;
    for (int denom : denominations) {
        if (change <= 0) break;
        int count = change / denom;
        if (count > 0 && moneySheets[denom] >= count) {
            moneySheets[denom] -= count;
            change -= count * denom;
            if (!first) cout << ", ";
            cout << "Rp " << denom << " (" << count << ")";
            first = false;
        }
    }
    cout << endl;
    return true;
}

// !ORDER
void addOrder() {
    string customerName, menuName;
    int customerIndex = -1, menuIndex = -1;
    vector<Menu*> orderItems;

    // Check if there is at least one chef and one waiter
    bool hasChef = false, hasWaiter = false;
    for (const auto &employee : EmployeeList) {
        if (employee->getType() == Chef) {
            hasChef = true;
        } else if (employee->getType() == Waiter) {
            hasWaiter = true;
        }
        if (hasChef && hasWaiter) break;
    }

    if (!hasChef || !hasWaiter) {
        cout << "The order can't be done, there is no chef or waiter!" << endl;
        return;
    }

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

    Customer* customer = CustomerList[customerIndex];

    while (true) {
        // Get menu name
        cout << "Enter menu's name (or enter 0 to stop): ";
        getline(cin, menuName);
        if (menuName == "0") break;

        // Find menu index
        menuIndex = -1;
        for (int i = 0; i < MenuList.size(); i++) {
            if (MenuList[i]->getName() == menuName) {
                menuIndex = i;
                break;
            }
        }

        // Check if menu exists
        if (menuIndex == -1) {
            cout << "Menu not found!" << endl;
            continue;
        }

        // Check if customer is allowed to buy non-halal items
        Menu* menu = MenuList[menuIndex];
        if (!menu->isHalal() && customer->getAge() < 19) {
            cout << "Customer is not allowed to buy non-halal items!" << endl;
            continue;
        }

        // Check if inventory is enough
        if (!inventoryEnough(menu)) {
            cout << "Not enough inventory for this menu!" << endl;
            continue;
        }

        // Use inventory and add menu to order
        useInventory(menu);
        orderItems.push_back(menu);
    }

    if (orderItems.empty()) {
        cout << "No items ordered!" << endl;
        return;
    }

    Order order(customer->getName(), customer->getBirthDate(), customer->getType());
    int totalPrice = 0;
    for (Menu* item : orderItems) {
        order.addItem(*item);
        totalPrice += item->getPrice();
    }

    order.printReceipt();

    if (cashier(totalPrice)) {
        OrderList.push_back(order);
    }
}

void showOrderHistory() {
    if (OrderList.empty()) {
        cout << "No orders have been made yet." << endl;
        return;
    }

    for (const auto &order : OrderList) {
        cout << order.intro() << endl;
    }
}

int main() {
    initializeMenuAndInventory();

    cout << "-----------------------------------------------------------" << endl;
    cout << "---------------- Sistem Manajemen Restoran ----------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "------ Daffa Rajendra, Kevin Anugerah, Dimas Andhika ------" << endl;

    while (true) {
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
            cin >> choose;
            cout << "-----------------------------------------------------------" << endl;

            if (choose == 1) {
                addInventory();
            } else if (choose == 2) {
                for (auto &inventory : InventoryList) {
                    cout << inventory->getName() << " - " << inventory->getStock() << endl;
                }
            }
        } else if (choose == 2) {
            cout << "1. Add Employee" << endl;
            cout << "2. Modify Employee" << endl;
            cout << "3. Delete Employee" << endl;
            cout << "4. Show Employee" << endl;
            cout << "---------------------------------------------------------------------------" << endl;
            cout << "Choose: ";
            cin >> choose;
            cout << "---------------------------------------------------------------------------" << endl;

            if (choose == 1) {
                addEmployee();
            } else if (choose == 2) {
                modifyEmployee();
            } else if (choose == 3) {
                deleteEmployee();
            } else if (choose == 4) {
                showEmployee();
            }
        } else if (choose == 3) {
            cout << "1. Add Customer" << endl;
            cout << "2. Modify Customer" << endl;
            cout << "3. Delete Customer" << endl;
            cout << "4. Show Customer" << endl;
            cout << "---------------------------------------------------------------------------" << endl;
            cout << "Choose: ";
            cin >> choose;
            cout << "---------------------------------------------------------------------------" << endl;

            if (choose == 1) {
                addCustomer();
            } else if (choose == 2) {
                modifyCustomer();
            } else if (choose == 3) {
                deleteCustomer();
            } else if (choose == 4) {
                showCustomer();
            }
        } else if (choose == 4) {
            cout << "1. Add Menu" << endl;
            cout << "2. Modify Menu" << endl;
            cout << "3. Delete Menu" << endl;
            cout << "4. Show Menu" << endl;
            cout << "5. Show Halal Menu" << endl;
            cout << "6. Show Non-Halal Menu" << endl;
            cout << "---------------------------------------------------------------------------" << endl;
            cout << "Choose: ";
            cin >> choose;
            cout << "---------------------------------------------------------------------------" << endl;

            if (choose == 1) {
                addMenu();
            } else if (choose == 2) {
                modifyMenu();
            } else if (choose == 3) {
                deleteMenu();
            } else if (choose == 4) {
                showMenu();
            } else if (choose == 5) {
                showHalalMenu();
            } else if (choose == 6) {
                showNonHalalMenu();
            }
        } else if (choose == 5) {
            cout << "1. Add Order" << endl;
            cout << "2. Order History" << endl;
            cout << "---------------------------------------------------------------------------" << endl;
            cout << "Choose: ";
            cin >> choose;
            cout << "---------------------------------------------------------------------------" << endl;

            if (choose == 1) {
                addOrder();
            } else if (choose == 2) {
                showOrderHistory();
            }
        } else if (choose == 6) {
            break;
        } else {
            cout << "Invalid input!" << endl;
        }
    }

    return 0;
}
