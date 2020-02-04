/*
 * DC_sercom.h
 *
 * Created: 1/31/2020 11:37:31 AM
 *  Author: VKaiser
 */ 


#ifndef DC_SERCOM_H_
#define DC_SERCOM_H_

#include "main.h"

struct cmd_issued
{
	uint32_t encLocMoveTo;
	uint8_t cmdID;
	
};
struct cmd_issued cmd_sent;

	struct cmd_response
	{
	uint32_t encoderLoc;

	uint8_t lastCmdRxd;
	uint8_t lastCmdStatus;
	uint8_t ID;
	uint8_t config;
	uint8_t status;
	uint8_t motorStatus;
	
	/*
	uint32_t voltage5V;
	uint32_t current5V;
	uint32_t peakCurrent5V;
	uint32_t voltage24V;
	uint32_t current24V;
	uint32_t peakCurrent24V;
	uint32_t voltage400V;		//future
	uint32_t current400V;		//future
	uint32_t peakCurrent400V;	//future

	uint32_t pcbTemp;
	*/
	};

struct cmd_response cmd_resp;
struct cmd_response cmd_resp_copy;


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