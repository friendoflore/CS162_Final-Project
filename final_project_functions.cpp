/******************************************************************************
 ** Filename: final_project.cpp
 ** Author: Tim Robinson
 ** Date: 3/16/2015
 ** Last modification date: 3/16/2015 11:14 AM PST
 *****************************************************************************/

#include <iostream>
#include <string>
#include <vector>

#include "final_project.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

/******************************************************************************
 ** Function: printRoomLinks
 ** Description: This function prints the name of the room located in each
 **	direction of the room passed into it.
 ** Parameters: A Body_Part object pointer.
 ** Preconditions: The body part's name and linked body parts must be
 **	appropriately initialized in order for this funcion to work as expected.
 ** Postconditions: This function finishes with the name of the linked rooms
 **	printed to the screen. If the link is a null pointer, the user is
 **	notified.
 *****************************************************************************/

void printRoomLinks(Body_Part* room) {
	if(room->getNorth() == NULL) {
		cout << "Nowhere to the North" << endl;
	} else {
		cout << "N:\t" << room->getNorth()->getName() << endl;
	}
	if(room->getEast() == NULL) {
		cout << "Nowhere to the East" << endl;
	} else {
		cout << "E:\t" << room->getEast()->getName() << endl;
	}
	if(room->getSouth() == NULL) {
		cout << "Nowhere to the South" << endl;	
	} else {
		cout << "S:\t" << room->getSouth()->getName() << endl;
	}
	if(room->getWest() == NULL) {
		cout << "Nowhere to the West" << endl;
	} else {
		cout << "W:\t" << room->getWest()->getName() << endl;
	}
	cout << endl;	
}

/******************************************************************************
 ** Function: traverseRooms
 ** Description: This function allows a user to travel from one body part to
 **	another in the game. If the direction passed in is a null pointer, the
 **	user is notified. If the body part is locked and is not "Blood", the user
 **	must pay a token in order to unlock the body part. If it is locked and it
 **	is "Blood", then the user must collect the remaining symptoms in order
 **	to unlock it.
 ** Parameters: A Player object pointer, Body_Part object pointer, and a 
 **	character representing the user's desired direction of travel.
 ** Preconditions: The body part's name and linked body parts and the
 **	player's member vector of symptoms must be appropriately initialized
 **	in order for this funcion to work as expected. The direction character
 **	must be 'N', 'E', 'S', or 'W'.
 ** Postconditions: This function finishes with returning the new body part
 **	if the user can change rooms validly or with returning the current
 **	body part (the body part passed in) if the user is not allowed to change
 **	body parts.
 *****************************************************************************/

