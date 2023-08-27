#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
using namespace std;

class Set
{
    int set = 0;

    size_t GetShift(char el)
    {
      return 1 << (el - 'a');
    }

  public:
    bool IsInSet(char el)
    {
      return (set & GetShift(el)) != 0;
    }

    void Add(char el)
    {
      if(!IsInSet(el))
      {
        set = set | GetShift(el);
      }
    }

    void Remove(char el)
    {
      if(!IsInSet(el))
      {
        throw invalid_argument("Element does not exist");
      }
      set = set & (~(GetShift(el)));
    }

    Set Union(const Set& other)
    {
      Set res;
      res.set = set | other.set;
      return res;
    }

    Set Intersect(const Set& other)
    {
      Set res;
      res.set = set & other.set;
      return res;
    }

    Set Difference(const Set& other)
    {
      Set res;
      res.set = set ^ (Intersect(other).set);
      return res;
    }

    void Print()
    {
      for(int i = 25; i >= 0; i--)
      {
        char el = char(i + 'a');
        cout << ((IsInSet(el)) ? el : '_');
      }
      cout << endl;
    }

    bool operator==(const Set& other)
    {
      return set == other.set;
    }

    void Clear()
    {
      set = 0;
    }
};

TEST_CASE("Testing class Set")
{
  Set set1;
  Set set2;

  SUBCASE("Testing add & remove")
  {
    set1.Add('a');
    set1.Add('z');
    set1.Add('c');
    set1.Add('r');
    set1.Add('h');
    set1.Add('g');
    set1.Add('g');
    set1.Add('j');

    CHECK(set1.IsInSet('a') == true);
    CHECK(set1.IsInSet('z') == true);
    CHECK(set1.IsInSet('c') == true);
    CHECK(set1.IsInSet('r') == true);
    CHECK(set1.IsInSet('h') == true);
    CHECK(set1.IsInSet('g') == true);
    CHECK(set1.IsInSet('j') == true);

    set1.Print();

    set1.Remove('a');
    set1.Remove('g');
    CHECK_THROWS_AS(set1.Remove('k'), invalid_argument);

    CHECK(set1.IsInSet('a') == false);
    CHECK(set1.IsInSet('g') == false);
  }

  SUBCASE("Testing two sets methods")
  {
    set1.Add('a');
    set1.Add('c');
    set1.Add('h');
    set1.Add('f');

    set2.Add('a');
    set2.Add('d');
    set2.Add('h');
    set2.Add('r');
    set2.Add('z');

    Set res, cor_res;

    res = set1.Union(set2);
    cor_res.Add('a');
    cor_res.Add('c');
    cor_res.Add('d');
    cor_res.Add('h');
    cor_res.Add('f');
    cor_res.Add('r');
    cor_res.Add('z');
    CHECK(res == cor_res);
    cor_res.Clear();

    res = set1.Intersect(set2);
    cor_res.Add('a');
    cor_res.Add('h');
    CHECK(res == cor_res);
    cor_res.Clear();

    res = set1.Difference(set2);
    cor_res.Add('c');
    cor_res.Add('f');
    CHECK(res == cor_res);
    cor_res.Clear();

    res = set2.Difference(set1);
    cor_res.Add('d');
    cor_res.Add('r');
    cor_res.Add('z');
    CHECK(res == cor_res);
    cor_res.Clear();
  }
}