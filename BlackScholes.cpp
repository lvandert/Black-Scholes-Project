//The main code file for the Black-Scholes Project
//Luke Vandertie and Dan Turturea

#include "StockDataIO.hpp"
#include "GetUserInput.hpp"
#include "Calculations.hpp"

void ClearScreen(int n)
{
	for(int j = 0; j<n; j++)
	{
		cout<<endl;
	}
}

int main()
{
	
	string datasheet = "S_P_500.txt";
	cout<<"This program uses S&P 500 data by default.  Would you like to use the default data (enter 1) or your own data (enter 2)?"<<endl;
	bool donewithfilename = false;
	while(!donewithfilename)
	{
		string tmpstring;
		cin>>tmpstring;
		if(!cin)
		{
			cin.clear();
    		cin.ignore(100000, '\n');
			cout<<"Please enter a 1 or a 2"<<endl;
		}
		else if(tmpstring != "1" && tmpstring != "2")
		{
			cout<<"Please just enter a 1 or 2"<<endl;
		}
		else if(tmpstring == "1")
		{
			break;
		}
		else if(tmpstring == "2")
		{
			cout<<"What is the name of your data file?\n";
			string tmpdatasheet;
			while(true)
			{
				cin>>tmpdatasheet;
				if(!cin)
				{
					cin.clear();
    				cin.ignore(100000, '\n');
    				cout<<"Please enter a valid data name\n";
				}
				else
				{
					datasheet = tmpdatasheet;
					donewithfilename = true;
					break;
				}
			}
		}
	}
	ifstream fin(datasheet);
	if(ImportStockTickers(datasheet)[0].price_ == -1)
	{
		error("Unable to read in your file.  Please go check to make sure your file has the correct name and restart the program.\n");

	}
	vector<stock_info> all_stock_details = ImportStockTickers(datasheet);
	ofstream fout("Black-Scholes Option Price Evaluations.csv");
	//Set the header of the output file
	int tickerw = 9;	//width of ticker column
	int currentw = 15;	//width of current price column
	int strikew = 13; 	//width of strike price column
	int optionw = 12; 	//width of option type column
	int volw = 12; 		//width of volatility column
	int ratew = 16; 	//width of risk-free rate column 
	int timew = 21; 	//width of total time (years) column
	int valw = 20; 		//width of fair option price column
	fout<<setw(tickerw)<<"Ticker,"; 
	fout<<setw(currentw)<<"Current Price,"<<setw(strikew)<<"Strike Price,"<<setw(optionw)<<"Option Type,"<<setw(volw)<<"Volatility,"<<setw(ratew)<<"Risk-Free Rate,";
	fout<<setw(timew)/*<<"Total Time (Years),";   */<<"Years,"<<setw(timew)<<"Months,"<<setw(timew)<<"Days,";
	fout<<setw(valw)<<"Fair Option Price,"<<endl;
	//Done setting the header for the output file
	ClearScreen(100);

	//Get the risk free rate once before running through each evaluation
	double RFrate = GetRiskFreeRate(all_stock_details);

	int numoptions = NumberOptions();

	for(int ii = 0; ii<numoptions; ii++)
	{
		ClearScreen(3);		
		double option_val;
	    cout<<"We will now get inputs for option number "<<ii + 1<<" of "<<numoptions<<"."<<endl;
		input_info user_input;
		user_input.ticker_ = GetTicker(all_stock_details);//get a ticker and check it exists in all_stock_details
		stock_info chosen_stock = GetStockInfo(user_input.ticker_, all_stock_details);//extract all the details on a stock from our list of stocks and their details
		user_input.strike_ = GetStrikePrice(chosen_stock);//Get a strike price on the option and use the stock's current price as a reality check
		user_input.optiontype_ = GetOptionType();//Get the option type (Call or Put) from the user
		user_input.totaltime_ = GetTime();//Get the total time to expiration (in years) of the option
		//*******************************************************Need to figure out risk-free rate*******************************************************
		chosen_stock.rate_ = RFrate;
		//***********************************************************************************************************************************************
		if(user_input.optiontype_ == 'c') 
		{
			option_val = CalculateCall(chosen_stock, user_input);
		}
		else if(user_input.optiontype_ == 'p')
		{
			option_val = CalculatePut(chosen_stock, user_input);
		}
		string fulloptiontype;
		switch(user_input.optiontype_)
		{
			case 'c':
				fulloptiontype = "call";
				break;
			case 'p':
				fulloptiontype = "put";
				break;
		}
		cout<<"The Black-Scholes estimated value of your "<<fulloptiontype <<" option is "<<option_val<<"\n\n\n"<<endl;
		fout<<setw(tickerw)<<user_input.ticker_<<",";
		fout<<setw(currentw)<<chosen_stock.price_<<","<<setw(strikew)<<user_input.strike_<<","<<setw(optionw)<<fulloptiontype<<","<<setw(volw)<<chosen_stock.volatility_<<","<<setw(ratew)<<chosen_stock.rate_<<",";
		
		//recover number of years, months, and days that make up the option time to expiration
		double T = user_input.totaltime_;
		int t = T;//conversion to int removes decimal
		double years = t;
		double M = (T - years)*12;//multiply decimal part of totaltime by 12
		int m = M;//conversion to int removes decimal
		double months = m;
		double D = (M-months)*365/12;
		int d = D;//take care of any slight rounding errors
		double days = d;
		
		fout<<setw(timew)/*<<user_input.totaltime_<<","; */<<years<<","<<setw(timew)<<months<<","<<setw(timew)<<days<<",";
		fout<<setw(valw)<<option_val<<","<<endl;
	} //stop taking inputs


}