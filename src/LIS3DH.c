/*
 * LIS3DH.c
 *
 * Created: 2018-04-25 6:14:51 PM
 *  Author: Riley
 */ 
 
 #include <stdint-gcc.h>
 #include <stdbool.h>
 #include <LP55231.h>
 #include <LIS3DH.h>
 #include <i2c_simple_master.h>


void LIS3DH_init(){
	LIS3DH_EnAxis();
	LIS3DH_SetDataRate(LIS3DH_DATARATE_100_HZ);
	LIS3DH_SetRange(LIS3DH_RANGE_2_G);
}

 uint8_t LIS3DH_Check()
 {
 volatile uint8_t x = I2C_0_read1ByteRegister((LIS3DH_ADDRESS  | 0x01), LIS3DH_REG_WHOAMI);

 return x;
 }


void LIS3DH_EnAxis()
{
I2C_0_write1ByteRegister(LIS3DH_ADDRESS, LIS3DH_REG_CTRL1, 0x07);
}


void LIS3DH_SetDataRate(lis3dh_dataRate_t DataRate)
{

uint8_t ctrl1 = I2C_0_read1ByteRegister(LIS3DH_ADDRESS  | 0x01, LIS3DH_REG_CTRL1);

ctrl1 &= ~(0xf0);
ctrl1 |= (DataRate << 4);
I2C_0_write1ByteRegister(LIS3DH_ADDRESS, LIS3DH_REG_CTRL1, ctrl1);

}


void LIS3DH_SetRange(lis3dh_range_t range)
{
  uint8_t r = I2C_0_read1ByteRegister(LIS3DH_ADDRESS | 0x01, LIS3DH_REG_CTRL4);
  r &= ~(0x30);
  r |= range << 4;
 I2C_0_write1ByteRegister(LIS3DH_ADDRESS, LIS3DH_REG_CTRL4, r);
}

uint16_t LIS3DH_ReadX()
{
uint16_t temp = 0x0000;
uint16_t data = I2C_0_read2ByteRegister(LIS3DH_ADDRESS  | 0x01, (LIS3DH_REG_OUT_X_L | 0x80));

temp |= (data >> 8);
temp &= ~(0xff00);
temp |= data << 8;
data = temp;

return data;
}


uint16_t LIS3DH_ReadY()
{
uint16_t temp = 0x00;
uint16_t data = I2C_0_read2ByteRegister(LIS3DH_ADDRESS  | 0x01, (LIS3DH_REG_OUT_Y_L | 0x80));

temp |= (data >> 8);
temp &= ~(0xff00);
temp |= data << 8;
data = temp;
return data;
}

uint16_t LIS3DH_ReadZ()
{
uint16_t temp = 0x00;
uint16_t data = I2C_0_read2ByteRegister(LIS3DH_ADDRESS  | 0x01, (LIS3DH_REG_OUT_Z_L | 0x80));

temp |= (data >> 8);
temp &= ~(0xff00);
temp |= data << 8;
data = temp;
return data;
}
