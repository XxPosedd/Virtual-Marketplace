#include "system.h"
#include "exceptions.h"


//========================================================================================================
// System - Constructors
//========================================================================================================
// These constructors initialize the system object, if load=true, it will automatically load saved data.
//========================================================================================================
System::System() {}
System::System(const bool load) {

    if(load) {
        this->loadData();
    }

}// end of System::system
//========================================================================================================


//========================================================================================================
// System - Load All Data
//========================================================================================================
// This loads products, users, logs, and discounts from their files into memory.
//========================================================================================================
void System::loadData() {

    this->loadProducts();
    this->loadUsers();
    this->loadLogs();
    this->loadDiscounts();

}// end of System::loadData()
//========================================================================================================


//========================================================================================================
// System - Load Products
//========================================================================================================
// stored like: Book;Great Book;10.10;B12345
//========================================================================================================
void System::loadProducts() {

    std::ifstream inFile;
    inFile.open("Products.txt");    // stored like:     Book;Great Book;10.10;B12345

    if(!inFile.is_open()) {
        std::cerr << "Failed to open file Products.txt" << std::endl;
        return;
    }
    else {
        std::string line;
        while(std::getline(inFile, line)) {
            std::string type{};
            std::string name{};
            std::string priceStr{};     // we use getline and then stod
            double price{};
            std::string id{};
            // owner is not set, will be set when loading users

            std::stringstream ss(line);

            std::getline(ss, type, ';');        // get data from string stream
            std::getline(ss, name, ';');
            std::getline(ss, priceStr, ';');
            std::getline(ss, id, ';');

            price = std::stod(priceStr);

            std::shared_ptr<Product> ptr;

            if(type == "Book") {                // new ptr based on type, uses constructos
                ptr = std::make_shared<Book>(name, price, id);
            }
            else if(type == "Electronics") {
                ptr = std::make_shared<Electronics>(name, price, id);
            }
            else if(type == "Clothing") {
                ptr = std::make_shared<Clothing>(name, price, id);
            }

            products.push_back(ptr);            // adds new ptr
        }

    }

    inFile.close();

}

//========================================================================================================
// System - Load Users
//========================================================================================================
// stored like Buyer;Bob the Buyer;11.17;B1234,E12345,C0925,B3285
//========================================================================================================
void System::loadUsers() {

    std::ifstream inFile;
    inFile.open("Users.txt");       // stored like Buyer;Bob the Buyer;U123;11.17;B1234,E12345,C0925,B3285
    
    if(!inFile.is_open()) {
        std::cerr << "Failed to open file Users.txt" << std::endl;
        return;
    }
    
    std::string line{};
    while(std::getline(inFile, line)) {
        std::stringstream ss(line); 
        std::string type{};
        std::string userName{};
        std::string userId{};
        double wallet{};
        std::string walltString{};          // we use getline then stod
        std::string fullProductList{};

        std::getline(ss, type, ';');
        std::getline(ss, userName, ';');
        std::getline(ss, userId, ';');   

        std::shared_ptr<User> ptr;

        if(type == "Buyer") {
            std::getline(ss, walltString, ';');     // buyer have a wallet while sellers do not
            wallet = std::stod(walltString);
            ptr = std::make_shared<Buyer>(userName, userId, wallet);
        }
        else if(type == "Seller") {
            ptr = std::make_shared<Seller>(userName, userId);
        }
        
        std::getline(ss, fullProductList);          // after cause buyer has wallets
        
        std::stringstream ss2(fullProductList);     // this deals with owned products
        std::string productId{};
        while(std::getline(ss2, productId, ',')) {  // get all products by id
            for(int i = 0; i < products.size(); ++i) {
                if(productId == products[i]->getId()) { // assign owner to product and products to user
                    ptr->setProduct(products[i]);
                    products[i]->setOwner(ptr);
                }
            }
        }

        users.push_back(ptr); 
    }

    inFile.close();
}// end of loadUsers
//========================================================================================================


