/* ScrollingGraph

Loosely inspired by, and definitely borrowing from, the code 
that came with Graph.
Reads values from serial, and plots a scrolling graph - 
and a Fourier transform of the graph.

Needs the .jar file from JTransforms: 
https://sites.google.com/site/piotrwendykier/software/jtransforms

*/

import processing.serial.*;

Serial myPort;
// A circular buffer.
int [] buffer;
int bpos;
// Fourier transform library
FloatFFT_1D ffft;
// Multiplier for the FFT so you can see it better.
// I like 0.1 because it means you can see peaks without them
// being clipped.
float gain = 0.1;

void setup() {
  // Adjust this
  size(800, 512); 
  buffer = new int[width];
  bpos = 0;
  
  myPort = new Serial(this, Serial.list()[0],115200);
  myPort.bufferUntil('\n');
  ffft = new FloatFFT_1D(width);
}

void draw() {
   background(0);
   stroke(255);
   float [] dft = new float[width];
   // Draw a graph
   for(int x=0;x<width-1;x++) {
      int y0 = buffer[(x+bpos)%width];
      y0 = (int)map(y0, 0, 1023, 0, height);
      int y1 = buffer[(x+bpos+1)%width];
      y1 = (int)map(y1, 0, 1023, 0, height);
      // We want y=0 to be at the bottom of the screen,
      // Cartesian-style
      line(x,height-y0-1,x+1,height-y1-1);
   }
   // OK, load up an array to Fourier transform
   for(int x=0;x<width;x++) {
      dft[x] = 1.0 * buffer[(x+bpos)%width];
   }
   // Do the transform, in place
   ffft.realForward(dft);
   stroke(127);
   // This is where it gets complicated.
   // The real values are in odd-numbered parts of the array
   // The imaginary values are in even-numbered parts
   // Therefore we need to work in units of 2
   // Also, we need start and end points for lines
   for(int i=0;i<(width/2)-1;i++) {
      int x1 = i*2;
      int x2 = i*2+2;
      // Get the magnitudes here.
      int y1 = (int)(sqrt(dft[(i*2)]*dft[(i*2)] + dft[(i*2)+1]*dft[(i*2)+1])*gain);
      int y2 = (int)(sqrt(dft[(i*2)+2]*dft[(i*2)+2] + dft[(i*2)+3]*dft[(i*2)+3])*gain);
      line(x1,height-y1-1,x2,height-y2-1);
   } 
}

// And this is pretty much a borrowing from Graph
void serialEvent(Serial myPort) {
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
   inString = trim(inString);
   float inByte = float(inString); 
   buffer[bpos] = int(inByte);
   bpos++;
   bpos %= width;  
  } 
}
