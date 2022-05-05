/********************************************************
*	DESCRIPTION	: Atomic model bullet generator
*
*	AUTHOR		: Wang Xiang
*
*	DATE		: 20-10-2010
*
*
********************************************************/


#ifndef BULLETGENERATOR_H
#define BULLETGENERATOR_H

//****    file includes    *********/
#include "atomic.h"



class BulletGenerator: public Atomic
{

public:
	BulletGenerator(const string &name = "BulletGenerator");

	virtual string className() const
		{return "BulletGenerator";}


protected:
	Model &initFunction();

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage &);


private:
	Port &bulletOut;


}; //Class BulletGenerator

#endif  //_BULLETGENERATOR_H
