/*
 * DC_sercom.h
 *
 * Created: 1/31/2020 11:37:31 AM
 *  Author: VKaiser
 */ 


#ifndef DC_SERCOM_H_
#define DC_SERCOM_H_

#include "main.h"


 /*
  * Global Variables
  */
#define MAX_RX_BUFFER_LENGTH	5
#define I2C_SLAVE_ADDRESS		0x18
#define I2C_DATA_LENGTH			10
#define I2C_TIMEOUT				10

__vo uint8_t rx_buffer[MAX_RX_BUFFER_LENGTH];

struct i2c_slave_module i2c_slave_instance;
struct i2c_slave_config config_i2c_slave;
struct i2c_slave_packet write_packet;
struct i2c_slave_packet read_packet;

void configure_i2c_slave(void);
void i2c_write_complete_callback(struct i2c_slave_module *const module);
void configure_i2c_callbacks(void);

void sys_config(void);

#endif /* DC_SERCOM_H_ */