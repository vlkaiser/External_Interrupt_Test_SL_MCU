/*
 * DC_sercom.h
 *
 * Created: 1/31/2020 11:37:31 AM
 *  Author: VKaiser
 */ 


#ifndef DC_SERCOM_H_
#define DC_SERCOM_H_

#include "main.h"




/******************* Prototypes *******************/

void configure_i2c_slave(void);
void configure_i2c_slave_callbacks(void);
void i2c_write_complete_callback(struct i2c_slave_module *const module);
void i2c_read_complete_callback(struct i2c_slave_module *const module);
void i2c_read_request_callback(	struct i2c_slave_module *const module);
void i2c_write_request_callback( struct i2c_slave_module *const module);

void sys_config(void);

//void setFlag(void);

#endif /* DC_SERCOM_H_ */