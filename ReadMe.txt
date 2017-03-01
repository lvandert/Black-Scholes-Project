Black-Scholes Program:
This program will take user inputs of strike price, option type, and time to expiration to calculate a fair option price based off stock data stored in an external data sheet.  The user can evaluate up to 20 options, and all the results from one running of the program will be exported to a .csv file which can be opened using Microsoft Excel for best viewing results, or a basic text editor.  If you would like different stock data, go to a Bloomberg terminal and download a spreadsheet of stock data to a .txt file.


Files Included:
BlackScholes.cpp  -  Main file
Calculations.hpp  -  Header file containing functions used for the Black-Scholes Calculation
Classes.hpp  -  Header file containing our struct definitions for carrying stock data
GetUserInput.hpp  -  Header file containing functions for receiving input from the user
StockDataIO.hpp  -  Header file containing functions for extracting stock info from a data sheet
Std_lib_facilities.h  -  The oft-used header file containing various useful definitions
S_P_500.txt  -  The data sheet to reference for stock information


Compiling Instructions:
Copy the folder “BlackScholes”  itself (with all the contents within it) to the CRC
Go to BlackScholes on the CRC
Compile by using the following code: g++ -g -std=c++11 BlackScholes.cpp -o BlackScholes
Type ./BlackScholes to run the program
