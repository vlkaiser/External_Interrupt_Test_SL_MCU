/*
 * DC_sercom.c
 *
 * Created: 1/31/2020 11:37:42 AM
 *  Author: VKaiser
 */ 
#include "DC_sercom.h"

 /* Timeout counter. */
 uint16_t timeout = 0;

 /**********************************************************************
 * @fn					- configure_i2c_slave
 * @brief				- Set up the I2C slave Module
 *
 * @param[in]			- N/A
 * @return				- void
 *
 * @note				- Initialization
 **********************************************************************/
  void configure_i2c_slave(void)
  {
	  /* Initialize config structure and software module. */
	  i2c_slave_get_config_defaults(&config_i2c_slave);

	  /* Change buffer timeout to something longer. */
	  config_i2c_slave.buffer_timeout = 10000;

	  /* Initialize and enable device with config. */
	  // SERCOM0 PAD[0] PA08 - SDA
	  // SERCOM0 PAD[1] PA09 - SCL
	  config_i2c_slave.pinmux_pad0    = PINMUX_PA08D_SERCOM2_PAD0;
	  config_i2c_slave.pinmux_pad1    = PINMUX_PA09D_SERCOM2_PAD1;
	  
	  i2c_slave_init(&i2c_slave_instance, SERCOM2, &config_i2c_slave);
	  i2c_slave_enable(&i2c_slave_instance);

  }// configure_i2c_master





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

	configure_i2c_slave();
}