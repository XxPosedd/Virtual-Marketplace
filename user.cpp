#include "user.h"
#include "product.h"
#include "exceptions.h"

User::User(const std::string& name, const std::string& i) : userName(name), id(i) {}
std::string User::getName() const {
    return userName;
}
std::string User::getId() const {
    return id;
}
std::ostream& operator<<(std::ostream& os, const User& user) {

    user.printDetails(os);
    return os;

}

Buyer::Buyer(const std::string& name, const std::string & i, const double funds) : User(name, i), wallet(funds) {}
void Buyer::addFunds(const double funds) {
    wallet += funds;
}
bool Buyer::purchase(std::shared_ptr<Product> item) {
    if(!item) {
       throw ProductNotFoundException("Cannot purchase a null product."); // throw exception
    }

    if(wallet < item->getPrice()) {
       throw InsufficientFundsException("Wallet: $" + std::to_string(wallet) + ", Price: $" + std::to_string(item->getPrice())); // throw exception
    }
    
    std::shared_ptr<User> ptr;
    this->addFunds(-item->getPrice());
    item->setOwner(shared_from_this());

    return 1;   // transaction was a sucess
                // bool to allow for saving transaction in system.cpp
    
}
double Buyer::getWallet() const {
    return wallet;
}
std::string Buyer::getType() const {
    return "Buyer";
}
void Buyer::printDetails(std::ostream& os) const {
    os << "Name: " << this->getName() << "\nId: " << this->getId() << "\nWallet: " << this->getWallet()<< "\nAmount of Bought Products: " << ownedProducts.size()  << std::endl;
}
void Buyer::printDetails() const {
    std::cout << "Name: " << this->getName() << "\nId: " << this->getId() << "\nWallet: " << this->getWallet()<< "\nAmount of Bought Products: " << ownedProducts.size()  << std::endl;
}
void Buyer::setProduct(std::shared_ptr<Product> product) {
    ownedProducts.push_back(product);
}
std::vector<std::shared_ptr<Product>> Buyer::getProducts() const {
    return ownedProducts;
}

Seller::Seller(const std::string& name, const std::string& id) : User(name, id) {}
void Seller::addProduct(std::shared_ptr<Product> newProduct) {
    products.push_back(newProduct);
}
void Seller::removeProduct(const std::string& field) {
    for(int i = 0; i < products.size(); ++i) {
        if((products[i]->getName() == field ) || (products[i]->getId() == field)) {
            products.erase(products.begin() + i);
            return;
        }
    }
}
std::string Seller::getType() const {
    return "Seller";
}
void Seller::printDetails(std::ostream& os) const {
    os << "Name: " << this->getName() << "\nId: " << this->getId() << "\nAmount of Products: " << products.size() << std::endl;
}
void Seller::printDetails() const {
    std::cout << "Name: " << this->getName() << "\nId: " << this->getId() << "\nAmount of Products: " << products.size() << std::endl;
}
void Seller::setProduct(std::shared_ptr<Product> product) {
    products.push_back(product);
}
std::vector<std::shared_ptr<Product>> Seller::getProducts() const {
    return products;
}