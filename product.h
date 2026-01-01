#ifndef PRODUCT_H
#define PRODUCT_H

#include "preprocessors.h"

class User; // has to be done to avoid circular dependencies

//========================================================================================================
// Product
//========================================================================================================
// for items that can be bought or sold
//========================================================================================================
// vairables:
//   @name  - Product name
//   @price - Product price
//   @id    - Unique identifier
//   @owner - Pointer to the user who owns the product
//========================================================================================================
class Product {
protected:
	std::string name;
	double price;
	std::string id;
	std::shared_ptr<User> owner;

public:
	Product(const std::string& name, const double price, const std::string& id);
	virtual ~Product() = default;

	// Getters
	std::string getName() const;
	double getPrice() const;
	std::string getId() const;
	std::shared_ptr<User> getOwner() const;
	std::string getOwnerName() const;
	virtual std::string getType() const = 0;

	// Setters
	void setOwner(std::shared_ptr<User> owner);

	// Operators
	bool operator==(const Product& otherProduct);
	friend std::ostream& operator<<(std::ostream& os, const Product& user);

	// Print functions
	virtual void printDetails(std::ostream& os) const = 0;
	virtual void printDetails() const = 0;
};// end of Product Class
//========================================================================================================


//========================================================================================================
// Book
//========================================================================================================
// Book product
//========================================================================================================
class Book : public Product {
public:
	Book(const std::string& name, const double price, const std::string& id);
	std::string getType() const override;
	void printDetails(std::ostream& os) const override;
	void printDetails() const override;
};// end of Book
//========================================================================================================


//========================================================================================================
// Electronics
//========================================================================================================
// Electronics product
//========================================================================================================
class Electronics : public Product {
public:
	Electronics(const std::string& name, const double price, const std::string& id);
	std::string getType() const override;
	void printDetails(std::ostream& os) const override;
	void printDetails() const override;
};// end of Electronics
//========================================================================================================


//========================================================================================================
// Clothing
//========================================================================================================
// Clothing product
//========================================================================================================
class Clothing : public Product {
public:
	Clothing(const std::string& name, const double price, const std::string& id);
	std::string getType() const override;
	void printDetails(std::ostream& os) const override;
	void printDetails() const override;
};// end of Clothing
//========================================================================================================

#endif // PRODUCT_H
