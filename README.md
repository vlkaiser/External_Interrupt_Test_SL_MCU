# External_Interrupt_Test_SL_MCU
External_Interrupt_Test_SL_MCU I2C cdevelopment

Intent:
Slave board will manage the motor controllers.

I2C write command from master:
- I2C Write triggers interrupt handler
- Read command structure
- Execute command issued
	- Send data to motor controller card
	- Recieve or otherwise verify execution
- Host return data on buffer for Master to read on poll 

Elements:
1. Motor Control
2. I2C Slave write request interrupt
3. I2C Read response
4. Command processing 
5. External interrupt - eg limit switches

Motor Control:
CVD215-K, CVD 2-Phase Bipolar Driver
Oriental Motors Motor

