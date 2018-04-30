//Karen Rees-Milton. Assignment 3. April 26 2018
//A program to provide a simple seat reservation system
//for an airline providing service between Ottawa and Kingston

#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;

//prototypes
int loadArrays(ifstream &, string[], int[][2]);
void printReport(ofstream &, const string[], const int[][2], int);
bool isFull(int);
bool reserveSeat(string[], int[][2], int &);
void validateSeat(int &, int);
void findPassenger(string, const string[], int &, int &);
const int SIZE = 12;

int main()
{
	int reservation[SIZE][2];
	string name[SIZE];
	int noPassengers = 0;
	int position;
	ifstream fin("reservations.dat");
	if (!fin.is_open())
	{
		cout << "error opening reservations.dat file - contact systems";
		system("pause");
		exit(-1);
	}
	ofstream fout("reservations.rpt");
	if (!fout.is_open())
	{
		cout << "error opening reservations.rpt file - contact systems";
		system("pause");
		exit(-2);
	}
	cout << "Search for non passenger \n";
	findPassenger("Superman", name, position, noPassengers);
	cout << "Passenger: Superman";
	if (position < noPassengers)
		cout << " is seated in row " << reservation[position][0]
		<< " seat " << reservation[position][1];
	else
		cout << " is not found ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);
	cout << "Load arrays\n";
	noPassengers = loadArrays(fin, name, reservation);
	printReport(fout, name, reservation, noPassengers);
	cout << "Search for existing passenger \n";
	findPassenger("J. Doe", name, position, noPassengers);
	cout << "Passenger: J. Doe";
	if (position < noPassengers)
		cout << " is seated in row " << reservation[position][0]
		<< " seat " << reservation[position][1];
	else
		cout << " is not found ";
	cout << endl;
	cout << "#1 Reserve for Superman in unoccupied seat (4, 1) : \n";
	if (reserveSeat(name, reservation, noPassengers))
		cout << "reservation made ";
	else
		cout << "reservation not made ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);

	cout << "#1 Reserve for Batman in Superman's seat (4, 1): \n";
	if (reserveSeat(name, reservation, noPassengers))
		cout << "reservation made ";
	else
		cout << "reservation not made ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);

	cout << "#1 Reserve for Batman again in unoccupied seat (4, 2):\n";
	if (reserveSeat(name, reservation, noPassengers))
		cout << "reservation made ";
	else
		cout << "reservation not made ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);

	cout << "#1 Reserve for Cat woman in unoccupied seat (4, 3)\n";
	if (reserveSeat(name, reservation, noPassengers))
		cout << "reservation made ";
	else
		cout << "reservation not made ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);
	cout << "program ended successfully" << endl;
	cout << "\nDump of Reservations.dat file\n";
	system("type reservations.dat");
	cout << "\nPrintout of Reservations Report\n";
	system("type reservations.rpt");
	system("pause");
}


//function to load arrays
int loadArrays(ifstream & inFile, string names[], int rowSeat[][2])
{
	int noPassengers;

	for (noPassengers = 0; noPassengers < SIZE; noPassengers++)
	{
		getline(inFile, names[noPassengers]);
		if (inFile.eof())
			break;
		if (isFull(noPassengers))
			break;
		for (int col = 0; col < 2; col++)
		{
			inFile >> rowSeat[noPassengers][col];
		}
		inFile.ignore(80, '\n');
	}
	return noPassengers;
}

//function to print to output file
void printReport(ofstream & outFile, const string names[], const int rowSeat[][2], int noPassengers)
{

	outFile << left << setw(20) << "Passenger"
		<< right << setw(8) << "row"
		<< setw(8) << "seat" << endl << endl;

	for (int index = 0; index < noPassengers; index++)
	{
		outFile << left << setw(20) << names[index] << right;
		for (int col = 0; col < 2; col++)
		{
			outFile << setw(8) << rowSeat[index][col];
		}
		outFile << endl;
	}
	outFile << endl << "Number of passengers = " << noPassengers << endl;
}

//function to check if array full
bool isFull(int noPassengers)
{
	return(noPassengers == SIZE);
}

