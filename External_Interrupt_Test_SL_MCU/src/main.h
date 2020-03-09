/*
 * main.h
 *
 * Created: 1/31/2020 11:06:05 AM
 *  Author: VKaiser
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <asf.h>
#include "user_board.h"
#include "DC_TypeDefs.h"
#include "DC_peripherals.h"
#include "DC_sercom.h"
#include "stdio.h"
#include "string.h"
#include "DC_Motors.h"

/* Globals */

#define I2C_BASE_SL_ADDR			0x12
uint8_t I2C_SL_ADDR;		// THIS BOARD'S SLAVE ADDRESS BASED ON J1, J2 Jumpers

#endif /* MAIN_H_ */