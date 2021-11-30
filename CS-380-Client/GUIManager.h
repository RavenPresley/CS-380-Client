#pragma once
#include <iostream>
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
	void ShowLoginMenu();
	void ShowMainMenu();
	void SendCommand(std:: string commandAndData);
	void DisplayData();
	void AddMachine();
	void NewIOMachine();
	void NewOUMachine();
	void DeleteMachine();
	void EditMachine();
	void SearchMachine();
	void EditLogins();
};

void GUIManager::ShowLoginMenu()
{	
	std::string user = "";
	std::string pass = "";

	std::cout << "IT Department Machine Registry System v.1.0";
	std::cout << "\n\n\t\tSign In:";
	std::cout << "\nEnter Username: ";
	std::cin >> user;
	std::cout << "\nEnter Password:";
	std::cin >> pass;


	SendCommand("L;" + user + "," + pass);
	/*need to pass username, password, and login command to server.
	* if server returns successful login, display main menu
	* if server returns unsuccessful login, display try again and reattempt login */
}

void GUIManager::ShowMainMenu()
{	
	char userCommand;
	std::cout << "*************Welcome****************"; //some sort of welcome message
	
	std::cout << "\n\n\t\tCommand List:";	//may be better to put this in its own ShowCommandList function
	std::cout << "[C] View All Machines"
		<< "\n[S] Search for Machine"
		<< "\n[E] Edit a Machine"
		<< "\n[A] Add a Machine"
		<< "\n[D] Delete a Machine"
		<< "\n[U] Edit User Logins";

	
	std::cout << "Enter a Command Character: ";
	std::cin >> userCommand;

	//switch statement to decide what command to execute
	switch (userCommand)
	{
	case 'C':
		DisplayData();
		break;
	case 'S':
		SearchMachine();
		break;
	case 'E':
		EditMachine();
		break;
	case 'A':
		AddMachine();
		break;
	case 'D':
		DeleteMachine();
		break;
	case 'U':
		EditLogins();
		break;
	default:
		std::cout << "Invalid Command. Please Try Again.";
	}
}

void GUIManager::DisplayData() //retrieves csv file from server, displays data to console
{

}

void GUIManager::SearchMachine() //prompts user for assetTag, searches csv file, more of a search and display
{
	std::string input;

	std::cout << "Enter AssetTag: ";

	std::cin >> input;
	SendCommand("S;" + input);//sends concatenated string of command and assetTag

	//get machine info back from server
	if (true) //if machine found??
	{
		//display machine string
	}
	else //if server returns NULL??
		std::cout<<"AssetTag Not Found." //prompt user for to enter another or return to menu
}

void GUIManager::EditMachine()
{
	//user enters assettag of machine to be edited
	//proper string format of machine displayed so user can copy it
	//prompts user to enter proper string format of edited machine
	//sends edited machine data to server to be updated
	std::string searchTag;
	std::string input;

	//search for machine to edit
	//display machine to be edited
	//send edited machine to server
	SendCommand("E;" + input);
}
void GUIManager::AddMachine() //prompts user to enter machine information in csv string format, sends to server
{
	std::string m;
	char useStatus;

	std::cout << "Is New Machine In Use or Out Of Use?"
		<< "\n[I] In Use"
		<< "\n[O] Out Of Use"
		<< "\n\n Enter I or O:";

	std::cin >> useStatus;

	switch(useStatus)
	{
	case 'I':
		NewIOMachine();
	case 'O':
		NewOUMachine();
	default:
		"Invalid Command. Please Try Again." //reloop
	}
}

void GUIManager::NewIOMachine()
{

}

void GUIManager::NewOUMachine()
{

}

void GUIManager::DeleteMachine()
{
	//promts user to enter assetTag of machine to be deleted
	//machine string displayed
	//ask user if this is the correct machine to be deleted (y or n)
	//ask user "are you sure you want to delete this machine? this cannot be undone. (y or no)
	//send command to server to delete machine
}

void GUIManager::EditLogins() 
{
	
	//prompts user for change in username and password
	//passes these to the server to be updated
}

void GUIManager::SendCommand(std::string comData)
{
	//send command to server somehow
}