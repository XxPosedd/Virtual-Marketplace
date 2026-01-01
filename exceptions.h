#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "preprocessors.h"

//========================================================================================================
// InsufficientFundsException
//========================================================================================================
// Thrown when a user tries to buy something but doesn't have enough funds.
//========================================================================================================
class InsufficientFundsException : public std::runtime_error {
public:
	InsufficientFundsException() 
		: std::runtime_error("Insufficient Funds") {}

	explicit InsufficientFundsException(const std::string& msg) 
		: std::runtime_error("Insufficient Funds: " + msg) {}
};// end of InsufficientFundsException
//========================================================================================================


//========================================================================================================
// ProductNotFoundException
//========================================================================================================
// Thrown when a requested product doesn't exist in the system.
//========================================================================================================
class ProductNotFoundException : public std::runtime_error {
public:
	ProductNotFoundException() 
		: std::runtime_error("Product Not Found") {}

	explicit ProductNotFoundException(const std::string& msg) 
		: std::runtime_error("Product Not Found: " + msg) {}
};// end of ProductNotFoundException
//========================================================================================================


//========================================================================================================
// UnauthorizedActionException
//========================================================================================================
// Thrown when a user attempts an action they do not have permisssion to perform.
//========================================================================================================
class UnauthorizedActionException : public std::runtime_error {
public:
	UnauthorizedActionException() 
		: std::runtime_error("Unauthorized Action") {}

	explicit UnauthorizedActionException(const std::string& msg) 
		: std::runtime_error("Unauthorized Action: " + msg) {}
};// end of UnauthorizedActionException
//========================================================================================================
#endif // EXCEPTION_H