//========================================================================================================
// System - Load Logs
//========================================================================================================
// stored like 1;S123;B8972;11.11;p123,p421,p3215
//========================================================================================================
void System::loadLogs() {

    std::ifstream inFile;
    inFile.open("Logs.txt");       // stored like 1;S123;B8972;11.11;p123,p421,p3215
    
    if(!inFile.is_open()) {
        std::cerr << "Failed to open file Logs.txt" << std::endl;
        return;
    }

    std::string line{};
    while(std::getline(inFile, line)) {
        std::stringstream ss(line); 
        std::string numStr{};
        std::string sellerId{};
        std::string buyerId{};
        std::string costStr{};
        std::string productStr{};
        std::string productId{};
        int num{};
        double cost;

        std::shared_ptr<User> seller;
        std::shared_ptr<User> buyer;
        
        std::getline(ss, numStr, ';');
        std::getline(ss, sellerId, ';');
        std::getline(ss, buyerId, ';');
        std::getline(ss, costStr, ';');

        num = stoi(numStr);
        cost = stod(costStr);

        for(int i = 0; i < users.size(); ++i) {

            if(users[i]->getId() == buyerId) {
                buyer = users[i];
            }
            else if(users[i]->getId() == sellerId) {
                seller = users[i];
            }

        }

        std::getline(ss, productStr);
        
        std::stringstream ss2(productStr);
        std::vector<std::shared_ptr<Product>> vec;

        while(std::getline(ss2, productId, ',')) {

            for(int i = 0; i < products.size(); ++i) {

                if(products[i]->getId() == productId) {
                    vec.push_back(products[i]);
                }

            }

        }

        std::shared_ptr<Log> ptr = std::make_shared<Log>(seller, buyer, vec, cost, num);

    }

    inFile.close();

}// end of System::loadLogs
//========================================================================================================


//========================================================================================================
// System - Load Discounts
//========================================================================================================
// Reads the discount definitions from Discounts.txt and creates the discount object.
//========================================================================================================


void System::loadDiscounts() {


    std::ifstream inFile("Discounts.txt");

    if (!inFile.is_open()) {

        std::cerr << "Failed to open Discounts.txt" << std:: endl;

        return;

    }

    std::string line;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string discountId;
        std::string productId;
        std::string percentageStr;

        std::getline(ss, discountId, ';');
        std::getline(ss, productId, ';');
        std::getline(ss, percentageStr, ';');

        double percentage = 0.0;

        std::shared_ptr<Product> matchedProduct = nullptr;

        for(const auto& p : products) {

            if (p->getId() == productId) {

                matchedProduct = p;

                break;

            }

        }

        if(!matchedProduct) {
            std::cerr << "Product ID not found for discount: " << productId << "\n";
            continue;
        }
        // Create and store discount
        auto d = std::make_shared<Discount>(discountId, matchedProduct, percentage);
        discounts.push_back(d);
    }

    inFile.close();

}  // end of System::loadDiscounts
//========================================================================================================


