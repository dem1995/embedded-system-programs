// Registers for port 0 
#define FIO0DIR (*(volatile unsigned int *)0x2009c000) 
#define FIO0PIN (*(volatile unsigned int *)0x2009c014) 
#define FIO0SET (*(volatile unsigned int *)0x2009c018) 
#define FIO0CLR (*(volatile unsigned int *)0x2009c01C) 
// Registers for port 1 
#define FIO1DIR (*(volatile unsigned int *)0x2009c020) 
#define FIO1PIN (*(volatile unsigned int *)0x2009c034) 
#define FIO1SET (*(volatile unsigned int *)0x2009c038) 
#define FIO1CLR (*(volatile unsigned int *)0x2009c03C) 
// Registers for port 2 
#define FIO2DIR (*(volatile unsigned int *)0x2009c040) 
#define FIO2PIN (*(volatile unsigned int *)0x2009c054) 
#define FIO2SET (*(volatile unsigned int *)0x2009c058) 
#define FIO2CLR (*(volatile unsigned int *)0x2009c05C) 
// Pairs of bits in the PINMODE registers control the 
// resistor mode for particular port bits: 
//    00 pull-up <-- this is the default 
//    01 repeater 
//    10 resistor disabled (PullNone) 
//    11 pull-down 
// PINMODE0 : port 0, bits 0-15 
// PINMODE1 : port 0, bits 16-31 
// PINMODE2 : port 1, bits 0-15 
// PINMODE3 : port 1, bits 16-31 
// PINMODE4 : port 2, bits 0-15 
// PINMODE5 : port 2, bits 16-31 
#define PINMODE0 (*(volatile unsigned int *)0x4002c040) 
#define PINMODE1 (*(volatile unsigned int *)0x4002c044) 
#define PINMODE2 (*(volatile unsigned int *)0x4002c048) 
#define PINMODE3 (*(volatile unsigned int *)0x4002c04c) 
#define PINMODE4 (*(volatile unsigned int *)0x4002c050) 
#define PINMODE5 (*(volatile unsigned int *)0x4002c054) 