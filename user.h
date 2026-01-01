#ifndef USER_H
#define USER_H

#include "preprocessors.h"
#include "product.h"

//========================================================================================================
// User Class
//========================================================================================================
// Represents a generic user in the system.
//========================================================================================================
// Variables:
//   @userName - Name of the user
//   @id       - Unique user identifier
//========================================================================================================
class User {
    protected:
        std::string userName;
        std::string id;
    public:
        User(const std::string& name, const std::string& id);
        virtual std::string getType() const = 0;
        std::string getName() const;
        std::string getId() const;
        friend std::ostream& operator<<(std::ostream& os, const User& user);
        virtual void printDetails(std::ostream& os) const = 0;
        virtual void printDetails() const = 0;
        virtual void setProduct(std::shared_ptr<Product> product) = 0;
        virtual std::vector<std::shared_ptr<Product>> getProducts() const = 0;
};// end of User Class
//========================================================================================================

//========================================================================================================
// Buyer Class
//========================================================================================================
// Represents a user who can purchase products.
//========================================================================================================
// Variables:
//   @wallet         - Current funds available for purchases
//   @ownedProducts  - List of owned products
//========================================================================================================
class Buyer : public User, public std::enable_shared_from_this<Buyer> {     // to facilitate purchase method
    private:
        std::vector<std::shared_ptr<Product>> ownedProducts;
        double wallet;
    public:
        Buyer(const std::string& name, const std::string& i, const double wallet);
        void addFunds(const double funds);
        bool purchase(std::shared_ptr<Product>);
        double getWallet() const;
        std::string getType() const override;
        void printDetails(std::ostream& os) const override;
        void printDetails() const override;
        void setProduct(std::shared_ptr<Product> product) override;
        std::vector<std::shared_ptr<Product>> getProducts() const override;
};// enf of Buyer Class
//========================================================================================================


//========================================================================================================
// Seller Class
//========================================================================================================
// Represents a user who sells products.
//========================================================================================================
// Variables:
//   @userName - Name of the seller
//   @id       - Unique identifier for the seller 
//   @products - List of products listed by the seller
//========================================================================================================
class Seller : public User {
    private:
        std::vector<std::shared_ptr<Product>> products;
    public:
        Seller(const std::string& name, const std::string& id);
        void addProduct(std::shared_ptr<Product> product);
        void removeProduct(const std::string& field);   // by name or id
        std::string getType() const override;
        void printDetails(std::ostream& os) const override; 
        void printDetails() const override;
        void setProduct(std::shared_ptr<Product> product) override;
        std::vector<std::shared_ptr<Product>> getProducts() const override;

};// end of Seller Class
//========================================================================================================
#endif
