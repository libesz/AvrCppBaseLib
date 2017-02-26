/* 
* Usart.h
*
* Created: 3/27/2015 8:34:22 PM
* Author: huszty
*/
//#define DEBUG 1
#undef DEBUG

#ifndef __USART_H__
#define __USART_H__

#include <avr/pgmspace.h>

class Usart
{
//functions
public:
  static void putc( unsigned char c );
  static void puts ( char *s);
  static void nl( void );
  static void puts_p(const char *progmem_s );
  static void puti( const int val );
private:
	Usart();
	~Usart();
	Usart( const Usart &c );
	Usart& operator=( const Usart &c );

}; //Usart
#define usart_puts_P(__s) Usart::puts_p(P(__s))
#define P(s) ({static const char c[] __attribute__ ((progmem)) = s;c;})

#ifdef DEBUG
  #define PUTC(x) Usart::putc(x)
  #define NL() Usart::nl()
  #define PUTS(x) usart_puts_P(x)
  #define PUTSS(x) Usart::puts(x)
  #define PUTI(x) Usart::puti(x)
#else
  #define PUTC(x)
  #define NL()
  #define PUTS(x)
  #define PUTI(x)
#endif
#endif //__USART_H__
