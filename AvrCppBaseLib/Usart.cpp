/* 
* Usart.cpp
*
* Created: 3/27/2015 8:34:22 PM
* Author: huszty
*/

#include "Usart.h"
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#ifndef UCSR0A
  #ifdef UCSRA
    #define UCSR0A UCSRA
    #define UDRE0 UDRE
    #define UDR0 UDR
  #else
    #ifdef USICS0
      #error "USI is not yet supported. If you don't need UART, exclude this file from compilation."
    #endif
  #endif
#endif

void Usart::putc( unsigned char c ) {
  while ((UCSR0A & (1 << UDRE0)) == 0);
  UDR0 = c;
}

void Usart::puts( char *s) {
  while (*s) {
    putc(*s);
    s++;
  }
}

void Usart::nl( void ) {
  usart_puts_P("\r\n");
}

void Usart::puts_p(const char *progmem_s ) {
  register char c;
  while ( (c = pgm_read_byte(progmem_s++)) )
  putc(c);
}

void Usart::puti( const int val ) {
  char buffer[sizeof(int)*8+1];
  puts( itoa(val, buffer, 10) );
}
