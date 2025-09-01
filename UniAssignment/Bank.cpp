#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>
#include <ctime>
#include <map>
#include <vector>
#include <cstdlib>

#define pb push_back

using namespace std;

int getValidInt();    
void clearScreen();
void billing(double& bill);
void checkStorage(const string& file);
double addCart(double& bill);
double manageCart(double& bill);
void checkBill(const string& file, double bill);
void checkOut(const string& filepath,double bill);
void customer_register();
void customer_registered_list();
void SalesReport();
string extractMonth(const string& date_line) ;
int extractday(const string& date_line);
double extractAmount(const string& line);
void management_option();
void view_specified_customerdetails();
void view_registered_customers();
double clearCart(double& bill);
void updateStock(const string& filepath);

const int MAX_STORAGE_ID = 130;
const int MIN_STORAGE_ID=101;
// Variables for choices and counters
int CUST_COUNT = 0;
const int MAX_CUSTOMER = 10000;  // Maximum number of customers the program can handle

int main() {
    double bill = 0.0;//keeps track of how much the customer has spent
    ofstream clr("bill.txt", ofstream::out | ofstream::trunc);//opens and empties the bill
    clr.close();

    int ans = 0;//tracks the user's choice for th main UI
    //UI
    do {
        clearScreen();
        cout << "~~~~~Welcome to Secure WeManageSoft4U~~~~~" << endl;
        cout << "1. Customer Management\n";
        cout << "2. Billing\n";
        cout << "3. Sales Reporting\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: \n";

        ans = getValidInt();//used to get a valid integer
        while (ans < 1 || ans > 4) {
            cout << "Please Insert a Valid Option" << endl;
            ans = getValidInt(); 
        }

        if (ans == 1) {
            clearScreen();//used to clear terminal
            management_option();//Opens customer management part
        } else if (ans == 2) {
            clearScreen();
            billing(bill);//Opens billing part
        } else if (ans == 3) {
            clearScreen();
            SalesReport();//Opens sales report part
        }

    } while (ans != 4);
}

//Billing Function

void billing(double& bill) {
    int ans = 0;
    //UI
    do {
        clearScreen();  
        cout << "~~~~~Billing~~~~~" << endl;
        cout << "1. Manage Shopping Cart\n";
        cout << "2. Checkout\n";
        cout << "3. Update Stock\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: \n";

        ans = getValidInt();
        while (ans < 1 || ans > 4) {
            cout << "Please Insert a Valid Option" << endl;
            ans = getValidInt(); 
        }

        if (ans == 1) {
            clearScreen();
            manageCart(bill);
        } else if (ans == 2) {
            clearScreen();
            checkOut("bill.txt", bill);
        }else if(ans==3){
            clearScreen();
            updateStock("Storage.txt");
        }

    } while (ans != 4);
}

double manageCart(double& bill) {
    int ans = 0;
    do {
        clearScreen();
        cout << "~~~~~Cart~~~~~" << endl;
        cout << "1. Add to Cart\n";
        cout << "2. Check Cart\n";
        cout << "3. Clear Cart\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: \n";

        ans = getValidInt();
        while (ans < 1 || ans > 4) {
            cout << "Please Insert a Valid Option" << endl;
            ans = getValidInt(); 
        }

        if (ans == 1) {
            clearScreen();
            addCart(bill);
        } else if (ans == 2) {
            checkBill("bill.txt", bill);
        }else if (ans==3){
            clearCart(bill);
        }

    } while (ans != 4);

    return bill;
}

double clearCart(double& bill){//clears the customer's cart
    ofstream clr("bill.txt", ofstream::out | ofstream::trunc);
    clr.close();
    cout << "Cart has been cleared\n" << "Press Enter to continue...";
    cin.ignore();
    cin.get();
    bill = 0;
    return 0;
}

