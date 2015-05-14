/**
 *
 *	Colorduino - Colorduino Library for Arduino V1.1
 *	Copyright (c) 2011 Sam C. Lin lincomatic@hotmail.com ALL RIGHTS RESERVED
 *	based on C code by zzy@iteadstudio
 *		Copyright (c) 2010 zzy@IteadStudio.	All right reserved.
 *	
 *	This library is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU Lesser General Public
 *	License as published by the Free Software Foundation; either
 *	version 2.1 of the License, or (at your option) any later version.
 *	
 *	This library is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *	Lesser General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with this library; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA, 02110-1301, USA
 *
 */


#include "Colorduino.h"



// global instance
ColorduinoObject Colorduino;



//-----------------------------------------------------------------------------
// methods
//-----------------------------------------------------------------------------
ISR(TIMER2_OVF_vect) {
	//Timer2	Service
	//
	// ISR fires every 256-TCNT2 ticks
	// so if TCNT2 = 100, ISR fires every 156 ticks
	// prescaler = 128 so ISR fires every 16MHz / 128 = 125KHz
	// 125KHz / 156 = 801.282Hz / 8 rows = 100.16Hz refresh rate
	// if TCNT2 = 61, ISR fires every 256 - 61 = 195 ticks
	// 125KHz / 195 = 641.026Hz / 8 rows = 80.128Hz refresh rate
	//	TCNT2 = 100;
	TCNT2 = 61;
	close_all_lines;
	Colorduino.run();
	Colorduino.open_line(Colorduino.line);
	if (++Colorduino.line > 7) Colorduino.line = 0;
}
/**
 *	the LED Hardware operate functions zone
 */



/**
 *	the LED datas operate functions zone
 */
void ColorduinoObject::run() {
	LED_SLB_SET;
	LED_LAT_CLR;
	ColorRGB * pixel = GetDrawPixel(0, line);

	for (unsigned char x = 0; x < ColorduinoScreenWidth; x++) {
		unsigned char temp = pixel ->b;
		unsigned char p;

		for (p = 0; p < ColorduinoBitsPerColor; p++) {
			if (temp & 0x80)
			LED_SDA_SET;
			else
			LED_SDA_CLR;
			temp <<= 1;
			LED_SCL_CLR;
			LED_SCL_SET;
		}
		temp = pixel ->g;

		for (p = 0; p < ColorduinoBitsPerColor; p++) {
			if (temp & 0x80)
			LED_SDA_SET;
			else
			LED_SDA_CLR;
			temp <<= 1;
			LED_SCL_CLR;
			LED_SCL_SET;
		}
		temp = pixel ->r;

		for (p = 0; p < ColorduinoBitsPerColor; p++) {
			if (temp & 0x80)
			LED_SDA_SET;
			else
			LED_SDA_CLR;
			temp <<= 1;
			LED_SCL_CLR;
			LED_SCL_SET;
		}
		pixel++;
	}
	LED_LAT_SET;
	LED_LAT_CLR;
}


//-----------------------------------------------------------------------------
void ColorduinoObject::LED_Delay(unsigned char i) {
	unsigned int y;
	y = i * 10;
	while (y--);
}



/*
int main() {
	string hexColor;
	vector < unsigned char > rgbColor(3);
	cout << "Enter Hex value (must be 6 valid Hex digits): 0x";
	cin >> hexColor;
	HextoDec(hexColor, rgbColor);
	cout << "\nWhen 0x" << hexColor << " is converted to RGB, it becomes:" << endl;
	cout << "R: " << int(rgbColor[0]) << endl;
	cout << "G: " << int(rgbColor[1]) << endl;
	cout << "B: " << int(rgbColor[2]) << endl;
	system("pause");
}
*/



//-----------------------------------------------------------------------------
// sets
//-----------------------------------------------------------------------------
void ColorduinoObject::SetWhiteBal(unsigned char wbval[3]) {
	// compensate for relative intensity differences in R/G/B brightness
	// array of 6-bit base values for RGB (0~63)
	// wbval[0]=red
	// wbval[1]=green
	// wbval[2]=blue
	LED_LAT_CLR;
	LED_SLB_CLR;
	for (unsigned char k = 0; k < ColorduinoScreenHeight; k++)
	for (unsigned char i = 3; i > 0; i--) {
		unsigned char temp = wbval[i - 1] << 2;
		for (unsigned char j = 0; j < 6; j++) {
			if (temp & 0x80)
			LED_SDA_SET;
			else
			LED_SDA_CLR;

			temp = temp << 1;
			LED_SCL_CLR;
			LED_SCL_SET;
		}
	}
	LED_SLB_SET;
}
