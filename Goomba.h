/*
 *  Goomba.h
 *  Movable
 *
 *  Created by Jeremy Sampson on 2/7/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __GOOMBA_H__
#define __GOOMBA_H__

//---------------------------------------------------------

#include "Walking.h"

//---------------------------------------------------------

class Goomba: public Walking {
    
public:
    // constructor
    Goomba();
    // destructor
    ~Goomba();
    
    // instance vars
    
    // point value if killed by mario
    int pointValue_;
    
    // methods
    
    // openGL draw method
    virtual void draw()=0;
    
};

//---------------------------------------------------------

#endif // _TURTLE_H