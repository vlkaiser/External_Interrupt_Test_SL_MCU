/*
 * CFile1.c
 *
 * Created: 2/5/2020 1:49:09 PM
 *  Author: VKaiser
 */ 
 #include "DC_Motors.h"

  /******************************************************************************************************
 * @fn					- configMotors()
 * @brief				- Port/pin config for motor driver and encoder signals, pushbutton, status led
 * @param[in]			- void
 * @return				- void
 *
 * @note				- called from main.c - test 
 ******************************************************************************************************/
 void configMotors(void)
 {
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);

	#ifdef XPLAINED_PRO
		pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
		pin_conf.input_pull = PORT_PIN_PULL_NONE;
		port_pin_set_config(DIR_PIN, &pin_conf);
		port_pin_set_config(PLS_PIN, &pin_conf);
		port_pin_set_config(STATUSLED, &pin_conf);
		
		pin_conf.direction  = PORT_PIN_DIR_INPUT;
		port_pin_set_config(PBTN, &pin_conf);
		
		pin_conf.input_pull = PORT_PIN_PULL_UP;
		port_pin_set_config(CHA_ENC, &pin_conf);
		port_pin_set_config(CHB_ENC, &pin_conf);
	#endif

	port_pin_set_output_level(DIR_PIN, LOW);
	port_pin_set_output_level(PLS_PIN, LOW);

 }

/******************************************************************************************************
 * @fn					- motorCCW()
 * @brief				- Move motor Counter Clockwise 
 * @param[in]			- NumSpeed - delay time in ms
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
 void motorCCW(int NumSpeed)
 {

	port_pin_set_output_level(DIR_PIN, HIGH);
	delay_ms(NumSpeed);
	port_pin_set_output_level(PLS_PIN, LOW);
	delay_ms(NumSpeed);
	port_pin_set_output_level(PLS_PIN, HIGH);
	delay_ms(NumSpeed);
	/*
	port_pin_set_output_level(DIR_PIN, LOW);
	delay_ms(NumSpeed);
	port_pin_set_output_level(PLS_PIN, HIGH);
	delay_ms(NumSpeed);
	port_pin_set_output_level(PLS_PIN, LOW);
	delay_ms(NumSpeed);
	*/

 }

 /******************************************************************************************************
 * @fn					- motorCCW()
 * @brief				- Move motor Clockwise 
 * @param[in]			- NumSpeed - delay time in ms
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
 void motorCW(int NumSpeed)
 {
	port_pin_set_output_level(DIR_PIN, HIGH);
	delay_ms(NumSpeed);
	port_pin_set_output_level(PLS_PIN, HIGH);
	delay_ms(NumSpeed);
	port_pin_set_output_level(PLS_PIN, LOW);
	delay_ms(NumSpeed);
 }