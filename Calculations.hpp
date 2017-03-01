//Calculations used in Black-Scholes Model
//Luke Vandertie and Dan Turturea
//Notre Dame Scientific Computing Fall 2016

/**
*\file Calculations.hpp
*\brief A file containing the techincal calculations involved in the Black-Scholes Model
*\Contains the functions for calculating Normal Distribution, "NormalDist()", d1, "Calculate_d1()", d2, "Calculate_d2()", the value of a call, "CalculateCall()", and the value of a put, "CalculatePut()".

*/
#pragma once
#include "std_lib_facilities.h"
#include "classes.hpp"

double phi(double t)
{
	return exp(-t*t);
}

//lambda for the integral implementation (takes in a function, start and stop points, and number of rectangles)
auto my_integral = [=](double f(double x),double a, double b, double n)
{
	double area_sum = 0;
	if(b>=a)
	{
		double rect_width = (b-a)/n;		
		for(double j = a; j<b; j += rect_width)//for each rectangle
		{
			area_sum += f(j)*rect_width;
		}
	}
	if(b<a)
	{
		double rect_width = (a-b)/n;
		for(double j = a; j>b; j -=rect_width)
		{
			area_sum -= f(j)*rect_width;
		}
	}

	return area_sum;
};

/*
*\brief Calculates the Normal Cumulative Distribution for value
*\param x Input for Normal Cumulative Distribution Function
*/

double NormalDist(double x)
{
	double y = x/sqrt(2);
	auto integral_val = my_integral(phi, 0, y, 1000.0);
    return .5 + (integral_val)/sqrt(3.14159);
	
}

//calculates our d1 for the Black Scholes Calculation
double Calculate_d1(stock_info &stockin, input_info &userin)
{
	double S = stockin.price_;
	double K = userin.strike_;
	double r = stockin.rate_;
	double sigma = stockin.volatility_;
	double T = userin.totaltime_;

    return (log(S/K)+(r+.5*pow(sigma,2))*T)/(sigma * sqrt(T));
}

//calculates our d2 for the Black Scholes Calculation
double Calculate_d2(stock_info stockin, input_info userin)
{
    double S = stockin.price_;
	double K = userin.strike_;
	double r = stockin.rate_;
	double sigma = stockin.volatility_;
	double T = userin.totaltime_;

    return (log(S/K)+(r+.5*pow(sigma,2))*T)/(sigma * sqrt(T)) - sigma*sqrt(T);
}

//Execute the Black-Scholes evaluation for a fair call price on the stock
double CalculateCall(stock_info stockin, input_info userin)
{
    double d1 = Calculate_d1(stockin, userin);
    double d2 = Calculate_d2(stockin, userin);

    double S = stockin.price_;
    double K = userin.strike_;
    double r = stockin.rate_;
    double T = userin.totaltime_;

    double Nd1 = NormalDist(d1);
    double Nd2 = NormalDist(d2);
    
    return S*Nd1 - K*exp(-r*T)*Nd2;
    
}

//Execute the Black-Scholes evaluation for a fair put price on the stock
double CalculatePut(stock_info stockin, input_info userin)
{
	double d1 = Calculate_d1(stockin, userin);
    double d2 = Calculate_d2(stockin, userin);

    double S = stockin.price_;
    double K = userin.strike_;
    double r = stockin.rate_;
    double T = userin.totaltime_;

    double N_d1 = NormalDist(-d1);
    double N_d2 = NormalDist(-d2);

    return K*exp(-r*T)*N_d2 - S*N_d1;
;
}