double addCart(double& bill) {//used to add items into the customer's cart
    string line;
    int id = -1;  
    do {
        clearScreen();
        checkStorage("Storage.txt");

        cout << "\nEnter Item ID to add to cart (or 0 to finish): ";
        id = getValidInt();  
        if (id == 0) break;

        while ((id < MIN_STORAGE_ID || id > MAX_STORAGE_ID) && id != 0) {
            cout << "Please Insert a Valid Item ID (101-130): ";
            id = getValidInt();
        }

        cout << "Enter quantity: ";
        int amt = getValidInt();
        while (amt < 0 || amt > 1000) {
            cout << "Please Insert a Valid Quantity (1-1000)/(Enter 0 to remove item): ";
            amt = getValidInt();
        }

        if (amt == 0) {
            ifstream fileIn("bill.txt");
            ofstream fileOut("temp.txt");//placeholder for bill, for when customers removes items from the cart
            bool removed = false;
            while (getline(fileIn, line)) {
                stringstream ss(line);
                string sid, name, sprice, samount, stotal;
                getline(ss, sid, ',');
                getline(ss, name, ',');
                getline(ss, sprice, ',');
                getline(ss, samount, ',');
                getline(ss, stotal, ',');

                if (stoi(sid) == id) {
                    bill -= stod(stotal);  
                    removed = true;
                    cout << name << " removed from cart. RM " << stotal << " deducted.\n";
                } else {
                    fileOut << line << endl;  
                }
            }
            fileIn.close();
            fileOut.close();
            remove("bill.txt");
            rename("temp.txt", "bill.txt");

            if (!removed) {
                cout << "Item not found in cart.\n";
            }

            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            continue;
        }

        ifstream file("Storage.txt");
        bool found = false;
        while (getline(file, line)) {
            stringstream ss(line);
            string sid, name, sprice, sstock;
            getline(ss, sid, ',');
            getline(ss, name, ',');
            getline(ss, sprice, ',');
            getline(ss, sstock, ',');
            if(sstock == "0"){
                cout << "Item is out of stock.\n";
                found = true;
                break;
            }
            else if (stoi(sid) == id) {
                double price = stod(sprice);
                double subtotal = price * amt;
                bill += subtotal;
                cout << amt << " x " << name << " added to cart. Subtotal: RM " << subtotal << endl;
                found = true;

                ofstream billFile("bill.txt", ios::app);
                billFile << sid << "," << name << "," << sprice << "," << amt << "," << subtotal << endl;
                billFile.close();

                break;
            }
        }

        file.close();
        if (!found) {
            cout << "Item ID not found. Please try again.\n";
        }

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();

    } while (id != 0);  

    return bill;
}




void checkStorage(const string& filepath) {//gets all items from storage
    ifstream infile(filepath);

    string line;
    cout << left << setw(10) << "ID"
         << setw(40) << "Name"
         << setw(40) << "Price(RM)"
         << "Availability" << endl; 


    cout << string(120, '-') << endl; 

    while (getline(infile, line)) {//stock will be 0 if there is no stock
        stringstream ss(line);
        string id, name, price, stock;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, price, ',');
        getline(ss,stock,',');
        if(stock == "0"){
            cout << left << setw(10) << id
             << setw(40) << name
             << setw(40) << price
             <<"OUT OF STOCK"<< endl;
        }else{
            cout << left << setw(10) << id
                << setw(40) << name
                << setw(40) << price
                << "IN STOCK" << endl;}
    }

    infile.close();
}

void checkBill(const string& filepath,double bill) {//outputs everything from the bill
    ifstream infile(filepath);

    string line;
    cout << left << setw(10) << "ID"
         << setw(40) << "Name"
         << setw(15) << "Price"
         << setw(15) << "Quantity"
         << setw(15) << "Subtotal" << endl;

    cout << string(95, '-') << endl;  

    while (getline(infile, line)) {
        stringstream ss(line);
        string id, name, price, quantity, subtotal;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, price, ',');
        getline(ss, quantity, ',');
        getline(ss, subtotal, ',');

        cout << left << setw(10) << id
             << setw(40) << name
             << setw(15) << price 
             << setw(15) << quantity
             << setw(15) << subtotal << endl;
    }

    infile.close();
    cout << "Total Bill is RM"<< bill << endl;
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}


