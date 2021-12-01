#pragma once
#include <iostream>
#include <stdlib.h>
/*/class GUIManager
{
public:
	GUIManager();
	void CreateGUI();
	void DisplayData();
	void DisplayLogin();
	void SendCommand();

};
// Hi Jon
// Hello :)
GUIManager::GUIManager()
{

}

void GUIManager::CreateGUI()
{

}

void GUIManager::DisplayData()
{

}

void GUIManager::DisplayLogin()
{

}

void GUIManager::SendCommand()
{

}
*/

class GUIManager
{
public:
	std::string DisplayLoginScreen();
	char DisplayCommandScreen();
	/*void GetData();
	void DisplayData();
	*/
	std::string AddMachine();
	std::string DeleteMachine();
	std::string EditMachine();
	std::string SearchMachine();
};

/*
void GUIManager::ToSource() //THIS WILL OBVIOUSLY NOT GO HERE LATER, WILL BE IN SOURCE
{
	std::string loginCommand = DisplayLoginScreen();
	
	std::string serverReturn = ""; //source sends data to server, server returns some sort of string, this string stores it for processing? 
	/*need to pass username, password, and login command to server.
	* if server returns "Login Accepted!" display main menu
	* f server returns "Login Denied!" display login screen again
	* if server returns "Login Maximum Reached!" display message and terminate program


	char userCommand = DisplayCommandScreen(); //gets command from user (A, D, etc or E to exit)

	while (userCommand != 'E') //will keep processing commands until user uses exit command "E"
	{
		switch (userCommand)
		{
		case 'C':
			userCommand = DisplayCommandScreen();
		case 'S':
			SearchMachine();
			userCommand = DisplayCommandScreen();
		case 'E': 
			EditMachine();
			userCommand = DisplayCommandScreen();
		case 'A':
			AddMachine();
			userCommand = DisplayCommandScreen();
		case 'D':
			DeleteMachine();
			userCommand = DisplayCommandScreen();
		case 'U':
			EditLogin();
			userCommand = DisplayCommandScreen();
		default:
			std::cout << "Invalid Command. Please Try Again."; //reloop
			userCommand = DisplayCommandScreen();
		}
	}

	//exits while loop when user enters 'E'
	
	//clear screen
	std::cout << "Exiting... "; 

	return; //exits program
}
*/

std::string GUIManager::DisplayLoginScreen()
{	
	system("CLS"); //clear screen

	std::string user = "";
	std::string pass = "";

	std::cout << "IT Department Machine Registry System v.1.0";
	std::cout << "\n\n\t\tPlease Sign In:";
	std::cout << "\nEnter Username: ";
	std::cin >> user;
	std::cout << "\nEnter Password: ";
	std::cin >> pass;

	return ("L;"+ user + "," + pass);
	
	/*need to pass username, password, and login command to server.
	* if server returns successful login, display main menu
	* if server returns unsuccessful login, display try again and reattempt login */
}

char GUIManager::DisplayCommandScreen() //asks for command from user, returns command string
{	
	system("CLS");	//clear screen
	char userCommand; //stores user command character
	
	std::cout << "*************Command Menu****************"; 
	
	std::cout << "\n\n\t\tCommand List:";	
	std::cout << "[C] View All Machines"
		<< "\n[S] Search for Machine"
		<< "\n[E] Edit a Machine"
		<< "\n[A] Add a Machine"
		<< "\n[D] Delete a Machine"
		<< "\n[Q] Quit\n";

	std::cout << "Enter a Command Character: ";
	std::cin >> userCommand;

	return userCommand; //returns control back to source, source will then use switch statement
}


/*
void GUIManager::GetData() //retrieves csv file from server
{

}
void GUIManager::DisplayData() //displays data to console
{

}
*/

std::string GUIManager::SearchMachine() //prompts user for assetTag, returns S;input
{
	system("CLS"); //clear screen

	std::string input;

	std::cout << "Enter AssetTag of Machine: ";

	std::cin >> input;

	return("S;" + input);
}

