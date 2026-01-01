#include "product.h"
#include "user.h"

Product::Product(const std::string& n, const double p, const std::string& i) : name(n), price(p), id(i) {}

std::string Product::getName() const {
    return this->name;
}
double Product::getPrice() const {
    return this->price;
}
std::string Product::getId() const {
    return this->id;
}
std::shared_ptr<User> Product::getOwner() const {
    return this->owner;
}
std::string Product::getOwnerName() const {
    return owner->getName();
}

void Product::setOwner(std::shared_ptr<User> newOwner) {
    owner = newOwner;
}

bool Product::operator==(const Product& otherProduct) {
    return this->getId() == otherProduct.getId();
}
std::ostream& operator<<(std::ostream& os, const Product& item) {

    item.printDetails(os);
    return os;

}

Book::Book(const std::string& n, const double p, const std::string& i) : Product(n, p, i) {}

std::string Book::getType() const {
    return "Book";
}
void Book::printDetails(std::ostream& os) const { 
    os << "Book - Name: " << this->getName() << "\nPrice: " << this->getPrice() << "\nId: " << this->getId() << "\nOwner: " << this->getOwnerName();
}
void Book::printDetails() const { 
    std::cout << "Book - Name: " << this->getName() << "\nPrice: " << this->getPrice() << "\nId: " << this->getId() << "\nOwner: " << this->getOwnerName();
}

Electronics::Electronics(const std::string& n, const double p, const std::string& i) : Product(n, p, i) {}

std::string Electronics::getType() const {
    return "Electronics";
}
void Electronics::printDetails(std::ostream& os) const {
    os << "Electronic - Name: " << this->getName() << "\nPrice: " << this->getPrice() << "\nId: " << this->getId() << "\nOwner: " << this->getOwnerName();
}
void Electronics::printDetails() const {
    std::cout << "Electronic - Name: " << this->getName() << "\nPrice: " << this->getPrice() << "\nId: " << this->getId() << "\nOwner: " << this->getOwnerName();
}

Clothing::Clothing(const std::string& n, const double p, const std::string& i) : Product(n, p, i) {}

std::string Clothing::getType() const {
    return "Clothing";
}
void Clothing::printDetails(std::ostream& os) const {
    os << "Clothing - Name: " << this->getName() << "\nPrice: " << this->getPrice() << "\nId: " << this->getId() << "\nOwner: " << this->getOwnerName();
}
void Clothing::printDetails() const {
    std::cout << "Clothing - Name: " << this->getName() << "\nPrice: " << this->getPrice() << "\nId: " << this->getId() << "\nOwner: " << this->getOwnerName();
}