#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void ChangeSubstr(string& str, string subs_from, string subs_to)
{
  int inx = str.find(subs_from);
  if(inx == string::npos)
  {
    throw invalid_argument("Substring does not exist");
  }

  str.replace(inx, subs_from.length(), subs_to);
}

struct Production
{
  string from;
  string to;
  bool is_tml = false; // true if terminal

  Production(string s)
  {
    size_t sep_len = 1;
    
    if(s.find(".") != string::npos)
    {
      is_tml = true;
      sep_len = 2;
    }
    
    size_t i = 0;
    while(s[i] != '>')
    {
      from += s[i];
      i++;

      if(i == s.length())
      {
        throw invalid_argument("Parameter must contain >");
      }
    }

    i += sep_len;
    while(s[i])
    {
      to += s[i];
      i++;
    }
  }
};

const size_t kMaxIteartionCount = 100;
const size_t kMaxStringLength = 50;
const size_t kMaxProductionCount = 10;

void MarkovAlgorithm(vector<Production> pr_arr, string& str)
{
  if(str.length() >= kMaxStringLength)
  {
    throw invalid_argument("String length limit is " + kMaxStringLength);
  }
  if(pr_arr.size() >= kMaxProductionCount)
  {
    throw invalid_argument("Production count limit is " + kMaxProductionCount);
  }

  size_t inx = 0;
  size_t iter_cnt = 0;
  while(inx != pr_arr.size())
  {
    if(str.find(pr_arr[inx].from) != string::npos)
    {
      ChangeSubstr(str, pr_arr[inx].from, pr_arr[inx].to);
      iter_cnt++;
      if(pr_arr[inx].is_tml)
      {
        return;
      }
      inx = 0;
    }
    else
    {
      inx++;
    }
    if(iter_cnt == kMaxIteartionCount)
    {
      throw runtime_error("Iteration count limit is " + kMaxIteartionCount);
    }
  }
}

void MarkovUnaryMinus(string& str)
{
  for(size_t i = 0; i < str.length(); i++)
  {
    if(str[i] != '|' && str[i] != '-')
    {
      throw invalid_argument("Invalid argument: must contain only | or -");
    }
  }

  Production p1("|-|>-");
  Production p2("->");
  
  vector<Production> p_v;
  p_v.push_back(p1);
  p_v.push_back(p2);

  MarkovAlgorithm(p_v, str);
}

void MarkovUnaryMultiply(string& str)
{
  for(size_t i = 0; i < str.length(); i++)
  {
    if(str[i] != '|' && str[i] != '*')
    {
      throw invalid_argument("Invalid argument: must contain only | or *");
    }
  }

  Production p1("|b>ba|");
  Production p2("ab>ba");
  Production p3("b>");
  Production p4("*|>b*");
  Production p5("*>c");
  Production p6("|c>c");
  Production p7("ac>c|");
  Production p8("c>");

  vector<Production> p_v;
  p_v.push_back(p1);
  p_v.push_back(p2);
  p_v.push_back(p3);
  p_v.push_back(p4);
  p_v.push_back(p5);
  p_v.push_back(p6);
  p_v.push_back(p7);
  p_v.push_back(p8);

  MarkovAlgorithm(p_v, str);
}

void MarkovBinaryToUnary(string& str)
{
  for(size_t i = 0; i < str.length(); i++)
  {
    if(str[i] != '0' && str[i] != '1')
    {
      throw invalid_argument("Invalid argument: must contain only 0 or 1");
    }
  }

  Production p1("1>0|");
  Production p2("|0>0||");
  Production p3("0>");

  vector<Production> p_v;
  p_v.push_back(p1);
  p_v.push_back(p2);
  p_v.push_back(p3);

  MarkovAlgorithm(p_v, str);
}

TEST_CASE("Testing Markov algorithm")
{
  string str;
  vector<Production> p_v;

  SUBCASE("Testing string of simple letters")
  {
    str = "abcb";
    
    Production p1("b>dd");
    Production p2("dc>cc");
    Production p3("ac>g");
    
    p_v.push_back(p1);
    p_v.push_back(p2);
    p_v.push_back(p3);
    
    MarkovAlgorithm(p_v, str);
    CHECK(str == "gccdd");
  }

  SUBCASE("Testing unary minus, multiply & binary to unary")
  {
    str = "||||-|||";
    MarkovUnaryMinus(str);
    CHECK(str == "|");

    str = "|||*||";
    MarkovUnaryMultiply(str);
    CHECK(str == "||||||");

    str = "110";
    MarkovBinaryToUnary(str);
    CHECK(str == "||||||");
  }

  SUBCASE("Testing exceptions: letters")
  {
    CHECK_THROWS_AS(Production p1("aaa"), invalid_argument);

    str = "ab";
    Production p1("a>ab");
    p_v.push_back(p1);
    CHECK_THROWS_AS(MarkovAlgorithm(p_v, str), runtime_error);

    str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    CHECK_THROWS_AS(MarkovAlgorithm(p_v, str), invalid_argument);

    str = "a";
    for(size_t i = 0; i < 10; i++)
    {
      p_v.push_back(p1);
    }
    CHECK_THROWS_AS(MarkovAlgorithm(p_v, str), invalid_argument);
  }

  SUBCASE("Testing exceptions: unary")
  {
    str = "a";
    CHECK_THROWS_AS(MarkovUnaryMinus(str), invalid_argument);
    CHECK_THROWS_AS(MarkovUnaryMultiply(str), invalid_argument);
    CHECK_THROWS_AS(MarkovBinaryToUnary(str), invalid_argument);
  }
}