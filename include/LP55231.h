/*
 * IncFile1.h
 *
 * Created: 2018-04-11 1:10:11 PM
 *  Author: Riley
 */ 

#ifndef LP55231_H_
#define LP55231_H_

	static const uint8_t LP55231_ADDRESS_W = 0x32;
	static const uint8_t LP55231_ADDRESS_R = 0x32;

	static const uint8_t RED1_P =	0x1C;
	static const uint8_t RED2_P =	0x1E;
	static const uint8_t GREEN1_P =	0x17;
	static const uint8_t GREEN2_P =	0x1B;
	static const uint8_t BLUE1_P =	0x16;
	static const uint8_t BLUE2_P =	0x1A;

	static const uint8_t LED1_REG = 0x06;

	static const uint8_t RED1 =		7;
	static const uint8_t RED2 =		9;
	static const uint8_t GREEN1 =	2;
	static const uint8_t GREEN2 =	6;
	static const uint8_t BLUE1 =	1;
	static const uint8_t BLUE2 =	5;

	static const uint8_t FADER1 =	1;
	static const uint8_t FADER2 =	2;
	static const uint8_t FADER3 =	3;


	static const uint16_t program1[] =
	{
		//Program 1 (left turn)
		0x9c10, // 0 map start 0x9x10, 0x9c90 starts at 1
		0x9c90, // 1 map end
		0x40ff, // 2 set PWM
		0x6000, // 3 wait
		0x4000, // 2 set PWM
		0x6000, // 3 wait
		0xa002, // 6 loop to 2
		0x000a, // 7 - empty placeholder
		0x0005, // 8 - empty placeholder
		0x000a, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // e - empty placeholder
		0x000a, // f - empty placeholder
		0x01c3, // 10 map begin - start of 2nd page
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0020, // 8 - empty placeholder
		0x0040, // 7 - empty placeholder
		0x0080, // 8 - empty placeholder
		0x000a, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // e - empty placeholder
		0x000a, // f - empty placeholder
		0x0005, // 1f  map end

	};

	static const uint16_t program2[] =
	{
		//Right turn
		0x9c10, // 0 map start 0x9x10, 0x9c90 starts at 1
		0x9c90, // 1 map end
		0x40ff, // 2 set PWM
		0x6000, // 3 wait
		0x4000, // 2 set PWM
		0x6000, // 3 wait
		0xa002, // 6 loop to 2
		0x000a, // 7 - empty placeholder
		0x0005, // 8 - empty placeholder
		0x000a, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // e - empty placeholder
		0x000a, // f - empty placeholder
		0x00f2, // 10 map begin - start of 2nd page
		0x0180, // 8 - empty placeholder
		0x0002, // 7 - empty placeholder
		0x0008, // 8 - empty placeholder
		0x0010, // 7 - empty placeholder
		0x0020, // 8 - empty placeholder
		0x0040, // 7 - empty placeholder
		0x0080, // 8 - empty placeholder
		0x000a, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // e - empty placeholder
		0x000a, // f - empty placeholder
		0x0005, // 1f  map end

	};

	static const uint16_t program3[] =
	{
		//Right turn
		0x9c10, // 0 map start 0x9x10, 0x9c90 starts at 1
		0x9c90, // 1 map end
		0x400f, // 2 set PWM
		0x9d80, // 5 map next
		0xa002, // 6 loop to 2
		0x000a, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x000a, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // e - empty placeholder
		0x000a, // f - empty placeholder
		0x000a, // f - empty placeholder
		0x0002, // 10 map begin - start of 2nd page
		0x0005, // c - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x000a, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // e - empty placeholder
		0x000a, // f - empty placeholder
		0x0005, // 1f  map end

	};

	static const uint16_t program4[] =
	{
		0x9c10, // 0 map start
		0x9c99, // 1 map end
		0x40ff, // 2 set PWM
		0x5000, // 3 wait
		0x4000, // 4 ramp down
		0x5000, // 3 wait
		0x9d80, // 5 map next
		0xa002, // 6 loop to 2
		0x0005, // 8 - empty placeholder
		0x000a, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // e - empty placeholder
		0x000a, // f - empty placeholder
		0x0001, // 10 map begin - start of 2nd page
		0x0002, // 8 - empty placeholder
		0x0004, // 7 - empty placeholder
		0x0008, // 8 - empty placeholder
		0x0010, // 7 - empty placeholder
		0x0020, // 8 - empty placeholder
		0x0040, // 7 - empty placeholder
		0x0080, // 8 - empty placeholder
		0x0100, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // e - empty placeholder
		0x000a, // f - empty placeholder
		0x0002, // 1f  map end
	};

	static const uint16_t program5[] =
	{
		0x9c10, // 0 map start
		0x9c90, // 1 map end
		0x40ff, // 2 set PWM
		0x5000, // 3 wait
		0x4000, // 4 ramp down
		0x5000, // 3 wait
		0x9d80, // 5 map next
		0xa002, // 6 loop to 2
		0x0005, // 8 - empty placeholder
		0x000a, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // e - empty placeholder
		0x000a, // f - empty placeholder
		0x0022, // 10 map begin - start of 2nd page
		0x0005, // 8 - empty placeholder
		0x000a, // 7 - empty placeholder
		0x0005, // 8 - empty placeholder
		0x000a, // 7 - empty placeholder
		0x0005, // 8 - empty placeholder
		0x000a, // 7 - empty placeholder
		0x0005, // 8 - empty placeholder
		0x000a, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // e - empty placeholder
		0x000a, // f - empty placeholder
		0x0002, // 1f  map end
	};



	static const uint16_t program6[] =
	{
		0x9c10, // 0 map start
		0x9c90, // 1 map end
		0x40ff, // 2 set PWM
		0x5000, // 3 wait
		0x4000, // 4 ramp down
		0x5000, // 3 wait
		0x9d80, // 5 map next
		0xa002, // 6 loop to 2
		0x0005, // 8 - empty placeholder
		0x000a, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // e - empty placeholder
		0x000a, // f - empty placeholder
		0x0173, // 10 map begin - start of 2nd page
		0x0005, // 8 - empty placeholder
		0x000a, // 7 - empty placeholder
		0x0005, // 8 - empty placeholder
		0x000a, // 7 - empty placeholder
		0x0005, // 8 - empty placeholder
		0x000a, // 7 - empty placeholder
		0x0005, // 8 - empty placeholder
		0x000a, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // e - empty placeholder
		0x000a, // f - empty placeholder
		0x0002, // 1f  map end
	};

	static const uint16_t program7[] =
	{
		0x9c10, // 0 map start
		0x9c90, // 1 map end
		0x4000, // 2 set PWM
		0xa002, // 6 loop to 2
		0x0005, // 8 - empty placeholder
		0x000a, // 7 - empty placeholder
		0x0005, // 8 - empty placeholder
		0x000a, // 7 - empty placeholder
		0x0005, // 8 - empty placeholder
		0x000a, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // e - empty placeholder
		0x000a, // f - empty placeholder
		0x0fff, // 10 map begin - start of 2nd page
		0x0122,//0x0022, // 11
		0x0173, // 7 - empty placeholder
		0x0005, // 8 - empty placeholder
		0x000a, // 7 - empty placeholder
		0x0005, // 8 - empty placeholder
		0x000a, // 7 - empty placeholder
		0x0005, // 8 - empty placeholder
		0x000a, // 9 - empty placeholder
		0x0005, // a - empty placeholder
		0x000a, // b - empty placeholder
		0x0005, // c - empty placeholder
		0x000a, // d - empty placeholder
		0x0005, // e - empty placeholder
		0x000a, // f - empty placeholder
		0x0002, // 1f  map end
	};

	void LP55231_Enable();

	void LP55231_Clear();

	void RightTurn();

	void LeftTurn();

	void BatteryCheck();

	void NoTurn();

	void LP55231_LoadProgram(uint16_t *program, uint8_t len);



#endif /* INCFILE1_H_ */