/* 
 * Copyright 2010 SparkFun Electronic
 * Written by Ryan Owens
*/

#include <avr/pgmspace.h>
#include <ctype.h>
#include "RGBMatrix.h"
#include "WProgram.h"
#include "RGB.h"

//A screen struct contains a character array of size 64. Each position in the array
//corresponds to the color of ann LED on the matrix.
typedef struct{
	char pixel[NUM_PIXELS];
} screen;

screen screenBuffer[BUFFER];	//Array of screens that represents the entire frame of matrices(if using a multi-board system)
screen myScreen[BUFFER];		//Array of screens used for scrolling text.
extern const char letters[];	//Get access to the 8X8 font to display letters on the matrix (located in RGB.h)

cRGBMatrix RGBMatrix;	//Create an instance of the class for use in the library

/*
	RGB Class constructor
	Sets the number of boards currently connected in the matrix system
	Inputs: int num_boards - The number of boards in the system
	Usage: RGBMatrix myMatrix(NUM_BOARDS);
*/
cRGBMatrix::cRGBMatrix(int num_boards)
{
	_num_boards=num_boards;
}

cRGBMatrix::cRGBMatrix(void)
{
	//Do Nothing
}

/*
	Configures SPI and I/O for communication with an RGB Matrix.
	Note: Pinout should reflect the pin assignments in the cRGBMatrix.h file
*/
void cRGBMatrix::begin(int num_boards)
{
	_num_boards=num_boards;
    //SPI Bus setup
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);	//Enable SPI HW, Master Mode, divide clock by 16    //SPI Bus setup
	//SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);	//Enable SPI HW, Master Mode, divide clock by 16    //SPI Bus setup
    
    //Set the pin modes for the RGB matrix
    pinMode(DATAOUT, OUTPUT);
    pinMode(DATAIN, INPUT);
    pinMode(SPICLOCK,OUTPUT);
    pinMode(SLAVESELECT,OUTPUT);	
	
	//Make sure the RGB matrix is deactivated
    digitalWrite(SLAVESELECT,HIGH); 		
	//Send the command mode character
    digitalWrite(SLAVESELECT, LOW);
    spiTransfer('%');
    digitalWrite(SLAVESELECT, HIGH);
    delay(100);
	//Configure the correct number of boards
    digitalWrite(SLAVESELECT, LOW);
    spiTransfer(_num_boards);
    digitalWrite(SLAVESELECT, HIGH);
    delay(100);	
}

/*
	Sends/receives a single byte to the SPI port.
	Inputs: char value - The value to be sent to the SPI port
	Returns: Value received from the SPI port
*/
char cRGBMatrix::spiTransfer(char value)
{
    SPDR = value;                    // Start the transmission
    while (!(SPSR & (1<<SPIF)))     // Wait for the end of the transmission
    {
    };
    return SPDR;                    // return the received byte
}

/*
	Sets the color of a pixel on a given matrix
	Note: display won't be updated until display() function is called
	Inputs: int screen - The specific matrix to have a pixel set
			int row - The row of the pixel to be set
			int column - The column of the pixel to be set
			char color - The color to be used for the pixel fill.
	Returns: 1 - Success
			 0 - Failure (invalid screen, row or column)
*/
char cRGBMatrix::fillPixel(int screen, int row, int column, char color)
{
	if((screen > _num_boards) || (screen < 0))return 0;
	if((column < 0) || column > NUM_COLUMNS)return 0;
	if((row < 0) || row > NUM_ROWS)return 0;
	if(color == 0x25 || color == 0x26)return 0;
	
	screenBuffer[screen].pixel[row*8+column]=color;
}

/*
	Fills a coloumn on a single matrix of the screenBuffer.
	Note: display won't be updated until display() function is called.
	Inputs: int screen - The specific matrix to have a column filled
			int column - The column number to be filled
			char color - The color used for the fill
	Returns: 1 - Success
			 0 - Failure (causes are invalued screen or column number)
*/
char cRGBMatrix::fillColumn(int screen, int column, char color)
{
	if((screen > _num_boards) || (screen < 0))return 0;
	if((column < 0) || column > NUM_COLUMNS)return 0;
	if(color == 0x25 || color == 0x26)return 0;
	
    for(int row=0; row<NUM_ROWS; row++)
    {
        screenBuffer[screen].pixel[column+(row*NUM_ROWS)]=color;
    }
	return 1;
}

/* 
	Fills a row on a single matrix of the screenBuffer.
	Note: display won't be updated until the display() function is called
	Inputs: int screen - The matrix to have a row filled
			int row - The row to be filled
			char color - The color to be used for the fill
	Returns: 1 - Success
			 0 - Failure (invalid screen or row)
*/
char cRGBMatrix::fillRow(int screen, int row, char color)
{
	if((screen > _num_boards) || (screen < 0))return 0;
	if((row < 0) || row > NUM_ROWS)return 0;
	if(color == 0x25 || color == 0x26)return 0;
	
    for(int column=0; column<NUM_COLUMNS; column++)
    {
        screenBuffer[screen].pixel[row*NUM_ROWS+column]=color;
    }
	return 1;	
}

