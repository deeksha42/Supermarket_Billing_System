# Supermarket Billing System

## Project Overview

This project is a console-based Supermarket Billing System implemented in C++. It allows administrators to manage products in the inventory and provides customers with the ability to view products and generate receipts. The system supports functionalities such as adding, editing, and removing products, listing all available products, and generating receipts.

## Features

### Administrator Features

- **Admin Login**: Secure login for administrators with a predefined username and password.
- **Add Product**: Add new products to the inventory, specifying the product code, name, price, and discount.
- **Edit Product**: Edit existing product details such as name, price, and discount.
- **Remove Product**: Remove a product from the inventory by specifying the product code.
- **List Products**: Display all products in the inventory with details including product code, name, price, and discount.

### Customer Features

- **List Products**: View the list of available products.
- **Generate Receipt**: Add products to the cart, specify quantities, and generate a receipt showing the total amount after discounts. The receipt can also be saved to a text file.

## Project Structure

```
├── products.txt                 # Contains product details with each line storing the product code, name, price, and discount.
├── supermarket.cpp              # Main source file containing the Supermarket class and application logic
├── supermarket_txt_bill.cpp     # Additional source file for saving the receipt to a text file
└── README.md                    # This documentation file
```

## How to Use

### Prerequisites

- A C++ compiler (e.g., g++, clang++)

### Compilation and Execution

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/deeksha42/Supermarket_Billing_System.git
   cd your-repo-name
   ```

2. **Compile the Program**:

   Use the following commands to compile the source code:

   ```bash
   g++ -o supermarket supermarket.cpp
   ```

   This will generate the executable file: `supermarket` .

3. **Run the Main Program**:

   Execute the main program using:

   ```bash
   ./supermarket
   ```

4. **Run the Receipt Export Program** (if needed):

   Execute the receipt export program using:

   ```bash
   g++ -o supermarket_txt_bill supermarket_txt_bill.cpp
   ./supermarket_txt_bill
   ```

### Object-Oriented Programming (OOP) Concepts Used in the Supermarket Billing System

1. **Classes and Objects**

   - **Class `Product`**: Represents a product in the supermarket. It contains attributes like `productCode`, `productName`, `price`, and `discount`. It also includes methods to set product details, retrieve product information, and display product details.

     - **Functions**:
       - `setProductDetails(int code, const string &name, float p, float d)`: Sets the attributes of the product.
       - `getProductCode()`, `getProductName()`, `getPrice()`, `getDiscount()`: Return the respective attributes of the product.
       - `displayProduct()`: Displays the product's details in a formatted manner.

   - **Class `Supermarket`**: Manages operations related to the supermarket, such as handling administrator and customer functionalities. It provides methods for adding, editing, removing products, listing products, and generating receipts.
     - **Functions**:
       - `adminMenu()`: Handles the administrator's menu for managing products.
       - `customerMenu()`: Manages the customer's menu for viewing products and generating receipts.
       - `addProduct()`: Adds a new product to `products.txt`.
       - `editProduct()`: Edits an existing product's details in `products.txt`.
       - `removeProduct()`: Removes a product from `products.txt`.
       - `listProducts()`: Lists all products from `products.txt`.
       - `generateReceipt()`: Generates a receipt for purchased products, displaying details and total amount.

2. **Encapsulation**

   - **Product Class**: Encapsulates product-related data (attributes) and operations (methods) within a single class, hiding the internal details and exposing only necessary functionality.
   - **Supermarket Class**: Encapsulates supermarket management functionalities and maintains the state and operations related to the products and user interactions.

3. **Abstraction**
   - **Product Class Methods**: Provide abstracted access to product data and operations, allowing interaction with product details without needing to understand the internal implementation.
   - **Supermarket Class Methods**: Abstract the complexities of adding, editing, and removing products, as well as generating receipts, providing a simplified interface for these operations.

In summary, the OOP concepts used in this Supermarket Billing System include encapsulation to manage product and supermarket operations within dedicated classes, and abstraction to provide simplified interfaces for interacting with product and supermarket functionalities.
