#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

class Stack
{
  int top;
  int arr[MAX_SIZE];
  public:
    Stack(): top(-1) {}
    bool push(int n);
    bool Pop();
    int getTop();
    void isEmpty();
};

bool Stack::push(int n)
{
  if(top >= MAX_SIZE - 1)
    return false;
  top++;
  arr[top] = n;
  return true;
}

bool Stack::Pop()
{
  if(top == -1)
    return false;
  top--;
  return true;
}

int Stack::getTop()
{
  
}

