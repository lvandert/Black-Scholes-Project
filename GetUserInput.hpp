//Get User Input Function
//Luke Vandertie and Dan Turturea
//Notre Dame Scientific Computing Fall 2016
//#include "std_lib_facilities.h" - inluded by classes.hpp
/**
 \file GetUserInput.hpp 
 *\A header file for functions relating to getting input from the user 
 * 
 */

#pragma once
#include "classes.hpp"

/**
 *\brief Asks the user how many options they would like to evaluate
 */
int NumberOptions()
{
	double number;
	int num_opt;
	while (true)
	{
		cout<<"How many options would you like to evaluate (please enter a positive integer): " <<endl;
		cin >> number;//reading in integers yieled serious errors (.5)
		
		if(!cin)
		{
			cin.clear();
    		cin.ignore(100000, '\n');
			cout<<"Please enter a positive integer.\n\n";
		}
		//integer check
		int integer_num;
		integer_num = 10*number;
		if(integer_num%10 != 0)
		{
			num_opt = -1;//set to reach fail state
		}
		else
		{
			num_opt = number;//convert to integer
		}

		if (num_opt < 1) // error-checking to ensure a positive integer was entered
		{
		    cout << "The number of options must be a positive integer value between 1 and 20 inclusive. Please try again." << endl<<endl;
		}
		else if (num_opt > 20) // set a cap on number of options the user can enter
		{
		    cout << "This program only allows you to evaluate up to 20 options at a time. Please try again." << endl<<endl;
		}
		else if(num_opt<=20 && num_opt>=1) //an integer between 1 and 20 inclusive must have been entered, break out of error-checking/input loop
	    {
	    	cin.clear();
    		cin.ignore(100000, '\n');
	        break;
	    }
	}//end error-checking/input loop
	return num_opt;
}//end NumberOptions()

/**
 * \brief A quick check to see if a ticker (string) exists in a vector of stocks
 * \param s The ticker to check for existence
 * \param v The vector of stocks to check in for the ticker
 */
bool TickerExists(string s, vector<stock_info> v)
{
    bool exists = false;
    for(int j = 0;j < v.size();j++)
    {
        if(v[j].ticker_ == s)
        {
        	exists = true;
        	return exists;
        }
    }
}

/**
 * \brief Ask user for a ticker and make sure it exists in our list of valid stocks
 * \param v The list of all valid stocks that can choose from
*/
string GetTicker(vector<stock_info> v)
{
	string ticker;
	char seelist;
	cout<<"Please enter the ticker for the stock you would like to buy an option on (Only S&P 500 stocks are available unless you imported your own data): "<<endl;
	while(true)
	{
	    cin>>ticker;
	    //If not a string is entered:
	    if(!cin)
	    {
	    	cin.clear();
    		cin.ignore(100000, '\n');
	        cout<<"Didn't recognize that input.\n";
	    }
	    for(int j = 0;j<ticker.size();j++)//deal with tickers in uppercase format like received from Bloomberg
	    {
	    	ticker[j] = toupper(ticker[j]);
	    }
	    //If a string that is invalid is entered:
	    if(!TickerExists(ticker, v))    
	    {
	        cout<<"Sorry, that ticker is unavailable in this program.\nPlease enter a different ticker:"<<endl;
	    }
	    //If a string that is valid is entered:
	    if(TickerExists(ticker, v))
	    {
	    	cout<<"The ticker "<<ticker<<" has been selected."<<endl;//confirm we reached this stage
	        break;
	    }
	    

	}
	return ticker;
}

/**
 * \brief Get the strike price from the user
 * \param stock The stock to run a reality check against (strike price isn't too far away from current price)
*/
double GetStrikePrice(stock_info stock)
{
	
	char yesorno;
	double strike = -1;
	bool donewithstrike = false;
	
	cout << "The current price for your stock is "<<stock.price_<<endl<<"What strike price would you like for this option? (Please enter a positive number - no commas needed)" << endl;
	
	while (!donewithstrike)//must check that a valid strike is entered and passes a reality check if needed
	{
    	while (strike <= 0)//check that a valid strike is entered
    	{
    		cin >> strike;
    		//If something other than a number is entered:
    		if (!cin)
    		{
    			cin.clear();
    			cin.ignore(100000, '\n');
    		    cout<<"Please enter a decimal number:\n";
    		}
    	    
    	    // If a non-positive number is entered
    		else if (strike <= 0) 
    		{
    		    cout << "The strike price must be a positive number. Please try again. " << endl;
    		}
    		else
    		{
    			cout<<"The strike price for this option will be "<<strike<<endl;
    			cin.clear();
    			cin.ignore(100000, '\n');
    			break;
    		}
    	}
    	//reality-check: if less than .75*current stock price or greater than 1.25*current stock price, ask to make sure they entered the right value
    	if (strike < .75* stock.price_ || strike > 1.25*stock.price_)
    	{
    		cout << "Are you sure your strike price is correct?" << endl;//reality-check question
    		while(true)//get a response to reality-check question
    		{
        		cin>>yesorno;
        		if(!cin)//invalid response type, keep asking for a correct response to reality-check question
        		{
        			cin.clear();
    				cin.ignore(100000, '\n');
        		   cout<<"Please enter just a 'Y' if you entered the correct strike price of "<<strike<<" or a 'N' if you would like to re-enteryour strike price."<<endl; 
        		}
        		else if(yesorno == 'y' || yesorno == 'Y')//strike price is correct, break out of reality-check loop and set donewithstrike to true to break out entire GetStrike loop
        		{
        			cin.clear();
    				cin.ignore(100000, '\n');
        		    donewithstrike = true;
        		    break;
        		}
        		else if(yesorno == 'n' || yesorno == 'N')//break out of get response to reality-check loop but still not donewithstrike so keep reading in strike price
        		{
        		    cout<<"Ok.  Please enter your strike price for this option:"<<endl;
        		    strike = -1;//send back to input loop
        		    break;
        		}
        		else//if no valid response received, keep asking for correct response to reality-check question
        		{
        			cin.clear();
    				cin.ignore(100000, '\n');
        		    cout<<"Sorry, please enter 'Y' or 'N'\n";
        		}   
    		}//end looping to get a response on if strike is correct
	    }//end reality-check
	    else //no need to reality-check
	    {
	    	donewithstrike = true;
	    }
	}//end error-checking on strike
	return strike;
}

