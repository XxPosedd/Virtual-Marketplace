#include "discounts&bundles.h"

// ---------------------- Discount Implementation ----------------------

Discount::Discount(const std::string& code,
                   std::shared_ptr<Product> product,
                   double percentage)
    : id(code), product(std::move(product)), percentage(percentage) {}

    
/**
 * This calculates the price after applying the discount percentage
 * to the product's original price and returns the discounted amount.
 */
double Discount::apply() const 
{
    double orig = product->getPrice();
    return orig * (1.0 - percentage / 100.0);
}

/**
 * This outputs the discount details to the specified output stream.
 * It shows the discount code, the product ID, the percentage off,
 * the original price, and the discounted price.
 */
void Discount::printDetails(std::ostream& os) const 
{
    double orig = product->getPrice();
    double now = apply();
    os << "Discount [" << id << "] on Product " << product->getId()
       << ": " << percentage << "% off (Orig $" << orig
       << " -> Now $" << now << ")\n";
}

// Retuns the code that identifies to discount 

std::string Discount::getId() const 
{

    return id;
}

double Discount :: getPercentage() const {
    return percentage;
}


std::shared_ptr<Product> Discount::getProduct() const {
    return product;
}
std::string Discount::getType() const {
    return "Discount";
}
std::string Discount::getProductName() const {
    return this->product->getName();
}

// ---------------------- Bundle Implementation ----------------------

// Constructor that creates a bundle deal, storing the list of products included in the bundle, setting the total bundle cost.

Bundle::Bundle(const std::string& code,
               const std::vector<std::shared_ptr<Product>>& products,
               double cost,
               const std::string& names,
               const std::string& desc)
    : id(code), products(products), cost(cost), names(names), description(desc) {}

// Returns the fixed total price set for the bundle deal
double Bundle::applyBundle() const 
{
    return cost;
}

// Prinys the bundle details to the ostream, which shows the bundle code, description,a nd product names.
void Bundle::printDetails(std::ostream& os) const 
{
    os << "Bundle [" << id << "] - " << description << "\n";
    os << "Includes: " << names << "\n";
    for (auto& p : products) {
        os << "  - " << p->getId() << " @ $" << p->getPrice() << "\n";
    }
    os << "Total Cost: $" << cost << "\n";
}

std::string Bundle::getId() const 
{
    return id;
}

std::string Bundle::getNames() const 
{
    return names;
}

std::string Bundle::getDescription() const 
{
    return description;
}

std::vector<std::shared_ptr<Product>> Bundle::getProducts() const {
    return products;
}
std::string Bundle::getType() const {
    return "Bundle";
}
