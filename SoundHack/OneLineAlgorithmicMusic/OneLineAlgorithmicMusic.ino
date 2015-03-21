// one-line algorithmic music
// see viznut's blog http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html
// and http://www.youtube.com/watch?v=GtQdIYUtAHg&feature=related

// ported to arduino by stimmer
// Audio out on pin 10

void setup() {
  TCCR1B = (TCCR1B & 0xf8) | 1;
  analogWrite(10,1);
}

void putb(byte b)
{
  static long m;
  long t;
  while((t=micros())-m < 125);
  m=t;
  
  OCR1B=b;
}

void loop() {
  long v;
  for(long t=0;;t++){
    putb(
  // uncomment ONE line below
  // or try making one of your own...
  //(t*20|t*3)>>1
  //t*((t>>12|t>>8)&63&t>>4)   // by viznut
  // ((-t&4095)*(255&t*(t&t>>13))>>12)+(127&t*(234&t>>8&t>>3)>>(3&t>>14)) // by tejeez
  // t*(t>>11&t>>8&123&t>>3)    // by tejeez
  // t*((t>>9|t>>13)&25&t>>6)   // by visy
  // (t*(t>>5|t>>8))>>(t>>16)   // by tejeez
  // ((t*(t>>8|t>>9)&46&t>>8))^(t&t>>13|t>>6) // by xpansive
  // ((t&4096)?((t*(t^t%255)|(t>>4))>>1):(t>>3)|((t&8192)?t<<2:t)) // by skurk (raer's version)
  // (t>>7|t|t>>6)*10+4*(t&t>>13|t>>6) // by viznut, xpansive, varjohukka
  // t*5&(t>>7)|t*3&(t*4>>10) // by miiro
  // (t|(t>>9|t>>7))*t&(t>>11|t>>9) // by red
  // v=(v>>1)+(v>>4)+t*(((t>>16)|(t>>6))&(69&(t>>9))) // by pyryp
  // (t>>6|t|t>>(t>>16))*10+((t>>11)&7)  //by viznut
   (t*(4|7&t>>13)>>((~t>>11)&1)&128) + ((t)*(t>>11&t>>13)*((~t>>9)&3)&127) // by stimmer
  );
  //putb(
  // uncomment ONE line below
  // or try making one of your own...
  //(t*20|t*3)>>1
  //t*((t>>12|t>>8)&63&t>>4)   // by viznut
  //((-t&4095)*(255&t*(t&t>>13))>>12)+(127&t*(234&t>>8&t>>3)>>(3&t>>14)) // by tejeez
  // t*(t>>11&t>>8&123&t>>3)    // by tejeez
  // t*((t>>9|t>>13)&25&t>>6)   // by visy
  // (t*(t>>5|t>>8))>>(t>>16)   // by tejeez
  // ((t*(t>>8|t>>9)&46&t>>8))^(t&t>>13|t>>6) // by xpansive
  // ((t&4096)?((t*(t^t%255)|(t>>4))>>1):(t>>3)|((t&8192)?t<<2:t)) // by skurk (raer's version)
  // (t>>7|t|t>>6)*10+4*(t&t>>13|t>>6) // by viznut, xpansive, varjohukka
  // t*5&(t>>7)|t*3&(t*4>>10) // by miiro
  // (t|(t>>9|t>>7))*t&(t>>11|t>>9) // by red
  // v=(v>>1)+(v>>4)+t*(((t>>16)|(t>>6))&(69&(t>>9))) // by pyryp
  // (t>>6|t|t>>(t>>16))*10+((t>>11)&7)  //by viznut
  // (t*(4|7&t>>13)>>((~t>>11)&1)&128) + ((t)*(t>>11&t>>13)*((~t>>9)&3)&127) // by stimmer
  //);
  }
  
}
