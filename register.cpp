/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Wang Xiang
*
*  EMAIL: wxiang@connect.carleton.ca
*
*  DATE: 20-10-2010
*
*******************************************************************/

#include "modeladm.h"
#include "mainsimu.h"
#include "bulletgenerator.h"       	// class BulletGenerator
#include "health.h"					// class Health
#include "speed.h"					// class speed
#include "bite.h"					// class bite
#include "yard.h"					// class map


void MainSimulator::registerNewAtomics()
{
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<BulletGenerator>() , "BulletGenerator" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Health>() , "Health" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Speed>() , "Speed" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Bite>() , "Bite" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Yard>() , "Yard" ) ;
}
