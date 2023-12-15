#include <iostream>

class BitSet
{
  int set = 0;
  public:
    void add(char c)     { set = set | (1 << (c - 'a')); }
    void remove(char c)  { set = set & (~(1 << (c - 'a'))); }
    bool isInSet(char c) { return set & (1 << (c - 'a')); }
    BitSet intersect(BitSet s) 
    { 
      BitSet result;
      result.set = set & s.set;
      return result;
    }
};