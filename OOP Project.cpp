/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <fstream> // File management ke liye

using namespace std;

// Base Class: JewelryItem (Inheritance & Polymorphism)
class JewelryItem {
protected:
    int id;
    string name;
    float weight;          // Weight in grams
    float purityPercentage;// Purity percentage (e.g., 92.5%, 80%, 50%)

public:
    JewelryItem(int i, string n, float w, float purity) 
        : id(i), name(n), weight(w), purityPercentage(purity) {
        if (w < 0 || purity < 0) {
            throw invalid_argument("Weight and purity percentage cannot be negative!");
        }
    }

    virtual ~JewelryItem() {}

    virtual void displayMenuItem() const {
        cout << "ID: " << id << " | Item: " << name << " | Weight: " << weight << "g\n";
    }

    virtual void displayDetails(float marketRate) const {
        cout << "\n-----------------------------------------\n";
        cout << "           SELECTED ITEM DETAILS         \n";
        cout << "-----------------------------------------\n";
        cout << "Item Name       : " << name << "\n";
        cout << "Item Weight     : " << weight << " grams\n";
        cout << "Silver Purity   : " << purityPercentage << "%\n";
        
        float finalPrice = calculatePrice(marketRate);
        cout << "Market Rate     : Rs. " << marketRate << " per gram\n";
        cout << "Calculated Price: Rs. " << finalPrice << "\n";
        cout << "-----------------------------------------\n";
    }

    float calculatePrice(float marketRate) const {
        return weight * marketRate * (purityPercentage / 100.0f);
    }

    int getId() const { return id; }
    string getName() const { return name; }
    float getWeight() const { return weight; }
    float getPurity() const { return purityPercentage; }
};

// Derived Classes using Inheritance
class Necklace : public JewelryItem {
public:
    Necklace(int i, float w, float purity) : JewelryItem(i, "Necklace", w, purity) {}
};

class Ring : public JewelryItem {
public:
    Ring(int i, float w, float purity) : JewelryItem(i, "Ring", w, purity) {}
};

class Bracelet : public JewelryItem {
public:
    Bracelet(int i, float w, float purity) : JewelryItem(i, "Bracelet", w, purity) {}
};

class Earring : public JewelryItem {
public:
    Earring(int i, float w, float purity) : JewelryItem(i, "Earring", w, purity) {}
};

class Watch : public JewelryItem {
public:
    Watch(int i, float w, float purity) : JewelryItem(i, "Silver Watch", w, purity) {}
};

// Customer Class
class Customer {
private:
    string name;
    string phone;
    string paymentMode;

public:
    void getDetails() {
        cout << "\n--- ENTER CUSTOMER DETAILS ---\n";
        cout << "Enter Full Name: ";
        cin.ignore();
        getline(cin, name);
        
        cout << "Enter Phone Number: ";
        getline(cin, phone);

        int payChoice;
        cout << "\nSelect Payment Mode:\n";
        cout << "1. Cash\n";
        cout << "2. UPI\n";
        cout << "3. Netbanking\n";
        cout << "Enter choice (1-3): ";
        cin >> payChoice;

        switch (payChoice) {
            case 1: paymentMode = "Cash"; break;
            case 2: paymentMode = "UPI"; break;
            case 3: paymentMode = "Netbanking"; break;
            default: paymentMode = "Cash (Default)"; break;
        }
    }

    // Yeh function screen wale bill ko ek nayi alag file mein save karega
    void generateSeparateBillFile(const JewelryItem* item, float marketRate) const {
        float totalBill = item->calculatePrice(marketRate);
        
        // Customer ke naam se ek nayi alag file banegi (jaise bill_Rahul.txt)
        string fileName = "bill_" + name + ".txt";
        ofstream billFile(fileName);
        
        if (!billFile) {
            cout << "\n[Error] File create nahi ho payi!\n";
            return;
        }

        // File ke andar exact wahi bill likha jayega jo screen par dikhta hai
        billFile << "=========================================\n";
        billFile << "        SAWARIYA JEWELLERS - BILL        \n";
        billFile << "=========================================\n";
        billFile << "Customer Name  : " << name << "\n";
        billFile << "Phone Number   : " << phone << "\n";
        billFile << "Payment Method : " << paymentMode << "\n";
        billFile << "-----------------------------------------\n";
        billFile << "Item Purchased : " << item->getName() << "\n";
        billFile << "Item Weight    : " << item->getWeight() << "g\n";
        billFile << "Silver Purity  : " << item->getPurity() << "%\n";
        billFile << "Total Payable  : Rs. " << totalBill << "\n";
        billFile << "-----------------------------------------\n";
        billFile << "Thank you for your purchase!\n";
        billFile << "Warm Regards,\nManagement Team, Sawariya Jewellers\n";
        billFile << "=========================================\n";

        billFile.close();
        cout << "\n[Success] Final bill ek nayi file '" << fileName << "' mein successfully save ho gaya hai!\n";
    }

