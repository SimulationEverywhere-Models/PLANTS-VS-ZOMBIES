/********************************************************
*	DESCRIPTION	: Atomic model Speed
*
*	AUTHOR		: Wang Xiang
*
*	DATE		: 20-10-2010
*
*
********************************************************/


#ifndef SPEED_H
#define SPEED_H

//****    file includes    *********/
#include "atomic.h"



class Speed : public Atomic
{

public:

	Speed(const string &name = "Speed");
	virtual string className() const
		{return "Speed";}


protected:

	Model &initFunction();

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage &);


private:

	const Port &encounter, &death, &eaten;
	Port &forward;

	bool stop;

}; //Class Speed

#endif  //_SPEED_H
