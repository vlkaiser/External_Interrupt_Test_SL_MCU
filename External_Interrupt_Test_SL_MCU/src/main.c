 /******************************************************************************************************
 * @fn					- 
 * @brief				- 
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/

/***************************************************************************************************************************
* Project							: SAMD20 Xplained I2C Master
* Program Name						:
* Author							: vkaiser
* Date Created						: Jan 31 2020
*
* Purpose							: Develop I2C SL on userboard (I2c Callback ASF)
*
*
* MCU								: ATSAMD20J18
* Language							: C
* Hardware Modifications			: N/A
* Debugger							: EDBG (On-board)
*
* Repo / Revision History			: https://github.com/vlkaiser/
*
* - Special Setup -
*  Header files for all drivers that have been imported from Atmel Software Framework (ASF).
*  Use in conjunction with			: SAMD20 Xplained Pro
*  Wiring Details					: PA08, PA09
*  Revision History					:
* 	Date				Author			Notes
* 						vkaiser			- Initial commit
*
***************************************************************************************************************************/
#include <main.h>

int main (void)
{
	system_init();
	sys_config();

	/* Insert application code here, after the board has been initialized. */
	while(1)
	{

		if( port_pin_get_input_level(BUTTON_0_PIN) == SW0_ACTIVE )
		{
			port_pin_toggle_output_level(LED0);
			delay_ms(100);
		}
		else
		{
			port_pin_set_output_level(LED0, ~LED0_ACTIVE);
		}
		
	}
}
