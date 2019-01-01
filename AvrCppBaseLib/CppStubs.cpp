/*
 * CppStubs.cpp
 *
 * Created: 2019. 01. 01. 19:32:02
 *  Author: Huszty Gergo
 */ 

#include <string.h>
#include <stdlib.h>
#include "CppStubs.h"

void * operator new(size_t size)
{
  return malloc(size);
}

void operator delete(void * ptr)
{
  free(ptr);
}

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);}
void __cxa_guard_release (__guard *g) {*(char *)g = 1;}
void __cxa_guard_abort (__guard *) {}

void __cxa_pure_virtual(void) {}