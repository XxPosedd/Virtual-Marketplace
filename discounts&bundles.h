#ifndef DISCOUNTS_AND_BUNDLES_H
#define DISCOUNTS_AND_BUNDLES_H

#include "preprocessors.h"
#include "user.h"
#include "product.h"

//========================================================================================================
// Bundle Struct
//========================================================================================================
// Represents a group of products sold together for one fixed price.
//========================================================================================================
// Members:
//   @id          - Code that identifies the bundle
//   @products    - List of products in the bundle
//   @cost        - Total price for the whole bundle
//   @names       - Combined product names as one string
//   @description - Text description of what's in the bundle
//========================================================================================================
struct Bundle
{
private:
	std::string id;
	std::vector<std::shared_ptr<Product>> products;
	double cost;
	std::string names;
	std::string description;

public:
	Bundle(const std::string& code,
	       const std::vector<std::shared_ptr<Product>>& products,
	       double cost,
	       const std::string& names,
	       const std::string& desc);

	double applyBundle() const;
	void printDetails(std::ostream& os = std::cout) const;

	// Getters
	 double getPercentage() const;
	std::string getId() const;
	std::string getNames() const;
	std::string getDescription() const;
	std::vector<std::shared_ptr<Product>> getProducts() const;
	std::string getType() const;
};// end of Bundle Struct
//========================================================================================================


//========================================================================================================
// Discount Stuct
//========================================================================================================
// Represents a discount applied to a single product.
//========================================================================================================
// Variables:
//   @id         - Code that identifies the discount
//   @product    - Product the discount is for
//   @percentage - How much percent to take off the price
//========================================================================================================
struct Discount
{
private:
	std::string id;
	std::shared_ptr<Product> product;
	double percentage;

public:
	Discount(const std::string& code,
	         std::shared_ptr<Product> product,
	         double percentage);

	double apply() const;
	void printDetails(std::ostream& os = std::cout) const;

	// Getters
	std::string getId() const;
	std::shared_ptr<Product> getProduct() const;
	std::string getType() const;
	std::string getProductName() const;
};// end of Discount Stuct
//========================================================================================================
#endif // DISCOUNTS_AND_BUNDLES_H
