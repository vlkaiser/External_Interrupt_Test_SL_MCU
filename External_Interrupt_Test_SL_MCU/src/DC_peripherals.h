/*
 * DC_peripherals.h
 *
 * Created: 3/9/2020 3:33:28 PM
 *  Author: VKaiser
 */ 


#ifndef DC_PERIPHERALS_H_
#define DC_PERIPHERALS_H_

#include "main.h"


void config_whoami(void);
void sys_config(void);

void configure_extint_channel(void);
void configure_extint_callbacks(void);
void extint_detection_callback_limitSW(void);


#endif /* DC_PERIPHERALS_H_ */