/********************************************************
*	DESCRIPTION	: Atomic model Speed
*
*	AUTHOR		: Wang Xiang
*
*	DATE		: 10-20-2010
*
*
********************************************************/


/********** file includes ****************************/

#include "speed.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "randlib.h"         // Random numbers library
#include "message.h"         // InternalMessage
#include "distri.h"          // class Distribution
#include "mainsimu.h"        // class MainSimulator
#include "strutil.h"



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: Speed
*
* Description: Constructor
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

Speed::Speed( const string &name) :
	Atomic(name),
	encounter(addInputPort("encounter")),
	death(addInputPort("death")),
	eaten(addInputPort("eaten")),
	forward(addOutputPort("forward")){	}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: Speed
*
* Description: Initialization
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

Model &Speed::initFunction()
{
	stop = false;

	Time t(00,00,05,00);
	holdIn(Atomic::active, t);
	return *this ;
};


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: external function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &Speed::externalFunction(const ExternalMessage &msg){
/*only one input should be used to change the state of stop.
 * If both encounter and death are received at the same time,
 * any of them should sed stop to true. But if eaten is
 * received with any other input at the same time, the stop
 * variable should be set to true*/

	if((msg.port() == encounter) && (msg.value() == 1)) {
		stop = true;
	}else{
		if((msg.port() == death) && (msg.value() == 1)) {
			stop = true;
		}else{
			if((msg.port() == eaten) && (msg.value() == 1)) {
				stop = false;
			}
		}
	}

	holdIn(Atomic::active, Time::Zero);
return *this;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: internal function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &Speed::internalFunction(const InternalMessage & )
{
	Time zombieSpeed(00,00,05,00);

	holdIn(active, zombieSpeed);
	return *this;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: output function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &Speed::outputFunction(const InternalMessage &msg)
{
	if (!stop){
		this->sendOutput(msg.time(), forward, 1);
	}
	return *this;
}