Body_Part* traverseRooms(Player* player, Body_Part* room, char direction) {
	string inputString;

	if(direction == 'N') {
		if(room->getNorth() == NULL) {
			cout << "There is nowhere to go North! " << endl;
			cout << "<Enter>";
			getline(cin, inputString);
			return room;

		// All symptoms must be activated in order to enter Blood

		} else if(room->getNorth()->getName() == "BLOOD") {
			if(player->getSymptoms().size() == 3) {
				cout << endl << "The host is weak enough for you to enter the blood!" << endl;
				room->getNorth()->setLock(false);
				cout << "<Enter>";
				getline(cin, inputString);
				return room->getNorth();
			} else {
				cout << endl << "The host needs to be weaker for you to enter the blood!" << endl;
				cout << "<Enter>";
				getline(cin, inputString);
				return room;
			}

		} else {

			// Some body parts require the payment of a token in order to enter
			
			if(room->getNorth()->getLock()) {
				cout << "You're not quite strong enough to go there!" << endl;
				if(player->getTokens() == 0) {
					cout << "You need to find a token to enter!" << endl;
					cout << "<Enter>";
					getline(cin, inputString);
				} else {
					cout << "Would you like to spend a token to enter? (y/n) " << endl;
					getline(cin, inputString);
					size_t incorrectInput = inputString.find_first_not_of("yY");
					if((incorrectInput == string::npos) && (inputString.length() == 1)) {
						cout << "Alright! You made it!" << endl;
						player->setTokens(player->getTokens() - 1);
						cout << "You have " << player->getTokens() << " token(s) left!" << endl;
						room->getNorth()->setLock(false);
						cout << "<Enter>";
						getline(cin, inputString);
						return room->getNorth();
					} else {
						cout << "Alright, come back when you want to spend the token!" << endl;
						cout << "<Enter>";
						getline(cin, inputString);
					}
				}



				return room;
			}
			return room->getNorth();
		}
	} else if(direction == 'E') {
		if(room->getEast() == NULL) {
			cout << "There is nowhere to go East! " << endl << endl;
			cout << "<Enter>";
			getline(cin, inputString);
			return room;
		
		} else if(room->getEast()->getName() == "BLOOD") {
			if(player->getSymptoms().size() == 3) {
				cout << endl << "The host is weak enough for you to enter the blood!" << endl;
				room->getEast()->setLock(false);
				cout << "<Enter>";
				getline(cin, inputString);
				return room->getEast();
			} else {
				cout << endl << "The host needs to be weaker for you to enter the blood!" << endl;
				cout << "<Enter>";
				getline(cin, inputString);
				return room;
			}

		} else {

			if(room->getEast()->getLock()) {
				cout << "You're not quite strong enough to go there!" << endl;
				if(player->getTokens() == 0) {
					cout << "You need to find a token to enter!" << endl;
					cout << "<Enter>";
					getline(cin, inputString);
				} else {
					cout << "Would you like to spend a token to enter? (y/n) " << endl;
					getline(cin, inputString);

					size_t incorrectInput = inputString.find_first_not_of("yY");
					if((incorrectInput == string::npos) && (inputString.length() == 1)) {
						cout << "Alright! You made it!" << endl;
						player->setTokens(player->getTokens() - 1);
						cout << "You have " << player->getTokens() << " token(s) left!" << endl;
						cout << "<Enter>";
						getline(cin, inputString);
						room->getEast()->setLock(false);
						return room->getEast();
					} else {
						cout << "Alright, come back when you want to spend the token!" << endl;
						cout << "<Enter>";
						getline(cin, inputString);
					}
				}


				return room;
			}

			return room->getEast();
		}
	} else if(direction == 'S') {
		if(room->getSouth() == NULL) {
			cout << "There is nowhere to go South! " << endl << endl;
			cout << "<Enter>";
			getline(cin, inputString);
			return room;

		} else if(room->getSouth()->getName() == "BLOOD") {
			if(player->getSymptoms().size() == 3) {
				cout << endl << "The host is weak enough for you to enter the blood!" << endl;
				room->getSouth()->setLock(false);
				cout << "<Enter>";
				getline(cin, inputString);
				return room->getSouth();
			} else {
				cout << endl << "The host needs to be weaker for you to enter the blood!" << endl << endl;
				cout << "<Enter>";
				getline(cin, inputString);
				return room;
			}
			

		} else {
			if(room->getSouth()->getLock()) {
				cout << "You're not quite strong enough to go there!" << endl;
				if(player->getTokens() == 0) {
					cout << "You need to find a token to enter!" << endl;
					cout << "<Enter>";
					getline(cin, inputString);
				} else {
					cout << "Would you like to spend a token to enter? (y/n) " << endl;
					getline(cin, inputString);

					size_t incorrectInput = inputString.find_first_not_of("yY");
					if((incorrectInput == string::npos) && (inputString.length() == 1)) {
						cout << "Alright! You made it!" << endl;
						player->setTokens(player->getTokens() - 1);
						cout << "You have " << player->getTokens() << " token(s) left!" << endl;
						room->getSouth()->setLock(false);
						cout << "<Enter>";
						getline(cin, inputString);
						return room->getSouth();
					} else {
						cout << "Alright, come back when you want to spend the token!" << endl;
					}
					cout << "<Enter>";
					getline(cin, inputString);
				}

				return room;
			}
			return room->getSouth();
		}
	} else {
		if(room->getWest() == NULL) {
			cout << "There is nowhere to go West! " << endl;
			return room;
		} else if(room->getWest()->getName() == "BLOOD") {
			if(player->getSymptoms().size() == 3) {
				cout << endl << "The host is weak enough for you to enter the blood!" << endl;
				room->getWest()->setLock(false);
				cout << "<Enter>";
				getline(cin, inputString);
				return room->getWest();
			} else {
				cout << endl << "The host needs to be weaker for you to enter the blood!" << endl << endl;
				cout << "<Enter>";
				getline(cin, inputString);
				return room;
			}
			

		} else {

			if(room->getWest()->getLock()) {
				cout << "You're not quite strong enough to go there!" << endl;
				if(player->getTokens() == 0) {
					cout << "You need to find a token to enter!" << endl;
					cout << "<Enter>";
					getline(cin, inputString);
				} else {
					cout << "Would you like to spend a token to enter? (y/n) " << endl;
					getline(cin, inputString);

					size_t incorrectInput = inputString.find_first_not_of("yY");
					if((incorrectInput == string::npos) && (inputString.length() == 1)) {
						cout << "Alright! You made it!" << endl;
						player->setTokens(player->getTokens() - 1);
						cout << "You have " << player->getTokens() << " token(s) left!" << endl;
						room->getWest()->setLock(false);
						return room->getWest();
					} else {
						cout << "Alright, come back when you want to spend the token!" << endl;
					}
					cout << "<Enter>";
					getline(cin, inputString);
				}

				return room;
			}

			return room->getWest();
		}
	}
}

