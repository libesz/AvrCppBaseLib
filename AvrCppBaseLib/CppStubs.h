/*
 * CppStubs.h
 *
 * Created: 2019. 01. 01. 19:32:15
 *  Author: Huszty Gergo
 */ 


#ifndef CPPSTUBS_H_
#define CPPSTUBS_H_

#include <string.h>

void * operator new(size_t size);
void operator delete(void * ptr);

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);

extern "C" void __cxa_pure_virtual(void);

#endif /* CPPSTUBS_H_ */