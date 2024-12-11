#include<bits/stdc++.h>
#include<fstream>

using namespace std;

class Product{
    private: 
    int code;
    string name;
    float price;
    float discount;
    const string adminEmail="nguyentienson0512@gmail.com";
    const string adminPassword="son05122005";
    public:
    Product(): code(0),price(0),discount(0) {}
    Product(int c, string n, float p, float d) : code(c), name(n), price(p), discount(d) {}

    int getCode() const { return code;}
    string getName() const { return name;}
    float getPrice() const{ return price;}
    float getDiscount() const { return discount;}

    void setDetails(int c, string n,float p,float d){
        code=c;
        name=n;
        price=p;
        discount=d;

    }
    //login admin
    bool adminLogin(){
        string email,password;
        cout<<"Enter admin email: "; cin>>email;
        cout<<"Enter admin password: ";cin>>password;
        if(email==adminEmail&&password==adminPassword){
            cout<<"Login successful!\n";
            return true;
        }
        else {
            cout<<"Invalid email or password.\n";
            return false;
        }
    }
    void admin(vector<Product> &products);
    static void loadProductsFromFile(const string& fileName, vector<Product>& products) {
        ifstream file(fileName);
        if (file.is_open()) {
            string line;
            getline(file, line); // Bỏ qua dòng tiêu đề
            while (getline(file, line)) {
                stringstream ss(line);
                string codeStr, name, priceStr, discountStr;

                getline(ss, codeStr, ',');
                getline(ss, name, ',');
                getline(ss, priceStr, ',');
                getline(ss, discountStr, ',');

                int code = stoi(codeStr);
                float price = stof(priceStr);
                float discount = stof(discountStr);

                products.emplace_back(code, name, price, discount);
            }
            file.close();
        } else {
            cerr << "Failed to open " << fileName << "\n";
        }
    }
    // void admin();
    void add();
    void edit();
    void rem();
    void list();

};
void Product::admin(vector<Product>& products) {
    if (!adminLogin()) return;

    int choice;
    do {
        cout << "\nAdmin Menu:\n";
        cout << "1. Add product\n";
        cout << "2. Edit product\n";
        cout << "3. Delete product\n";
        cout << "4. View products\n";
        cout << "5. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct(products);
                break;
            case 2:
                editProduct(products);
                break;
            case 3:
                deleteProduct(products);
                break;
            case 4:
                viewProducts(products);
                break;
            case 5:
                saveToFile(products);
                cout << "Exiting admin menu.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);
};
void addProduct(vector<Product>& products) {
    int c;
    string n;
    float p, d;
    cout << "Enter product code: ";
    cin >> c;
    cout << "Enter product name: ";
    cin.ignore();
    getline(cin, n);
    cout << "Enter product price: ";
    cin >> p;
    cout << "Enter product discount: ";
    cin >> d;

    products.emplace_back(c, n, p, d);
    cout << "Product added successfully.\n";
};
void editProduct(vector<Product>& products) {
    int codeToEdit;
    cout << "Enter product code to edit: ";
    cin >> codeToEdit;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto& product : products) {
        if (product.getCode() == codeToEdit) {
            string n;
            float p, d;
            cout << "Enter new product name: ";
            getline(cin, n);

            cout << "Enter new product price: ";
            while (!(cin >> p) || p < 0) {
                cout << "Invalid price. Please enter a positive number: ";
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore bad input
            }

            cout << "Enter new product discount: ";
            while (!(cin >> d) || d < 0 || d > 100) {
                cout << "Invalid discount. Please enter a value between 0 and 100: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore bad input
            }

            product.setDetails(codeToEdit, n, p, d);
            cout << "Product updated successfully.\n";
            return;
        }
    }

    cout << "Product not found.\n";
};

void deleteProduct(vector<Product>& products) {
    int codeToDelete;
    cout << "Enter product code to delete: ";
    cin >> codeToDelete;

    auto it = remove_if(products.begin(), products.end(), [&](const Product& product) {
        return product.getCode() == codeToDelete;
    });

    if (it != products.end()) {
        products.erase(it, products.end());
        cout << "Product deleted successfully.\n";
    } else {
        cout << "Product not found.\n";
    }
};
void viewProducts(const vector<Product>& products) {
    cout << "\nProduct List:\n";
    for (const auto& product : products) {
        cout << "Code: " << product.getCode()
                  << ", Name: " << product.getName()
                  << ", Price: " << product.getPrice()
                  << ", Discount: " << product.getDiscount() << "%\n";
    }
};

void saveToFile(vector<Product>& products) {
    sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.getPrice() < b.getPrice();
    });

    ofstream file("products.csv");
    if (file.is_open()) {
        file << "Code,Name,Price,Discount\n";
        for (const auto& product : products) {
            file << product.getCode() << "," << product.getName() << "," << product.getPrice() << "," << product.getDiscount() << "\n";
        }
        file.close();
        cout << "Products saved to products.csv successfully.\n";
    } else {
        cout << "Failed to open file for writing.\n";
    }
};

class Customer{
    private:
    string name;
    string email;
    string username;
    string password;
    public:
    Customer(): 
    name(""),email(""),username(""),password(""){}
    //creating a new customer

