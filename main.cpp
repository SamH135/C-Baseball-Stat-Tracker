// Sam Heidler - srh220000 - Project 0 in C++

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cmath>
using namespace std;

// function prototypes
int getFileData(fstream &); 
void processData(int);
void findLeader(int);

// global constant to set maximum array size 
const int MAX_PLAYERS = 30;

// global arrays for all functions to access
// to make lists of player stats
string nameArr[MAX_PLAYERS];  
string batStats[MAX_PLAYERS];


string BALeader[MAX_PLAYERS];
string onBasePercentLeader[MAX_PLAYERS];

string hitLeader[MAX_PLAYERS];

int hit[MAX_PLAYERS];
int out[MAX_PLAYERS];
int strikeout[MAX_PLAYERS];
int walk[MAX_PLAYERS];
int hitBy[MAX_PLAYERS];
int sacrifice[MAX_PLAYERS];
int atBat[MAX_PLAYERS];
int onBaseNum[MAX_PLAYERS];
int plateAppear[MAX_PLAYERS];
double battingAverage[MAX_PLAYERS];
double onBasePercent[MAX_PLAYERS];



int main()
{
	int numberPlayers;
	// create file objects
	fstream inFile;
	
	// initialize local variables and arrays
	
	string fileName; 
	string nameArr[MAX_PLAYERS];  
	string batStats[MAX_PLAYERS];
	
	// get file name from user and store it in fileName
   	cout << "Enter the file name to be opened (be sure to include file type ex: '.txt'): " << endl;
   	cin >> fileName;
	
	// Open the specified file - "project0Stats.txt" on my laptop
	inFile.open(fileName.c_str());
	//inFile.open("project0Stats.txt");        // use for testing
	
	// notify user if a bad file name was entered
	if (inFile.fail())
    {
       cout << "The file could not be found, check to make sure it exists in memory." << endl;
       return 1;
    }
    
    // function calls   
	numberPlayers = getFileData(inFile); // this function parses data and return number of players
	processData(numberPlayers);          // this function performs logic on arrays
	findLeader(numberPlayers);           // this function performs a simple search and prints output
	
	
	// close input file   
	inFile.close();
	return 0;
}

/*******************************************************
 *                    getFileData                      *
 * This function loops to get input for the user file  *
 * and parses names/batting stats to arrays            *
 *******************************************************/
int getFileData(fstream &inFile) 
{
	string name, battingRecord; // holds player name and batting stats as a string
	int num_players = 0; // count number of players
	char ch1, ch2;
	
	// initialize counter variables for each stat
	int hitCount = 0;
	int outCount = 0;
	int strikeoutCount = 0;
	int walkCount = 0;
	int hitByCount = 0;
	int sacrificeCount = 0;
	
	for (int x=0; x < MAX_PLAYERS; x++)
	{
		getline(inFile, name, ' '); // gets name from first input file line 
		nameArr[x] = (name); // + "\n"); // stops at the first space encountered
		
		num_players += 1; // increments number of players
		
		getline(inFile, battingRecord, '\n'); // gets batting stats that come after each name
		batStats[x] = (battingRecord + "\n"); // stops at the newline char
		
		string str = batStats[x];
		
		
		int arrLength = str.length();
		char* charStatArr = new char[arrLength];

		
		strcpy(charStatArr, str.c_str());
		for (int i=0; i < arrLength; i++)
		{
			ch2 = charStatArr[i];
			switch (ch2)
			{
				case 'H': hitCount += 1;
					break;
				case 'O': outCount += 1;
					break;
				case 'K': strikeoutCount += 1;
					break;
				case 'W': walkCount += 1;
					break;
				case 'P': hitByCount += 1;
					break;
				case 'S': sacrificeCount += 1;
					break;
				default:
					break;
			}
			
			// this group of statements assigns the stat values to
			// their appropriate arrays for each player 
			hit[x] = hitCount;
			out[x] = outCount;
			strikeout[x] = strikeoutCount;
			walk[x] = walkCount;
			hitBy[x] = hitByCount;
			sacrifice[x] = sacrificeCount;
			
			atBat[x] = (hit[x] + out[x] + strikeout[x]);
			onBaseNum[x] = (hit[x] + walk[x] + hitBy[x]);
			plateAppear[x] = (hit[x] + out[x] + strikeout[x] + walk[x] + hitBy[x] + sacrifice[x]);
			
			
			
			
			
		}
		
		// this group of statements resets the counter 
		// variables to 0 in order to process the next 
		// player's stats
		hitCount = 0;
		outCount = 0;
		strikeoutCount = 0;
		walkCount = 0;
		hitByCount = 0;
		sacrificeCount = 0;
		
		
		
			 
		// look at next character in file without changing the read position 	 
		ch1 = inFile.peek();
		
		// if next character is EOF, end loop
		if (ch1 == EOF)
		{
			break;
		}
   	}
	
	return num_players;	   
}


