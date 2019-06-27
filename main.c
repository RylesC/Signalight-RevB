#include <atmel_start.h>
#include <LP55231.h>
#include <LIS3DH.h>
#include <i2c_simple_master.h>
#include <main.h>

//volatile uint8_t x1, x2, x3 = 0x00;
//volatile uint16_t x, y, z, w = 0x00;

int16_t hyst = 4000;
int16_t z_on = 6000;
int16_t z_trigger;
int16_t range = 4000;
int16_t  pos = 16384;
int16_t  mid = 0;
int16_t  neg = -16384;

uint16_t N = 32;

uint8_t WindowSize = 32;

int main(void)
{
	int16_t  x_data[64] = {0};
	int16_t  y_data[64] = {0};
	int16_t  z_data[64] = {0};
	uint16_t RingPos = 0;
	/* Initializes MCU, drivers and middleware */
	
	atmel_start_init();

	/* Initialize Accelerometer */
	LIS3DH_init();

	/*Initialize LP55231 */
	LP55231_Enable();

	x = LIS3DH_ReadX();
	y = LIS3DH_ReadY();
	z = LIS3DH_ReadZ();
	
	for (int i = 0; i < 64; i++)
	{
	x_data[i] = x;
	y_data[i] = y;
	z_data[i] = z;
	}

	b_flag = 1;
	int32_t xsum = (int32_t)x << 5;
	int32_t ysum = (int32_t)y << 5;
	int32_t zsum = (int32_t)z << 5;

	while (1) {
	
	if(timer_flag){

		x_data[RingPos] = LIS3DH_ReadX();
		y_data[RingPos] = LIS3DH_ReadY();
		z_data[RingPos] = LIS3DH_ReadZ();
		
		x = MovingAverage(x_data, &xsum, RingPos);
		y = MovingAverage(y_data, &ysum, RingPos);
		z = MovingAverage(z_data, &zsum, RingPos);

		RingPos++;
		if (RingPos >= 64)
		{
		RingPos = 0;
		}
		timer_flag = 0;
	}
	
	
	if(hyst_flag){
	z_trigger = z_on + hyst;
	}
	else{
	z_trigger = z_on;
	}

	if(z > -z_trigger)
	{
		if((x > (pos - range)) && !(y > (pos - range)) && !(y < neg + range) && !r_flag) //Right turn
		{
			LP55231_Clear();
			RightTurn();
			r_flag = 1;
			l_flag = 0;
			b_flag = 0;
			n_flag = 0;
			hyst_flag = 1;
		}
		if((y > (pos - range)) && !(x > (pos - range)) && !(x < neg + range) && !l_flag) //Left turn
		{
			LP55231_Clear();
			LeftTurn();
			l_flag = 1;
			r_flag = 0;
			b_flag = 0;
			n_flag = 0;
			hyst_flag = 1;
		}

		if((y < (neg + range))  && !(x > (pos - range)) && !(x < neg + range) && !b_flag)// battery
		{
			LP55231_Clear();
			BatteryCheck();
			l_flag = 0;
			r_flag = 0;
			b_flag = 1;
			n_flag = 0;
			hyst_flag = 1;
		}
	}
	else
	{
		if((l_flag || r_flag || b_flag) && !n_flag)
		{
		LP55231_Clear();
		NoTurn();
		r_flag = 0;
		l_flag = 0;
		b_flag = 0;
		n_flag = 1;
		hyst_flag = 0;
		}
	}
	}
}

int16_t MovingAverage(int16_t *DataArray, int32_t *sum, uint8_t RingPos){
	
	volatile uint8_t LastPos = 0;
	volatile uint16_t result = 0;

	if(RingPos - 32 < 0){
	LastPos = 64 - 32 + RingPos; 
	}
	else{
	LastPos = RingPos - 32;
	}
		 
	*sum = *sum - (int32_t)DataArray[LastPos] + (int32_t)DataArray[RingPos];

	result = *sum >> 5;

	LastPos = result;

	return (int16_t)result;
}