void checkOut(const string& filepath, double bill) {
    ifstream infile(filepath);
    if(infile.peek() == ifstream::traits_type::eof()){
        cout << "You have nothing in your cart" << endl;
        cout << "Press Enter to Continue...";
        cin.ignore();
        cin.get();
    } else {
        int num = 0;
        ifstream inCount("Count.txt");
        if (inCount >> num) {
            num += 1;
        } else {
            num = 1;
        }

        cout << "Enter Customer ID: "; 
        int id = getValidInt();

        if(!(id > 0 && id < num)) {
            do {
                cout << "Invalid ID, Please Enter an Existing Customer ID or Enter -1 to Register a Customer:";
                id = getValidInt(); 
                if(id == -1){
                    customer_register(); // gives the choice to make a new customer id

                    // Read latest customer ID after registration
                    ifstream readID("Count.txt");
                    if (readID.is_open()) {
                        readID >> id;
                        readID.close();
                    }
                    break;
                }
            } while(!(id > 0 && id < num));
        }

        ofstream rFile("Receipts.txt", ios::app);
        rFile << "Customer ID: " << id << endl; 

        string line;
        while (getline(infile, line)) {
            rFile << line << endl; 
        }

        time_t timestamp;
        time(&timestamp);

        rFile << "Total Spent: RM" << bill << endl << ctime(&timestamp) << "\n" << endl;
        rFile.close();
        #ifdef _WIN32
            cout << "Checkout only works with Linux/MacOS systems that have qrencode installed." << endl; 
        #else
            int result = system("qrencode -t ASCIIi 'https://drive.google.com/file/d/1gpjuYmK-LzT42HvikTjEhmdiwj3SYrtM/view?fbclid=IwY2xjawMKdpdleHRuA2FlbQIxMQABHlz5PiZcxEAu_2hX9lpXL2_3KT3xD6z-23Ty37MPxBG6ysgzm1EYE3KgltNm_aem_Xop_4VnSsK01FV5xAb5Kig&pli=1'");
            if (result != 0) cerr << "Failed to generate QR code.\n";
        #endif
        cout << "\nPress Enter when finished checking out\n";
        cin.ignore();
        cin.get();
        cout << "Checkout Complete\n" << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

void updateStock(const string& filepath) {
    vector<string> lines;
    string line;

    // Read all lines into memory
    ifstream infile(filepath);
    while (getline(infile, line)) {
        lines.pb(line);
    }
    infile.close();

    // Show storage
    checkStorage(filepath);

    // Ask for item ID
    cout << "\nEnter Item ID to update stock: ";
    int id = getValidInt();
    do{
        cout << "Invalid ID\nEnter a Valid ID: ";
        int id = getValidInt();
    }while(id <=MIN_STORAGE_ID && id > MAX_STORAGE_ID);
    bool found = false;
    for (auto& l : lines) {
        stringstream ss(l);
        string sid, name, sprice, sstock;
        getline(ss, sid, ',');
        getline(ss, name, ',');
        getline(ss, sprice, ',');
        getline(ss, sstock, ',');

        if (stoi(sid) == id) {
            found = true;

            int stockStatus;
            do {
                cout << "Enter new stock status(1 if in stock, 2 if out of stock): ";
                stockStatus = getValidInt();
                if (stockStatus != 0 && stockStatus != 1) {
                    cout << "Invalid input. Please enter 0 or 1.\n";
                }
            } while (stockStatus != 0 && stockStatus != 1);

            // Replace the line with updated stock value
            l = sid + "," + name + "," + sprice + "," + to_string(stockStatus);
            cout << "Stock updated successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "Item ID not found.\n";
        return;
    }

    ofstream outfile(filepath, ofstream::out | ofstream::trunc);
    for (const auto& l : lines) {
        outfile << l << "\n";
    }
    outfile.close();

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

int getValidInt() {
    int num;
    while (true) {
        cin >> num;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n'); 
            cout << "Invalid input. Please enter a valid integer." << endl;
        } else {
            cin.ignore(10000, '\n');//removes decimals 
            break;
        }
    }
    return num;
}

void clearScreen() {//clears terminal depending on what OS is being used
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//CUSTOMER MANAGEMENT

// Structure to store customer details
struct customer {
    string name;
    string nationality;
    string email;
    string address;
    string contact_number;
    int customer_id;
};

customer cust[MAX_CUSTOMER]; // Array to store customer data





// Function for customer registration
void customer_register() {

    // Read the last saved customer ID from file
    ifstream readID("Count.txt");
    int last_id = 0;
    if (readID.is_open()) {
        readID >> last_id;
        readID.close();
    }

    // Reference to the current new customer
    customer& new_customer = cust[CUST_COUNT];

    // Assign next ID to new customer
    cust[CUST_COUNT].customer_id = last_id + 1;

    cout << "Customer ID: " << new_customer.customer_id << endl;

    // Take customer details from user
    cout << "Please enter your name: ";
    getline(cin, new_customer.name);

    cout << "Please enter your nationality: ";
    getline(cin, new_customer.nationality);

    cout << "Please enter your email: ";
    getline(cin, new_customer.email);

    cout << "Please enter your address: ";
    getline(cin, new_customer.address);

    cout << "Please enter your personal contact number: ";
    getline(cin, new_customer.contact_number);

    cout << "\n" << endl;

    // Save customer details into Customer.txt file
    ofstream writefile("Customer.txt", ofstream::out | ofstream::app);
    if (writefile.is_open()) {
        writefile << "Customer ID: " << cust[CUST_COUNT].customer_id << endl;
        writefile << "Name: " << cust[CUST_COUNT].name << endl;
        writefile << "Nationality: " << cust[CUST_COUNT].nationality << endl;
        writefile << "Email: " << cust[CUST_COUNT].email << endl;
        writefile << "Address: " << cust[CUST_COUNT].address << endl;
        writefile << "Personal Contact: " << cust[CUST_COUNT].contact_number << endl;
        writefile << "\n";
        writefile.close();
    }

    // Save the last used customer ID into Count.txt
    ofstream saveID("Count.txt", ofstream::out);
    if (saveID.is_open()) {
        saveID << cust[CUST_COUNT].customer_id;
        saveID.close();
    }
    // Increase in-memory customer count
    CUST_COUNT++;

}

// Function to display all registered customers from file
void view_registered_customers() {
    ifstream infile("Customer.txt");
    if (infile.is_open()) {
        string line;
        cout << "\n~~~Registered Customers~~~";
        while (getline(infile, line)) {
            cout << line << endl;
        }
        infile.close();
    }
    else {
        cout << "Unable to open Customer.txt file." << endl;
    }
}

// Function to view details of a specific customer by ID
void view_specified_customerdetails() {
    int customer_id = 0;

    // Get the last customer ID from Count.txt
    ifstream readID("Count.txt");
    int last_id = 0;
    if (readID.is_open()) {
        readID >> last_id;
        readID.close();
    }
    cout << "\n";
    cout << "Enter Customer ID that need to check: ";
    cin >> customer_id;

    // Check if ID is valid
    if (customer_id > 0 && customer_id <= last_id) {
        ifstream infile("Customer.txt");
        if (infile.is_open()) {
            string line;
            while (getline(infile, line)) {
                // Find the line with matching ID
                if (line == "Customer ID: " + to_string(customer_id)) {
                    cout << line << endl;
                    // Print next 5 lines (other details)
                    for (int i = 0; i < 5; i++) {
                        if (getline(infile, line)) {
                            cout << line << endl;
                        }
                        else {
                            break;
                        }
                    }
                    break;
                }
            }
            infile.close();
        }
        else {
            cout << "Unable to open Customer.txt file." << endl;
        }
    }
    else {
        cout << "Invalid Customer Id" << endl;
    }
    cout << "\n";
}

// Function to show in-memory registered customer list
void customer_registered_list() {
    cout << "~~~Registered Customer List~~~\n" << endl;
    for (int i = 0; i < CUST_COUNT; i++) {
        cout << "Customer ID:" << cust[i].customer_id << endl;
        cout << "       Name:" << cust[i].name << endl;
    }

    cout << "\n";
    cout << "Total Customers:" << CUST_COUNT << endl<<endl;
}

//void customer_registered_list() {
//    char choice;
//    int num = 0;
//    cout << "--Customer Registration--" << endl;
//    cout << "\n";
//    do {//i made it loop here
//        customer_register();
//        cout << "Register another customer? (Y/N) : ";
//        cin >> choice;
//        cin.ignore();
//        choice = toupper(choice);
//        if (choice != 'Y' && choice != 'N') {
//            do {
//                cout << "Invalid input" << endl;
//                cout << "Please re-enter your choice:";
//                cin >> choice;
//                cin.ignore();
//                choice = toupper(choice);
//            } while (choice != 'Y' && choice != 'N');
//        }
//    } while (choice != 'N');
//}

// Function to display main customer management menu
void management_option() {
    int option = 0;
    char choice;
    cout << "\n~~~Welcome to Customer Management~~~\n" << endl;

    do {
        cout << "1. Customer Registration" << endl;
        cout << "2. View Registered Customers" << endl;
        cout << "3. View Specified Customer Details" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your option: ";
        cin >> option;
        cin.ignore();
        clearScreen(); // Clear screen after input

        // Handle menu choice
        if (option == 1) {
            do{
                customer_register();
                
                // Ask user if they want to register another customer
                cout << "Register another customer? (Y/N) : ";
                cin >> choice;
                cin.ignore();
                choice = toupper(choice); // Convert to uppercase
                    // Validate input
                if (choice != 'Y' && choice != 'N') {
                    do {
                        cout << "Invalid input" << endl;
                        cout << "Please re-enter your choice:";
                        cin >> choice;
                        cin.ignore();
                        choice = toupper(choice);
                    } while (choice != 'Y' && choice != 'N');
                }
                if(choice=='N')break;
            }while(choice =='Y'); // Repeat if user wants to add more customers
            customer_registered_list();
        }
        else if (option == 2) {
            view_registered_customers();
        }
        else if (option == 3) {
            view_specified_customerdetails();
        }
        else if (option == 4) {
            break;
        }
        else {
            cout << "Please Insert a Valid Option" << endl;
            cin >> option;
            cin.ignore();
        }
    } while (option != 4); // Loop until user chooses to exit
}

void customer_management() {

    management_option(); // Show menu

    customer_registered_list(); // Show list after menu ends
}


//Sales Report function

void SalesReport() {
    ifstream file("Receipts.txt");
    string line;

    //assigning the months to a vector to retrieve revenue data and allow it to be used as an input when entering in the function. 
    vector<map<int,double>>revenue_day(12);
    map<string,double>revenue_month={
        {"Jan", 0}, {"Feb", 0}, {"Mar", 0}, {"Apr", 0},{"May", 0}, {"Jun", 0}, {"Jul", 0}, {"Aug", 0},{"Sep", 0}, {"Oct", 0}, {"Nov", 0}, {"Dec", 0}
    };
    map<string,double>month_info={
        {"Jan", 0}, {"Feb", 1}, {"Mar", 2}, {"Apr", 3}, {"May", 4}, {"Jun", 5}, {"Jul", 6}, {"Aug", 7},{"Sep", 8}, {"Oct", 9}, {"Nov", 10}, {"Dec", 11}
    };
    vector<string> month_names = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    while (getline(file, line)) {
        if (line.find("Total Spent: RM") != string::npos) {
            double amount = extractAmount(line);

            string date_line;
            if (getline(file, date_line)) {
                string month = extractMonth(date_line);
                int day = extractday(date_line);
                int month_index=month_info[month];
                revenue_month[month] += amount;
                revenue_day[month_index][day]+=amount;
            }
        }
    }

    int choice;
    cout << "Choose report type:\n";
    cout << "1. View by specific day\n";
    cout << "2. View by specific month\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

// entering the month and day to view profits and revenue
    if (choice == 1) {
        int day, month;
        do {
        cout << "Enter the month: ";
        cin >> month;
            if (month < 1 || month > 12) {
                cout << "Invalid month.\n";
            }
        } while (month < 1 || month > 12);

        do {
        cout << "Enter the day: ";
        cin >> day;
            if (day < 1 || day > 31) {
                cout << "Invalid day.\n";
                
            }
        } while (day < 1 || day > 31);

    cin.get();
        //We assume profit is 15%
        double total_revenue = revenue_day[month - 1][day];
        cout << "Total revenue for " << month_names[month - 1] << " " << day << ": RM " << fixed << setprecision(2) << total_revenue << "\n";
        cout << "Total profit for " << month_names[month - 1] << " " << day << ": RM " << fixed << setprecision(2) << total_revenue * 0.15 << "\n";


    } else if (choice == 2) {
        string month;
        do {
        cout << "Enter the month (e.g., Jan, Feb, etc.): ";
        getline(cin, month);
        // Capitalize first letter, lowercase the rest
        if (!month.empty()) {
            month[0] = toupper(month[0]);
            for (size_t i = 1; i < month.size(); ++i) {
                month[i] = tolower(month[i]);
            }
        }
        if (revenue_month.find(month) == revenue_month.end()) {
            cout << "Invalid month.\n";
        }
    } while (revenue_month.find(month) == revenue_month.end());
    double total_revenue = revenue_month[month];
    cout << "Total revenue for " << month << ": RM " << fixed << setprecision(2) << total_revenue << "\n";
    cout << "Total profit for " << month << ": RM " << fixed << setprecision(2) << total_revenue * 0.15 << "\n";

    } else if (choice == 3) {
        return;
    } else {
        cout << "Invalid option.\n";
    }

    cout << "\nPress Enter to continue...";
    cin.get();
}


string extractMonth(const string& date_line) {
    istringstream iss(date_line);
    string day, month;
    iss >> day >> month;
    return month;
}

int extractday(const string& date_line) {
    istringstream iss(date_line);
    string weekday, month;
    int day;
    iss >> weekday >> month >> day;
    return day;
}


double extractAmount(const string& line) {
    auto pos = line.find("RM");
    if (pos != string::npos) {
        string amount_str = line.substr(pos + 2);
        return stod(amount_str);
    }
    return 0.0;
}