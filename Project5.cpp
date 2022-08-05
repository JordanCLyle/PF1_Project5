//---------------------------------------------------
// Purpose: Implement menu-based spreadsheet program.
// Author:  Dr. John Gauch
// Editor: Jordan Lyle
//---------------------------------------------------

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

// Global constants
const int ROWS = 9;
const int COLS = 9;

//---------------------------------------------------
// Read and convert location string to row col value
//---------------------------------------------------
void get_location(int &row, int &col)
{
   // Initialize variables
   row = -1;
   col = -1;

   // Loop until a valid location is entered
   while (row < 0 || row > ROWS-1 || col < 0 || col > COLS-1)
   {
      // Get user input
      cout << "Enter location between A1 and I9: " << endl;
      string location = "";
      cin >> location;
   
      // Calculate col between 0 and COLS-1
      if (location.length() > 0)
         col = location[0] - 'A';
 
      // Print error message
      if (col < 0 || col > COLS-1)
         cout << "Error: column should be between A and I" << endl;

      // Calculate row between 0 and ROWS-1
      if (location.length() > 1)
         row = location[1] - '1';
 
      // Print error message
      if (row < 0 || row > ROWS-1)
         cout << "Error: row should be between 1 and 9" << endl;
   }
}

//---------------------------------------------------
// Print command menu to user and get input
//---------------------------------------------------
int get_menu_choice()
{
   // Print command menu
   cout << "Welcome to MiniCalc the PF1 Killer App\n"
        << "   0) Quit the program\n"
        << "   1) Store specified data value\n"
        << "   2) Store random data values\n"
        << "   3) Calculate minimum of data values\n"
        << "   4) Calculate maximum of data values\n"
        << "   5) Calculate sum of data values\n"
        << "   6) Calculate product of data values\n"
        << "   7) Calculate average of data values\n"
        << "   8) Calculate standard deviation of data values\n";

   // Initialize variables
   string input = "";
   int command = -1;

   // Loop until a valid location is entered
   while (command < 0 || command > 8)
   {
      // Get user input
      cout << "Enter command: ";
      cin >> input;
      if (input.length() == 1)
         command = input[0] - '0';

      // Print error message
      if (command < 0 || command > 8)
         cout << "Error: command should be between 0 and 8" << endl;
   }
   return command;
}
void printArr(float arr[ROWS][COLS])
{
    // Outputs the table with all of the current values of the array
    cout << "     A      B      C      D      E      F      G      H      I";
    cout << fixed << "\n-----------------------------------------------------------------\n";
    int count2 = 0;
    for (int r = 0; r < 9; r++)
        {
            cout << count2 + 1 << "| ";
            count2 = count2 + 1;
            for (int c = 0; c < 9; c++)
                    cout << fixed << setprecision(2) << arr[r][c] << " | ";
                    cout << fixed << "\n-----------------------------------------------------------------\n";
        }
}
float userValue(float arr[ROWS][COLS], float &min, float &max, float &sum, float &product, int &count, int &trueValue)
{
    cout << "What is the value you want to store?\n";
    float value = 0;
    cin >> value;
    if (cin.fail())
        {
            cin.clear();  // Prevents the user from putting a character or string as a value
        }
    trueValue = value; // Helps create the range for the random data option
    return(value);
}
void randValue(float arr[ROWS][COLS], float &min, float &max, float &sum, float &product, int &count, int &trueValue, int rows2, int cols2, int rows1, int cols1)
{
    // Initializes the srand and the seed
    srand((unsigned) time(0));
    float value = value;
    // Calculates random value without previous values by user
    if (trueValue != 0)
        {
             for (int i = rows1; i <= rows2; i++)
                {
                    for (int j = cols1; j <= cols2; j++)
                        {
                            arr[i][j] = (rand() % (trueValue*2) + 1);
                        }
                }            
        }
    else if (trueValue == 0) // Calculates random value without previous values by user
        {
             for (int i = rows1; i <= rows2; i++)
                {
                    for (int j = cols1; j <= cols2; j++)
                        {
                            arr[i][j] = (rand() % (100) + 1);
                        }
                }            
        }
    // Makes calculations easier to execute by preventing the user from inserting an invalid range
    if (rows2 - rows1 < 0 || cols2 - cols1 < 0)
        {
            cout << endl << "Make sure rows and columns of the second location are greater than the first!" << endl;
        }
    else
        {
            printArr(arr); //Prints the array only if the range is valid
        }
}
//---------------------------------------------------
// Main program
//---------------------------------------------------
int main()
{
   // Initialize spreadsheet array
   float data[ROWS][COLS];
   for (int row = 0; row < ROWS; row++)
   for (int col = 0; col < COLS; col++)
      data[row][col] = 0;

   // Loop processing menu commands
   // Initialization of variables
   int command = get_menu_choice();
   int rows = 0;
   int cols = 0;
   int trueValue = 0;
   int count = 0;
   float min = 10000000;
   float max = 0;
   float sum = 0;
   float product = 1;
   float average = 0;
   float stdev = 0;
   while (command != 0)
   {
      // Switch statement for processing commands
      switch(command)
        {
        // Takes the user's value and puts it in the given spot in the array
        case 1 :
        {
            get_location(rows, cols); // Gets location user wants to store value
            data[rows][cols] = userValue(data, min, max, sum, product, count, trueValue); // Puts value into the array
            printArr(data); //Prints Array
            count++; // Keeps track of how many data values were inputted
            break;
        }
        // Gets the location from the user and creates a random value
        case 2 : 
        {
            cout << "(Start Value)" << endl;
            get_location(rows,cols); // Gets lower bound location
            int rows1 = rows; //Stores lower bound row value
            int cols1 = cols; //Stores lower bound column value
            cout << "(End Value)" << endl;
            get_location(rows, cols); //Gets upper bound location
            int rows2 = rows; //Stores upper bound row value
            int cols2 = cols; //Stores upper bound column value
            //Calls the function to fill the random values
            randValue(data, min, max, sum, product, count, trueValue, rows2, cols2, rows1, cols1);
            break;
        }
        case 3 :
        {
            cout << "(Start Value)" << endl;
            get_location(rows,cols); 
            int rows1 = rows; 
            int cols1 = cols;
            cout << "(End Value)" << endl;
            get_location(rows,cols); 
            int rows2 = rows; 
            int cols2 = cols; 
            min = 10000000000; // Sets value of min to a very high value
            // Searches every value and finds the minimum value of the array in the range
            for (int i = rows1; i <= rows2; i++)
                {
                    for (int j = cols1; j <= cols2; j++)
                        {
                            if (data[i][j] < min)
                                min = data[i][j];
                        }
                }            
            cout << "The min value of the inputted data is: ";
            cout << min << endl;
            // Gets location the user wants to store the minimum in
            get_location(rows, cols);
            data[rows][cols] = min;
            printArr(data);
            break;
        }
        case 4 :
        // States the maximum value of the data inputted
        {
            cout << "(Start Value)" << endl;
            get_location(rows,cols);
            int rows1 = rows;
            int cols1 = cols;
            cout << "(End Value)" << endl;
            get_location(rows,cols);
            int rows2 = rows;
            int cols2 = cols;
            max = 0;
            // Searches the array for the maximum value in the given range
            for (int i = rows1; i <= rows2; i++)
                {
                    for (int j = cols1; j <= cols2; j++)
                        {
                            if (data[i][j] > max)
                                max = data[i][j];
                        }
                }            
            cout << "The max value of the inputted data is: ";
            cout << max << endl;
            // Puts maximum value in the location the user desires
            get_location(rows, cols);
            data[rows][cols] = max;
            printArr(data);
            break;
        }
        // States the sum of the data inputted
        case 5 :
        {
            cout << "(Start Value)" << endl;
            get_location(rows,cols);
            int rows1 = rows;
            int cols1 = cols;
            cout << "(End Value)" << endl;
            get_location(rows,cols);
            int rows2 = rows;
            int cols2 = cols;
            sum = 0;
            //Sums all of the data in a range
            for (int i = rows1; i <= rows2; i++)
                {
                    for (int j = cols1; j <= cols2; j++)
                        {
                            sum = sum + data[i][j];
                        }
                }            
            cout << "The sum of the inputted data is: ";
            cout << sum << endl;
            // Stores the sum in a location the user chooses
            get_location(rows, cols);
            data[rows][cols] = sum;
            printArr(data);
            break;
        }
        // States the product of the data inputted
        case 6 :
        {
            cout << "(Start Value)" << endl;
            get_location(rows,cols);
            int rows1 = rows;
            int cols1 = cols;
            cout << "(End Value)" << endl;
            get_location(rows,cols);
            int rows2 = rows;
            int cols2 = cols;
            product = 1;
            // Finds the product of the values in a given range
            for (int i = rows1; i <= rows2; i++)
                {
                    for (int j = cols1; j <= cols2; j++)
                        {
                            product = product*data[i][j];
                        }
                }            
            cout << "The product of the inputted data is: ";
            cout << product << endl;
            // Stores the product in a given location by the user
            get_location(rows, cols);
            data[rows][cols] = product;
            printArr(data);
            break;
        }
        // States the average of the data inputted
        case 7 :
        {
            cout << "(Start Value)" << endl;
            get_location(rows,cols);
            int rows1 = rows;
            int cols1 = cols;
            cout << "(End Value)" << endl;
            get_location(rows,cols);
            int rows2 = rows;
            int cols2 = cols;
            average = 0;
            // Finds the average of all of the values in a given range
            for (int i = rows1; i <= rows2; i++)
                {
                    for (int j = cols1; j <= cols2; j++)
                        {
                            average = average + data[i][j];
                            count++;
                        }
                }            
            cout << "The average of the inputted data is: ";
            cout << average / count << endl;
            // Stores the average in a location the user desires
            get_location(rows, cols);
            data[rows][cols] = average/count;
            count = 0;
            printArr(data);
            break;
        }
        // Calculates and states the standard deviation of the data inputted
        case 8 :
        {
            cout << "(Start Value)" << endl;
            get_location(rows,cols);
            int rows1 = rows;
            int cols1 = cols;
            cout << "(End Value)" << endl;
            get_location(rows,cols);
            int rows2 = rows;
            int cols2 = cols;
            stdev = 0;
            // Finds the sum of all of the data in the given range and how many data entries are in the range
            for (int i = rows1; i < rows2; i++)
            {
                for (int j = cols1; j < cols2; j++)
                {
                            sum = sum + data[i][j];
                            count++;
                }
            }
            // Uses sum and count to find the standard deviation of each individual value in the range
            for (int i = rows1; i < rows2; i++)
            {
                for (int j = cols1; j < cols2; j++)
                {
                            stdev = stdev + (pow((data[i][j] - (sum / count)),2));
                }
            }
                stdev = sqrt((stdev  / count)); // Calculates standard deviation of the whole set
                cout << "The standard deviation of the inputted data is: " ;
                cout << stdev << endl;
                // Puts standard deviation value in the location the user desires
                get_location(rows, cols);
                data[rows][cols] = stdev;
                count = 0;
                printArr(data);
                break;
        }
        default :
            break; 
        }

      // Get next command
      if (command != 0)
      {
          command = get_menu_choice();
      }
   }
   return 0;
}
