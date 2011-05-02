// Jay Bondzeleske, John (Jack) Johnson, Jamie Veals
//------------------------------------------------------------

#ifndef _CCOIN_H
#define _CCOIN_H

//------------------------------------------------------------

#include "Drawable.h"


//------------------------------------------------------------

class Ccoin:public Drawable{
    
    //------------------------------------------------------------
    
private:
    GLuint texture_[4];
    void sprite();
    int texturePos;
    int count_;
public:
	Ccoin()
    {
        texturePos = 0;
        count_ = 0;
        sprite(); 
    }
    
	virtual ~Ccoin()
	{
        
	}
    
	// OpenGL abstract method to draw object
	virtual void draw(bool update);
	// Returns object type COIN
	int objectType() { return BACKGROUND; }
};



#endif