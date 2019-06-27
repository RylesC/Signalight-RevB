/*
 * LP55231.c
 *
 * Created: 2018-04-11 1:12:45 PM
 * Author: Riley
 */ 
 
#include <stdint-gcc.h>	
#include <stdbool.h>
#include <driver_init.h>
#include <compiler.h>
#include <LP55231.h>
#include <main.h>
#include <i2c_simple_master.h>
	
	void LP55231_init(){

	}

	void LP55231_SetLogBrightness(uint8_t channel, bool state)
	{
	
	uint8_t regVal, bitVal;
		if(channel > 9){
		return;
		}
		regVal = I2C_0_read1ByteRegister(LP55231_ADDRESS_R, LED1_REG + channel -1);
		bitVal = state?0x20:0x00;
		regVal &= ~0x20;
		regVal |= bitVal;

		I2C_0_write1ByteRegister(LP55231_ADDRESS_W, LED1_REG + channel -1, regVal);

	}


	void LP55231_SetDriveCurrent(uint8_t channel, uint8_t level)
	{

		uint8_t regVal, bitVal;
		if(channel > 9)
		{
			return;
		}

		I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x26 + channel -1, level);

	}

	void LP55231_Busy()
	{
	uint8_t val;
		do
		{
		val = I2C_0_read1ByteRegister(LP55231_ADDRESS_R, 0x3A) & 0x20; // start up busy bit
		}
		while(val);
	}

	void LP55231_Enable(){
	volatile uint8_t val;

	I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x00, 0x40); // Enable Chip
	I2C_0_write1ByteRegister(LP55231_ADDRESS_W,0x36,0x03); // Enables internal clock and 
	I2C_0_write1ByteRegister(LP55231_ADDRESS_W,0x36,0x7F); // 01111111


	// then wait to change modes
		do
		{
		val = I2C_0_read1ByteRegister(LP55231_ADDRESS_R, 0x3A) & 0x20; // start up busy bit
		}
		while(val);

		I2C_0_read1ByteRegister(LP55231_ADDRESS_R, 0x3A);
	}
	

	void LP55231_Reset(){
	I2C_0_write1ByteRegister(LP55231_ADDRESS_W,0x3D,0xFF);
	}


	void LP55231_SetPWM(uint8_t LED, uint16_t BRIGHTNESS){

	uint8_t OUTPUT = (BRIGHTNESS *255/100);
	I2C_0_write1ByteRegister(LP55231_ADDRESS_W,LED,OUTPUT); //
	}


	void LP552321_SetFader(uint8_t fader, uint8_t BRIGHTNESS){
	
	volatile uint8_t OUTPUT = (BRIGHTNESS *255/100);
	I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x48, OUTPUT); //
	}


	void LP55231_AddToFader(uint8_t fader, uint8_t LED){

	volatile uint8_t data,reg;

	if(fader > 3 || LED > 9){
	return;
	}

	reg= I2C_0_read1ByteRegister(LP55231_ADDRESS_R, (0x05 + LED));

	data = (fader << 6);
	reg &= ~0xc0;
	reg |= data;
	I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x05 + LED,reg);
	reg= I2C_0_read1ByteRegister(LP55231_ADDRESS_R, (0x05 + LED));

	}

	void LP55231_WaitForBusy()
	{
		volatile uint8_t val;

		// then wait to change modes
		do
		{
			val = I2C_0_read1ByteRegister(LP55231_ADDRESS_R, 0x3A) & 0x10; // engine busy bit
		}
		while(val);

	}
	


	void LP55231_LoadProgram(uint16_t *program, uint8_t len)
	{
		volatile uint8_t val, data;
		volatile uint8_t p;
		volatile uint16_t check;

		if(len >= 96)
		{
		return;
		}

		I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x00, 0x40);
		I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x01, 0x00);
		LP55231_WaitForBusy();
		I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x01, 0x14);
		LP55231_WaitForBusy();
		
		for (p = 0; p <= len/64; p++)
		{
		I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x4f, p);
			
			for(uint8_t i = 0; i < 16; i = i + 2) 
			{


			data = ((program[i/2 + p*16] >> 8 ) & 0xff);

			LP55231_WaitForBusy();

			I2C_0_write1ByteRegister(LP55231_ADDRESS_W, (0x50 + i), data);
			
			LP55231_WaitForBusy();

			data = ((program[i/2 + p*16]) & 0xff);

			I2C_0_write1ByteRegister(LP55231_ADDRESS_W, (0x51 + i), data);

			LP55231_WaitForBusy();
			}
		}

	}

	void LP55231_SetEngineModeFree(uint8_t engine){

	volatile uint8_t val;
	
	val = I2C_0_read1ByteRegister(LP55231_ADDRESS_R, 0x00);
	
	I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x00, 0x40);

	val &= ~0x30 >> ((engine-1)*2);

	val |= 0x20 >> ((engine-1)*2);

	I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x00, val);


	}

	void LP55231_SetEngineRunning(uint8_t engine)
	{
	uint8_t mask = 0x00;

	switch(engine){
	case 1:
		mask |= 0x20;
		break;
	case 2:
		mask |= 0x08;
		break;
	case 3:
		mask |= 0x02;
		break;
	default:
		break;
	}

	I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x4C, 0x00);
	I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x37, 0x00);
	I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x01, 0x00);
	I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x01, mask);
	}


	void LeftTurn()
	{
	LP55231_LoadProgram(program1, sizeof(program1));
	LP55231_SetEngineModeFree(1);
	LP55231_SetEngineRunning(1);
	}

	void RightTurn()
	{
	LP55231_LoadProgram(program2, sizeof(program2));
	LP55231_SetEngineModeFree(1);
	LP55231_SetEngineRunning(1);
	}

	void NoTurn()
	{
	LP55231_LoadProgram(program3, sizeof(program3));
	LP55231_SetEngineModeFree(1);
	LP55231_SetEngineRunning(1);
	}

	void BatteryCheck()
	{
	
	LP55231_Clear();
	I2C_0_write1ByteRegister(LP55231_ADDRESS_W, 0x00, 0x40);
	volatile uint16_t lp1, lp2;
	
	
	lp1 =  ADC_0_get_conversion(0);
	lp2 =  ADC_0_get_conversion(0);
	battery = ADC_0_get_conversion(0);

	battery = (battery + lp1 + lp2)/3;

	LP55231_SetPWM(0x16,50);
	
	if(battery > 865)
	{
	LP55231_SetPWM(0x1e,50);
	}
	if(battery > 844)
	{
	LP55231_SetPWM(0x17,50);
	}
	if(battery > 827)
	{
	LP55231_SetPWM(0x1d,50);
	}
	if(battery > 812)
	{
	LP55231_SetPWM(0x1c,50);
	}
	if(battery > 791)
	{
	LP55231_SetPWM(0x1b,50);
	}
	if(battery > 770)
	{
	LP55231_SetPWM(0x1a,50);
	}
	if(battery > 759)
	{
	LP55231_SetPWM(0x18,50);
	}
	}

	void LP55231_Clear()
	{
	LP55231_LoadProgram(program7, sizeof(program7));
	LP55231_SetEngineModeFree(1);
	LP55231_SetEngineRunning(1);
	
	LP55231_WaitForBusy();
	//count = 0;
	//while(count < 100){}
	}