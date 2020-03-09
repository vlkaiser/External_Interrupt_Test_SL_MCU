/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

#if defined(__GNUC__)
void board_init(void) WEAK __attribute__((alias("system_board_init")));
#elif defined(__ICCARM__)
void board_init(void);
#  pragma weak board_init=system_board_init
#endif

 void config_led(void);
 void config_btn(void);
 void config_GPIO(void);

/******************************************************************************************************
 * @fn					- config_led
 * @brief				- Configure led0, turn it off
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
 void config_led(void)
 {
	 struct port_config pin_conf;
	 port_get_config_defaults(&pin_conf);

	 pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	 port_pin_set_config(LED_0_PIN, &pin_conf);
	 port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
 }

 void config_GPIO(void)
 {
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);

	pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED_0_PIN, &pin_conf);
	port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);

	pin_conf.direction  = PORT_PIN_DIR_INPUT;
	port_pin_set_config(I2C_STRAP_0, &pin_conf);
	pin_conf.input_pull = PORT_PIN_PULL_DOWN;

	pin_conf.direction  = PORT_PIN_DIR_INPUT;
	port_pin_set_config(I2C_STRAP_1, &pin_conf);
	pin_conf.input_pull = PORT_PIN_PULL_DOWN;
 }

  /******************************************************************************************************
 * @fn					- config_btn
 * @brief				- Configure btn0 as input
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
#ifdef XPLAINED_PRO
 void config_btn(void)
 {
	 struct port_config pin_conf;
	 port_get_config_defaults(&pin_conf);

	/* Set buttons as inputs */
	pin_conf.direction  = PORT_PIN_DIR_INPUT;
	pin_conf.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(BUTTON_0_PIN, &pin_conf);
 }
#endif

void system_board_init(void)
{
 	/*Configure system tick to generate periodic interrupts */
 	SysTick_Config(system_gclk_gen_get_hz(GCLK_GENERATOR_0));
 	delay_init();

	#ifdef XPLAINED_PRO
	config_led();
	config_btn();
	#endif

	#ifdef ROBOT_SCAN
	config_GPIO();
	#endif

}