std::string GUIManager::EditMachine()
{
	system("CLS"); //clear screen

	std::string searchTag; //assetTag of machine to edit
	std::string input;	//input 
	std::string mEdited; //edited string to return

	std::cout << "Enter Asset Tag of Machine to Edit";
	{
		
	}
	return("E;" + mEdited);
}
std::string GUIManager::AddMachine() //prompts user to enter machine information
{
	system("CLS"); //clear screen

	std::string mData; //stores machine information to be returned
	std::string input; //stores current user input
	char useStatus; //used to decide which sections to fill
	
	//"AssetTag,ServiceTagNum,MakeAndModel,SerialNumber,IsMac, I:((BuildingName,RoomNumber,
	//PublicOrPrivate,DepartmentInfo,OwnerInfo,)) O: ((SurplusStatus,ReimageStatus,WorkingStatus,ITLocation)) ,IUorOU"
	
	std::cout << "Enter AssetTag: ";
	std::cin >> input;
	mData = input;

	std::cout << "Enter Service Tag Number: ";
	std::cin >> input;
	mData = mData + "," + input;

	std::cout << "Enter Name of Model: ";
	std::cin >> input;
	mData = mData + "," + input;

	std::cout << "Enter Serial Number: ";
	std::cin >> input;
	mData = mData + "," + input;

	std::cout << "T or F: Machine is a Mac? ";
	std::cin >> input;
	mData = mData + "," + input;
	
	std::cout << "Is New Machine In Use or Out Of Use?"
		<< "\n[I] In Use"
		<< "\n[O] Out Of Use"
		<< "\n\n Enter I or O:";

	std::cin >> useStatus;
	while (useStatus != 'I' && useStatus != 'i' && useStatus != 'O' && useStatus != 'o') //input validation
	{
		std::cout << "Invalid Entry. Please Type I or O: ";
		std::cin >> useStatus;
	}
	if (useStatus == 'I') //in use Machine
	{
		std::cout << "Enter Name of Building: ";
		std::cin >> input;
		mData = mData + "," + input;

		std::cout << "Enter Room Number: ";
		std::cin >> input;
		mData = mData + "," + input;

		std::cout << "Is Machine Public or Private?: ";
		std::cin >> input;
		mData = mData + "," + input;

		std::cout << "Enter Name of Department: ";
		std::cin >> input;
		mData = mData + "," + input;

		std::cout << "Enter Name of Owner: ";
		std::cin >> input;
		mData = mData + "," + input;

		mData += ",,,,,IU"; //completes IU string
	}
	else //out of use Machine
	{
		mData += ",,,,,";

		std::cout << "Enter Surplus Status: ";
		std::cin >> input;
		mData = mData + "," + input;

		std::cout << "Enter Reimage Status: ";
		std::cin >> input;
		mData = mData + "," + input;

		std::cout << "Enter Working Status: ";
		std::cin >> input;
		mData = mData + "," + input;

		std::cout << "Enter IT Location: ";
		std::cin >> input;
		mData = mData + "," + input;

		mData += ",OU"; //completes OU string
	}
	return ("A;" + mData);
}

std::string GUIManager::DeleteMachine()
{
	system("CLS"); //clear screen

	std::string input; //stores assetTag of machine to delete
	char validate;	//stores y or n

	std::cout << "Enter Asset Tag of Machine to Delete: "; //prompt user for assetTag
	std::cin >> input;

	std::cout << "Are you sure you want to delete machine with assetTag " << input << " ? (Y or N): "; //confirms deletion
	std::cin >> validate;

	while (validate != 'y' && validate != 'Y' && validate != 'n' && validate != 'N') //input validation
	{
		std::cout << "Invalid Entry. Please Enter Y or N: ";
		std::cin >> validate;
	}

	if (validate == 'Y' || validate == 'y') //if user confirms deletion
	{
		return ("D;" + input);
	}
	else
		return '\0'; //returns NULL string, source will not send anything to server and will reload main menu
}


