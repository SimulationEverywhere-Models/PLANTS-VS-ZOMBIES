/********************************************************
*	DESCRIPTION	: Atomic model Health
*
*	AUTHOR		: Wang Xiang
*
*	DATE		: 20-10-2010
*
*
********************************************************/


#ifndef HEALTH_H
#define HEALTH_H

//****    file includes    *********/
#include "atomic.h"



class Health : public Atomic
{

public:

	Health(const string &name = "Health");
	virtual string className() const
		{return "Health";}


protected:

	Model &initFunction();

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage &);


private:

	const Port &hit;
	Port &death;
	static const int zombieHealth = 5;

	int HP;

	bool sent;

}; //Class Health

#endif  //_HEALTH_H