//function to reserve a seat for a new passenger
bool reserveSeat(string names[], int rowSeat[][2], int & length)
{
	bool seatReserved = false;
	if (isFull(length))
		cout << "Plane is fully booked" << endl;
	else
	{
		string name;
		int row, seat, rowCtr;
		cout << "Enter passenger name ";
		getline(cin, name);
		cout << "Enter row number ";
		cin >> row;
		validateSeat(row, 10);
		cout << "Enter seat number ";
		cin >> seat;
		validateSeat(seat, 3);
		for (rowCtr = 0; rowCtr < length; rowCtr++)
		{
			if (rowSeat[rowCtr][0] == row)
				if (rowSeat[rowCtr][1] == seat)
				{
					cout << "Row " << row << " Seat " << seat
						<< " is already booked" << endl;
					break;
				}
		}
		if (rowCtr == length)
		{
			names[length] = name;
			seatReserved = true;
			rowSeat[length][0] = row;
			rowSeat[length][1] = seat;
			length++;
		}
	}
	return seatReserved;
}

//function to validate seat or row
void validateSeat(int & rowSeat, int maxValue)
{
	while (cin.fail() || rowSeat > maxValue || rowSeat < 1)
	{
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Number must be between 1 and " << maxValue
			<< " Re-enter " << endl;
		cin >> rowSeat;
	}
	cin.ignore(80, '\n');
}

//function to find a passenger
void findPassenger(string name, const string names[], int & position, int & noPassengers)
{
	position = 0;
	for (; position < noPassengers; position++)
	{
		if (names[position] == name)
			break;
	}
}

/******I/O dialog****************************
Search for non passenger
Passenger: Superman is not found
Load arrays
Search for existing passenger
Passenger: J. Doe is seated in row 1 seat 2
#1 Reserve for Superman in unoccupied seat (4, 1) :
Enter passenger name Superman
Enter row number 44
Number must be between 1 and 10 Re-enter
0
Number must be between 1 and 10 Re-enter
4
Enter seat number 0
Number must be between 1 and 3 Re-enter
33
Number must be between 1 and 3 Re-enter
1
reservation made
#1 Reserve for Batman in Superman's seat (4, 1):
Enter passenger name Batman
Enter row number 4
Enter seat number 1
Row 4 Seat 1 is already booked
reservation not made
#1 Reserve for Batman again in unoccupied seat (4, 2):
Enter passenger name Batman
Enter row number 4
Enter seat number 2
reservation made
#1 Reserve for Cat woman in unoccupied seat (4, 3)
Enter passenger name Cat woman
Enter row number 4
Enter seat number 3
reservation made
program ended successfully

Dump of Reservations.dat file
J. Doe
1       2
P.  Smith
5       3
T. Jones
3       1
K. Rees
7       1
J. Milton
6       2
G. Watson
6       1

Printout of Reservations Report
Passenger                row    seat


Number of passengers = 0
Passenger                row    seat

J. Doe                     1       2
P.  Smith                  5       3
T. Jones                   3       1
K. Rees                    7       1
J. Milton                  6       2
G. Watson                  6       1

Number of passengers = 6
Passenger                row    seat

J. Doe                     1       2
P.  Smith                  5       3
T. Jones                   3       1
K. Rees                    7       1
J. Milton                  6       2
G. Watson                  6       1
Superman                   4       1

Number of passengers = 7
Passenger                row    seat

J. Doe                     1       2
P.  Smith                  5       3
T. Jones                   3       1
K. Rees                    7       1
J. Milton                  6       2
G. Watson                  6       1
Superman                   4       1

Number of passengers = 7
Passenger                row    seat

J. Doe                     1       2
P.  Smith                  5       3
T. Jones                   3       1
K. Rees                    7       1
J. Milton                  6       2
G. Watson                  6       1
Superman                   4       1
Batman                     4       2

Number of passengers = 8
Passenger                row    seat

J. Doe                     1       2
P.  Smith                  5       3
T. Jones                   3       1
K. Rees                    7       1
J. Milton                  6       2
G. Watson                  6       1
Superman                   4       1
Batman                     4       2
Cat woman                  4       3

Number of passengers = 9
Press any key to continue . . .
************************************/




