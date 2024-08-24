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
        cout << "Error opening file. Please make sure 'products.txt' exists.\n";
        return;
    }

    cout << "\n\n----------------------------------------------------------------\n";
    cout << "Code"
         << "\t"
         << "Name"
         << "\t"
         << "Price"
         << "\t"
         << "Discount" << endl;
    cout << "----------------------------------------------------------------\n";

    int code;
    string name;
    float price, discount;

    // Rewind the file pointer to the beginning
    inFile.clear();          // Clear the end-of-file flag
    inFile.seekg(0, ios::beg);  // Move the file pointer to the beginning

    while (inFile >> code >> name >> price >> discount)
    {
        cout << code << "\t" << name << "\t" << price << "\t" << discount << endl;
    }

    inFile.close();
}

void Supermarket::generateReceipt()
{
    Product cart[100]; // Assuming a maximum of 100 products in the cart
    int cartSize = 0;
    char choice;
    int quantity;

    do
    {
        listProducts();

        int code;

        cout << "\nEnter Product Code: ";
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

        cout << "\nEnter Quantity: ";
        while (true)
        {
            if (cin >> quantity)
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

        fstream inFile("products.txt",ios::in);

        if (!inFile)
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
                found = true;
                Product product;
                product.setProductDetails(productCode, productName, price, discount);
                cart[cartSize++] = product;

                float amount = (price - (price * discount / 100)) * quantity;
                cout << "\nProduct added to the cart successfully.\n\n";
                cout << "\nDiscounted Amount for this product: " << (price - (price * discount / 100) )<< endl;
                break;
            }
        }

        if (!found)
        {
            cout << "Product not found.\n";
        }

        inFile.close();

        cout << "Do you want to add another item to the cart? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    if (cartSize > 0)
    {
        cout << "\n--------------------------------------------------------------\n";
cout << "                         RECEIPT\n";
cout << "----------------------------------------------------------------\n";
cout << "Code\t" << "Name\t" << "Price\t" << "Discount\t" << "Quantity\t" << "Total\t" << endl;
cout << "----------------------------------------------------------------\n";

float totalAmount = 0;

for (int i = 0; i < cartSize; ++i)
{
    float amount = cart[i].getPrice() - (cart[i].getPrice() * cart[i].getDiscount() / 100);
    amount *= quantity;  
    totalAmount += amount;
    cout << cart[i].getProductCode() << "\t" << cart[i].getProductName() << "\t"
         << cart[i].getPrice() << "\t" << cart[i].getDiscount() << "\t\t" << quantity << "\t\t" << amount << endl;
}

cout << "----------------------------------------------------------\n";
cout << "\nTotal Amount: " << totalAmount << "\n";
cout << "----------------------------------------------------------\n";

    }
    else
    {
        cout << "\nCart is empty. No receipt generated.\n";
    }
}

int main()
{
    Supermarket supermarket;
    int userType;

    while (true)
    {
        cout << "\n_______________________________________________________________" << endl;
        cout << "\n-------------------------------------------------------------- " << endl;
        cout << "\n       Welcome to the Supermarket Billing System\n";
        cout << "\n-------------------------------------------------------------- " << endl;
        cout << "\n_______________________________________________________________" << endl;
        cout << "1. Administrator\n";
        cout << "2. Customer\n";
        cout << "3. Exit\n";
        cout << "\n_______________________________________________________________" << endl;
        cout << "Enter user type: ";
        cin >> userType;

        switch (userType)
        {
        case 1:
            supermarket.adminMenu();
            break;
        case 2:
            supermarket.customerMenu();
            break;
        case 3:
            cout << "Exiting program. Goodbye!\n";
            exit(0);
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