    Customer(string n, string e, string u, string p)
    :name(n), email(e),username(u),password(p){}

    string getName() const { return name; }
    string getEmail() const { return email; }
    string getUsername() const { return username; }

    void setDetails(string n,string e,string u, string p){
        name=n;
        email=e;
        username=u;
        password=p;
    }

    //check login
    static bool login(const string &filename, const string &username, const string &password){
        ifstream file(filename);
        if(file.is_open()){
            string line;
            while(getline(file,line)){
                stringstream ss(line);
                string name,email,user,pass;

                //csv line
                getline(ss, name, ',');
                getline(ss, email, ',');
                getline(ss, user, ',');
                getline(ss, pass, ',');

                if(user==username && pass==password){
                    file.close();
                    return true;
                    //successful
                }
            }
            file.close();
        }
        else{
            cout<<"Unable to open file."<<endl;
        }
        return false;//login failed

    }

};
class Cart {
private:
    vector<pair<Product, int>> items; // List of products and their quantities

public:
    void addProduct(const Product& product, int quantity) {
        for (auto& item : items) {
            if (item.first.getCode() == product.getCode()) {
                item.second += quantity;
                return;
            }
        }
        items.emplace_back(product, quantity);
    }
    const vector<pair<Product, int>>& getItems() const {
        return items;
    }
    void removeProduct(int productCode) {
        items.erase(remove_if(items.begin(), items.end(), [productCode](const pair<Product, int>& item) {
            return item.first.getCode() == productCode;
        }), items.end());
    }

    void displayCart() const {
        if (items.empty()) {
            cout << "Cart is empty.\n";
            return;
        }

        float totalCost = 0;
        cout << "\nCart Details:\n";
        for (const auto& item : items) {
            float itemPrice = item.first.getPrice() * (1 - item.first.getDiscount() / 100);
            float itemTotal = itemPrice * item.second;
            totalCost += itemTotal;

            cout << "Product: " << item.first.getName()
                 << ", Quantity: " << item.second
                 << ", Price per unit: " << fixed << setprecision(2) << itemPrice
                 << ", Total: " << itemTotal << "\n";
        }
        cout << "Total Cost: " << totalCost << "\n";
    }

    void saveCartToFile() const {
        ofstream file("Cart.csv");
        if (file.is_open()) {
            file << "Product,Quantity,Price per Unit,Total\n";
            for (const auto& item : items) {
                float itemPrice = item.first.getPrice() * (1 - item.first.getDiscount() / 100);
                float itemTotal = itemPrice * item.second;
                file << item.first.getName() << "," << item.second << "," << itemPrice << "," << itemTotal << "\n";
            }
            file.close();
            cout << "Cart saved to Cart.csv successfully.\n";
        } else {
            cout << "Failed to save cart to file.\n";
        }
    }
};
class Order {
private:
    Cart cart;
    string status;
    
public:
    Order() : status("Pending") {}

    void createOrder(const Cart& c) {
        cart = c;
        status = "Pending";
    }

    void updateStatus(const string& newStatus) {
        status = newStatus;
    }

    void displayOrder() const {
        cout << "\nOrder Details:\n";
        cart.displayCart();
        cout << "Order Status: " << status << "\n";
    }

    void printReceipt(const string& fileName) const {
        ofstream receiptFile(fileName);
        if (receiptFile.is_open()) {
            receiptFile << "Order Receipt\n";
        for (const auto& item : cart.getItems()) {
               receiptFile << "Product: " << item.first.getName()
                            << ", Quantity: " << item.second
                            << ", Price per Unit: " << item.first.getPrice() * (1 - item.first.getDiscount() / 100)
                            << ", Total: " << item.first.getPrice() * (1 - item.first.getDiscount() / 100) * item.second << "\n";
            }
            receiptFile << "Order Status: " << status << "\n";
            receiptFile.close();
            cout << "Receipt saved to " << fileName << "\n";
        } else {
            cout << "Failed to open file " << fileName << "\n";
        }
    }
};

int main() {
    const string productFile = "products.csv";
    vector<Product> products;

    Product::loadProductsFromFile(productFile, products);

    int choice;
    cout << "1. Admin\n2. Customer\nEnter your role: ";
    cin >> choice;

    if (choice == 1) {
        Product admin;
        admin.admin(products);   
         } else if (choice == 2) {
        Cart cart;
        int productCode, quantity;
        while (true) {
            cout << "Available products:\n";
            for (const auto& product : products) {
                cout << "Code: " << product.getCode()
                          << ", Name: " << product.getName()
                          << ", Price: " << product.getPrice()
                          << ", Discount: " << product.getDiscount() << "%\n";
            }

            cout << "Enter product code to add to cart (0 to checkout): ";
            cin >> productCode;
            if (productCode == 0) break;

            auto it = find_if(products.begin(), products.end(), [productCode](const Product& p) {
                return p.getCode() == productCode;
            });

            if (it != products.end()) {
                cout << "Enter quantity: ";
                cin >> quantity;
                cart.addProduct(*it, quantity);
            } else {
                cout << "Invalid product code.\n";
            }
        }

        cart.displayCart();
    }

    return 0;
}
