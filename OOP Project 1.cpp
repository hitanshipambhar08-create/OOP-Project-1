#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <fstream> // File Management System

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
        
        float basePrice = calculateBasePrice(marketRate);
        float gstAmount = basePrice * 0.03f; // 3% GST
        float finalPrice = basePrice + gstAmount;

        cout << "Market Rate     : Rs. " << marketRate << " per gram\n";
        cout << "Base Price      : Rs. " << basePrice << "\n";
        cout << "GST (3%)        : Rs. " << gstAmount << "\n";
        cout << "Total Payable   : Rs. " << finalPrice << "\n";
        cout << "-----------------------------------------\n";
    }

    float calculateBasePrice(float marketRate) const {
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

    void generateSeparateBillFile(const JewelryItem* item, float marketRate) const {
        float basePrice = item->calculateBasePrice(marketRate);
        float gstAmount = basePrice * 0.03f;
        float totalBill = basePrice + gstAmount;
        
        string fileName = "bill_" + name + ".txt";
        ofstream billFile(fileName);
        
        if (!billFile) {
            cout << "\n[Error] File create nahi ho payi!\n";
            return;
        }

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
        billFile << "Base Price     : Rs. " << basePrice << "\n";
        billFile << "GST (3%)       : Rs. " << gstAmount << "\n";
        billFile << "Total Payable  : Rs. " << totalBill << "\n";
        billFile << "-----------------------------------------\n";
        billFile << "Thank you for your purchase!\n";
        billFile << "Warm Regards,\nManagement Team, Sawariya Jewellers\n";
        billFile << "=========================================\n";

        billFile.close();
        cout << "\n[Success] Final bill in File'" << fileName << endl ;
    }

    void printConsoleBill(const JewelryItem* item, float marketRate) const {
        float basePrice = item->calculateBasePrice(marketRate);
        float gstAmount = basePrice * 0.03f;
        float totalBill = basePrice + gstAmount;

        cout << "\n=========================================\n";
        cout << "           FINAL BILL SUMMARY            \n";
        cout << "=========================================\n";
        cout << "Customer Name  : " << name << "\n";
        cout << "Phone Number   : " << phone << "\n";
        cout << "Payment Method : " << paymentMode << "\n";
        cout << "-----------------------------------------\n";
        cout << "Item Purchased : " << item->getName() << "\n";
        cout << "Base Price     : Rs. " << basePrice << "\n";
        cout << "GST (3%)       : Rs. " << gstAmount << "\n";
        cout << "Total Payable  : Rs. " << totalBill << "\n";
        cout << "-----------------------------------------\n";
        cout << "Thank you for your purchase!\n";
        cout << "Warm Regards,\nManagement Team, Sawariya Jewellers\n";
        cout << "=========================================\n";
    }
};

int main() {
    const float silverMarketRate = 220.0f; // Updated rate: Rs. 220 per gram

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
                    cout << "Today's Silver Market Rate: Rs. " << silverMarketRate << "/g (with 3% GST applicable)\n";
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
                            customer.generateSeparateBillFile(selectedItem, silverMarketRate);
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