/******************************************************************************
 ** Function: displayMenu
 ** Description: This function prints the menu of selections the user can 
 **	make to take actions relevant to them regardless of their current room.
 ** Parameters: None.
 ** Preconditions: None.
 ** Postconditions: This function finishes with the menu printed to the screen.
 *****************************************************************************/

void displayMenu() {
	cout << "1)\tDisplay clues" << endl;
	cout << "2)\tDisplay symptoms" << endl;
	cout << "3)\tDisplay tokens" << endl;
	cout << "4)\tDisplay Known Map" << endl;
	cout << "[\"hidden\" option:" << endl;
	cout << "0) Display full instructions]" << endl;
}

/******************************************************************************
 ** Function: actionSelector
 ** Description: This function processes the user's selection from the menu.
 **	The input to this function should already be validated.
 ** Paramters: Player object pointer, Body Part object pointer, character of
 **	the user's menu selection, and the vector of all body parts.
 ** Preconditions: The player, body part, body vector, and user selection
 **	character must be appropriately initialized and assigned in order for
 **	this function to work as expected.
 ** Postconditions: This function finishes with returning the current body part
 **	or the body part returned by the traverseRooms function.
 *****************************************************************************/

Body_Part* actionSelector(Player* player, Body_Part* current, char choice, vector<Body_Part*> map) {
	string inputString;

	// The selection of '0' is for the purpose of displaying the instructions to
	//		achieve the quickest win

	if(choice == '0') {
		cout << "1) The goal is to get to the brain and enter the brain and solve" << endl;
		cout << "   the puzzle" << endl;
		cout << "2) Enter the determinant of the matrix presented by the brain in" << endl;
		cout << "   order to win the game" << endl << endl;
		cout << "Gameplay instructions (this is the fastest way, not the only way):" << endl; 
		cout << "\t(\"->\" means \"then go to\"):" << endl;
		cout << "1) Go to the Left Foot (get the token to unlock Stomach)" << endl;
		cout << "2) Enter the Stomach (pay) -> Chest -> Neck." << endl;
		cout << "3) Continue back and forth through the Stomach, Chest, and Neck" << endl;
		cout << "\tThis causes all three symptoms to be activated (use this to get" << endl;
		cout << "\tinto Blood later)" << endl;
		cout << "4) After all symptoms caused/collected, go to Chest ->" << endl;
		cout << "   Right Arm -> Right Hand" << endl;
		cout << "5) Go back to Right Arm -> Chest -> Left Arm -> Left Hand. There" << endl;
		cout << "   will be a token." << endl;
		cout << "\t(Go to both hands repeatedly to get tokens. Once both have" << endl;
		cout << "\tbeen reached again, another token will appear in that hand.)" << endl;
		cout << "6) Go to Mouth, pay to unlock it." << endl;
		cout << "7) Go, from Mouth -> Right Hand -> Mouth -> Left Hand ->" << endl;
		cout << "   Mouth -> Right Hand -> Mouth -> Left Hand" << endl;
		cout << "\t(i.e. Generate and collect 2 more tokens." << endl; 
		cout << "\tThese are for the brain.)" << endl;
		cout << "8) Go back to Mouth -> Neck -> Blood (if all symptoms collected," << endl;
		cout << "   Blood is unlocked)" << endl;
		cout << "9) Go to Brain, pay to unlock it." << endl;
		cout << "10) Pay a token to solve the puzzle. It is randomly generated." << endl;
		cout << "\tThe determinant of 2 x 2 matrix |a b| is a*d - b*c" << endl;
		cout << "\t                                |c d|" << endl;
		cout << "11) Relish in success" << endl;
		cout << "<Enter>";
		getline(cin, inputString);

	// Display found clues

	} else if(choice == '1') {
		vector<string> cluesToPrint = player->getClues();
		if(cluesToPrint.size() == 0) {
			cout << endl << "You haven't found any clues!" << endl;
			cout << "<Enter>";
			getline(cin, inputString);
		} else {
			cout << endl << "Clues Found:" << endl;
			for(int i = 0; i < cluesToPrint.size(); i++) {
				cout << cluesToPrint[i] << endl;
			}
			cout << endl;
			cout << "<Enter>";
			getline(cin, inputString);
		}

	// Display collected/caused symptoms

	} else if(choice == '2') {
		vector<string> symptomsToPrint = player->getSymptoms();
		if(symptomsToPrint.size() == 0) {
			cout << endl << "You haven't caused any symptoms!" << endl;
			cout << "<Enter>";
			getline(cin, inputString);
		} else {
			cout << endl << "Symptoms caused:" << endl;
			for(int i = 0; i < symptomsToPrint.size(); i++) {
				cout << symptomsToPrint[i] << endl;
			}
			cout << endl;
			cout << "<Enter>";
			getline(cin, inputString);
		}


	// Display current token count
		
	} else if(choice == '3') {
		if(player->getTokens() == 0) {
			cout << endl << "You have no tokens!" << endl;
			cout << "<Enter>";
			getline(cin, inputString);
		} else {
			cout << endl << "You have " << player->getTokens() << " token(s)!" 
				  << endl;
			cout << "<Enter>";
			getline(cin, inputString);
		}

	// Display the game map of discovered body parts
		
	} else if(choice == '4') {
		displayKnownMap(map);
		cout << "<Enter>";
		getline(cin, inputString);

	// Traverse Rooms

	} else {
		current = traverseRooms(player, current, choice);
		cout << endl << current->getName() << endl << endl;
	}
	return current;
}

