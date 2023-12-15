#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <stack>
#include <string>
#include <math.h>

using namespace std;

int Priority(char c)
{
  if(c == '^')
  {
    return 3;
  }
  if(c == '/' || c == '*' || c == '%')
  {
    return 2;
  }
  else if(c == '+' || c == '-')
  {
    return 1;
  }
  else
  {
    return -1;
  }
}

bool IsOperation(char o)
{
  return o == '+' || o == '-' || o == '*' || o == '/' || o == '^';
}

int CalculateExpression(int n1, int n2, char operation)
{
  switch(operation)
  {
    case '+':
      return n1 + n2;
    case '-':
     return n1 - n2;
    case '*':
     return n1 * n2;
    case '/':
      return n1 / n2;
    case '^':
     return pow(n1, n2);
    
    default:
      return -1;
  }
}

string ExpressionToReversedPolishNotation(string notation)
{
  stack<char> s;
  string result;
  int len = notation.length();

  for(int i = 0; i < len; i++) 
  {
    if(notation[i] >= '0' && notation[i] <= '9')
    {
      result += notation[i];
    }

    else if(notation[i] == '(')
    {
      s.push('(');
    }

    else if(notation[i] == ')')
    {
      while(s.top() != '(')
      {
        result += s.top();
        s.pop();
      }
      s.pop();
    }

    // operator
    else 
    {
      while(!s.empty() && (Priority(notation[i]) <= Priority(s.top())))
      {
        result += s.top();
        s.pop();
      }
      s.push(notation[i]);
    }
  }

  while(!s.empty())
  {
    result += s.top();
    s.pop();
  }

  return result;
}

int CalculateNotation(string notation)
{
  stack<int> s;
  int len = notation.length();

  for(int i = 0; i < len; i++) 
  {
    if(IsOperation(notation[i]))
    {
      int n2 = s.top();
      s.pop();
      int n1 = s.top();
      s.pop();

      s.push(CalculateExpression(n1, n2, notation[i]));
    }
    else
    {
      s.push((int)(notation[i]) - 48);
    }
  }
  return s.top();
}

TEST_CASE("Testing reversed polish notation")
{
  SUBCASE("Testing convert to notation")
  {
    CHECK(ExpressionToReversedPolishNotation("2+3") == "23+");
    CHECK(ExpressionToReversedPolishNotation("(2+3)") == "23+");
    CHECK(ExpressionToReversedPolishNotation("2+2^2") == "222^+");
    CHECK(ExpressionToReversedPolishNotation("(2+2)^2") == "22+2^");
    CHECK(ExpressionToReversedPolishNotation("(5+6)^2") == "56+2^");
    CHECK(ExpressionToReversedPolishNotation("(2+3)^(2/2)+1") == "23+22/^1+");
    CHECK(ExpressionToReversedPolishNotation("(1+2)*(2/1)^2-3") == "12+21/2^*3-");
  }

  SUBCASE("Testing calculate notation")
  {
    CHECK(CalculateNotation("23+") == 5);
    CHECK(CalculateNotation("222^+") == 6);
    CHECK(CalculateNotation("22+2^") == 16);
    CHECK(CalculateNotation("56+2^") == 121);
    CHECK(CalculateNotation("23+22/^1+") == 6);
    CHECK(CalculateNotation("12+21/2^*3-") == 9);
  }
}