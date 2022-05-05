/********************************************************
*	DESCRIPTION	: Atomic model Yard
*
*	AUTHOR		: Wang Xiang
*
*	DATE		: 10-20-2010
*
*
********************************************************/


/********** file includes ****************************/

#include "yard.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "randlib.h"         // Random numbers library
#include "message.h"         // InternalMessage
#include "distri.h"          // class Distribution
#include "mainsimu.h"        // class MainSimulator
#include "strutil.h"



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: Yard
*
* Description: Constructor
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

Yard::Yard( const string &name) :
	Atomic(name),
	forward(addInputPort("forward")),
	death(addInputPort("death")),
	bites(addInputPort("bites")),
	success(addOutputPort("success")),
	eaten(addOutputPort("eaten")),
	encounter(addOutputPort("encounter")){	}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: Yard
*
* Description: Initialization
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

Model &Yard::initFunction()
{
	dead = false;
	sentSuccess = false;
	sentEncounter = false;
	sentEaten = false;

	//Deploy a zombie at a random location on the map (x,y)
	x = (int)(rand()/(double)RAND_MAX * yardLength);
	y = (int)(rand()/(double)RAND_MAX * yardWidth);
	cout<<x<<endl;
	cout<<y<<endl;

	plantHP = plantHealth;

	Time t(00,00,05,00);
	holdIn(Atomic::active, t);
	return *this ;
};


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: external function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &Yard::externalFunction(const ExternalMessage &msg)
{
	if ((msg.port() == death) && (msg.value() == 1)) {dead = true;}

	//SingleZombie model informing Yard to decrease plant's health
	//If receiving a bite signal, the zombie should not still be moving
	if((msg.port() == bites) && (msg.value() == 1) && (plantHP > 0)) {
		plantHP -= 1;
	}else{
		if((msg.port() == forward) && (msg.value() == 1) && (x > 0))
		{x -= 1;}
	}

	holdIn(Atomic::active, Time::Zero);
	return *this;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: internal function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &Yard::internalFunction(const InternalMessage & )
{
	passivate();
	return *this;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: output function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &Yard::outputFunction(const InternalMessage &msg)
{
	if (dead){
		if (!sentSuccess){
			this->sendOutput(msg.time(), success, 0);
			sentSuccess = true;
		}
	}else{
		if ((x == 1) && (plantHP > 0) && (!sentEncounter)){
			this->sendOutput(msg.time(), encounter, 1);
			sentEncounter = true;
		}else{
			if ((plantHP == 0) && (!sentEaten)){
				this->sendOutput(msg.time(), eaten, 1);
				sentEaten = true;
			}
		}

		if ((x == 0) && (!sentSuccess)){
			this->sendOutput(msg.time(), success, 1);
			sentSuccess = true;
		}
	}
	return *this;
}
