/****************************************************************/
/* PROGRAM: Slot Machine 																				*/
/* 																															*/
/* AUTHOR: William Evermann																			*/
/* 																															*/
/* DATE: February 9th, 2015																			*/
/* 																															*/
/* REVISIONS: 0.3																								*/
/* 																															*/
/* PURPOSE: Design A Slot Machine Style Program That Works Like	*/
/* A Real Slot Machine, Where The User Can Print Or Save the		*/
/* machine config, Print a certain Spot, Or Play Simulated Slots*/
/****************************************************************/

//header files
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
using namespace std;

	//	Slot Struct
struct slot{
	char symbol[10];
	int bonus;
	bool hasBonus;
};

	//	Function Prototypes
void readIn(char symbolArr[6][10], int bonusArr[6]);

int symbolBonus(slot machine[10][3], int r1, int r2, int r3);

void printReels(slot machine[10][3]);

void saveReels(slot machine[10][3]);

void stringCopy(char str1[10], char str2[10]);

bool stringCompare(char str1[10], char str2[10]);

	//	Main Function
int main()
{
	srand (time(NULL));
	//	Declare Slot Information
	slot machine[10][3];
	//	Declare Variables
	ifstream fin;
	ofstream fout;
	int selection, reelSelection;
	int r, r1, r2, r3;
	int rowNum, colNum;
	int payOut;

	//	Declare Array
	char symbolArr[6][10];
	int bonusArr[6];
	char configName[20];
	char fileNameArr[20];

	//	Reads in the File to Arrays for processing
	readIn(symbolArr, bonusArr);

	//	Menu System
	do{
		cout << endl;
		cout << "CS202 Casino Slots" << endl;
		cout <<	" -------------------"	<< endl;
		cout <<	" 1. Populate Slot Reels With A NEW Machine Config"	<< endl;
		cout <<	" 2. Populate Slot Reels with EXISTING Machine Config"	<< endl;
		cout <<	" 3. Print Machie Config On Screen"	<< endl;
		cout <<	" 4. Save Machine Config To A File" << endl;
		cout <<	" 5. Select a Specific Location"	<< endl;
		cout << " 6. Play Simulated Slots" << endl;
		cout << " 0. Quit CS202 Casino Slots" << endl;
		cout << endl;
		cout <<	" Please enter your selection: ";
		cin>> selection;

    switch (selection)
  	  {

	//	Populates With New Machine Config
  	    case 1:
  	      cout << "Populating" << endl;
					for(int row = 0; row < 10; row++){
						for(int col = 0; col < 3; col++){ 
							r = rand() %6;
							stringCopy(machine[row][col].symbol, symbolArr[r]);
							machine[row][col].bonus = bonusArr[r];
							//cout << bonusArr[r] << endl;
							}
					}
  	      break;

	//	Populates With Exitsing Machine Config
  	    case 2:
  	      cout << "File Name: " << endl;
  	      cin >> configName;
					cout << endl;
					fin.open (configName);
					for(int row = 0; row < 10; row++){
						for(int col = 0; col < 3; col++){ 
							fin >> machine[row][col].symbol;
							fin >> machine[row][col].bonus;
							//cout << bonusArr[r] << endl;
							}
					}
  	      break;

	//	Print Machine Config To Screen
  	   case 3:
  	      cout << "Print Screen" << endl;
  	      cout << endl;
					printReels(machine);
  	      break;

	//	Save Machine Config To File
  	    case 4:
  	      cout << "Save File" << endl;
  	      cout << endl;
					saveReels(machine);
  	      break;

	//	Print a Specific Location 
  	    case 5:
  	      cout << "Row Selection" << endl;
  	      cin >> rowNum;
					cout << "Collumn Selection" << endl;
					cin >> colNum;
					cout << machine[rowNum][colNum].symbol << ' '
							 << machine[rowNum][colNum].bonus << endl;
  	      break;

	//	Simulates the Slot Machine with completely random Symbols each time
				case 6:
						r1 = rand() %10;
						r2 = rand() %10;
						r3 = rand() %10;
						payOut = symbolBonus(machine, r1, r2, r3);
						cout << machine[r1][0].symbol << '\t' << machine[r2][1].symbol 
								 << '\t' << machine[r3][2].symbol << '\t' << payOut << endl;
						cout << endl;

					break;

  	    default://User assistance if Selection above 6
  	      cout << "Please Make A Selection Between 1 and 6." << endl;
  	      cout << endl;
  	  } 
  	}while (selection != 0);

	return 0;
}

