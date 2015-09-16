///////////////////////////////////////////////////////////////////////////
//Author:      Mark
//Date:        3/4/2014
//Description: ui list implementation
//All content (c) 2014 DigiPen (USA) Corporation, all rights reserved.
///////////////////////////////////////////////////////////////////////////
#include "Precompiled.h"
#include "Primitives.h"

DEFINE_CONVERSIONS
{
  
  CONVERTS(char, std::string);
  CONVERTS(std::string, char);
  CONVERTS(char, unsigned);
  CONVERTS(char, double);
  CONVERTS(char, float);  
  CONVERTS(char, int);
  CONVERTS(char, short);
  CONVERTS(char, long);
  CONVERTS(char, bool);

  CONVERTS(unsigned, double);
  CONVERTS(unsigned, float);  
  CONVERTS(unsigned, int);
  CONVERTS(unsigned, short);
  CONVERTS(unsigned, long);
  CONVERTS(unsigned, bool);

  CONVERTS(double, float);
  CONVERTS(double, int);
  CONVERTS(double, short);
  CONVERTS(double, long);
  CONVERTS(double, bool);

  CONVERTS(float, int);
  CONVERTS(float, short);
  CONVERTS(float, bool);
  CONVERTS(float, long);

  CONVERTS(long, int);
  CONVERTS(long, short);
  CONVERTS(long, bool);

  CONVERTS(int, bool);
  CONVERTS(int, short);
  CONVERTS(uint16_t, double);
  CONVERTS(uint16_t, int);

  CONVERTS(double, uint16_t);
  CONVERTS(int, uint16_t);

  CONVERTS(short, bool);
}