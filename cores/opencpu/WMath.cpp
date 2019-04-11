#include <interface.h>

void randomSeed(unsigned long seed)
{
  if (seed != 0)
  {
    srand(seed);
  }
}

long random(long howbig)
{
  if (howbig == 0)
  {
    return 0;
  }
  return rand() % howbig;
}

long random(long howsmall, long howbig)
{
  if (howsmall >= howbig)
  {
    return howsmall;
  }
  long diff = howbig - howsmall;
  return random(diff) + howsmall;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

unsigned int  makeWord(unsigned int  w)
{
  return w;
}

unsigned int makeWord(unsigned char h, unsigned char l)
{
  return (h << 8) | l;
}
