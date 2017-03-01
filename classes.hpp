//Black-Scholes Project Classes
//Luke Vandertie and Dan Turturea
//Notre Dame Scientific Computing Fall 2016

/**
*\file classes.hpp
*\brief A header file which contains our project-specific classes.
*/


/**
*\Class which carries relevant stock information: current price and volatility.
*/
#pragma once
#include "std_lib_facilities.h"

struct stock_info{
    string ticker_;
	double price_; 
	double volatility_;
	double rate_; //market risk free rate calculated from 10-Year Treasury Yield - use decimal form i.e. .05 not 5%
};

/**
*\Class which can carries info input from the user.
*/

struct input_info{
	string ticker_; //ticker representing a stock
	double strike_; //strike price on the option, K
	char optiontype_; //c or p for call or put
	double totaltime_; // time to maturity
};
