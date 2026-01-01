#ifndef LOG_H
#define LOG_H

#include "user.h"
#include "product.h"

//========================================================================================================
// Log
//========================================================================================================
// Records a completed transaction between a seller and a buyer.
//========================================================================================================
// Variables:
//   @seller            - The user selling the item(s)
//   @buyer             - The user buying the item(s)
//   @products          - List of products involved (can include bundles)
//   @cost              - Final price paid by the buyer
//   @transactionNumber - ID for the transaction (should be log.size() + 1 in system)
//========================================================================================================
struct Log {
private:
	std::shared_ptr<User> seller;
	std::shared_ptr<User> buyer;
	std::vector<std::shared_ptr<Product>> products; // can have multiple products in the case of bundles
	double cost;                                    // records the price paid (discounted or not)
	int transactionNumber;                          // starts at 1, assigned by system on creation

public:
	Log(const std::shared_ptr<User> seller,
	    const std::shared_ptr<User> buyer,
	    const std::vector<std::shared_ptr<Product>>& products,
	    const double cost,
	    const int transactionNumber);

	void print() const;

	// Getters
	std::shared_ptr<User> getSeller() const;
	std::shared_ptr<User> getBuyer() const;
	double getCost() const;
	// for saveData
	int getTransactionNumber() const;
	std::vector<std::shared_ptr<Product>> getItems() const;
};// end of Log Struct
//========================================================================================================
#endif // LOG_H