    void printConsoleBill(const JewelryItem* item, float marketRate) const {
        float totalBill = item->calculatePrice(marketRate);
        cout << "\n=========================================\n";
        cout << "           FINAL BILL SUMMARY            \n";
        cout << "=========================================\n";
        cout << "Customer Name  : " << name << "\n";
        cout << "Phone Number   : " << phone << "\n";
        cout << "Payment Method : " << paymentMode << "\n";
        cout << "-----------------------------------------\n";
        cout << "Item Purchased : " << item->getName() << "\n";
        cout << "Total Payable  : Rs. " << totalBill << "\n";
        cout << "-----------------------------------------\n";
        cout << "Thank you for your purchase!\n";
        cout << "Warm Regards,\nManagement Team, Sawariya Jewellers\n";
        cout << "=========================================\n";
    }
};

int main() {
    const float silverMarketRate = 85.0f; 

    vector<JewelryItem*> catalog;
    catalog.push_back(new Necklace(1, 50.0f, 92.5f)); 
    catalog.push_back(new Ring(2, 7.5f, 80.0f));      
    catalog.push_back(new Bracelet(3, 25.0f, 92.5f)); 
    catalog.push_back(new Earring(4, 4.0f, 50.0f));   
    catalog.push_back(new Watch(5, 60.0f, 92.5f));    

    int mainChoice;

    do {
        cout << "\n=========================================\n";
        cout << "       WELCOME TO SAWARIYA JEWELLERS     \n";
        cout << "=========================================\n";
        cout << "1. Admin Login\n";
        cout << "2. Customer Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";

        try {
            if (!(cin >> mainChoice)) {
                throw runtime_error("Invalid input type! Please enter a valid number.");
            }

            if (mainChoice == 1) {
                string adminPass;
                cout << "\nEnter Admin Password (default: admin123): ";
                cin >> adminPass;
                if (adminPass == "admin123") {
                    cout << "\n[Access Granted] Welcome, Admin!\n";
                    cout << "Today's Silver Market Rate: Rs. " << silverMarketRate << "/g\n";
                    cout << "Total items currently in catalog: " << catalog.size() << "\n";
                } else {
                    cout << "\n[Access Denied] Incorrect password!\n";
                }

            } else if (mainChoice == 2) {
                cout << "\n=========================================\n";
                cout << "         CUSTOMER SHOPPING PORTAL        \n";
                cout << "=========================================\n";
                cout << "Today's Silver Market Rate: Rs. " << silverMarketRate << "/g\n";
                cout << "\n--- AVAILABLE SHOP ITEMS ---\n";

                for (const auto& item : catalog) {
                    item->displayMenuItem();
                }
                cout << "6. We will buy next time\n"; 

                int itemId;
                cout << "\nEnter your choice (1-6): ";
                cin >> itemId;

                if (itemId == 6) {
                    cout << "\n-----------------------------------------\n";
                    cout << "Thank you for visiting Sawariya Jewellers.\n";
                    cout << "We hope to see you again soon!\n";
                    cout << "Warm Regards,\nManagement Team, Sawariya Jewellers\n";
                    cout << "-----------------------------------------\n";
                } else {
                    JewelryItem* selectedItem = nullptr;
                    for (auto item : catalog) {
                        if (item->getId() == itemId) {
                            selectedItem = item;
                            break;
                        }
                    }

                    if (selectedItem == nullptr) {
                        cout << "\n[Error] Invalid Item ID selected!\n";
                    } else {
                        selectedItem->displayDetails(silverMarketRate);

                        char agreement;
                        cout << "Do you agree to buy this item? (y/n): ";
                        cin >> agreement;

                        if (agreement == 'y' || agreement == 'Y') {
                            Customer customer;
                            customer.getDetails(); 
                            
                            // Yeh function screen wale bill ko alag file mein save karega
                            customer.generateSeparateBillFile(selectedItem, silverMarketRate);
                            
                            // Yeh function screen par bill show karega
                            customer.printConsoleBill(selectedItem, silverMarketRate);
                        } else {
                            cout << "\n-----------------------------------------\n";
                            cout << "Thank you for visiting Sawariya Jewellers.\n";
                            cout << "We hope to see you again soon!\n";
                            cout << "Warm Regards,\nManagement Team, Sawariya Jewellers\n";
                            cout << "-----------------------------------------\n";
                        }
                    }
                }

            } else if (mainChoice == 3) {
                cout << "\nThank you for using Sawariya Jewellers system. Goodbye!\n";
            } else {
                cout << "\nInvalid choice! Please select between 1 and 3.\n";
            }

        } catch (const exception& e) {
            cout << "\n[Exception Caught] Error: " << e.what() << "\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }

    } while (mainChoice != 3);

    return 0;
}