/**********************************************************************/
/* FUNCTION: readIn																										*/
/* 																																		*/
/* PURPOSE: Read in the symbols files																	*/
/* 																																		*/
/**********************************************************************/
void readIn(char symbolArr[6][10], int bonusArr[6]){

	//open file symbols	
	ifstream fin;
	ofstream fout;

	fin.open ("symbols");
	//cout<< "File read in"<<endl;

	int i;
	int j;
 
	//For loop to save the file to an array
	for(i = 0; i < 6; i++)
		{
			fin >> symbolArr[i] >> bonusArr[i];
	//cout << symbolArr[i] << bonusArr[i] << endl;
		}
	fin.close();

	//cout << "File Read In" << endl;
	return;
}

/**********************************************************************/
/* FUNCTION: symbolBonus																							*/
/* 																																		*/
/* PURPOSE: Returns the symbol bonus values to show how much the user	*/
/* won.																																*/
/**********************************************************************/
int symbolBonus(slot machine[10][3], int r1, int r2, int r3){
	int payOut = machine[r1][0].bonus + machine[r2][1].bonus + machine[r3][2].bonus;
	return payOut;
}


/**********************************************************************/
/* FUNCTION: printReels																								*/
/* 																																		*/
/* PURPOSE: print reels to the terminal.															*/
/* 																																		*/
/**********************************************************************/
void printReels(slot machine[10][3]){
	for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 3; j++)
				{
					cout<< machine[i][j].symbol << "\t";
				}
			cout<< endl;
		}
}

/**********************************************************************/
/* FUNCTION: saveReels																								*/
/* 																																		*/
/* PURPOSE: Saves the reels to a file																	*/
/* 																																		*/
/**********************************************************************/
void saveReels(slot machine[10][3]){
	char arrFileOut[20];

	cout<< "What would you like to name the output file? " << endl;
	cin>> arrFileOut;

	ofstream fileout(arrFileOut);

	for(int i = 0; i < 10; i++)
		{
			for(int j = 0; j < 3; j++)
				{
					fileout<< machine[i][j].symbol << '\t';
					fileout<< machine[i][j].bonus << '\t';
				}
			fileout<< endl;
		}
}

/**********************************************************************/
/* FUNCTION: stringCopy																								*/
/* 																																		*/
/* PURPOSE: Copy the values from one array to another									*/
/* 																																		*/
/**********************************************************************/
void stringCopy(char str1[10], char str2[10]){
	int i = 0;
	//cout << str1 << str2<< endl;
	while( str2[i] != '\0'){
		str1[i] = str2[i];
		//cout << str1[i] << endl;
		i++;
	}
	str1[i] = '\0';
}

/**********************************************************************/
/* FUNCTION: stringCompare																						*/
/* 																																		*/
/* PURPOSE: Compares the contents of two strings and returns true if	*/
/* the Two strings are the same length and contain the same chars.		*/
/**********************************************************************/
bool stringCompare(char str1[10], char str2[10]){
	int i;
	while( str1[i] != '\0' && str2[i] != '\0'){
		if(str1[i] != str2[i]){
			return false;
			}
	}
	if(str1[i] == '\0' && str2[i] == '\0'){
		return true;
	}
	else
	{
		return false;
	}
}
