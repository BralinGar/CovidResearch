//----------------------------------------------------------------------------
// QUEST SUMMER 2022 HS RESEARCH PROJECT
//----------------------------------------------------------------------------
// Student Name : Bralin GARCIA
// Assignment : Covid-19 Vaccination Impact Final Project Program 
// Submission Date: 7/13/22
// Complier Info : Win 10 / Dev-C++ 5.11
// Purpose : Analyzes covid cases and deaths on pre-wave and post-wave vaccination time frames then assesses the impact on
//covid-19 vaccination on the r-values of the data, program cannot interpret the type of impact of such case, and only works
//for USA data as per data provided
//----------------------------------------------------------------------------
//userInput = user's string input
//correlation1 = Coefficient correlation of pre-wave covid-19 vaccination of covid cases to covid deaths
//correlation2 = Coefficient correlation of post-wave covid-19 vaccination of covid cases to covid deaths




#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
using namespace std; 


//Functions declarations later defined in the program
double average(double array[], int size);
double myCorrelationCoefficientCalculator(double x[], double y[], int size);
double giveCorrelationCoefficients(string country, string returnValue);
string decision(double rValue);


//Main function that starts on the beginning of program
int main()
{
        
        //Greeting that details purpose of program
        cout << "Welcome to Investigation of Effectiveness of the Covid -19 Vaccination\n" << endl;
        cout << "The program was developed to show Effectiveness of the Covid -19 Vaccination based the read data.\n" << endl;
        cout << "This Program investigate the correlation between confirmed cases vs confirmed deaths before and the after the Covid -19 Vaccination campaign launch\n" << endl;
        cout << "Eventually to address the question of -Does Covid -19 Vaccination have an impact on the number of deaths?-\n" << endl;
        cout << "The calculation method is based upon the correlation coefficient of pre-vaccination wave and post-vaccination wave data.\n" << endl;
        //===========================================================================
        
        //Tracks userInput
        string userInput;
        
        //While loop for user interface
        while(userInput != "USA" && userInput != "EXIT")
        {
                //Repeatable prompt to give user instructions on input
                cout << "To start Please enter the country name." << endl;
                cout << "To exit please type exit." << endl;
                
                //Get user input
                cin >> userInput;
                
                //User input for USA
                if(userInput == "USA")
                {
                        system("CLS");
                        
                        //Get pre and post wave correlation coefficients
                        double correlation1 = giveCorrelationCoefficients(userInput, "PRE");
                        double correlation2 = giveCorrelationCoefficients(userInput, "POST");
                        
                        //Output interpretations based on correlation coefficients
                        cout << "Pre-Wave Covid cases and deaths data has a " << decision(correlation1) << endl << endl;
                        cout << "Post-Wave Covid cases and deaths data has a " << decision(correlation2) << endl << endl;
                        
                        //This is not on the rubric but I wasn't sure how the previous interpretation answers the research
                        //question so I made this arbitrary checker to see deviances in both values since one is pre-wave
                        //and the other is post wave, so the deviance in value would be caused by covid-19 vaccination
                        if(abs(correlation1-correlation2) > 0.2)
                                cout << "Covid-19 Vaccination has a significant enough impact on the number of deaths"<< endl<< endl;
                        else
                                cout << "Covid-19 Vaccination does not have an significant enough impact on the number of deaths"<< endl<< endl;
                }
                //Exit line
                else if(userInput == "EXIT")
                {
                        system("CLS");
                }
                //Wrong input checker
                else
                {
                        system("CLS");
                        cout << "Wrong Input! Try Again." << endl;
                }
                
        }
        cout << "Thank you for using this program";
        return 0; // End program
}


//Finds the mean value of an array of ints
double average(double array[], int size)
{
        double sum(0);
        
        for(int i = 0; i < size; i++)
                sum+=array[i];
        
        double avg = sum / size;
        
        return avg;
}


//Correlation coefficient calculator function that takes in two 1-D arrays and a size
double myCorrelationCoefficientCalculator(double x[], double y[], int size)
{
        
        const double averageX = average(x, size);
        const double averageY = average(y, size);
        
        double dividend(0), divisor(0), xSumSquare(0), ySumSquare(0), correlationCoefficient(0);
        
        for(int i = 0; i < size; i++)
        {
                dividend += (x[i] - averageX) * (y[i] - averageY);
                xSumSquare += pow((x[i] - averageX), 2);
                ySumSquare += pow((y[i] - averageY), 2);
        }
                
        divisor = sqrt(xSumSquare * ySumSquare);
        correlationCoefficient = dividend/divisor;
        
        return correlationCoefficient;
} 


//Function that places all data into 1-D arrays and returns coefficient correlation value
double giveCorrelationCoefficients(string country, string returnValue)
{
        double correlationValue1, correlationValue2;
        
        //USA-only data entry
        if(country == "USA")
        {
                //array declaration and size of pre-wave data
                int ARRAY_SIZE_1 = 183;
                double preConfirmedCases[ARRAY_SIZE_1];
                double preConfirmedDeaths[ARRAY_SIZE_1];
                
                //array declaration and size of post-wave data
                int ARRAY_SIZE_2 = 152;
                double postConfirmedCases[ARRAY_SIZE_2];
                double postConfirmedDeaths[ARRAY_SIZE_2];
                
                //Files opened from local directory
                ifstream inputData1;
                inputData1.open("BeforeVaccination.txt");
                
                ifstream inputData2;
                inputData2.open("AfterVaccination.txt");
                
                //Populated both 1-D arrays with data from files
                for(int i = 0; i < ARRAY_SIZE_1; i++)
                {
                        inputData1 >> preConfirmedCases[i];
                        inputData1 >> preConfirmedDeaths[i];
                }
                
                for(int i = 0; i < ARRAY_SIZE_2; i++)
                {
                        inputData2 >> postConfirmedCases[i];
                        inputData2 >> postConfirmedDeaths[i];
                }
                
                //Close files to prevent corruption
                inputData1.close();
                inputData2.close();
                
                //Calculate the coefficient correlation of pre-wave and post-wave data
                correlationValue1 = myCorrelationCoefficientCalculator(preConfirmedCases, preConfirmedDeaths, ARRAY_SIZE_1);
                correlationValue2 = myCorrelationCoefficientCalculator(postConfirmedCases, postConfirmedDeaths, ARRAY_SIZE_2);
        }
        //No country available except USA
        else 
                return 0;
        
        //Return values based on if declaration needed pre or post wave data
        if(returnValue == "PRE") 
                return correlationValue1;
        else if(returnValue == "POST") 
                return correlationValue2;
        
        //return 0 if no returnValue was given in declaration of function
        return 0;
}


//Matches correlation coefficient value with interpretation based on rubric
string decision(double rValue)
{
        string decisionString;
        
        if(rValue == 0) 
                decisionString = "No correlation at all";
        else if(0 < rValue && rValue < 0.2) 
                decisionString = "Very weak correlation";
        else if(0.2 <= rValue && rValue < 0.4) 
                decisionString =  "Weak correlation";
        else if(0.4 <= rValue && rValue < 0.6) 
                decisionString = "Moderate correlation";
        else if(0.6 <= rValue && rValue < 0.8) 
                decisionString = "Strong correlation";
        else if(0.8 <= rValue && rValue < 1) 
                decisionString = "Very Strong correlation";
        else if(rValue == 1) 
                decisionString = "Perfect correlation";
        else 
                decisionString = "No Value";
        
        return decisionString;
}