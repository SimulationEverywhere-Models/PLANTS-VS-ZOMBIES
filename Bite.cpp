/********************************************************
*	DESCRIPTION	: Atomic model Bite
*
*	AUTHOR		: Wang Xiang
*
*	DATE		: 10-20-2010
*
*
********************************************************/


/********** file includes ****************************/

#include "bite.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "randlib.h"         // Random numbers library
#include "message.h"         // InternalMessage
#include "distri.h"          // class Distribution
#include "mainsimu.h"        // class MainSimulator
#include "strutil.h"



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: Bite
*
* Description: Constructor
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

Bite::Bite( const string &name) :
	Atomic(name),
	encounter(addInputPort("encounter")),
	eaten(addInputPort("eaten")),
	bites(addOutputPort("bites")){	}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: Bite
*
* Description: Initialization
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

Model &Bite::initFunction()
{
	start = false;

	holdIn(Atomic::active, Time::Zero);
	return *this ;
};


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: external function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &Bite::externalFunction(const ExternalMessage &msg){

	if((msg.port() == eaten) && (msg.value() == 1)) {
		start = false;
	}else{
		if((msg.port() == encounter) && (msg.value() == 1)) {
			start = true;
		}
	}

	holdIn(Atomic::active, Time::Zero);
return *this;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: internal function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &Bite::internalFunction(const InternalMessage & )
{
	Time biteRate(00,00,02,00);

	holdIn(active, biteRate);
	return *this;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: output function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &Bite::outputFunction(const InternalMessage &msg)
{
	if (start){
		this->sendOutput(msg.time(), bites, 1);
	}
	return *this;
}
