#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
using namespace std;

const int kMaxSize = 100;

class Table
{
  struct Row
  {
    int key;
    string data;
  };
  Row* arr_;
  int cur_;

  public:
    Table() 
    { 
      arr_ = new Row[kMaxSize]; 
      cur_ = 0; 
    }
    ~Table()
    {
      delete[] arr_;
    }

    bool AddRow(Row r)
    {
      if(IsFull())
        return false;
      arr_[cur_] = r;
      cur_++;
      return true;
    }

    bool RemoveRow(int key_pos)
    {
      for(int i = 0; i < cur_; i++)
        if(arr_[i].key == key_pos)
        {
          cur_--;
          for(; i < cur_; i++)
            arr_[i] = arr_[i + 1];
          return true;
        }
      return false;
    }

    string* FindRow(int key_pos)
    {
      for(int i = 0; i < cur_; i++)
        if(arr_[i].key == key_pos)
          return &(arr_[i].data);
      return nullptr;
    }

    bool ChangeRow(int k, string d)
    {
      for(int i = 0; i < cur_; i++)
        if(arr_[i].key == k)
        {
          arr_[i].data = d;
          return true;
        }
      return false;
    }

    void ClearTable()
    {
      delete[] arr_;
      arr_ = new Row[kMaxSize];
      cur_ = 0;
    }

    void PrintTable()
    {
      if(cur_ == 0)
        cout << "table is empty" << endl;
      for(int i = 0; i < cur_; i++)
        cout << "row " << i << ": " << arr_[i].key << ", " << arr_[i].data << endl;
    }

    bool IsFull() { return cur_ == kMaxSize; }

    int Size() { return cur_; }
};

TEST_CASE("Testing class Table")
{
  Table table;

  SUBCASE("Testing add")
  {
    CHECK(table.AddRow({1, "a"}) == true);
    CHECK(table.AddRow({2, "b"}) == true);
    CHECK(table.AddRow({3, "c"}) == true);
    CHECK(table.Size() == 3);

    cout << endl;
    table.PrintTable();
  }

  SUBCASE("Testing remove")
  {
    table.AddRow({1, "a"});
    table.AddRow({2, "b"});
    table.AddRow({3, "c"});

    CHECK(table.RemoveRow(1) == true);
    CHECK(table.RemoveRow(3) == true);
    CHECK(table.RemoveRow(1) == false);
    CHECK(table.Size() == 1);
  }

  SUBCASE("Testing find")
  {
    table.AddRow({1, "a"});
    table.AddRow({2, "b"});

    CHECK(*(table.FindRow(1)) == "a");
    CHECK(table.FindRow(3) == 0);
  }

  SUBCASE("Testing change")
  {
    table.AddRow({1, "a"});
    table.AddRow({2, "b"});
    CHECK(table.ChangeRow(2, "c") == true);
    CHECK(*(table.FindRow(2)) == "c");
  }

  SUBCASE("Testing is full")
  {
    CHECK(table.IsFull() == false);

    for(int i = 0; i < 100; i++)
      table.AddRow({i, "a"});
    
    CHECK(table.IsFull() == true);
  }

  SUBCASE("Testing clear")
  {
    table.AddRow({1, "a"});
    table.AddRow({2, "b"});
    table.AddRow({3, "c"});

    table.ClearTable();
    CHECK(table.Size() == 0);

    cout << endl;
    table.PrintTable();
  }
}