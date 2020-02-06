/*
 * DC_sercom.c
 *
 * Created: 1/31/2020 11:37:42 AM
 *  Author: VKaiser
 */ 
#include "DC_sercom.h"

 /*
  * Global Variables
  */
#define MAX_RX_BUFFER_LENGTH	256
#define I2C_SLAVE_ADDRESS		0x18
//#define I2C_DATA_LENGTH		10
#define I2C_TIMEOUT				10

#define CONF_I2C_SLAVE_MODULE   SERCOM2		//SERCOM port
//#define SLAVE_ADDRESS 0x12
//#define SLAVE_ADDRESS			0x1A		//Address of the slave

//__vo uint8_t rx_buffer[MAX_RX_BUFFER_LENGTH];

struct i2c_slave_module i2c_slave_instance;
struct i2c_slave_config config_i2c_slave;
struct i2c_slave_packet rw_packet;

/*
#define DATA_LENGTH 10
static uint8_t write_buffer[DATA_LENGTH] = { 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xAA, 0xAB, 0xAC, 0xAD };
*/
//#define DATA_LENGTH 5
//static uint8_t write_buffer[DATA_LENGTH] = { 0x0A, 0x0B, 0x0C, 0x0D, 0x0E };
//static uint8_t read_buffer [DATA_LENGTH];


 /* Timeout counter. */
 uint16_t timeout = 0;

/******************************************************************************************************
 * @fn					- SysTick_Handler
 * @brief				- SysTick handler interrupt override
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void SysTick_Handler(void)
{
	// Your code goes here
}

/**********************************************************************
 * @fn					- configure_i2c_slave
 * @brief				- Initialize config structure and module instance
 *
 * @param[in]			- 
 * @return				- void
 *
 * @note				- 
 **********************************************************************/
void configure_i2c_slave(void)
{
	/* Initialize config structure and module instance */
	i2c_slave_get_config_defaults(&config_i2c_slave);

	/* Change address and address_mode */
	config_i2c_slave.address      = I2C_SLAVE_ADDRESS;
	config_i2c_slave.address_mode = I2C_SLAVE_ADDRESS_MODE_MASK;

	/* Initialize and enable device with config */
	i2c_slave_init(&i2c_slave_instance, CONF_I2C_SLAVE_MODULE, &config_i2c_slave);

	i2c_slave_enable(&i2c_slave_instance);
}

/**********************************************************************
 * @fn					- configure_i2c_slave_callbacks
 * @brief				- Register and enable callback functions
 *
 * @param[in]			- 
 * @return				- void
 *
 * @note				- 
 **********************************************************************/
void configure_i2c_slave_callbacks(void)
{
	/* Register and enable callback functions */
	i2c_slave_register_callback(&i2c_slave_instance, i2c_read_request_callback,	I2C_SLAVE_CALLBACK_READ_REQUEST);
	i2c_slave_enable_callback(&i2c_slave_instance,	I2C_SLAVE_CALLBACK_READ_REQUEST);

	i2c_slave_register_callback(&i2c_slave_instance, i2c_write_request_callback, I2C_SLAVE_CALLBACK_WRITE_REQUEST);
	i2c_slave_enable_callback(&i2c_slave_instance, I2C_SLAVE_CALLBACK_WRITE_REQUEST);

	i2c_slave_register_callback(&i2c_slave_instance, i2c_write_complete_callback, I2C_SLAVE_CALLBACK_WRITE_COMPLETE);
	i2c_slave_enable_callback(&i2c_slave_instance, I2C_SLAVE_CALLBACK_WRITE_COMPLETE);

	i2c_slave_register_callback(&i2c_slave_instance, i2c_read_complete_callback, I2C_SLAVE_CALLBACK_READ_COMPLETE);
	i2c_slave_enable_callback(&i2c_slave_instance, I2C_SLAVE_CALLBACK_READ_COMPLETE);
}


/**********************************************************************
 * @fn					- i2c_write_complete_callback
 * @brief				- i2c SLAVE write complete triggers this callback
 *
 * @param[in]			- struct i2c_slave_module
 * @param[in]			- *const module
 * @return				- void
 *
 * @note				- MASTER: i2c_read, SLAVE: write-to-buf Complete
 **********************************************************************/
void i2c_write_complete_callback(struct i2c_slave_module *const module)
{
	LED_Toggle(LED0);
	//Never happens
}

/**********************************************************************
 * @fn					- i2c_read_complete_callback
 * @brief				- i2c SLAVE read complete triggers this callback
 *							
 *
 * @param[in]			- struct i2c_slave_module
 * @param[in]			- *const module
 * @return				- void
 *
 * @note				- MASTER: i2c_write, SLAVE: read-into-buf Complete
 *						This is also triggered for master-write-addr prior to read
 **********************************************************************/
void i2c_read_complete_callback(struct i2c_slave_module *const module)
{
	LED_Toggle(LED0);
	if (cmd_sent.cmdID != 0)
	{
		//If new data, set flag to process data.
		flgcmdRx = TRUE;			
	}

}

/**********************************************************************
 * @fn					- i2c_read_request_callback
 * @brief				- i2c master read request triggers this callback
 *
 * @param[in]			- struct i2c_slave_module
 * @param[in]			- *const module
 * @return				- void
 *
 * @note				- I2C Read Callback
 **********************************************************************/
void i2c_read_request_callback(	struct i2c_slave_module *const module)
{
	/* Init i2c packet */
	//rw_packet.data_length = DATA_LENGTH;
	//rw_packet.data        = write_buffer;

	rw_packet.data_length = sizeof(cmd_resp);
	rw_packet.data = (uint8_t *)&cmd_resp;

	/* Write buffer to master */
	i2c_slave_write_packet_job(module, &rw_packet);
	
	//LED_Toggle(LED0);
}

/**********************************************************************
 * @fn					- i2c_write_request_callback
 * @brief				- i2c master write request triggers this callback
 *
 * @param[in]			- struct i2c_slave_module
 * @param[in]			- *const module
 * @return				- void
 *
 * @note				- I2C Write Callback
 **********************************************************************/
void i2c_write_request_callback(struct i2c_slave_module *const module)
{
	/* Init i2c packet */
	//rw_packet.data_length = DATA_LENGTH;
	//rw_packet.data        = read_buffer;
	rw_packet.data_length = sizeof(cmd_sent);
	rw_packet.data = (uint8_t *)&cmd_sent;


	/* Read buffer from master */
	if (i2c_slave_read_packet_job(module, &rw_packet) != STATUS_OK)
	{
	}

}


 /******************************************************************************************************
 * @fn					- sys_config
 * @brief				- Calls all the config functions (called from main.c)
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void sys_config(void)
{
	SysTick_Config(system_gclk_gen_get_hz(GCLK_GENERATOR_0));

	configure_i2c_slave();
	configure_i2c_slave_callbacks();

		cmd_resp.lastCmdRxd = 0x11;
		cmd_resp.lastCmdStatus = 0x22;
		cmd_resp.ID = 0x33;
		cmd_resp.config = 0x44;
		cmd_resp.status = 0x55;
		cmd_resp.motorStatus = 0x66;
		cmd_resp.encoderLoc= 0xAABBCCDD;

}