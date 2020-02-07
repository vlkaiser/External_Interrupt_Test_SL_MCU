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
	configMotors();
	
	while(1)
	{
		/* Process new Data */
		if(flgcmdRx == TRUE)
		{
			//Reset Flag
			flgcmdRx = FALSE;	
			
			//TODO: Either set cmd_resp and reply as MS Polls for i2cread, 
			// Or setup GPIO between MS/SL to indicate dataReady
			cmd_resp.encoderLoc = 0;
			cmd_resp.lastCmdStatus = 0;
			cmd_resp.config = 0;
			cmd_resp.motorStatus = 0;
			cmd_resp.status = dWAIT;


			//copy command struct
			cmd_processed = cmd_sent;
			
			//clear cmd_sent buf
			cmd_sent.cmdID = 0;
			cmd_sent.encLocMoveTo = 0;

			port_pin_toggle_output_level(STATUSLED);
			
			switch(cmd_processed.cmdID)
			{
				case PWR_UP:	
					motorCW(50);
					cmd_resp.status = dRDY;
					cmd_resp.encoderLoc = endPwrUp;
					break;

				case PWR_DWN:
					motorCW(50);
					break;
					cmd_resp.status = dRDY;
					cmd_resp.encoderLoc = endPwrDown;			
				case MEAS_ST:
					motorCCW(50);
					cmd_resp.status = dRDY;
					cmd_resp.encoderLoc = endMeas;
					break;
				
				case ESTP:
					port_pin_set_output_level(STATUSLED, HIGH);
					delay_ms(500);
					port_pin_set_output_level(STATUSLED, LOW);
					cmd_resp.status = dRDY;
					cmd_resp.encoderLoc = endESTOP;
					break;

				default:
					break;
			}
			
		}

		//if( port_pin_get_input_level(BUTTON_0_PIN) == SW0_ACTIVE )
		if( port_pin_get_input_level(PBTN) == HIGH )
		{
			//port_pin_toggle_output_level(LED0);
			port_pin_toggle_output_level(STATUSLED);
			//delay_ms(100);
			motorCW(500);
		}
		else
		{
			port_pin_set_output_level(STATUSLED, LOW);
			port_pin_toggle_output_level(LED0);
			delay_ms(100);
			port_pin_set_output_level(DIR_PIN, LOW);
			port_pin_set_output_level(PLS_PIN, LOW);
		}
		
	}
	
}
