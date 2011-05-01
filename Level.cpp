//Level.cpp
//Zach Adams, Alex Strohmeyer, Josh Woods

#include <cstdlib>
#include <string>
#include "Level.h"
#include "Drawable.h"
#include <fstream>
#include "Nonbreakable.h"
#include "LList.h"
#include "Coin.h"
#include "Goomba.h"
#include "Turtle.h"
#include "Plant.h"
#include "Breakable.h"
#include "Pipe.h"
#include "Flag.h"
#include "Background.h"
#include "Passable.h"

using namespace std;

bool Level::instanceFlag = false;
Level* Level::single = NULL;
Level* Level::sharedLevel()
{
	if(! instanceFlag)
	{
		single = new Level();
		instanceFlag = true;
		return single;
	}
	else 
		{
			return single;
		}
	}

//------------------------------------------------------------
Level::Level()
{




}
//------------------------------------------------------------
Level::~Level()
{
	instanceFlag = false;
}
//------------------------------------------------------------
void Level::makeLevel(int levelNumber)
{
    //if the level already exists delete it
	if ((activeDrawable_.first() != NULL) || (activeMovable_.first() != NULL) || (activeBlocks_.first() != NULL)) {
		resetLevel();
	}
	
	// Mac environment variable for home directory
    char *cHomeDir = NULL;
    
    cHomeDir = getenv("HOME");
    
    // I think Windows uses HOMEPATH
    if (!cHomeDir) {
        cHomeDir = getenv("HOMEPATH");
    }
    string homeDir = cHomeDir;
    homeDir += "/CS330/";
    string fname;
    
	ifstream inFile;
	if (levelNumber== 1) {
        fname = homeDir + "levelfiles/level1.txt";
		inFile.open(fname.c_str());
	}
	else if (levelNumber== 2) {
        fname = homeDir + "levelfiles/level3.txt";
		inFile.open(fname.c_str());
	}
	
	int xcoord = 0, ycoord = 0, type, reward;
	char object;
	
	//checks if the file exists and is readable
	while (inFile.good()) {
		
		object= inFile.get();
		
		/*at this point the variable 'object' has the next item in the .txt 
		 and here the 'object' and it's xcord and ycord are sent off to the 
		 correct LList*/

		if (object== 'b') {
			//create breakable block
			Breakable *bBlock = new Breakable;
			bBlock->setTop(ycoord  + 16);
			bBlock->setBottom(ycoord);
			bBlock->setLeft(xcoord);
			bBlock->setRight(xcoord + 16);
			//add block to the list
			if (xcoord<256){
				activeBlocks_.append(bBlock);
			}
			else {
				levelBlocks_.append(bBlock);
			}
		}

		else if (object== 'B' || object=='M' || object=='C' || object=='S'){
			
			// sets the type and reward based off the letter passed and creates the block
			if (object == 'B') {
				type = REGULAR;
				reward = 0;
			}
			else if (object == 'M'){
				type = QUESTION;
				reward = MUSHROOM;
			}
			else if (object == 'S'){
				type = QUESTION;
				reward = STAR;
			}
			else if (object == 'C'){
				type = QUESTION;
				reward = COIN;
			}
			//creates the block with the type and reward
			Nonbreakable *nBlock = new Nonbreakable(type, reward);
			nBlock->setTop(ycoord  + 16);
			nBlock->setBottom(ycoord);
			nBlock->setLeft(xcoord);
			nBlock->setRight(xcoord + 16);
			
			//place in correct list
			if (xcoord<256) {
				activeBlocks_.append(nBlock);
			}
			else {
				levelBlocks_.append(nBlock);
			}
		}

		else if (object == 'c') {
			
			//create coin
			Coin *coin = new Coin;
			coin->setTop(ycoord  + 16);
			coin->setBottom(ycoord);
			coin->setLeft(xcoord);
			coin->setRight(xcoord + 16);
			
			//place in correct list
			if (xcoord<256) {
				activeDrawable_.append(coin);
			}
			else {
				levelDrawable_.append(coin);
			}
		}

		else if (object== 'f'){
			//create flag pole
			Flag *flag = new Flag;
			flag->setTop(ycoord  + 16);
			flag->setBottom(ycoord);
			flag->setLeft(xcoord+6);
			flag->setRight(xcoord + 10);
			//place in correct list
			if (xcoord<256){
				activeBlocks_.append(flag);
			}
			else {
				levelBlocks_.append(flag);
			}
		}

		else if (object== 'P'){
			//create Pipe top
			Pipe *pipe = new Pipe;
			pipe->setType(0);
			pipe->setTop(ycoord  + 16);
			pipe->setBottom(ycoord);
			pipe->setLeft(xcoord);
			pipe->setRight(xcoord + 32);
			//place in correct list
			if (xcoord<256){
				activeBlocks_.append(pipe);
			}
			else {
				levelBlocks_.append(pipe);
			}
		}

		else if (object== 'p'){
			//create Pipe body
			Pipe *pipe = new Pipe;
			pipe->setType(1);
			pipe->setTop(ycoord  + 16);
			pipe->setBottom(ycoord);
			pipe->setLeft(xcoord);
			pipe->setRight(xcoord + 32);
			//place in correct list
			if (xcoord<256){
				activeBlocks_.append(pipe);
			}
			else {
				levelBlocks_.append(pipe);
			}
		}

		else if (object== 'g'){
			
			//create goomba
			Goomba *goomba = new Goomba;
			goomba->setTop(ycoord  + 16);
			goomba->setBottom(ycoord);
			goomba->setLeft(xcoord);
			goomba->setRight(xcoord + 16);
			
			//place in correct list
			if (xcoord<256) {
				activeMovable_.append(goomba);
			}
			else {
				levelMovable_.append(goomba);
			}
		}

		else if (object == 'k') {
			
			//create koopa
			Turtle *koopa = new Turtle;
			koopa->setTop(ycoord  + 24);
			koopa->setBottom(ycoord);
			koopa->setLeft(xcoord);
			koopa->setRight(xcoord + 16);
			
			//place in correct list
			if (xcoord<256) {
				activeMovable_.append(koopa);
			}
			else {
				levelMovable_.append(koopa);
			}
		}

		 else if (object == 'z') {
			
			//create plant
			Plant *plant = new Plant;
			plant->setTop(ycoord  + 24);
			plant->setBottom(ycoord);
			plant->setLeft(xcoord-8);
			plant->setRight(xcoord + 8);
			
			//place in correct list
			if (xcoord<256) {
				activeMovable_.append(plant);
			}
			else {
				levelMovable_.append(plant);
			} 
		}

		else if (object == 's') {
			
			//creates the coordinates for marios starting point
			leftStart_ = xcoord;
			bottomStart_ = ycoord;
		}

        else if (object== 'u' || object=='y' || object=='w' || object=='1'|| object=='2' || object=='3' || object=='7' || object =='8' || object== 'v' || object== 't' || object== 'd'){
            
			//create bush
            Background *background = new Background(object);
            background->setTop(ycoord  + background->getHeight());
            background->setBottom(ycoord);
            background->setLeft(xcoord);
            background->setRight(xcoord + background->getWidth());
            
            //place in correct list
            if (xcoord<256) {
                activeDrawable_.append(background);
            }
            else {
                levelDrawable_.append(background);
            }
        }
        else if (object== 'q' || object=='a' || object=='r'){
            
			//create bush
            Passable *passable = new Passable(object);
            passable->setTop(ycoord + 16);
            passable->setBottom(ycoord);
            passable->setLeft(xcoord);
            passable->setRight(xcoord + 16);
            
            //place in correct list
            if (xcoord<256) {
                activeDrawable_.append(passable);
            }
            else {
                levelDrawable_.append(passable);
            }
        }
        

		//increases the y value until the objects hit the top of the screen
		if (ycoord < 224) {
			ycoord += 16;
		}
		//when the y value hits the highest point it resets to 0 and increases the x value
		else if (ycoord == 224) {
         xcoord += 16;
         ycoord = 0; 
		}
	
	}
	inFile.close();
}
//------------------------------------------------------------
void Level::updateExtents(int leftBound, int rightBound)
{
	//increases the active range for blocks to prevent an issue with goombas falling off the level
	int blockRight = rightBound + 96;
	//creates a left buffer range for movables and blocks
	//blocks extend 16 past movables to correctly delete movables
	int blockLeft, movableLeft;
	//creates the buffer for blocks and movables after the extents update enough
	if (leftBound >= 48){
		blockLeft = leftBound - 48;
	}
	else {
		blockLeft = leftBound;
	}
	if (leftBound >= 32){
		movableLeft = leftBound - 32;
	}
	else {
		movableLeft = leftBound;
	}

	//removes from the levelDrawable_ llist and adds onto the end of the active list
	while (levelDrawable_.first() != NULL) {
		if (levelDrawable_.first()->left() < rightBound) {
			Drawable *obj = levelDrawable_.removeFirst();
			activeDrawable_.append(obj);
		}
		else {
			break;
		}
	}
	
	//removes from the active list when and deleted the object when the right end of an object falls off the left bound
	while (activeDrawable_.first() != NULL) {
		if (activeDrawable_.first()->right() < leftBound) {
			Drawable *obj = activeDrawable_.removeFirst();
			delete obj;
		}
		else {
			break;
		}
	}
	
	//removes from the levelMovable_ llist and appends to the active list
	while (levelMovable_.first() != NULL) {
		if (levelMovable_.first()->left() < rightBound) {
			Drawable *obj = levelMovable_.removeFirst();
			activeMovable_.append(obj);
		}
		else {
			break;
		}
	}
	
	//removes from the activeMovable_ llist and deletes the object
	while (activeMovable_.first() != NULL) {
		if (activeMovable_.first()->right() < movableLeft) {
			Drawable *obj = activeMovable_.removeFirst();
			delete obj;
		}
		else {
			break;
		}
	}
	
	//removes from the levelBlocks_ llist and appends to the active list
	while (levelBlocks_.first() != NULL) {
		if (levelBlocks_.first()->left() < blockRight) {
			Drawable *obj = levelBlocks_.removeFirst();
			activeBlocks_.append(obj);
		}
		else {
			break;
		}
	}
	
	//removes from the activeBlocks_ llist and deletes the object
	while (activeBlocks_.first() != NULL) {
		if (activeBlocks_.first()->right() < blockLeft) {
			Drawable *obj = activeBlocks_.removeFirst();
			delete obj;
		}
		else {
			break;
		}
	}
}
//------------------------------------------------------------
void Level::removeDrawable(Drawable *obj)
{
	int type;
	
	//checks the object type and calls remove on the correct list
	type = obj->objectType();

	if ((type == FLAG) || (type == FIREFLOWER) || (type == COIN)) {
		activeDrawable_.removeDrawable(obj);
	}

	else if ((type == BREAKABLE) || (type == QUESTION) || (type == REGULAR)) {
		activeBlocks_.removeDrawable(obj);
	}

	else {
		activeMovable_.removeDrawable(obj);
	}
}
//------------------------------------------------------------
void Level::loadTestLevel()
{
	//creates 2 rows of blocks across the bottom of the level for debugging
	int left, bottom, i;
	bottom = 0;
	left = 0;
	for (i=0; i<10; ++i) {
		Nonbreakable *block = new Nonbreakable(REGULAR);
		block->setTop(bottom  + 16);
		block->setBottom(bottom);
		block->setLeft(left);
		block->setRight(left + 16);
		activeBlocks_.append(block);
		left += 16;
	}
    bottom = 64;
    left = 32;
    for (i=0; i<4; ++i) {
		Nonbreakable *block = new Nonbreakable(REGULAR);
		block->setTop(bottom  + 16);
		block->setBottom(bottom);
		block->setLeft(left);
		block->setRight(left + 16);
		activeBlocks_.append(block);
		left += 16;
	}
}
//------------------------------------------------------------
void Level::addDrawable(Drawable *obj)
{
	//inserts the object to the correct list
	activeDrawable_.insertInSortedOrder(obj);
}
//------------------------------------------------------------
void Level::addMovable(Drawable *obj)
{
	//inserts the object to the correct list
	activeMovable_.insertInSortedOrder(obj);

}
//------------------------------------------------------------
void Level::resetLevel()
{
	//empties the active lists
	while (activeMovable_.first() != NULL) {
		Drawable *obj = activeMovable_.removeFirst();
		delete obj;
	}
	while (activeDrawable_.first() != NULL) {
		Drawable *obj = activeDrawable_.removeFirst();
		delete obj;
	}
	while (activeBlocks_.first() != NULL) {
		Drawable *obj = activeBlocks_.removeFirst();
		delete obj;
	}

	//empties the level Lists
	while (levelMovable_.first() != NULL) {
		Drawable *obj = levelMovable_.removeFirst();
		delete obj;
	}
	while (levelDrawable_.first() != NULL) {
		Drawable *obj = levelDrawable_.removeFirst();
		delete obj;
	}
	while (levelBlocks_.first() != NULL) {
		Drawable *obj = levelBlocks_.removeFirst();
		delete obj;
	}
}