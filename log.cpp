#include "log.h"

Log::Log(const std::shared_ptr<User> s, const std::shared_ptr<User> b, const std::vector<std::shared_ptr<Product>>& p, const double c, const int num) : seller(s), buyer(b), products(p), cost(c), transactionNumber(num) {}
void Log::print() const {
    std::cout << "Transaction " << transactionNumber << ":"
        << "\n\tSeller: " << seller->getId() 
        << "\n\tBuyer:" << buyer->getId();
    for(int i = 0; i < products.size(); ++i) {
        std::cout << "\n\tProduct " << i << ": " << products[i]->getId();
    }
    std::cout << "\n\tCost: " << cost << std::endl << std::endl;
}
std::shared_ptr<User> Log::getSeller() const {
    return seller;
}
std::shared_ptr<User> Log::getBuyer() const {
    return buyer;
}
double Log::getCost() const {
    return cost;
}