/*******************************************************
 *                    processData                      *
 * This function loops to process data for each player *
 *******************************************************/
void processData(int numberPlayers)
{
	for(int i = 0; i < numberPlayers; i++)   // x = round(1000 * x) / 1000
	{
		if (atBat[i] == 0.0)
		{
			battingAverage[i] = 0.0;
		}
		else
		{
			battingAverage[i] = (static_cast<float>(hit[i]) / static_cast<float>(atBat[i]));
		}
		if(plateAppear[i] == 0.0)
		{
			onBasePercent[i] = 0.0;
		}
		else
		{
			onBasePercent[i] = (static_cast<float>(onBaseNum[i]) / static_cast<float>(plateAppear[i]));
		}
		
		
	}
	
	
}

/*******************************************************
 *                    findLeader                       *
 * This function loops to process data for each player *
 *               and displays output                   *     
 *******************************************************/
 void findLeader(int numberPlayers)
 {
 	// output to console
 	for (int x=0; x < numberPlayers; x++)
	{
		cout << nameArr[x] << endl
			 << "BA: " << fixed << setprecision(3) << (round(1000.0 * battingAverage[x]) / 1000.0) << endl
			 << "OB%: " << fixed << setprecision(3) << (round(1000.0 * onBasePercent[x]) / 1000.0) << endl
			 << "H: " << hit[x] << endl
			 << "BB: " << walk[x] << endl
			 << "K: " << strikeout[x] << endl
			 << "HBP: " << hitBy[x] << endl
			 << "\n";
	}
	
	// this group of statements finds BA leader(s) and displays them
	cout << "LEAGUE LEADERS" << endl;
	cout << "BA: ";
	
 	double BaMax = battingAverage[0];  
 	for(int x=0; x < numberPlayers; x++)
	{
		if(battingAverage[x] > BaMax)   // this successfully finds max value in each array
		{
			BaMax = battingAverage[x];
		}
	}
	
	int BaLeaderCount = 0;
	for(int x=0; x < numberPlayers; x++) // count number of leaders
	{
		if(battingAverage[x] == BaMax)
		{
			BaLeaderCount += 1; // increments number of batting leaders 
		}
	}
	
	for(int x=0; x < numberPlayers; x++)
	{
		if(battingAverage[x] == BaMax)
		{
			cout << nameArr[x];
			if(BaLeaderCount > 1)
			{
				cout << ", ";
				BaLeaderCount -= 1; // decrements number of batting leaders
			}
		}
	}
	
	cout << " " << BaMax << endl;
	
	// this group of statements finds on-base % leader(s) and displays them
	cout << "OB%: ";
	
 	double ObMax = onBasePercent[0];  
 	for(int x=0; x < numberPlayers; x++)
	{
		if(onBasePercent[x] > ObMax)   // this successfully finds max value in each array
		{
			ObMax = onBasePercent[x];
		}
	}
	
	int ObLeaderCount = 0;
	for(int x=0; x < numberPlayers; x++) // count number of leaders
	{
		if(onBasePercent[x] == ObMax)
		{
			ObLeaderCount += 1; // increments number of leaders 
		}
	}
	
	for(int x=0; x < numberPlayers; x++)
	{
		if(onBasePercent[x] == ObMax)
		{
			cout << nameArr[x];
			if(ObLeaderCount > 1)
			{
				cout << ", ";
				ObLeaderCount -= 1; // decrements number of leaders
			}
		}
	}
	
	cout << " " << ObMax << endl;
	
	// this group of statements finds hit leader(s) and displays them
	cout << "H: ";
	
 	int hMax = hit[0];  
 	for(int x=0; x < numberPlayers; x++)
	{
		if(hit[x] > hMax)   // this successfully finds max value in each array
		{
			hMax = hit[x];
		}
	}
	
	int hLeaderCount = 0;
	for(int x=0; x < numberPlayers; x++) // count number of leaders
	{
		if(hit[x] == hMax)
		{
			hLeaderCount += 1; // increments number of leaders 
		}
	}
	
	for(int x=0; x < numberPlayers; x++)
	{
		if(hit[x] == hMax)
		{
			cout << nameArr[x];
			if(hLeaderCount > 1)
			{
				cout << ", ";
				hLeaderCount -= 1; // decrements number of leaders
			}
		}
	}
	
	cout << " " << hMax << endl;
	
	// this group of statements finds walk leader(s) and displays them
	cout << "BB: ";
	
 	int bMax = walk[0];  
 	for(int x=0; x < numberPlayers; x++)
	{
		if(walk[x] > bMax)   // this successfully finds max value in each array
		{
			bMax = walk[x];
		}
	}
	
	int bLeaderCount = 0;
	for(int x=0; x < numberPlayers; x++) // count number of leaders
	{
		if(walk[x] == bMax)
		{
			bLeaderCount += 1; // increments number of leaders 
		}
	}
	
	for(int x=0; x < numberPlayers; x++)
	{
		if(walk[x] == bMax)
		{
			cout << nameArr[x];
			if(bLeaderCount > 1)
			{
				cout << ", ";
				bLeaderCount -= 1; // decrements number of leaders
			}
		}
	}
	
	cout << " " << bMax << endl;
	
	// this group of statements finds strikeout (lowest amount) leader(s) and displays them
	cout << "K: ";
	
 	int kMin = strikeout[0];  
 	for(int x=0; x < numberPlayers; x++)
	{
		if(strikeout[x] < kMin)   // this successfully finds max value in each array
		{
			kMin = strikeout[x];
		}
	}
	
	int kLeaderCount = 0;
	for(int x=0; x < numberPlayers; x++) // count number of leaders
	{
		if(strikeout[x] == kMin)
		{
			kLeaderCount += 1; // increments number of leaders 
		}
	}
	
	for(int x=0; x < numberPlayers; x++)
	{
		if(strikeout[x] == kMin)
		{
			cout << nameArr[x];
			if(kLeaderCount > 1)
			{
				cout << ", ";
				kLeaderCount -= 1; // decrements number of leaders
			}
		}
	}
	
	cout << " " << kMin << endl;
	
	// this group of statements finds hit-by-pitch leader(s) and displays them
	cout << "HBP: ";
	
 	int hbMax = hitBy[0];  
 	for(int x=0; x < numberPlayers; x++)
	{
		if(hitBy[x] > hbMax)   // this successfully finds max value in each array
		{
			hbMax = hitBy[x];
		}
	}
	
	int hbLeaderCount = 0;
	for(int x=0; x < numberPlayers; x++) // count number of leaders
	{
		if(hitBy[x] == hbMax)
		{
			hbLeaderCount += 1; // increments number of leaders 
		}
	}
	
	for(int x=0; x < numberPlayers; x++)
	{
		if(hitBy[x] == hbMax)
		{
			cout << nameArr[x];
			if(hbLeaderCount > 1)
			{
				cout << ", ";
				hbLeaderCount -= 1; // decrements number of leaders
			}
		}
	}
	
	cout << " " << hbMax << endl;
		
}

