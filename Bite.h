/********************************************************
*	DESCRIPTION	: Atomic model Bite
*
*	AUTHOR		: Wang Xiang
*
*	DATE		: 20-10-2010
*
*
********************************************************/


#ifndef BITE_H
#define BITE_H

//****    file includes    *********/
#include "atomic.h"



class Bite : public Atomic
{

public:

	Bite(const string &name = "Bite");
	virtual string className() const
		{return "Bite";}


protected:

	Model &initFunction();

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage &);


private:

	const Port &encounter, &eaten;
	Port &bites;

	bool start;

}; //Class Bite

#endif  //_BITE_H
