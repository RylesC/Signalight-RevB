/*
 * mian.h
 *
 * Created: 2018-04-26 12:55:44 PM
 *  Author: Riley
 */ 


#ifndef MAIN_H_
#define MAIN_H_


volatile uint8_t PushFlag;
volatile uint8_t TimerCount, charge; 
volatile int16_t x, y , z, battery, count;
volatile uint8_t r_flag, l_flag, b_flag, battery_flag, Stat, button_count, startup_flag, timer_flag, hyst_flag, n_flag;
uint16_t m;

volatile uint8_t t;


int16_t MovingAverage(int16_t *DataArray,int32_t *sum, uint8_t pos);

#endif /* MIAN_H_ */