//========================================================================================================
// System - Save Data
//========================================================================================================
// Saves products, users, discounts, and logs into their files.
//========================================================================================================
void System::saveData() {

	std::ofstream productFile;
	// Stores: Book;Great Book;10.10;B12345
	productFile.open("Products.txt");

	if(!productFile.is_open()) {
		std::cerr << "Failed to open Products.txt for writing.\n";
		return;
	}
	else {
		for(int i=0; i<products.size(); ++i) {
			productFile << products[i]->getType() << ";"
			            << products[i]->getName() << ";"
			            << products[i]->getPrice() << ";"
			            << products[i]->getId() << "\n";
		}
	}

	productFile.close();

	std::ofstream userFile;
	userFile.open("Users.txt");    // stored like: Buyer;Bob the Buyer;11.17;B1234,E12345,C0925,B3285

	if(!userFile.is_open()) {
		std::cerr << "Failed to open Users.txt.\n";
		return;
	}
	else {
		// returns "Buyer" or "Seller"
		for(int i=0; i<users.size(); ++i) {
			std::string type = users[i]->getType();
			std::string name = users[i]->getName();
			std::string id = users[i]->getId();

			userFile << type << ";" << name << ";" << id << ";";

			if(type == "Buyer") {
				std::shared_ptr<Buyer> buyer = std::dynamic_pointer_cast<Buyer>(users[i]);
				userFile << buyer->getWallet() << ";";
			}
			
			std::vector<std::shared_ptr<Product>> owned = users[i]->getProducts();
			for(int j=0; j<owned.size(); ++j) {
				userFile << owned[j]->getId();
				if(j != owned.size() - 1) {
					userFile << ",";
				}
			}

			userFile << "\n";
		}
	}

	userFile.close();	// Closes and saves it

	std::ofstream discountFile;
	discountFile.open("Discounts.txt");    // stored like D123;B12345;0.15

	if(!discountFile.is_open()) {
		std::cerr << "Failed to open Discounts.txt.\n";
		return;
	}
	else {
		for(int i = 0; i < discounts.size(); ++i) {
			discountFile << discounts[i]->getId() << ";"
			             << discounts[i]->getProduct()->getId() << ";"
			             << discounts[i]->getPercentage() << "\n";
		}
	}

	discountFile.close();

	std::ofstream logFile;
	logFile.open("Logs.txt");   // stored like 1;S123;B8972;11.11;P123,P421,P3215

	if (!logFile.is_open()) {
		std::cerr << "Failed to open Logs.txt.\n";
		return;
	}
	else {
		for(int i = 0; i < log.size(); ++i) {
			logFile << log[i]->getTransactionNumber() << ";"
			        << log[i]->getSeller()->getId() << ";"
			        << log[i]->getBuyer()->getId() << ";"
			        << log[i]->getCost() << ";";

			std::vector<std::shared_ptr<Product>> items = log[i]->getItems();
			for(int j = 0; j < items.size(); ++j) {
				logFile << items[j]->getId();
				if (j != items.size() - 1) {
					logFile << ",";
				}
			}
			logFile << "\n";
		}
	}

	logFile.close();
}// end of System::saveData
//========================================================================================================


//========================================================================================================
// System - Search (by price range)
//========================================================================================================
// Finds products and discounts with a price that falls in a specific range.
//========================================================================================================
std::vector<std::string> System::search(const std::string& query) const {

    int counter = 1;
    std::vector<std::string> matches;

    for(auto& p : products) {
        if(p->getName() == query) {
            matches.push_back(p->getId());  // if id matches, put into vector
            std::cout << "Result " << counter << ": " 
                << "\n\tName: " << p->getName()
                << "\n\tId: " << p->getId()
                << "\n\tType: " << p->getType()
                << std::endl << std::endl;
            ++counter;
        }
        else if(p->getType() == query) {
            matches.push_back(p->getId());  // if type matches, put into vector
            std::cout << "Result " << counter << ": " 
                << "\n\tName: " << p->getName()
                << "\n\tId: " << p->getId()
                << "\n\tType: " << p->getType()
                << std::endl << std::endl;
            ++counter;
        }
    }

    return matches;

}// end of System::search
//========================================================================================================


//========================================================================================================
// System - Transaction Handling
//========================================================================================================
//
std::vector<std::string> System::search(const int upperPrice, const int lowerPrice) const {

    int counter = 1;
    std::vector<std::string> matches;

    for(auto& p : products) {
        if(p->getPrice() >= lowerPrice && p->getPrice() <= upperPrice) {
            matches.push_back(p->getId());  // if price is in range, put into vector
            std::cout << "Result " << counter << ": " 
                << "\n\tName: " << p->getName()
                << "\n\tId: " << p->getId()
                << "\n\tPrice: " << p->getPrice()
                << std::endl << std::endl;
            ++counter;
        }
    }

    counter = 1;

    for(auto& d : discounts) {     // same as above but for discounts
        if(d->apply() >= lowerPrice && d->apply() <= upperPrice) {
            matches.push_back(d->getId());
            std::cout << "Result " << counter << ": " 
                << "\n\tName: " << d->getProductName()
                << "\n\tId: " << d->getId()
                << "\n\tPrice: " << d->apply()
                << std::endl << std::endl;
            ++counter;
        }
    }

    return matches;

}// end of System::search
//========================================================================================================


//========================================================================================================
// System - Displays Bundles and Discounts
//========================================================================================================
// Shows all available discount deals, followed by the bundle offers to the console.
//========================================================================================================
void System::displayBundles() const {
    // Displays all available discounts
    std::cout << "\n=== Available Discounts ===\n";
    for (auto& d : discounts) 
    {
        d->printDetails(std::cout);
    }

    // Displays all available bundles
    std::cout << "\n=== Available Bundles ===\n";
    for (auto& b : bundles) {
        b->printDetails(std::cout);
    }
}// end of System::displayBundles
//========================================================================================================