/**
 * \brief Get the option type, call, 'c', or put, 'p'.
*/
char GetOptionType()//returned lowercase
{
	char optiontype;
	cout<<"Would you like this option to be a call (enter 'C') or put (enter 'P')?"<<endl;
	while(true)
	{
	    cin>> optiontype;
	    if(!cin)
	    {
	    	cin.clear();
    		cin.ignore(100000, '\n');
	    	cout<<"Please enter just the character 'C' for call or 'P' for put."<<endl;
	    } 
	    optiontype = tolower(optiontype);
	    if(optiontype != 'c' && optiontype != 'p') //if something other than a C,c,P,p is entered
	    {
	    	cin.clear();
            cin.ignore(100000, '\n');
	    	cout<<"Please enter just a 'C' for call or 'P' for put."<<endl;
	    }
		else if(optiontype == 'c')
		{
			cin.clear();
    		cin.ignore(100000, '\n');
			cout<<"You have chosen a call option on the stock."<<endl;
			break;//done getting input
		}
		else if(optiontype == 'p')
		{
			cin.clear();
    		cin.ignore(100000, '\n');
			cout<<"You have chosen a put option on the stock"<<endl;
			break;
		}
	}//end error-checking/input loop
	return optiontype;
}

/**
 * \brief Ask the user how long until the option matures
 * Will take in number of years, months, and days, and output as one number in terms of years.
 * Error-Checks to make sure the time to expiration is positive.
*/
double GetTime()
{
	double y, m, d;
	double totaltime = -1;
	cout<<"We will ask for time to maturity on this option in terms of number of years + number of months + number of days."<<endl;
	
	while(totaltime <= 0)//time greater than zero check
	{
	    while(true)//read in years
	    {
	        cout<<"First, please enter the number of years until expiration: "<<endl;    
	        cin>>y;
	        
	        if(!cin)
	        {
	        	cin.clear();
    			cin.ignore(100000, '\n');
	            cout<<"Please enter a number"<<endl;
	        }
	        else if (y < 0) 
	        {
	        cout<<"Years must be non-negative."<<endl;
	        }
	        else if (y >= 0)
	        {
	        	cin.clear();
    			cin.ignore(100000, '\n');
	            break;
	        }
	        
	    }
	    while(true)//read in months
	    {
	        cout<<"Second, please enter the number of months until expiration: "<<endl;    
	        cin>>m;
	        
	        if(!cin)
	        {
	        	cin.clear();
    			cin.ignore(100000, '\n');
	            cout<<"Please enter a number"<<endl;
	        }
	        else if (m < 0) 
	        {
	        cout<<"Months must be non-negative."<<endl;
	        }
	        else if (m >= 0)
	        {
	        	cin.clear();
    			cin.ignore(100000, '\n');
	            break;
	        }
	    }
	    while(true)//read in days
	    {
	        cout<<"Finally, please enter the number of days until expiration: "<<endl;    
	        cin>>d;
	        
	        if(!cin)
	        {
	        	cin.clear();
    			cin.ignore(100000, '\n');
	            cout<<"Please enter a number"<<endl;
	        }
	        else if (d < 0) 
	        {
	        cout<<"Days must be non-negative."<<endl;
	        }
	        else if (d >= 0)
	        {
	        	cin.clear();
    			cin.ignore(100000, '\n');
	            break;
	        }	        
	    }
	    totaltime = (y + (m/12.0) + (d/365.0));
	    
	    if(totaltime == 0)//all zeroes were entered, need a positive amount of time for calculation
	    {
	        cout<<"Please enter a time to expiration greater than 0"<<endl;
	    }
	    else if(totaltime > 0)//a valid time to expiration has been entered, break out of error-checking/input loop
	    {
	        cout<<"The total time to expiration is "<<totaltime<<" years."<<endl;
	        break;
	    }
	}//end error-checking/input loop
    return totaltime;
}//end function
