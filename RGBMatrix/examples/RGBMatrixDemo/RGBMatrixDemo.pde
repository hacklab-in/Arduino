//Add libraries for using the LED Matrices
#include <RGB.h>
#include <RGBMatrix.h>

//Define how many LED matrices are connected to create the frame.
int NUM_BOARDS = 8;

//Colors are defined in the RGB.h file
//Creating an array of the colors makes them easier to cycle through. Read the rest of the sketch to see how this is done.
char colors[8] = {BLACK, RED, GREEN, BLUE, ORANGE, MAGENTA, TEAL, WHITE};

void setup()
{
    delay(5000);        //The matrices won't start accepting data for 5 seconds after they are powered up.
    RGBMatrix.begin(NUM_BOARDS);    //Start the communication with the LED matrices.
}

void loop()
{

    //This section will scroll a message across the frame. 
    RGBMatrix.scroll("SPARKFUN ELECTRONICS", TEAL, 15);

    //This section will use the fillChar command to put characters onto the frame.
    RGBMatrix.clear();  //Start by clearing the frame.
    char letter = 'A';  //Create a starting character.
    //Put a character onto each screen in the frame. Start with the matrix connected to the Arduino
    for(int board=NUM_BOARDS-1; board>=0; board--)
    {
      RGBMatrix.fillChar(board, letter, GREEN);
      letter +=1;  //Get the next character in the alphabet to display on the next screen.
    }
    RGBMatrix.display();  //Post the new data to the frame.
    delay(2000);

    //This section uses the fillPixel Command to draw a border around the frame
    RGBMatrix.clear();  //Clear the frame of the old data	
	
    //This section uses the fillPixel Command to draw a border around the frame
    for(int column=0; column<NUM_COLUMNS; column++)
    {
        //Put a white pixel on every column of the top and bottom row of every board in the frame.
        for(int board=0; board<NUM_BOARDS; board++)
        {
            RGBMatrix.fillPixel(board, 0, column, WHITE);
            RGBMatrix.fillPixel(board, 7, column, WHITE);
        }
    }
    //Put a white pixel on every row of the first and last column in the frame.
    for(int row=0; row<NUM_ROWS; row++)
    {
        //Put the column of pixels on the first board in the frame.
        RGBMatrix.fillPixel(NUM_BOARDS-1, row, 7, WHITE);
        //Put the column of pixels on the last board in the frame.
        RGBMatrix.fillPixel(0, row, 0, WHITE);
    }
    //Put the image onto the frame.
    RGBMatrix.display();
    delay(1000);

    //This section uses the fillRow function to fill the frame with differnt colors row by row.
    //Repeat this section for each color in the 'colors' array.
    for(char color=1; color<8; color++)
    {
        //Fill the frame 1 row at a time.
        for(int row=0; row<NUM_ROWS; row++)
        {
            //Fill the row on every board in the frame.
            for(int board=0; board<NUM_BOARDS; board++)
            {
                RGBMatrix.fillRow(board, row, colors[color]);
            }
            //Update the display each time we add a row.
            RGBMatrix.display();
            delay(50);        
        }
        
        //After adding all of the rows to the frame, we want to remove them.
        //We can 'remove' a row by coloring the row with black.
        //Add a black row to the frame 1 row at a time
        for(int row=0; row<NUM_ROWS; row++)
        {
            //Add the black row to the entire frame.
            for(int board=0; board<NUM_BOARDS; board++)
            {
                RGBMatrix.fillRow(board, row, BLACK);
            }
            //Update the display with the 'removed' row.
            RGBMatrix.display();
            delay(50);        
        }
    }
 
    //This section uses the fillColumn function to fill the frame with different colors.
    //Repeat this section for each color in the 'colors' array.
    for(char color=1; color<8; color++)
    {
        //Start the loop at the first board in the frame.
        for(int board=NUM_BOARDS-1; board>=0; board--)
        {
            //Start filling columns from the left side of the board.
            for(int column=NUM_COLUMNS-1; column>=0; column--)
            {
                RGBMatrix.fillColumn(board, column, colors[color]);
                //Update the display every time we color a new column.
                RGBMatrix.display();
                delay(50);            
            }
        }
        //Now remove all of the columns of color by adding a 'black' column
        for(int board=0; board<NUM_BOARDS; board++)
        {
            for(int column=0; column<NUM_COLUMNS; column++)
            {
                RGBMatrix.fillColumn(board, column, BLACK);
                RGBMatrix.display();
                delay(50);            
            }
        }    
    }

}