/******************************************************************************
 ** Function: displayKnownMap
 ** Description: This function prints the map of the known body (if the user
 **	has been there, it and its symmetric partner is printed).
 ** Parameters: The vector containing body parts.
 ** Preconditions: The vector must contain the valid body parts that are
 **	appropriately initiated in order for this function to work as expected.
 ** Postconditions: This function finishes with the known map printed to the
 **	screen.
 *****************************************************************************/

void displayKnownMap(vector<Body_Part*> map) {
	for(int i = map.size() - 1; i >= 0; i--) {
		if((map[i]->getName() == "BRAIN") && (map[i]->get_entries() > 0)) {
			cout << "     _o_  " << endl;
		}
		if((map[i]->getName() == "MOUTH") && (map[i]->get_entries() > 0)) {
			cout << "    ( - )  " << endl;
		}
		if((map[i]->getName() == "NECK") && (map[i]->get_entries() > 0)) {
			cout << "     (|)  " << endl;
		}
		if((map[i]->getName() == "CHEST") && (map[i]->get_entries() > 0)) {
			cout << "   ______ " << endl;
		}
		if((map[i]->getName() == "STOMACH") && (map[i]->get_entries() > 0)) {
			cout << "  |  ( )  |" << endl;
			cout << "  |   |   |" << endl;
			cout << "  |  ( )  |" << endl;
			cout << " |    |    |" << endl;
		}
		if((map[i]->getName() == "RIGHT LEG") && (map[i]->get_entries() > 0)) {
			cout << "  _________ " << endl;
			cout << " |         |" << endl;
			cout << " |         |" << endl;
			cout << " |         |" << endl;
		}
		if((map[i]->getName() == "RIGHT FOOT")) {
			cout << "--         --";
		}

	}
	cout << endl << endl;
}



// Get and set functions for the Player class

Player::Player() {

}

void Player::setName(string player_name) {
	name = player_name;
}
void Player::setTokens(int tokens) {
	num_tokens = tokens;
}
void Player::addClue(string new_clue) {
	clues.push_back(new_clue);
}
void Player::addSymptom(string new_symptom) {
	symptoms.push_back(new_symptom);
}


string Player::getName() {
	return name;
}
int Player::getTokens() {
	return num_tokens;
}
vector<string> Player::getClues() {
	return clues;
}
vector<string> Player::getSymptoms() {
	return symptoms;
}



// Get and set functions for the Body_Part class

Body_Part::Body_Part() {

}

void Body_Part::setLinks(Body_Part* north, Body_Part* east, Body_Part* south, Body_Part* west) {
	northLink = north;
	eastLink = east;
	southLink = south;
	westLink = west;
}

void Body_Part::setName(string part_name) {
	name = part_name;
}
void Body_Part::setType(string part_type) {
	type = part_type;
}
void Body_Part::set_token(bool value) {
	has_token = value;
}
void Body_Part::add_entry() {
	entries += 1;
}
void Body_Part::setClue(string newClue) {
	clue = newClue;
}
void Body_Part::setLock(bool locked) {
	is_locked = locked;
}
void Body_Part::setSymptom(string newSymptom) {
	symptom = newSymptom;
}


Body_Part* Body_Part::getNorth() {
	return northLink;
}
Body_Part* Body_Part::getEast() {
	return eastLink;
}
Body_Part* Body_Part::getSouth() {
	return southLink;
}
Body_Part* Body_Part::getWest() {
	return westLink;
}

string Body_Part::getName() {
	return name;
}
string Body_Part::getType() {
	return type;
}
bool Body_Part::get_token() {
	return has_token;
}
int Body_Part::get_entries() {
	return entries;
}
string Body_Part::getClue() {
	return clue;
}
bool Body_Part::getLock() {
	return is_locked;
}
string Body_Part::getSymptom() {
	return symptom;
}