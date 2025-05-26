#include<iostream>
#include<string>
using namespace std;
struct expense {
    public: 
    int id;
    int price;
    string name;
    expense*next;
    expense(int id, int price, string name) : id(id), price(price), name(name) {}
};
class expensemanager{
public:
    expense* expenses[100];
    int count;

    expensemanager() : count(0) {}

    void addExpense(int id, int price, string name) {
        expenses[count++] = new expense(id, price, name);
    }

    void displayExpenses() {
        for (int i = 0; i < count; i++) {
            cout << "ID: " << expenses[i]->id << ", Price: " << expenses[i]->price << ", Name: " << expenses[i]->name << endl;
        }
    }

    ~expensemanager() {
        for (int i = 0; i < count; i++) {
            delete expenses[i];
        }
    }
};
struct expenselistmanager {
    public:
    expensemanager manager;

    void addExpense(int id, int price, string name) {
        manager.addExpense(id, price, name);
    }

    void displayExpenses() {
        manager.displayExpenses();
    }
};
struct expenselist{
    expense*head;
    expenselist*next;
    expenselist(expense* head) : head(head), next(nullptr) {};

};
struct masterlist{
    public:
    expenselist*head;
masterlist() : head(nullptr) {}
    ~masterlist() {
        expenselist* current = head;
        while (current) {
            expenselist* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
};
class expensemanager{
public:
    masterlist*master;

    expensemanager() : master(new masterlist()) {}

    void addExpense(int id, int price, string name) {
        expense* newExpense = new expense(id, price, name);
        if (!master->head) {
            master->head = new expenselist(newExpense);
        } else {
            expenselist* current = master->head;
            while (current->next) {
                current = current->next;
            }
            current->next = new expenselist(newExpense);
        }
    }

    void displayExpenses() {
        expenselist* current = master->head;
        while (current) {
            cout << "Expense List:" << endl;
            for (expense* e = current->head; e; e = e->next) {
                cout << "ID: " << e->id << ", Price: " << e->price << ", Name: " << e->name << endl;
            }
            current = current->next;
        }
    }

    ~expensemanager() {
        expenselist* current = master->head;
        while (current) {
            expenselist* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        delete master;
    }
};
int main(){

master->head= nullptr;
expensemanager manager;

while(true){
    int id, price;
    string name;
    cout << "Enter expense ID, price and name (or -1 to exit): ";
    cin >> id;
    if (id == -1) break;
    cin >> price;
    cin.ignore(); // To ignore the newline character after reading price
    getline(cin, name);

    manager.addExpense(id, price, name);
    cout<<"current expenses:"<<endl;
    manager.displayExpenses();
    cout << endl;

    cout << "Do you want to add another expense? (yes/no): ";   
    string choice;
    cin >> choice;
    if (choice != "yes") {
        break;
    }
    cout << endl;
    cout << "Current expenses:" << endl;
    manager.displayExpenses();
    cout << endl;
    cout << "Exiting expense manager." << endl;
    return 0;
}
}
