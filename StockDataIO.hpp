//Data Sheet References
//Luke Vandertie and Dan Turturea
//Notre Dame Scientific Computing Fall 2016

/**
*\file StockData.hpp
*\brief A header file containing funtions related to manipulating data from the excel spreadsheet of stock info 
*/
#pragma once
#include "classes.hpp"
#include "std_lib_facilities.h"

vector<stock_info> ImportStockTickers(string datasheet)
{

	ifstream fin(datasheet);
	string ticker;
	string random1; 
	double Prev;
	double Vol;
	char percent_sign;
	vector<stock_info> stock_list;
	if(!fin)
	{
		stock_info tmpstock;
		tmpstock.price_ = -1;
		stock_list.push_back(tmpstock);
	}
	
	while(fin)
	{
		fin>>ticker;
		if(ticker != "PX_LAST" && ticker != "12MO_PUT_IMP_VOL")
		{
			fin>>random1>>random1>>Prev>>Vol;
			stock_info tmpstock;
			tmpstock.ticker_ = ticker;
			tmpstock.price_ = Prev;
			tmpstock.volatility_ = Vol/100;//convert from percent to decimal
			stock_list.push_back(tmpstock);
		}
	}
	return stock_list;
}

//takes in a ticker and a vector of stocks and their details, and then finds the data associated with that stock (current price and volatility)

 stock_info GetStockInfo(string s, vector<stock_info> stock_list) 
 {
	//iterate through the ticker (string) components of the vector until desire ticker found
	//if ticker not found, return a fake stock with a price of -1 to indicate that a valid stock was not found
 	stock_info desired_stock;
 	desired_stock.price_;
 	for(int ii = 0; ii<stock_list.size(); ii++)
 	{
 		if(stock_list[ii].ticker_ == s)
 		{
 			desired_stock = stock_list[ii];
 			break;
 		}
 	}
 	if(desired_stock.price_ == -1)
 	{
 		//throw error("No stock found")
 	}
 	else
 	{
 		return desired_stock;
	}	
}

double GetRiskFreeRate(vector<stock_info> v)
{
	for(int j = 0; j<v.size();j++)
	{
		if(v[j].ticker_ == "RISK")
		{
			return v[j].price_;
		}
	}
}
