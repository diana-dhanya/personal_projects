//dhanya narayan dkn170000
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;
//functions that are going to be worked on 
void switchRow(double *array, int size, int &row1, int &row2)
{
	//first check whether array or row is in reduced echelon form
	for (int mem = 0; mem < size; mem++)
	{
		if (mem%5 == 0 && *array == 1 && size <= 12)
			cout << "Each variable column is 1. Step 1 checked.\n";
		//step 2 is to check whether zero is at all columns except constant 
		if ((mem > 0 && mem < 3 && *array == 0) || (mem == 4 && *array == 0) || (mem == 6 && *array == 0) || (mem > 7 && mem < 10 && *array == 0))
			cout << "One or all rows have been solved.\n";
		if (size > 12) //this is only for a 4*4 matrix where last row has all zeros
		{
			if (mem > 11 && mem < 16 && *array == 0)
				cout << "Last row is all zeros.\n";
		}
		array++;
	}
	array-=size;
	//create a copy of the array and display on console
	//create a pointer that points to the array
	double *rowptr1 = array+(row1-1)*4;
	double *rowptr2 = array+(row2-1)*4;
	//create a temporary variable
	double temp;
	for (int i = 1; i <= 4; i++)
	{
		temp = *rowptr1;
		*rowptr1 = *rowptr2;
		*rowptr2 = temp;
		rowptr1++;
		rowptr2++;
	}
	int count = 1;
	for(int i = 0; i < size; i++)
	{
		//use cout fixed setprecision 2 showpoint
	    cout << fixed << setprecision(2) << showpoint;
		cout << *array;
		array++;
		if(count % 4 == 0) //print a new line
			cout << endl;
		count++;
	}
	array-=size;
}
void multiplyRow(double *array, int size, double &quantity, int &rowUse)
{
	//first check whether array or row is in reduced echelon form
	for (int mem = 0; mem < size; mem++)
	{
		if (mem%5 == 0 && *array == 1 && size <= 12)
			cout << "Each variable column is 1. Step 1 checked.\n";
		//step 2 is to check whether zero is at all columns except constant 
		if ((mem > 0 && mem < 3 && *array == 0) || ((mem == 4 && *array == 0) && (mem == 6 && *array == 0))|| (mem > 7 && mem < 10 && *array == 0))
		{
			cout << "One or all rows have been solved.\n";
			cout << "Do not continue row operation if a particular row has been solved.\n";
			return;
		}
		if (size > 12)
		{
			if (mem > 11 && mem < 16 && *array == 0)
				cout << "Last row is all zeros.\n";
		}
		array++;
	}
	array-=size;
	//create a row pointer that points to the array 
	double *rowptr = array+(rowUse - 1)*4;
	//create a temporary variable to use
	double temp1;
	double temp2;
	for (int i = 1; i <= 4; i++)
	{
		*rowptr = temp1;
		temp1 = temp1 * quantity;
		temp2 = temp1;
		temp2 = *rowptr;
		rowptr++;
	}
	int count = 1;
	for(int i = 0; i < size; i++)
	{
		//use cout fixed setprecision 2 showpoint
	    cout << fixed << setprecision(2) << showpoint;
		cout << *array;
		array++;
		if(count % 4 == 0) //print a new line
			cout << endl;
		count++;
	}
	array-=size;
}
//this function adds scalar multiple of one row to another row of user's choice
void addScalar(double *array, int size, int &row1, int &row2, double &scalMul)
{
		//first check whether array or row is in reduced echelon form
	for (int mem = 0; mem < size; mem++)
	{
		if (mem%5 == 0 && *array == 1 && size <= 12)
			cout << "Each variable column is 1. Step 1 checked.\n";
		//step 2 is to check whether zero is at all columns except constant 
		if ((mem > 0 && mem < 3 && *array == 0) || ((mem == 4 && *array == 0) && (mem == 6 && *array == 0))|| (mem > 7 && mem < 10 && *array == 0))
		{
			cout << "One or all rows have been solved.\n";
			cout << "Do not continue row operation if a particular row has been solved.\n";
			return;
		}
		if (size > 12)
		{
			if (mem > 11 && mem < 16 && *array == 0)
				cout << "Last row is all zeros.\n";
		}
		array++;
	}
	array-=size;
	//create a row pointer that points to the specific row
	double *rowptr1 = array + (row1 - 1)*4;
	double *rowptr2 = array + (row2 - 1)*4;
	//create temporary variables to use
	//create a temporary variable to use and dereference pointer 1 
	double temp1;
	double temp2;
	for (int i = 1; i <= 4; i++)
	{
		*rowptr1 = temp1;
		temp1 = temp1 * scalMul;
		temp2 = temp1;
		temp2 = *rowptr1;
		rowptr1++;
	}
	//in this case, a multiple of x != 0 has been multiplied to one row and 
	//added to another row in that case we need more temporary variables to 
	//manipulate the data
	double temp3;
	for (int i = 1; i <= 4; i++)
	{
		//dereference and set *rowptr1 to a temporary variable temp 3
		*rowptr1 = temp3;
		temp3 = *rowptr2 + *rowptr1;
		*rowptr2 = temp3;
		rowptr1++;
		rowptr2++;
	}
	int count = 1;
	for(int i = 0; i < size; i++)
	{
		//use cout fixed setprecision 2 showpoint
	    cout << fixed << setprecision(2) << showpoint;
		cout << *array;
		array++;
		if(count % 4 == 0) //print a new line
			cout << endl;
		count++;
	}
	array-=size;
}
//main function
int main()
{
	string equation; //variable to hold file in equation
	ifstream infile; //open a file
	//open a file matrix.txt
	infile.open("matrix.txt.txt", ios::in);
	//check whether file exists
	if (infile)
		cout << "File exists. Parsing equations..." << endl;
	else
    {
    	cout << "File not found.\n";
    	exit(0);
	}
	//next count number of equations in the file
	int eqCount = 0;
	while (!infile.eof())
	{
		getline(infile, equation); //parse a line and continue
		//increase equation count by 1
		eqCount++;
	}
	//close file and reopen it
	infile.close();
	infile.open("matrix.txt.txt");
	cout << "Number of players = " << eqCount << endl; //number of players = number of equations
	/*create a while loop again to parse the equations once more and add
	coefficients to the columns*/
	//initialize a dynamically allocated array of type double with constant no. of columns
	int numRows = eqCount;
	const int numCols = 4;
	int arrSize = numRows * numCols;
	double* matrixarr = new double[arrSize];
	//initialized new array and set all values to zero at first
	for (int i = 0; i < arrSize; i++)
		*matrixarr = 0.0;
	//make arrptr point to matrixarr
	double *arrptr = NULL;
	arrptr = matrixarr;
	//in the while loop, arrptr is placed at the starting address of the target row after parsing
	while (!infile.eof())
	{
		//get variable coefficients and make sure all pointers are null
		//maximum size of array is 16
		double filecoef;
		double fileconst;
		char filevar;
		//initialize array pointer to initial row address to prevent confusion
		//find whether each coefficient is present or not
		char ch = infile.peek();
		if (isdigit(ch))
		{
			infile >> filecoef;
			infile >> filevar;
			if(filevar == 'x')
			{
				//arrptr at its current position
				*matrixarr = filecoef;
			}
			else if (filevar == 'y')
			{
				//move pointer 1 place
				arrptr = arrptr + 1;
				*matrixarr = filecoef;
				arrptr = arrptr - 1;	
			}
			else if (filevar == 'z')
			{
			    arrptr = arrptr + 2;
			    *matrixarr = filecoef;
			    arrptr = arrptr - 2;
			}		
	    }
	    else if (!isdigit(ch))
	    {
	    	filecoef = 1;
	    	infile >> filevar;
	    	if(filevar == 'x')
			{
				//arrptr at its current position
				*matrixarr = filecoef;
			}
			else if (filevar == 'y')
			{
				//move pointer 1 place
				arrptr = arrptr + 1;
				*matrixarr = filecoef;	
				arrptr = arrptr - 1;	
			}
			else if (filevar == 'z')
			{
			    arrptr = arrptr + 2;
			    *matrixarr = filecoef;
			    arrptr = arrptr - 2;
			}		
		}
		else if (ch == '=')
		{
			infile >> fileconst;
			//move pointer 3 spaces then move back to starting row
			arrptr = arrptr + 3;
			*matrixarr = fileconst;
			arrptr = arrptr - 3;
		}
	matrixarr = matrixarr + 4;
	}
	matrixarr-=arrSize;
	arrptr = NULL;
	/*note: since variables are of any order, the pointer will be at first at its starting address 
	then it will move 1, 2 or 3 addresses depending on the situation*/
	//print matrix
	cout << "current status of matrix is:" << endl;
	double matrixAdd;
	//put arrptr back to null
	*arrptr = NULL;
	int counter = 0;
	for (matrixAdd = 0; matrixAdd < arrSize; matrixAdd++)
	{
		//use cout fixed setprecision 2 showpoint
		cout << fixed << setprecision(2) << showpoint;
		cout << *arrptr;
		arrptr++;
		if (counter % 4 == 0)
			cout << endl;
		counter++;
	}
	//create a do while loop that asks user for choice to perform row manipulations
	int choice;
	do
	{
		cout << "Enter a choice.\n";
		cout << "1. switch 2 rows.\n";
		cout << "2. multiply row by a non zero number.\n";
		cout << "3. multipy one row by a number and add it to another row.\n";
		cout << "4. Exit program.\n";
		cout << "Enter your choice: ";
		cin >> choice;
		while (choice < 0 || choice > 4)
		{
			cout << "Invalid choice.\n"; //user must enter a choice that is either from 1 - 4
			cin >> choice;
		}
		if (choice == 1)
		{
			int userRow1;
			int userRow2;
			cout << "Enter row numbers to switch." << endl;
			cin >> userRow1;
			cin >> userRow2;
			//validate your choice, userRow should be between 1 and specified number of rows
			while (userRow1 < 1 || userRow1 > eqCount)
			{
				cout << "Rows must not be equal to each other and must be 1-4.\n";
				cin >> userRow1;
			}
			while (userRow2 < 1 || userRow2 > eqCount)
			{
				cout << "Rows must not be equal to each other and must be 1-4.\n";
				cin >> userRow2;
			}
			while (userRow1 == userRow2)
			{
				cout << "Row must not be same.\n";
				cin >> userRow1 >> userRow2;
			}
			//pass these values to a function
			switchRow(matrixarr, arrSize, userRow1, userRow2);
		}
		else if (choice == 2)
		{
			int rowChoice;
			double multiply; //user must enter a valid row and a valid non zero multiplier
			cout << "Enter row number and a multiple to multiply said row.\n";
			cin >> rowChoice;
			cin >> multiply;
			while (rowChoice < 1 || rowChoice > eqCount)
			{
				cout << "Row number is invalid and multiplier must not be zero.\n";
				cin >> rowChoice;
			}
			while (multiply == 0.0)
			{
				cout << "multiplier must not be zero.\n";
				cin >> multiply;
			}
			//pass these values to a function and display modified matrix to console
			multiplyRow(matrixarr, arrSize, multiply, rowChoice);
		}
		else if (choice == 3)
		{
			cout << "Enter row to be multiplied, enter a number to multiply said row, add to another row of your choice.\n";
			int row1;
			int row2;
			double scalar;
			cin >> row1 >> row2 >> scalar;
			while (row1 > 0 || row1 < eqCount)
			{
				cout << "Row is invalid.\n";
				cin >> row1;
			}
			while (row2 > 0 || row2 < eqCount)
			{
				cout << "Row is invalid.\n";
				cin >> row2;
			}
			while (scalar == 0)
			{
				cout << "scalar is invalid.\n";
				cin >> scalar;
			}
			//pass these values to the function as specified
			addScalar(matrixarr, arrSize, row1, row2, scalar);
		}
		else if (choice == 4)
		{
			cout << "Program quit." << endl;
			exit(0);
		}
	} while(choice != 4);
	//delete array after using
	delete [] matrixarr;
	infile.close();
	return 0;
}

