#include "product.cpp"
#include "user.cpp"
#include "system.cpp"
#include "log.cpp"
#include "discounts&bundles.cpp"

  void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

int main() {

System system;
 int choice;

    do {
        std::cout << "Virtual Marketplace ===\n";
        std::cout << "1. Register Buyer\n";
        std::cout << "2. Register Seller\n";
        std::cout << "3. Add Product\n";
        std::cout << "4. Apply Discount\n";
        std::cout << "5. Create Bundle\n";
        std::cout << "6. Make Transaction\n";
        std::cout << "7. View Logs\n";
        std::cout << "8. Search Products by Price Range\n";
        std::cout << "0. Exit\n";
        std::cout << "Select option: ";
        std::cin >> choice;

 try {
            switch (choice) {
                case 1: {
                    std::string name;
                    double wallet;
                    std::cout << "Enter buyer name: ";
                    std::getline(std::cin, name);
                    std::cout << "Enter wallet balance: ";  
                    std::cin >> wallet;
            
                    system.registerUser(std::make_shared<Buyer>(name, wallet));
                    break;
                }

                case 2: {
                    std::string name;
                    std::cout << "Enter seller name: ";
                    std::getline(std::cin, name);
                    system.registerUser(std::make_shared<Seller>(name));
                    break;
                }
                  case 3: {
                    std::string name, type, id;
                    double price;
                    std::cout << "Enter product name: ";
                    std::getline(std::cin, name);
                    std::cout << "Enter price: ";
                    std::cin >> price;
                    clearInput();
                    std::cout << "Enter product ID: ";
                    std::getline(std::cin, id);
                    std::cout << "Enter type (Book/Electronics/Clothing): ";
                    std::getline(std::cin, type);

                    std::shared_ptr<Product> product;
                    if (type == "Book") product = std::make_shared<Book>(name, price, id);
                    else if (type == "Electronics") product = std::make_shared<Electronics>(name, price, id);
                    else if (type == "Clothing") product = std::make_shared<Clothing>(name, price, id);
                    else throw ProductNotFoundException("Product Not Found!");

                    std::string sellerId;
                    std::cout << "Enter seller ID: ";
                    std::getline(std::cin, sellerId);
                    system.addProduct(product, sellerId);
                    break;
                }

                 case 4; {
                        std::string prodId;
                        double perc;
                        std::cout << "Enter product ID to discount: ";
                        std::getline(std::cin, prodId);
                        std::cout << "Enter discount percentage: ";
                        std::cin >> perc;
                        clearInput();

             


    return 0;
}	