/*
	Fills a screen in the screenBuffer
	Note: display won't be updated until the display() function is called.
	Inputs: int screen - The screen to be filled
			char color - The color to be used for the fill.
	Returns: 1 - Success
			 0 - Failure (invalid board)
*/
char cRGBMatrix::fillScreen(int screen, char color)
{
	if((screen < 0) || (screen > _num_boards))return 0;
	if(color == 0x25 || color == 0x26)return 0;

    for(int row=0; row<NUM_ROWS; row++)
    {
        for(int column=0; column<NUM_COLUMNS; column++)
        {
            screenBuffer[screen].pixel[row*NUM_ROWS+column]=color;
        }
    }
	return 1;
}

/*
	Puts a character into a posotion in the screenBuffer
	Note: display won't be updated until the display() function is called.
	Inputs: char * buffer - The screen that will get the character
			char letter - The letter to put onto the screen
			char color - The color of the letter
	Returns: 1 - Success
*/
char cRGBMatrix::fillChar(int screen, char letter, char color)
{
	int letter_offset=0;	//The position of the letter in the letters[] array.
	
	if((screen < 0) || (screen > _num_boards))return 0;
	if(color == 0x25 || color == 0x26)return 0;
	
	if(isalpha(letter))letter = toupper(letter);	//Convert to uppercase
    letter_offset = letter - 'A'+1;	//Find the offset in the letters[] array
    letter_offset *=8;
    if(letter == ' ')letter_offset=0;	//If we get a space or invalid character, display a space
    if(!isalpha(letter))letter_offset=0;
	//Fill the screen with data from the letters[] array
	for(int column=0; column<NUM_COLUMNS; column++)
    {
        for(int row=0; row<NUM_ROWS; row++)
        {
			//Strange looking algorithm converts rows to columns and vice versa.
			if(letters[letter_offset+(7-column)] & (1<<row))screenBuffer[screen].pixel[row*8+column]=color;
            else screenBuffer[screen].pixel[row*8+column]=BLACK;
        }
    }
	
	return 1;
}

/*
	Sends the data in screenBuffer to the matrices.
*/
void cRGBMatrix::display(void)
{
	digitalWrite(SLAVESELECT, LOW);	//Select the LED matrices
	spiTransfer(0x26);				//SEnd the Start of frame character
	//Use the _num_boards parameter to determine how many frames to send
	for(int screen=0; screen<_num_boards; screen++)
	{
		sendScreen(screenBuffer[screen].pixel);	//Send frame data over SPI.
	}
	digitalWrite(SLAVESELECT, HIGH);	//Unselect the LED matrices
}

/*
	Sends the frame of data determined by the screen parameter
	Inputs: char * screen - The 64 byte buffer to send over SPI
*/
void cRGBMatrix::sendScreen(char * screen)
{
    for(int row=0; row<NUM_ROWS; row++)
    {
        for(int column=0; column<NUM_COLUMNS; column++)
        {
            spiTransfer(screen[(row*8)+column]);
        }
    }
}

/*
	Scrolls a single fame onto and off of the frame.
*/
void cRGBMatrix::scrollBuffer(int speed)
{
	//This huge loop scrolls a character one column to the left each time through.
    for(int scroll = 7; scroll >=0; scroll--)
    {
        for(int board = _num_boards+1; board >=0; board--)
        {
            for(int row=0; row<NUM_ROWS; row++)
            {
                for(int column=0; column<NUM_COLUMNS; column++)
                {
                    myScreen[board].pixel[row*NUM_ROWS+column]=screenBuffer[(column+scroll)/8+board].pixel[(row*NUM_ROWS)+(column+scroll)%8];
                }
            }
        }

        digitalWrite(SLAVESELECT, LOW);
        spiTransfer(0x26);
		//We start from the second index so that a character can be scrolled all the way off the frame.
        for(int i=0; i<_num_boards; i++)sendScreen(myScreen[i].pixel);
        digitalWrite(SLAVESELECT, HIGH);
        delay(speed);
    }
}

/*
	Scrolls an entire message on and off of the frame.
	Inputs: char * message - The message to be scrolled
*/
char cRGBMatrix::scroll(char * message, char color, int speed)
{
    int messageLength=0;
    char disp[58]="";
    
	if(color == 0x25 || color == 0x26)return 0;
	
	//Precede the message with spaces so the message starts off of the frame.
	for(int i=0; i<_num_boards; i++)disp[i]=' ';
    strcat(disp, message);
	//Find the length of the screen (including the spaces we added).
    messageLength=strlen(disp);
	//Scroll each character onto and off of the frame.
    for(int messageIndex=0; messageIndex<messageLength; messageIndex++)
    {
        for(int screen=_num_boards+1; screen>=0; screen--)
        {
			fillChar(_num_boards+1-screen, disp[messageIndex+screen], color);
		}
        scrollBuffer(speed);
    }	
	return 1;
}

/*
	Clears the entire frame by filling all the screens with Black
*/
void cRGBMatrix::clear(void)
{
	for(int board=0; board<_num_boards; board++)
	{
		fillScreen(board, BLACK);
	}
	display();
}