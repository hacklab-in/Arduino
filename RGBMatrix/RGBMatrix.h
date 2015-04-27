/* 
 * Copyright 2010 SparkFun Electronic
 * Written by Ryan Owens
*/

#ifndef RGBMatrix_h
#define RGBMatrix_h

#include <avr/pgmspace.h>
#include "WProgram.h"

//Define the SPI Pin Numbers
#define DATAOUT 11		//MOSI
#define DATAIN  12		//MISO 
#define SPICLOCK  13	//sck
#define SLAVESELECT 10	//ss

#define NUM_ROWS	8
#define NUM_COLUMNS	8
#define NUM_PIXELS	64
#define BUFFER	10	//Maximum frame is 8 boards. Buffer can hold an additional char
					//before and after first/last character.

class cRGBMatrix
{
	public:
		/*
			RGB Class constructor
			Sets the number of boards currently connected in the matrix system
			Inputs: int num_boards - The number of boards in the system
			Usage: RGBMatrix myMatrix(NUM_BOARDS);
		*/
		cRGBMatrix(int num_boards);
		cRGBMatrix(void);
		
		/*
			Configures SPI and I/O for communication with an RGB Matrix.
			Note: Pinout should reflect the pin assignments in the RGBMatrix.h file
		*/		
		void begin(int num_boards);
		
		/*
			Sets the color of a pixel on a given matrix
			Inputs: int screen - The specific matrix to have a pixel set
					int row - The row of the pixel to be set
					int column - The column of the pixel to be set
					char color - The color to be used for the pixel fill.
			Returns: 1 - Success
					 0 - Failure (invalid screen, row or column)
		*/
		char fillPixel(int screen, int row, int column, char color);
		
		/*
			Fills a coloumn on a single matrix of the screenBuffer.
			Note: display won't be updated until display() function is called.
			Inputs: int screen - The specific matrix to have a column filled
					int column - The column number to be filled
					char color - The color used for the fill
			Returns: 1 - Success
					 0 - Failure (causes are invalued screen or column number)
		*/		
		char fillColumn(int screen, int column, char color);
		
		/* 
			Fills a row on a single matrix of the screenBuffer.
			Note: display won't be updated until the display() function is called
			Inputs: int screen - The matrix to have a row filled
					int row - The row to be filled
					char color - The color to be used for the fill
			Returns: 1 - Success
					 0 - Failure (invalid screen or row)
		*/		
		char fillRow(int screen, int row, char color);
		
		/*
			Fills a screen in the screenBuffer
			Note: display won't be updated until the display() function is called.
			Inputs: int screen - The screen to be filled
					char color - The color to be used for the fill.
			Returns: 1 - Success
					 0 - Failure (invalid board)
		*/		
		char fillScreen(int screen, char color);
		
		/*
			Puts a character into a posotion in the screenBuffer
			Note: display won't be updated until the display() function is called.
			Inputs: int screen - The matrix that will get the character
					char letter - The letter to put onto the screen
					char color - The color of the letter
			Returns: 1 - Success
		*/		
		char fillChar(int screen, char letter, char color);
		
		/*
			Scrolls an entire message on and off of the frame.
			Inputs: char * message - The message to be scrolled
					char color - The color for the text
					int speed - The scroll speed for the message
		*/		
		char scroll(char * message, char color, int speed);
		
		/*
			Sends the data in screenBuffer to the matrices.
		*/		
		void display(void);
		/*
			Clears the entire frame by filling all the screens with Black
		*/		
		void clear(void);
		
	private:
		/*
			Sends/receives a single byte to the SPI port.
			Inputs: char value - The value to be sent to the SPI port
			Returns: Value received from the SPI port
		*/	
		char spiTransfer(char value);
		
		/*
			Sends the frame of data determined by the screen parameter
			Inputs: char * screen - The 64 byte buffer to send over SPI
		*/		
		void sendScreen(char * screen);

		/*
			Scrolls a single fame onto and off of the frame.
			Inputs: int speed - The scroll speed
		*/		
		void scrollBuffer(int speed);
		int _num_boards;
};

extern cRGBMatrix RGBMatrix;

#endif