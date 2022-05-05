/********************************************************
*	DESCRIPTION	: Atomic model Health
*
*	AUTHOR		: Wang Xiang
*
*	DATE		: 10-20-2010
*
*
********************************************************/


/********** file includes ****************************/

#include "Health.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "randlib.h"         // Random numbers library
#include "message.h"         // InternalMessage
#include "distri.h"          // class Distribution
#include "mainsimu.h"        // class MainSimulator
#include "strutil.h"



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: Health
*
* Description: Constructor
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

Health::Health( const string &name) :
	Atomic(name),
	hit(addInputPort("hit")),
	death(addOutputPort("death")){	}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: Health
*
* Description: Initialization
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

Model &Health::initFunction()
{
	HP = zombieHealth;
	sent = false;

	holdIn(Atomic::active, Time::Zero);
	return *this ;
};


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: external function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &Health::externalFunction(const ExternalMessage &msg){

	if((msg.port() == hit) && (msg.value() == 1) && (HP > 0)) {
		HP -= 1;
	}

	holdIn(Atomic::active, Time::Zero);
return *this;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: internal function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &Health::internalFunction(const InternalMessage & )
{
	passivate();
	return *this;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: output function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &Health::outputFunction(const InternalMessage &msg)
{
	if ((HP == 0) && !sent){
		this->sendOutput(msg.time(), death, 1);
		sent = true;
	}
	return *this;
}
