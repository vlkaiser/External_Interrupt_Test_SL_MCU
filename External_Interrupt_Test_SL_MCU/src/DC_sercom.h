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

#define CONF_I2C_SLAVE_MODULE   SERCOM2		//SERCOM port
//#define SLAVE_ADDRESS 0x12
#define SLAVE_ADDRESS			0x1A		//Address of the slave

__vo uint8_t rx_buffer[MAX_RX_BUFFER_LENGTH];

struct i2c_slave_module i2c_slave_instance;
struct i2c_slave_config config_i2c_slave;
struct i2c_slave_packet rw_packet;

//! [packet_data]
#define DATA_LENGTH 10
static uint8_t write_buffer[DATA_LENGTH] = { 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xAA, 0xAB, 0xAC, 0xAD };
static uint8_t read_buffer [DATA_LENGTH];

/******************* Prototypes *******************/

void configure_i2c_slave(void);
void configure_i2c_slave_callbacks(void);
void i2c_write_complete_callback(struct i2c_slave_module *const module);
void i2c_read_request_callback(	struct i2c_slave_module *const module);
void i2c_write_request_callback( struct i2c_slave_module *const module);

void sys_config(void);

#endif /* DC_SERCOM_H_ */