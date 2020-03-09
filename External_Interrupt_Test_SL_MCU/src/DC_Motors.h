/*
 * DC_Motors.h
 *
 * Created: 2/5/2020 1:49:35 PM
 *  Author: VKaiser
 */ 


#ifndef DC_MOTORS_H_
#define DC_MOTORS_H_

#include "main.h"

void configMotors(void);
void motorCW(int NumSpeed);
void motorCCW(int NumSpeed);

void motorHOME(void);

#endif /* DC_MOTORS_H_ */