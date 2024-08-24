#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

class Product
{
private:
    int productCode;
    string productName;
    float price;
    float discount;

public:
    void setProductDetails(int code, const string &name, float p, float d)
    {
        productCode = code;
        productName = name;
        price = p;
        discount = d;
    }

    int getProductCode()
    {
        return productCode;
    }

    string getProductName()
    {
        return productName;
    }

    float getPrice()
    {
        return price;
    }

    float getDiscount()
    {
        return discount;
    }

    void displayProduct()
    {
        cout << productCode << "\t" << productName << "\t" << price << "\t" << discount << "%" << endl;
    }
};

class Supermarket
{
private:
    string adminUsername;
    string adminPassword;

public:
    Supermarket()
    {
        adminUsername = "admin";
        adminPassword = "admin123";
    }

    int adminLogin(const string &username, const string &password)
    {
        if((username == adminUsername && password == adminPassword))
        return 1;
        else 
        return 0;
    }

    void adminMenu();
    void customerMenu();
    void addProduct();
    void editProduct();
    void removeProduct();
    void listProducts();
    void generateReceipt();
};

void Supermarket::adminMenu()
{
    int choice;
    string username, password;

    cout << "\n-------------------------------------------------------------- " << endl;
    cout << "Enter Administrator Username: ";
    cin >> username;
    cout << "Enter Administrator Password: ";
    cin >> password;

    if (adminLogin(username, password) == 1)
    {
        while (true)
        {
            cout << "\n-------------------------------------------------------------- " << endl;
            cout << "\n                       ADMINISTRATOR MENU\n ";
            cout << "\n-------------------------------------------------------------- " << endl;
            cout << "1. Add Product\n";
            cout << "2. Edit Product\n";
            cout << "3. Remove Product\n";
            cout << "4. List Products\n";
            cout << "5. Logout\n";
            cout << "---------------------------------------------------------------- " << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                addProduct();
                break;
            case 2:
                editProduct();
                break;
            case 3:
                removeProduct();
                break;
            case 4:
                listProducts();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    else
    {
        cout << "Invalid username or password.Please try again !\n";
    }
}

void Supermarket::customerMenu()
{
    int choice;

    while (true)
    {
        cout << "\n-------------------------------------------------------------- " << endl;
        cout << "\n                       CUSTOMER MENU:\n";
        cout << "\n-------------------------------------------------------------- " << endl;
        cout << "1. List Products\n";
        cout << "2. Generate Receipt\n";
        cout << "3. Logout\n";
        cout << "\n-------------------------------------------------------------- " << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            listProducts();
            break;
        case 2:
            generateReceipt();
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Supermarket::addProduct()
{
    int code;
    string name;
    float price, discount;

    cout << "\n-------------------------------------------------------------- " << endl;
    cout << "\nEnter Product Code: ";
    while (true)
    {
        if (cin >> code)
        {
            // Check if the product code already exists
            fstream checkFile("products.txt",ios::in);
            int existingCode;
            bool exists = false;

            while (checkFile >> existingCode >> name >> price >> discount)
            {
                if (existingCode == code)
                {
                    exists = true;
                    cout << "Product with this code already exists. Please enter a unique code: ";
                    
                    break;
                }
            }

            checkFile.close();

            if (!exists)
                break;
        }
        else
        {
            cout << "Invalid input. Please enter a valid numeric value: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Product Name: ";
    getline(cin, name);

    cout << "Enter Product Price: ";
    while (true)
    {
        if (cin >> price)
        {
            break;
        }
        else
        {
            cout << "Invalid input. Please enter a valid numeric value: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "Enter Product Discount (in %): ";
    while (true)
    {
        if (cin >> discount)
        {
            break;
        }
        else
        {
            cout << "Invalid input. Please enter a valid numeric value: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Now we can append the new product to the file
    fstream outFile("products.txt", ios::app);

    if (!outFile)
    {
        cout<< "Error opening file." << endl;
        exit(1);
    }

    outFile << code << " " << name << " " << price << " " << discount << endl;

    cout << "\nProduct added successfully.\n";

    outFile.close();
    
}

void Supermarket::editProduct()
{
    int code;
    cout << "\nEnter the Product Code to edit: ";
    while (true)
    {
        if (cin >> code)
        {
            break;
        }
        else
        {
            cout << "Invalid input. Please enter a valid numeric value: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    fstream inFile("products.txt", ios::in);

    if (!inFile)
    {
        cout << "Error opening file." << endl;
        exit(1);
    }

    fstream outFile("temp.txt", ios::app | ios::out);

    if (!outFile)
    {
        cout << "Error opening file." << endl;
        exit(1);
    }

    int productCode;
    string productName;
    float price, discount;

    bool found = false;

    while (inFile >> productCode >> productName >> price >> discount)
    {
        if (productCode == code)
        {
            cout << "Enter new Product Name: ";
            cin.ignore();
            getline(cin, productName);

            cout << "Enter new Product Price: ";
            while (true)
            {
                if (cin >> price)
                {
                    break;
                }
                else
                {
                    cout << "Invalid input. Please enter a valid numeric value: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            cout << "Enter new Product Discount (%): ";
            while (true)
            {
                if (cin >> discount)
                {
                    break;
                }
                else
                {
                    cout << "Invalid input. Please enter a valid numeric value: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            found = true;
            cout << "\nProduct edited successfully.\n";
        }

        outFile << productCode << " " << productName << " " << price << " " << discount << endl;
    }

    if (!found)
    {
        cout << "Product not found.\n";
    }

    inFile.close();
    outFile.close();

    remove("products.txt");
    rename("temp.txt", "products.txt");
}

void Supermarket::removeProduct()
{
    int code;
    cout << "\nEnter the Product Code to remove: ";
    while (true)
    {
        if (cin >> code)
        {
            break;
        }
        else
        {
            cout << "Invalid input. Please enter a valid numeric value: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    fstream inFile("products.txt", ios::in);

    if (!inFile)
    {
        cout << "Error opening file." << endl;
        exit(1);
    }

    fstream outFile("temp.txt", ios::out | ios::app);

    if (!outFile)
    {
        cout << "Error opening file." << endl;
        exit(1);
    }

    int productCode;
    string productName;
    float price, discount;

    int found = false;

    while (inFile >> productCode >> productName >> price >> discount)
    {
        if (productCode == code)
        {
            found = 1;
            cout << "\nProduct removed successfully.\n";
        }
        else
        {
            outFile << productCode << " " << productName << " " << price << " " << discount << endl;
        }
    }

    if (!found)
    {
        cout << "Product not found.\n";
    }

    inFile.close();
    outFile.close();

    remove("products.txt");
    rename("temp.txt", "products.txt");
}

void Supermarket::listProducts()
{
    fstream inFile("products.txt", ios::in);

    if (!inFile)
    {
        cout << "Error opening file." << endl;
        exit(1);
    }

    cout << "\n-------------------------------------------------------------- " << endl;
    cout << "\nProduct Code\tProduct Name\tPrice\tDiscount\n";
    cout << "\n-------------------------------------------------------------- " << endl;

    int productCode;
    string productName;
    float price, discount;

    while (inFile >> productCode >> productName >> price >> discount)
    {
        cout << productCode << "\t\t" << productName << "\t\t" << price << "\t" << discount << "%" << endl;
    }

    inFile.close();
}

void Supermarket::generateReceipt()
{
    int code;
    int quantity;
    char choice;
    float total = 0;
    float totalDiscount = 0;

    fstream inFile("products.txt", ios::in);
    if (!inFile)
    {
        cout << "Error opening file." << endl;
        exit(1);
    }

    ofstream receiptFile("receipt.txt");
    if (!receiptFile)
    {
        cout << "Error creating receipt file." << endl;
        exit(1);
    }

    receiptFile << fixed << setprecision(2);
    receiptFile << "\n------------------------------------------------------------------------- " << endl;
    receiptFile << "                       SUPER MARKET BILL RECEIPT\n ";
    receiptFile << "\n------------------------------------------------------------------------- " << endl;
    receiptFile << "\nProduct Code\tProduct Name\tPrice\tQuantity\tTotal\tDiscount\n";
    receiptFile << "\n-------------------------------------------------------------------------" << endl;

    bool hasItems = false; // Flag to check if any items were added

    do
    {
        cout << "Enter the Product Code: ";
        cin >> code;

        inFile.clear();
        inFile.seekg(0, ios::beg);

        int productCode;
        string productName;
        float price, discount;

        bool found = false;

        while (inFile >> productCode >> productName >> price >> discount)
        {
            if (productCode == code)
            {
                found = true;
                cout << "Enter the quantity: ";
                cin >> quantity;

                float itemTotal = price * quantity;
                float itemDiscount = itemTotal * discount / 100;
                total += itemTotal;
                totalDiscount += itemDiscount;

                receiptFile << productCode << "\t\t" << productName << "\t\t" << price << "\t" << quantity << "\t\t" << itemTotal << "\t" << itemDiscount << endl;
                
                hasItems = true; // Mark that an item was added to the receipt
                break;
            }
        }

        if (!found)
        {
            cout << "Product not found. Please enter a valid product code.\n";
        }
        else
        {
            cout << "Do you want to add another product? (y/n): ";
            cin >> choice;
        }

    } while (choice == 'y' || choice == 'Y');

    if (hasItems)
    {
        receiptFile << "\n--------------------------------------------------------------" << endl;
        receiptFile << "Total:\t\t\t\t\t\t" << total << endl;
        receiptFile << "Total Discount:\t\t\t\t\t" << totalDiscount << endl;
        receiptFile << "Final Amount:\t\t\t\t\t" << total - totalDiscount << endl;
        receiptFile << "\n-------------------------------------------------------------- " << endl;

        cout << "\nReceipt generated and saved to receipt.txt successfully." << endl;
    }
    else
    {
        receiptFile << "No items were added to the receipt." << endl;
        cout << "No items were added to the receipt." << endl;
    }

    receiptFile.close();
    inFile.close();
}

int main()
{
    Supermarket supermarket;
    int choice;

    while (true)
    {
        cout << "\n----------------------------------------------------------------------------" << endl;
        cout << "\n                       SUPERMARKET BILLING SYSTEM\n ";
        cout << "\n---------------------------------------------------------------------------- " << endl;
        cout << "1. Administrator\n";
        cout << "2. Customer\n";
        cout << "3. Exit\n";
        cout << "------------------------------------------------------------------------------ " << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            supermarket.adminMenu();
            break;
        case 2:
            supermarket.customerMenu();
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
