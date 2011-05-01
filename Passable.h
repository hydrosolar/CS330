// Jay Bondzeleske, John (Jack) Johnson, Jamie Veals
//------------------------------------------------------------

#ifndef _PASSABLE_H
#define _PASSABLE_H

//------------------------------------------------------------

#include "Drawable.h"

//------------------------------------------------------------

class Passable:public Drawable{
    
    //------------------------------------------------------------
    
private:
    GLuint texture_;
    void sprite();
    int type_;
public:
	Passable(char type)
    {
        
        if (type == 'q') {
            type_ = 0;
        }
        else if (type == 'a'){
            type_ = 1;
        }
        else if (type == 'r'){
            type_ = 2;
        }
        sprite(); 
    }
    
	virtual ~Passable()
	{
        
	}
    
	// OpenGL abstract method to draw object
	virtual void draw(bool update);
	// Returns object type COIN
	int objectType() { return PASSABLE; }
};



#endif