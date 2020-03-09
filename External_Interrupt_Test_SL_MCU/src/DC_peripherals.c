/*
 * DC_peripherals.c
 *
 * Created: 3/9/2020 3:34:43 PM
 *  Author: VKaiser
 */ 

 #include <DC_peripherals.h>

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

	config_whoami();	//Determine which motor board is connected to: before i2c_config

	configure_extint_channel();
	configure_extint_callbacks();
	system_interrupt_enable_global();

	configure_i2c_slave();
	configure_i2c_slave_callbacks();

}

/**********************************************************************
 * @fn					- config_whoami
 * @brief				- Determine which motor the board is connected to
 *
 * @param[in]			- N/A
 * @return				- void
 *
 * @note				- Strap0,1 make up - 01: X, 10: Y, 11: Z
 **********************************************************************/
 void config_whoami(void)
 {
	/* TODO: Read the jumpers and determine X, Y, Z motor */
	//uint8_t strap0, strap1;
	__vo uint8_t strap0, strap1, strapID;
	
	strap0 = port_pin_get_input_level(I2C_STRAP_0);
	strap1 = port_pin_get_input_level(I2C_STRAP_1);

	strapID = ( (strap1 << 1) | (strap0) );

	I2C_SL_ADDR = ( I2C_BASE_SL_ADDR | (strapID << 2) );
	cmd_resp.ID = I2C_SL_ADDR;

 }// config_whoami


 /******************************************************************************************************
 * @fn					- configure_extint_channel
 * @brief				- Configure button0 as external interrupt
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void configure_extint_channel(void)
{
	struct extint_chan_conf config_extint_chan;
	extint_chan_get_config_defaults(&config_extint_chan);
	
	config_extint_chan.gpio_pin = LIMIT_SW_EIC_PIN;
	config_extint_chan.gpio_pin_mux = LIMIT_SW_EIC_MUX;
	config_extint_chan.gpio_pin_pull = EXTINT_PULL_UP;
	config_extint_chan.detection_criteria = EXTINT_DETECT_FALLING;
	
	extint_chan_set_config(LIMIT_SW_EIC_LINE, &config_extint_chan);
}

 /******************************************************************************************************
 * @fn					- configure_extint_callbacks
 * @brief				- Link external interrupt to callback routine
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void configure_extint_callbacks(void)
{
	extint_register_callback(extint_detection_callback_limitSW, LIMIT_SW_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(LIMIT_SW_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
}

/******************************************************************************************************
 * @fn					- extint_detection_callback_limitSW
 * @brief				- Callback routine triggered on interrupt
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void extint_detection_callback_limitSW(void)
{
	delay_ms(100);
 }