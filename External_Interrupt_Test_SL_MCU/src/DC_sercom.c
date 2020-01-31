/*
 * DC_sercom.c
 *
 * Created: 1/31/2020 11:37:42 AM
 *  Author: VKaiser
 */ 
#include "DC_sercom.h"

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
	config_i2c_slave.address      = SLAVE_ADDRESS;
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
	rw_packet.data_length = DATA_LENGTH;
	rw_packet.data        = write_buffer;

	/* Write buffer to master */
	i2c_slave_write_packet_job(module, &rw_packet);
	/*
	while( i2c_slave_write_packet_wait(module, &rw_packet) )
	{
			// Increment timeout counter and check if timed out. 
			if (timeout++ == I2C_TIMEOUT) {
				return -1;
				break;
			}
	}
	*/
	LED_Toggle(LED0);
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
	rw_packet.data_length = DATA_LENGTH;
	rw_packet.data        = read_buffer;


	
	/* Read buffer from master */
	i2c_slave_read_packet_job(module, &rw_packet);
	/*
	while( i2c_slave_read_packet_wait(module, &rw_packet) != STATUS_OK )
		{
			// Increment timeout counter and check if timed out. 
			if (timeout++ == I2C_TIMEOUT) {
				return -1;
				break;
			}
		}
		*/
	LED_Toggle(LED0);
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
}