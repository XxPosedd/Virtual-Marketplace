#ifndef SYSTEM_H
#define SYSTEM_H

#include "user.h"
#include "product.h"
#include "log.h"
#include "discounts&bundles.h"

//========================================================================================================
// System
//========================================================================================================
// Manages all product, user, discount, bundle, and transaction operations.
//========================================================================================================
// Vairables:
//   @products   - All listed products in the system
//   @users      - All registered users (sellers and buyers)
//   @log        - Records of completed transactions
//   @discounts  - Active discount offers linked to specific products
//   @bundles    - Active bundle deals grouping multiple products
//========================================================================================================
class System {
    private:
        std::vector<std::shared_ptr<Product>> products;
        std::vector<std::shared_ptr<User>> users;
        std::vector<std::shared_ptr<Log>> log;
        std::vector<std::shared_ptr<Discount>> discounts;
        std::vector<std::shared_ptr<Bundle>> bundles;
        void loadProducts();
        void loadUsers();
        void loadLogs();
        void loadDiscounts();
    public:
        System();
        System(const bool load);
        void loadData();
        void saveData();
        std::vector<std::string> search(const std::string& nameOrType) const;
        std::vector<std::string> search(const int upperPrice, const int lowerPrice) const;
        void displayBundles() const;
        void registerUser(std::shared_ptr<User> user);
        void addProduct(std::shared_ptr<Product> product, std::string sellerId);
        void addDiscount(std::shared_ptr<Discount> discount);
        void addBundle(std::shared_ptr<Bundle> bundle);        
        void transaction(const std::string id, std::shared_ptr<Buyer> buyer);
};// end of System Class
//========================================================================================================

#endif
