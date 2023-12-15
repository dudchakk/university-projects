#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
using namespace std;

const int kMaxSize = 10;

struct Row
{
  int key;
  string data;
  
  Row(): key(0) {}
  Row(int k, string d): key(k), data(d) {}
};

class HashTable
{
  Row* arr_;
  int last_;
  int el_cnt_;

  unsigned int GetHash(int key)
  {
    return key % kMaxSize;
  }

  unsigned int GetRehash(unsigned int hash, int j)
  {
    return (hash + j) % kMaxSize;
  }

  public:
    HashTable() 
    { 
      arr_ = new Row[kMaxSize];
      last_ = 0; 
      el_cnt_ = 0;
    }

    ~HashTable()
    {
      delete[] arr_;
    }

    bool AddRow(Row r)
    {
      unsigned int hash = GetHash(r.key);
      int j = 0;
      unsigned int rehash = GetRehash(hash, j);
      
      while(arr_[rehash].key != 0)  
      {
        if(arr_[rehash].key == r.key)
        {
          arr_[rehash].data = r.data;
          return true;
        }
        
        rehash = GetRehash(hash, ++j);
        
        if(rehash == hash)
        {
          throw underflow_error("Unable to add new element: table is full");
        }
      }

      if(last_ < rehash)
      {
        last_ = rehash;
      }
      arr_[rehash] = r;
      el_cnt_++;
      return true;
    }

    int FindRow(int key_, Row &r)
    {
      unsigned int hash = GetHash(key_);
      int j = 0;
      unsigned int rehash = GetRehash(hash, j);
      
      while(arr_[rehash].key != key_ && arr_[rehash].key != 0)
      {
        rehash = GetRehash(hash, ++j);
      }

      if(arr_[rehash].key == key_)
      {
        r = arr_[rehash];
        return rehash;
      }

      return -1;
    }

    bool ChangeRow(int key_, string data_)
    {
      Row r;
      int rehash = FindRow(key_, r);
      
      if(rehash != -1)
      {
        arr_[rehash].data = data_;
        return true;
      }
      
      return false;
    }

    bool RemoveRow(int key_)
    {
      Row r;
      int rehash = FindRow(key_, r);
      
      if(rehash != -1)
      {
        if(key_ == last_)
        {
          for(int i = --last_; i >= 0; i--)
          {
            if(arr_[i].key != 0)
            {
              last_ = i;
              break;
            }
          }
        }

        arr_[rehash].key = 0;
        arr_[rehash].data = "";
        el_cnt_--;
        return true;
      }

      return false;
    }

    void ClearTable()
    {
      delete[] arr_;
      arr_ = new Row[kMaxSize];
      last_ = 0;
      el_cnt_ = 0;
    }

    int GetElementCount()
    {
      return el_cnt_;
    }

    void PrintTable()
    {
      if(last_ == 0)
      {
        cout << "table is empty" << endl;
        return;
      }
      
      for(int i = 0; i <= last_; i++)
      {
        if(arr_[i].key != 0)
        {
          cout << "row " << i << ": " << arr_[i].key << ", " << arr_[i].data << endl;
        }
        else
        {
          cout << "row " << i << " is empty" << endl;
        }
      }
    }
};

TEST_CASE("Testing class HashTable")
{
  HashTable ht;

  SUBCASE("Testing add")
  {
    CHECK(ht.AddRow({1, "a"}) == true);
    CHECK(ht.AddRow({11, "b"}) == true);
    CHECK(ht.AddRow({27, "c"}) == true);
    CHECK(ht.AddRow({10, "d"}) == true);
    CHECK(ht.AddRow({2, "e"}) == true);
    
    CHECK(ht.GetElementCount() == 5);
    
    CHECK(ht.AddRow({2, "c"}) == true);
    CHECK(ht.GetElementCount() == 5);
    
    cout << endl;
    ht.PrintTable();
  }

  SUBCASE("Testing remove")
  {
    ht.AddRow({1, "a"});
    ht.AddRow({5, "b"});
    ht.AddRow({9, "c"});

    CHECK(ht.RemoveRow(1) == true);
    CHECK(ht.RemoveRow(9) == true);
    CHECK(ht.RemoveRow(1) == false);
    
    CHECK(ht.GetElementCount() == 1);
  }

  SUBCASE("Testing find")
  {
    ht.AddRow({1, "a"});
    ht.AddRow({12, "b"});

    Row r;
    CHECK(bool(ht.FindRow(1, r)) == true);
    CHECK(bool(ht.FindRow(12, r)) == true);
    CHECK(ht.FindRow(3, r) == -1);
  }

  SUBCASE("Testing change")
  {
    CHECK(ht.AddRow({1, "a"}) == true);
    CHECK(ht.AddRow({11, "b"}) == true);
    CHECK(ht.AddRow({27, "c"}) == true);
    
    CHECK(ht.ChangeRow(11, "c") == true);
    CHECK(ht.ChangeRow(27, "b") == true);
    
    Row r;
    ht.FindRow(11, r);
    CHECK(r.data == "c");
    ht.FindRow(27, r);
    CHECK(r.data == "b");
  }

  SUBCASE("Testing is full")
  {
    for(int i = 1; i <= 10; i++)
      ht.AddRow({i, "a"});
    
    CHECK_THROWS_AS(ht.AddRow({11, "a"}), underflow_error);
  }

  SUBCASE("Testing clear")
  {
    ht.AddRow({1, "a"});
    ht.AddRow({2, "b"});
    ht.AddRow({3, "c"});

    ht.ClearTable();
    CHECK(ht.GetElementCount() == 0);

    cout << endl;
    ht.PrintTable();
  }
}