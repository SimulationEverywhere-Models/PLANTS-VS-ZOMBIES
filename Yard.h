/********************************************************
*	DESCRIPTION	: Atomic model Yard
*
*	AUTHOR		: Wang Xiang
*
*	DATE		: 20-10-2010
*
*
********************************************************/


#ifndef YARD_H
#define YARD_H

//****    file includes    *********/
#include "atomic.h"



class Yard : public Atomic
{

public:

	Yard(const string &name = "Yard");
	virtual string className() const
		{return "Yard";}


protected:

	Model &initFunction();

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage &);


private:

	const Port &forward, &death, &bites;
	Port &encounter, &eaten, &success;

	static const int yardLength = 10;
	static const int yardWidth = 5;

	static const int plantHealth = 5;

	int x, y, plantHP;

	bool dead;
	bool sentSuccess, sentEncounter, sentEaten;

}; //Class Yard

#endif  //_YARD_H
