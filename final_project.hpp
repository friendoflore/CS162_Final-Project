/******************************************************************************
 ** Filename: final_project.cpp
 ** Author: Tim Robinson
 ** Date: 3/16/2015
 ** Last modification date: 3/16/2015 11:14 AM PST
 *****************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Player
{
public:
	Player();
	void setName(string);
	void setTokens(int);
	void addClue(string);
	void addSymptom(string);

	string getName();
	int getTokens();
	vector<string> getClues();
	vector<string> getSymptoms();

private:
	string name;
	int num_tokens;
	vector<string> clues;
	vector<string> symptoms;
};

class Body_Part 
{
public:
	Body_Part();
	virtual void setName(string);
	virtual void setLinks(Body_Part*, Body_Part*, Body_Part*, Body_Part*);
	virtual void setType(string);
	virtual void set_token(bool);
	virtual void add_entry();
	virtual void setClue(string);
	virtual void setLock(bool);
	virtual void setSymptom(string);

	virtual string getName();
	virtual Body_Part* getNorth();
	virtual Body_Part* getEast();
	virtual Body_Part* getSouth();
	virtual Body_Part* getWest();
	virtual string getType();
	virtual bool get_token();
	virtual int get_entries();
	virtual string getClue();
	virtual bool getLock();
	virtual string getSymptom();


protected:
	Body_Part* northLink;
	Body_Part* eastLink;
	Body_Part* southLink;
	Body_Part* westLink;

	string name;
	string type;
	bool has_token;
	int entries;
	string clue;
	bool is_locked;
	string symptom;


};

class Extremity : public Body_Part 
{
public:

private:

};

class Limb : public Body_Part
{
public:

private:

};

class Torso : public Body_Part
{
public:

private:


};

class Foot : public Extremity
{

};

class Hand : public Extremity
{

};

class Leg : public Limb
{

};

class Arm : public Limb
{

};
class Mouth : public Body_Part
{

};

class Blood : public Body_Part
{

};

class Brain : public Body_Part
{

};


Body_Part* traverseRoom(Player*, Body_Part*, char);
void printRoomLinks(Body_Part*);
void displayMenu();
Body_Part* actionSelector(Player*, Body_Part*, char, vector<Body_Part*>);
void displayKnownMap(vector<Body_Part*>);

