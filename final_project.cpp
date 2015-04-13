/******************************************************************************
 ** Filename: final_project.cpp
 ** Author: Tim Robinson
 ** Date: 3/16/2015
 ** Last modification date: 3/16/2015 11:14 AM PST
 ** Description: This program runs a puzzle in which the user controls a 
 **	parasite within a human body. The parasite's goal is to kill the body
 **	that they inhabit. There are 14 "rooms" that are different body parts
 **	of the person. The parasite begins in the right foot and the user must
 **	figure out how to beat the game. In travelling from body part to body
 **	part, the user must discover the symptoms that can be activated and
 **	activate them. The user has a final challenge that will kill the body,
 **	but it will require collecting symptoms, collecting tokens in order to
 **	access more body parts, and solve the general puzzle in order to reach
 **	the final body part.
 ** Input: This program accepts room (i.e. body part) change directions as 
 **	input. The user can also display the symptoms that are activated (that 
 **	they have "collected") and the body parts they have infected.
 ** Output: This program outputs information about each room as the user enters
 **	and lets the user know when they have reached the exit.
 *****************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "final_project.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
	srand(time(NULL));

	// The group of lines below sets up the initial conditions of the game board

	Foot* left_foot = new Foot;
	left_foot->setName("LEFT FOOT");
	left_foot->setType("EXTREMITY");
	left_foot->set_token(true);
	Foot* right_foot = new Foot;
	right_foot->setName("RIGHT FOOT");
	right_foot->setType("EXTREMITY");
	Hand* left_hand = new Hand;
	left_hand->setName("LEFT HAND");
	left_hand->setType("EXTREMITY");
	Hand* right_hand = new Hand;
	right_hand->setName("RIGHT HAND");
	right_hand->setType("EXTREMITY");
	Leg* left_leg = new Leg;
	left_leg->setName("LEFT LEG");
	left_leg->setType("LIMB");
	left_leg->setClue("To cross the blood-brain barrier, you'll need to DETERMINE an integer to enter.");
	Leg* right_leg = new Leg;
	right_leg->setName("RIGHT LEG");
	right_leg->setType("LIMB");
	right_leg->setClue("Look for tokens in the extremities!");
	Arm* left_arm = new Arm;
	left_arm->setName("LEFT ARM");
	left_arm->setType("LIMB");
	left_arm->setClue("You'll need to do some damage in order to win. You do damage by travelling in the body.");
	Arm* right_arm = new Arm;
	right_arm->setName("RIGHT ARM");
	right_arm->setType("LIMB");
	right_arm->setClue("Check BOTH hands for a token!");
	Torso* stomach = new Torso;
	stomach->setName("STOMACH");
	stomach->setType("TORSO");
	stomach->setLock(true);
	stomach->setSymptom("VOMITING");
	Torso* chest = new Torso;
	chest->setName("CHEST");
	chest->setType("TORSO");
	chest->setSymptom("COUGHING");
	Torso* neck = new Torso;
	neck->setName("NECK");
	neck->setType("TORSO");
	neck->setSymptom("DEBILITATING HEADACHE");
	Mouth* mouth = new Mouth;
	mouth->setName("MOUTH");
	mouth->setLock(true);
	Blood* blood = new Blood;
	blood->setName("BLOOD");
	blood->setLock(true);
	Brain* brain = new Brain;
	brain->setName("BRAIN");
	brain->setLock(true);

	// This group of lines creates all the links between the body parts for the
	// 	game board
	
	left_foot->setLinks(left_leg, NULL, NULL, NULL);
	right_foot->setLinks(right_leg, NULL, NULL, NULL);
	left_leg->setLinks(stomach, NULL, left_foot, right_leg);
	right_leg->setLinks(stomach, left_leg, right_foot, NULL);
	stomach->setLinks(chest, left_leg, NULL, right_leg);
	chest->setLinks(neck, left_arm, stomach, right_arm);
	left_arm->setLinks(left_hand, NULL, chest, NULL);
	right_arm->setLinks(right_hand, NULL, chest, NULL);
	left_hand->setLinks(mouth, left_foot, left_arm, blood);
	right_hand->setLinks(mouth, blood, right_arm, right_foot);
	mouth->setLinks(neck, right_hand, NULL, left_hand);
	neck->setLinks(NULL, blood, mouth, chest);
	blood->setLinks(brain, left_hand, neck, right_hand);
	brain->setLinks(NULL, NULL, blood, NULL);


	Body_Part* current_body_part = new Body_Part;

	// This vector is used to display the known game map

	vector<Body_Part*> Body;
	Body.push_back(right_foot);
	Body.push_back(left_foot);
	Body.push_back(right_leg);
	Body.push_back(left_leg);
	Body.push_back(stomach);
	Body.push_back(chest);
	Body.push_back(right_arm);
	Body.push_back(left_arm);
	Body.push_back(right_hand);
	Body.push_back(left_hand);
	Body.push_back(neck);
	Body.push_back(mouth);
	Body.push_back(blood);
	Body.push_back(brain);

	string inputString;

	// These booleans are used to govern token generation
	bool right_enter = false;
	bool left_enter = false;

	cout << endl << "Please enter your name: ";
	getline(cin, inputString);
	Player* player = new Player;
	player->setName(inputString);
	player->setTokens(0);

	// Introduction

	cout << endl << "Welcome, " << player->getName() << endl;
	cout << "You are a fuzzy little parasite and you just found a new host! EXCITING!"
		  << endl;
	cout << "Since you are a parasite, your goal is to take over the host completely!" 
		  << endl;
	cout << "You infected the host in the RIGHT FOOT!" 
		  << endl << "Good luck out there!" << endl << endl;


	// This construct is used to make the console output more readable
	cout << "<Enter>";
	getline(cin, inputString);


	// When the game_timer reaches 0, the game is over (the host is healed of 
	//		you, the parasite)
	int game_timer = 60;

	current_body_part = right_foot;
	Body_Part* temp_body_part = new Body_Part;
	temp_body_part = current_body_part;
	bool foundExit = false;

	// This while loop governs the cycle of a turn for the user

	while(!foundExit) {
		if(game_timer == 0) {
			cout << "Oh no! the host healed itself of you!" << endl;
			cout << "Hopefully you have better luck next time!" << endl;
			cout << "<Enter> to quit";
			getline(cin, inputString);
			exit(0);
		}

		cout << "Time until host is healed: " << game_timer << endl << endl;
		game_timer -= 1;

		// If the user has not changed rooms, do not advance the turn

		if(temp_body_part->getName() != current_body_part->getName()) {
			temp_body_part = current_body_part;

			// Track the number of times the user has entered a body part
			current_body_part->add_entry();

			// If each hand has been visited, generate a token in the hand most
			//		recently visited (user collects the token upon generation)
			if(current_body_part->getName() == "RIGHT HAND") {
				right_enter = true;
			}
			if(current_body_part->getName() == "LEFT HAND") {
				left_enter = true;
			}
			if(right_enter && left_enter) {
				current_body_part->set_token(true);
				right_enter = false;
				left_enter = false;
			}

			// Only check for a token if the body part is an extremity
			//	 	(a hand or foot)

			if(current_body_part->getType() == "EXTREMITY") {
				if(current_body_part->get_token()) {
					player->setTokens(player->getTokens() + 1);
					cout << "You found a token! " << endl;
					current_body_part->set_token(false);
				} else {
					cout << "No tokens in this extremity!" << endl;
				}
			}

			// Only look for clues in limbs

			if((current_body_part->getName() == "RIGHT LEG") && (current_body_part->get_entries() == 1)) {
				cout << endl << "The limbs contain clues to help you win the game!" << endl;
				cout << "**You found your first clue!**" << endl << endl;
				player->addClue(current_body_part->getClue());
			}
			if((current_body_part->getName() == "LEFT LEG") && (current_body_part->get_entries() == 1)) {
				cout << endl << "**You found another clue!**" << endl << endl;
				player->addClue(current_body_part->getClue());
			}
			if((current_body_part->getName() == "RIGHT ARM") && (current_body_part->get_entries() == 1)) {
				cout << endl << "**You found another clue!**" << endl << endl;
				player->addClue(current_body_part->getClue());
			}
			if((current_body_part->getName() == "LEFT ARM") && (current_body_part->get_entries() == 1)) {
				cout << endl << "**You found another clue!**" << endl << endl;
				player->addClue(current_body_part->getClue());
			}

			// Only check for symptom development in torso body parts

			if((current_body_part->getName() == "STOMACH") && (current_body_part->get_entries() == 3)) {
				cout << "You've done enough damage to the stomach to cause " << current_body_part->getSymptom() 
					  << "!" << endl;
				player->addSymptom(current_body_part->getSymptom());
			}
			if((current_body_part->getName() == "CHEST") && (current_body_part->get_entries() == 3)) {
				cout << "You've done enough damage to the chest to cause " << current_body_part->getSymptom() 
					  << "!" << endl;
				player->addSymptom(current_body_part->getSymptom());
			}
			if((current_body_part->getName() == "NECK") && (current_body_part->get_entries() == 3)) {
				cout << "You've done enough damage to the neck to cause " << current_body_part->getSymptom() 
					  << "!" << endl;
				player->addSymptom(current_body_part->getSymptom());
			}

			cout << "<Enter>";
			getline(cin, inputString);
		}

		cout << "Current Body Part:\t" << current_body_part->getName() << endl << endl;
		cout << "(Type a direction letter to go to body part)" << endl << endl;
		printRoomLinks(current_body_part);
		displayMenu();
		cout << endl;

		bool reprompt = false;

		// Do-while loop to control menu selection input validation

		do {
			cout << "What would you like to do? ";
			getline(cin, inputString);

			size_t incorrectInput = inputString.find_first_not_of("01234NESW");
			if((incorrectInput == string::npos) && (inputString.length() == 1)) {
				current_body_part = actionSelector(player, current_body_part, *inputString.c_str(), Body);
				reprompt = false;
			} else {
				cout << "You must make a valid choice!" << endl;
				reprompt = true;
			}
		} while(reprompt);

		// This runs the final puzzle portion of the game located in the brain

		if(current_body_part->getName() == "BRAIN") {
			cout << endl << "You made it to the BRAIN!!!" << endl;
			cout << "You need to enter the correct integer in order to cross" << endl;
			cout << "     the BLOOD-BRAIN barrier and take over the host!" << endl;
			cout << "If you get it wrong, you'll need to find another token to" << endl;
			cout << "     try again!" << endl << endl;
			
			// If the user has tokens, ask if they would like to try the puzzle

			if(player->getTokens() > 0) {
				cout << "Would you like to spend a token in order to try for the win? (y/n) ";
				getline(cin, inputString);
				size_t incorrectInput = inputString.find_first_not_of("yY");
				if((incorrectInput == string::npos) && (inputString.length() == 1)) {
					cout << "Alright! You spent one token! " << endl;
					player->setTokens(player->getTokens() - 1);
					
					// Generate random "matrix" elements

					int a = rand() % 15;
					int b = rand() % 15;
					int c = rand() % 15;
					int d = rand() % 15;

					cout << endl << "|\t" << a << "\t" << b << "\t|" << endl;
					cout << "|\t" << c << "\t" << d << "\t|" << endl << endl;
					cout << endl << "What is your answer!? ";
					getline(cin, inputString);
					size_t incorrectInput = inputString.find_first_not_of("-0123456789");
					
					if(incorrectInput == string::npos) {

						// Calculate determinant of matrix elements

						int result = (a * d) - (b * c);
						if(result == atoi(inputString.c_str())) {
							cout << "You successfully crossed the BLOOD-BRAIN barrier!" << endl;
							cout << player->getName() << ", you have successfully infected the host completely!" << endl;
							getline(cin, inputString);
							cout << endl << endl << endl << "***********************************************" << endl;
							cout << "*** CONGRATULATIONS ***************************" << endl;
							cout << "****** CONGRATULATIONS ************************" << endl;
							cout << "********* CONGRATULATIONS *********************" << endl;
							cout << "************ CONGRATULATIONS ******************" << endl;
							cout << "*************** CONGRATULATIONS ***************" << endl;
							cout << "****************** CONGRATULATIONS ************" << endl;
							cout << "********************* CONGRATULATIONS *********" << endl;
							cout << "************************ CONGRATULATIONS ******" << endl;
							cout << "*************************** CONGRATULATIONS ***" << endl;
							cout << "***********************************************" << endl;

							getline(cin, inputString);
							cout << endl << endl;
							cout << "                                          **" << endl;
							cout << "**************************************** *****" << endl;
							cout << "*** CONGRATULATIONS ******************* ******" << endl;
							cout << "****** CONGRATULATIONS *************** ********" << endl;
							cout << "********* CONGRATULATIONS *********** *********" << endl;
							cout << "************ CONGRATULATIONS ******* **********" << endl;
							cout << "*************** CONGRATULATIONS *** ***********" << endl;
							cout << "****************** CONGRATULATIONS NS *********" << endl;
							cout << "********************* CONGRATULAT ATIONS ******" << endl;
							cout << "************************ CONGRAT ATULATIONS ***" << endl;
							cout << "*************************** CON **************" << endl;
							cout << "****************************** **" << endl;


							getline(cin, inputString);
							cout << endl;
							cout << "                                       *" << endl;
							cout << "                                       **" << endl;
							cout << "************************************* *****" << endl;
							cout << "*** CONGRATULATIONS **************** ******" << endl;
							cout << "****** CONGRATULATIONS ************ ********" << endl;
							cout << "********* CONGRATULATIONS ******** *********" << endl;
							cout << "************ CONGRATULATIONS **** **********" << endl;
							cout << "*************** CONGRATULATIONS  ***********" << endl;
							cout << "****************** CONGRATULATI NS *********" << endl;
							cout << "********************* CONGRATU ATIONS ******" << endl;
							cout << "************************ CONG ATULATIONS ***" << endl;
							cout << "***************************  **************" << endl;
							cout << "*************************** *" << endl;


							getline(cin, inputString);
							cout << endl << endl;
							cout << "                                     *****" << endl;
							cout << "********************************** ******** " << endl;
							cout << "*** CONGRATULATIONS ************* ******** " << endl;
							cout << "****** CONGRATULATIONS ********* ******** *" << endl;
							cout << "********* CONGRATULATIONS ***** ******** **" << endl;
							cout << "************ CONGRATULATIONS * ******** ***" << endl;
							cout << "*************** CONGRATULATIO ******** ****" << endl;
							cout << "****************** CONGRATUL NS ***** *****" << endl;
							cout << "********************* CONGR ATIONS * ******" << endl;
							cout << "************************ C ATULATIO *******" << endl;
							cout << "************************* ******** *****" << endl;
							cout << "************************ *      * ****" << endl;

							getline(cin, inputString);
							cout << endl << endl;
							cout << "                                  *****" << endl;
							cout << "******************************* ******** ***" << endl;
							cout << "*** CONGRATULATIONS ********** ******** ****" << endl;
							cout << "****** CONGRATULATIONS ****** ******** *****" << endl;
							cout << "********* CONGRATULATIONS ** ******** ******" << endl;
							cout << "************ CONGRATULATION S******* *******" << endl;
							cout << "*************** CONGRATULA OIONS*** ********" << endl;
							cout << "****************** CONGRA TULATION *********" << endl;
							cout << "********************* CO NGRATULI **********" << endl;
							cout << "*********************** ATIONS * S*********" << endl;
							cout << "********************** ******** TIONS ***" << endl;
							cout << "********************* *      * *********" << endl;

							getline(cin, inputString);
							cout << endl << endl;
							cout << "                        *****             " << endl;
							cout << "********************* ******** *************" << endl;
							cout << "*** CONGRATULATIONS  ******** **************" << endl;
							cout << "****** CONGRATULATI ******** ***************" << endl;
							cout << "********* CONGRATI ATIONS** ****************" << endl;
							cout << "************ CONG ATULATIO *****************" << endl;
							cout << "**************** ONGRATUL NS ***************" << endl;
							cout << "************** *** CONG LATIONS ************" << endl;
							cout << "************* ******** RATULATIONS *********" << endl;
							cout << "************ ******** CONGRATULATIONS ******" << endl;
							cout << "*********** ******** *** CONGRATULATIONS ***" << endl;
							cout << "********** *      * *********************" << endl;

							getline(cin, inputString);
							cout << endl << endl;
							cout << "           *****" << endl;
							cout << "******** ATIONS * **************************" << endl;
							cout << "*** CON ATULATIO ***************************" << endl;
							cout << "****** ONGRATUL ****************************" << endl;
							cout << "***** ***CONGR ATIONS***********************" << endl;
							cout << "**** ******** ATULATIONS********************" << endl;
							cout << "*** ******** ONGRATULATIONS ****************" << endl;
							cout << "** ******** *** CONGRATULATIONS ************" << endl;
							cout << "* ******** ******* CONGRATULATIONS *********" << endl;
							cout << " ******** *********** CONGRATULATIONS ******" << endl;
							cout << "******** *************** CONGRATULATIONS ***" << endl;
							cout << "      * **********************************" << endl;

							getline(cin, inputString);
							cout << endl;
							cout << "  **" << endl;
							cout << "********" << endl;
							cout << "*** CON  **********************************" << endl;
							cout << "******* ULATIONS**************************" << endl;
							cout << "****** GRATULATIONS**************************" << endl;
							cout << "*****  CONGRATULATIONS***********************" << endl;
							cout << "**** **** CONGRATULATIONS********************" << endl;
							cout << "*** ******** CONGRATULATIONS ****************" << endl;
							cout << "** ************ CONGRATULATIONS **************" << endl;
							cout << "* **************** CONGRATULATIONS ***********" << endl;
							cout << " ******************** CONGRATULATIONS ********" << endl;
							cout << "************************ CONGRATULATIONS *****" << endl;
							cout << "*********************************************" << endl;

							getline(cin, inputString);
							cout << endl << endl << endl << "***********************************************" << endl;
							cout << "*** CONGRATULATIONS ***************************" << endl;
							cout << "****** CONGRATULATIONS ************************" << endl;
							cout << "********* CONGRATULATIONS *********************" << endl;
							cout << "************ CONGRATULATIONS ******************" << endl;
							cout << "*************** CONGRATULATIONS ***************" << endl;
							cout << "****************** CONGRATULATIONS ************" << endl;
							cout << "********************* CONGRATULATIONS *********" << endl;
							cout << "************************ CONGRATULATIONS ******" << endl;
							cout << "*************************** CONGRATULATIONS ***" << endl;
							cout << "***********************************************" << endl;


							cout << "<Enter> to quit! ";
							getline(cin, inputString);

							// GAME OVER - WIN

							exit(0);
						} else {
							cout << "Oh no!! You'll have to pay another token to try again." << endl;
						}
					} else {
						cout << "You must enter an integer! Find another token to try again!" << endl;
						cout << "<Enter>";
						getline(cin, inputString);
					}
					
				} else {
					cout << "Come back when you want to pay for a shot at the win!" << endl;
					cout << "<Enter>";
					getline(cin, inputString);
				}
			} else {
				cout << "You need to find a token to try and win!" << endl;
				cout << "<Enter>";
				getline(cin, inputString);
			}
		}
	}

	return 0;
}
