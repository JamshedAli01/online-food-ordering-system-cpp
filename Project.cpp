#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class User{
    private:
    string username;
    string password;

public:
    User(string u, string p){username = u; password = p;}
    string getUsername() const {return username;}
    string getPassword() const {return password;}
    void setUsername(string u){username = u;}
    void setPassword(string p){password = p;}

    bool savetofile(){
        ofstream file("data.txt", ios::app);
        return file.is_open() && (file << username << "," << password << endl, file.close(), true);
    }

    static bool authentication(const string& u, const string& p){
        ifstream file("data.txt");
        string line;
        while (getline(file, line)){
            size_t comma = line.find(",");
            if (line.substr(0, comma) == u && line.substr(comma + 1) == p)
                return true;
        }
        return false;
    }
};
// Authentication system
class AuthSystem{
public:
    static void show_welcome_on_screen(){
        cout <<"\n======================" << endl;
        cout <<" AUTHENTICATION MENU:" << endl;
        cout <<"======================"<< endl;
        cout <<"1. Sign up (Register new user)" << endl;
        cout <<"2. Log in" << endl;
        cout <<"Enter your choice: ";
    }

    static bool registerUser(){
        string username, password, confirm_Password;  
        cout<<"Enter your name: ";
        cin>>username;
        cout <<"Enter password: ";
        password = getPasswordInput();
        cout <<"Confirm Password: ";
        confirm_Password = getPasswordInput();

        if (password != confirm_Password){
            cout << "Passwords do not match!" << endl;
            return false;
        }

        User newUser(username, password);
        if (newUser.savetofile()){
            cout<<"Registration successful!"<<endl;
            return true;
        } else {
            cout<<"Registration failed!"<<endl;
            return false;
        }
    }

    static bool loginUser(){
        string username, password;
        
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        password = getPasswordInput();

        if (User::authentication(username, password)){
            cout << "Login successful!" << endl;
            return true;
        } else{
            cout << "Incorrect password or username!" << endl;
            cout << "Try again!" << endl;
            return false;
        }
    }

private:
    static string getPasswordInput(){
        string password = "";
        char ch;
        while (true){
            ch = getch();
            if (ch == 13) {
                break;
            } else if (ch == 8){
                if (!password.empty()){
                    cout<<"\b \b";
                    password.pop_back();
                }
            } else{
                cout<<'*';
                password += ch;
            }
        }
        cout << endl;
        return password;
    }
};
//Menu Class:
class MenuItem {
private:
    string name;
    double price;
public:
    MenuItem(){name = ""; price = 0.0;}
    MenuItem(string n, double p){name = n; price = p;}
    string getName() const {return name; }
    double getPrice() const {return price; }
    void display() const {
        cout << name << ", Rs. "<<price<<"."<<endl;
    }
};
//Restaurant Class:
class Restaurant{
private:
    string name;
    vector<MenuItem> menu;
public:
    Restaurant() {name = "";}
    Restaurant(string n) {name = n;}

    string getName() const {return name;}
    vector<MenuItem> getMenu() const {return menu;}
    void addMenuItem(string itemName, double price) {
        menu.push_back(MenuItem(itemName, price));
    }
    void displayMenu() const {
        cout << "\n==================================================" << endl;
        cout << "               " << name << " MENU" << endl;
        cout << "==================================================" << endl;
        for (size_t i = 0; i < menu.size(); i++) {
            cout << i + 1 << ". ";
            menu[i].display();
        }
        cout << endl;
    }
    MenuItem getMenuItem(int choice) const {
        if (choice >= 1 && choice <= static_cast<int>(menu.size())) {
            return menu[choice - 1];
        }
        return MenuItem("Invalid", 0.0);
    }
    int getMenuSize() const {
        return menu.size();
    }
};

class RestaurantManager{
private:
    vector<Restaurant> restaurants;
public:
    RestaurantManager() {
        initializeRestaurants();
    }

    void initializeRestaurants() {
        //Al-asr foods
        Restaurant alAsr("Al-asr foods");
        alAsr.addMenuItem("Fajita Pizza", 800);
        alAsr.addMenuItem("Chicken Role", 100);
        alAsr.addMenuItem("Malai Boti Role", 250);
        alAsr.addMenuItem("Legend Rench Pizza", 800);
        alAsr.addMenuItem("Chicken Tikka Pizza", 800);
        alAsr.addMenuItem("Pizza Srirach", 800);
        alAsr.addMenuItem("Sriracha Burger", 400);
        alAsr.addMenuItem("Chicken Bihari Boti", 280);
        restaurants.push_back(alAsr);

        //Khan Baba
        Restaurant khanBaba("Khan Baba");
        khanBaba.addMenuItem("Chicken Karhai", 1200);
        khanBaba.addMenuItem("Chicken Karhai(Desi)", 1400);
        khanBaba.addMenuItem("Beef Biryani", 800);
        khanBaba.addMenuItem("Chicken Korma", 1500);
        khanBaba.addMenuItem("Tea (Chaye)", 80);
        khanBaba.addMenuItem("Chicken Steamed Tikka", 300);
        khanBaba.addMenuItem("Motton White Karhai", 3400);
        khanBaba.addMenuItem("Motton Karhai", 3000);
        restaurants.push_back(khanBaba);

        //TDM siji point
        Restaurant siji("TDM siji point");
        siji.addMenuItem("Aage Wali Raan", 3500);
        siji.addMenuItem("Peeche Wali Raan", 4000);
        siji.addMenuItem("Seena (Chanp)", 5000);
        siji.addMenuItem("Siri with Magaz", 1000);
        restaurants.push_back(siji);

        //Ajwa hotel and restaurant
        Restaurant Ajwa("Ajwa hotel and restaurant");
        Ajwa.addMenuItem("Chai(Tea)", 80);
        Ajwa.addMenuItem("Ice-Cream", 150);
        Ajwa.addMenuItem("Cold Drink", 100);
        Ajwa.addMenuItem("Karahi", 1300);
        Ajwa.addMenuItem("Chicken Biryani", 900);
        Ajwa.addMenuItem("Beef Pulao", 1000);
        Ajwa.addMenuItem("Malai Boti", 300);
        Ajwa.addMenuItem("Gola Kabab", 300);
        restaurants.push_back(Ajwa);

        //Geo Mari Hotel
        Restaurant geo("Geo Mari Hotel");
        geo.addMenuItem("Dudh Patti Chaye", 100);
        geo.addMenuItem("Chaye with Biscuit", 150);
        geo.addMenuItem("Kawa tea", 50);
        geo.addMenuItem("Karhai", 1500);
        geo.addMenuItem("chikken Tikka", 300);
        geo.addMenuItem("Karhai", 1500);
        restaurants.push_back(geo);
    }

