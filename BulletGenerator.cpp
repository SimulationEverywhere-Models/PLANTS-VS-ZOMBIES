/********************************************************
*	DESCRIPTION	: Atomic model bullet generator
*
*	AUTHOR		: Wang Xiang
*
*	DATE		: 20-10-2010
*
*
********************************************************/


/********** file includes ****************************/

#include "BulletGenerator.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "randlib.h"         // Random numbers library
#include "message.h"         // InternalMessage
#include "distri.h"          // class Distribution
#include "mainsimu.h"        // class MainSimulator
#include "strutil.h"



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: BulletGenerator
*
* Description: Constructor
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

BulletGenerator::BulletGenerator( const string &name) :
	Atomic(name),
	bulletOut( addOutputPort("bulletOut")){
	}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: BulletGenerator
*
* Description: Initialization
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &BulletGenerator::initFunction()
{
	holdIn(Atomic::active, Time::Zero);
	return *this ;
};


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: external function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &BulletGenerator::externalFunction(const ExternalMessage & ){
	  cout<< "we shouldn't see this message no inputs"<<endl;
return *this;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: internal function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &BulletGenerator::internalFunction(const InternalMessage & )
{
	//holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) );
	double x = rand()/(double)RAND_MAX *10;
	cout<<x<<endl;
	Time t(0,0,x,0) ;
	holdIn(active, t);
	return *this;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*Function Name: output function
*
*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
Model &BulletGenerator::outputFunction(const InternalMessage &msg)
{
	this->sendOutput(msg.time(), bulletOut, 1);
	return *this;
}