//========================================================================================================
// System - Register New User
//========================================================================================================
// Adds a new user object to the system's user list.
//========================================================================================================
void System::registerUser(std::shared_ptr<User> user) {
    users.push_back(user);
}// end of System::registerUser
//========================================================================================================


//========================================================================================================
// System - Add Product
//========================================================================================================
// Adds a product to the system and assigns it to the seller.
//========================================================================================================
void System::addProduct(std::shared_ptr<Product> product, std::string sellerId) {
	
    for(int i = 0; i < users.size(); ++i) {
        if(users[i]->getId() == sellerId) {
            products.push_back(product);
            users[i]->setProduct(product);
            return;
        }
    }
}// end of System::addProduct
//========================================================================================================


//========================================================================================================
// System - Add Discount
//========================================================================================================
// Registers a new discount deal in the system.
//========================================================================================================
void System::addDiscount(std::shared_ptr<Discount> discount) {
	discounts.push_back(discount);
}// end of System::addDiscount
//========================================================================================================


//========================================================================================================
// System - Add Bundle
//========================================================================================================
// Registers a new bundle offer in the system.
//========================================================================================================
void System::addBundle(std::shared_ptr<Bundle> bundle) {
	bundles.push_back(bundle);
}// end of System::addBundle
//========================================================================================================


//========================================================================================================
// System - Transaction Handling
//========================================================================================================
void System::transaction(const std::string id, std::shared_ptr<Buyer> buyer) {  // transaction by the id, does not matter if it is a discount, bundle, or normal product
    for(int i = 0; i < discounts.size(); ++i) {
        if(id == discounts[i]->getId()) {  // checks if id points to discount
            double price = discounts[i]->apply();  // calculates discounted price
            if(buyer->getWallet() < price)
                throw InsufficientFundsException("Wallet: $" + std::to_string(buyer->getWallet()) + ", Price: $" + std::to_string(price)); // throw exception
            buyer->addFunds(-price);  // deducts funds
            auto prod = discounts[i]->getProduct();  // get product pointer
            prod->setOwner(buyer);  // transfer ownership
            std::vector<std::shared_ptr<Product>> vec{ prod };
            log.push_back(std::make_shared<Log>(
            prod->getOwner(), buyer, vec, price, log.size() + 1
            ));
            return;
        }
    }   // checks if id points to discount
    for(int i = 0; i < bundles.size(); ++i) {
        if(id == bundles[i]->getId()) {  // checks if id points to bundle
            double price = bundles[i]->applyBundle();  // calculates bundle price
            if(buyer->getWallet() < price)
                throw InsufficientFundsException("Wallet: $" + std::to_string(buyer->getWallet()) + ", Price: $" + std::to_string(price)); // throw exception
            buyer->addFunds(-price);  // deducts funds
            auto vec = bundles[i]->getProducts();  // gets bundle items
            for(auto& p : vec) {
                p->setOwner(buyer);  // transfers ownership of each item
            }
            log.push_back(std::make_shared<Log>(
                vec[0]->getOwner(), buyer, vec, price, log.size() + 1
            ));
            return;
        }
    }   // checks if id points to bundle

    for(int i = 0; i < products.size(); ++i) {
        if(id == products[i]->getId()) {    // if there is a product with the proper id
            std::vector<std::shared_ptr<Product>> vec;  // log takes a vector as an argument
            vec.push_back(products[i]); // adds product to vector, only one. 
            std::shared_ptr<Log> newLog = std::make_shared<Log>(products[i]->getOwner(), buyer, vec, products[i]->getPrice(), log.size() + 1);  // creates a new log ptr
            bool good = buyer->purchase(products[i]);   // complete transaction and see if it went through okay
            if(good) {
                log.push_back(newLog); // if transaction okay, save the log pointer
            }
            return;
        }
    }

    throw ProductNotFoundException("Product with ID " + id + " not found.");// throw product not fond exception

}// end of System::transaction
//========================================================================================================