    void displayRestaurants() const {
        cout<<"\n=================================================="<<endl;
        cout<<"           AVAILABLE RESTAURANTS" << endl;
        cout<<"=================================================="<<endl;
        cout<<"All the major restaurants and food points are given below:"<<endl;
        for(size_t i = 0; i < restaurants.size(); i++) {
            cout << i + 1 << ". " << restaurants[i].getName() << endl;
        }
        cout << endl;
    }
    Restaurant getRestaurant(int choice) const {
        if(choice >= 1 && choice <= static_cast<int>(restaurants.size())) {
            return restaurants[choice - 1];
        }
        return Restaurant("Invalid!");
    }
    int getRestaurantCount() const {
        return restaurants.size();
    }
};

// Order system
class OrderSystem {
private:
    RestaurantManager manager;

public:
    void startOrdering() {
        int restaurantChoice;
        char moreOrders;
        
        do {
            system("cls");
            manager.displayRestaurants();
            cout << "Enter your choice (1-" << manager.getRestaurantCount() << "): ";
            if (!(cin >> restaurantChoice)) {
                cout << "Invalid input! Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Press any key to continue...";
                getch();
                continue;
            }

            if (restaurantChoice < 1 || restaurantChoice > manager.getRestaurantCount()) {
                cout << "Invalid choice! Please enter a number between 1 and " << manager.getRestaurantCount() << endl;
                cout << "Press any key to continue...";
                getch();
                continue;
            }
            Restaurant selectedRestaurant = manager.getRestaurant(restaurantChoice);
            processRestaurantOrder(selectedRestaurant);
            cout << "Do you wanna order more? (Y/n): ";
            cin >> moreOrders;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (moreOrders == 'Y' || moreOrders == 'y');
    }

private:
    void processRestaurantOrder(Restaurant& restaurant) {
        system("cls");
        restaurant.displayMenu();
        
        int itemChoice;
        cout << "Enter your choice (1-" << restaurant.getMenuSize() << "): ";
        
        if (!(cin >> itemChoice)) {
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        if (itemChoice < 1 || itemChoice > restaurant.getMenuSize()) {
            cout << "Invalid choice! Please enter a number between 1 and " << restaurant.getMenuSize() << endl;
            return;
        }

        MenuItem selectedItem = restaurant.getMenuItem(itemChoice);
        cout<<"\n==================================================" << endl;
        cout<<"           ORDER CONFIRMATION" << endl;
        cout<<"==================================================" << endl;
        cout<<"Your Order Has Been Booked!!!\nYour order is just 30 mins ahead!!"<<endl;;
        cout<<"Item: " <<selectedItem.getName() << endl;
        cout<<"Price: Rs. " <<selectedItem.getPrice() << endl;
        cout<<"==================================================" << endl;
        cout << "Press any key to continue..."<<endl;
        getch();
    }
};
int main(){
    cout << "\t\t==================================================================" << endl;
    cout<<"                                 \t\tWELCOME!!\n";
    cout<<"                        \t\tFOOD ORDERING SYSTEM TANDO ADAM\n";
    cout << "\t\t==================================================================" << endl;
    cout << endl;
    AuthSystem auth;
    OrderSystem orderSystem;
    bool isAuthenticated = false;

    // Authentication phase
    while (!isAuthenticated) {
        auth.show_welcome_on_screen();

        int authChoice;
        if (!(cin >> authChoice)) {
            cout << "Invalid input! Please enter 1 or 2." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press any key to continue...";
            getch();
            continue;
        }

        switch (authChoice)
        {
            case 1: isAuthenticated = auth.registerUser();
                break;
            case 2: isAuthenticated = auth.loginUser();
                break;
            default: cout<<"Invalid choice! Please enter 1 or 2."<<endl;
        }

        if(!isAuthenticated)
        {
            cout<<"Press any key to continue...";
            getch();
        }
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // Ordering phase
    cout << "Press any key to continue to main menu...";
    getch();
    orderSystem.startOrdering();
    cout<<"\n=================================================="<<endl;
    cout<<"     THANK YOU FOR USING OUR SERVICE!"<<endl;
    cout<<"=================================================="<<endl;
    return 0;
}