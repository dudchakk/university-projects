#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
using namespace std;

const int kMaxSize = 5;

class Queue
{
  int* arr_;
  int head_inx_;
  int tail_inx_;

  public:
    Queue(): head_inx_(-1), tail_inx_(-1)
    {
      arr_ = new int[kMaxSize];
      for(size_t i = 0; i < kMaxSize; i++)
      {
        arr_[i] = 0;
      }
    }
    ~Queue()
    {
      Clear();
      delete[] arr_;
    }

    int Add(int el)
    {
      if((tail_inx_ - head_inx_ + 1) % kMaxSize == 0)
      {
        throw out_of_range("Unable to add new element: queue is full");
      }

      tail_inx_ = (++tail_inx_) % kMaxSize;
      arr_[tail_inx_] = el;
      
      if(head_inx_ == -1)
      {
        head_inx_ = 0;
      }

      return arr_[tail_inx_];
    }

    int Remove()
    {
      if(IsEmpty())
      {
        throw out_of_range("Unable to remove element: queue is empty");
      }

      int res = arr_[head_inx_];
      arr_[head_inx_] = 0;

      if(head_inx_ == tail_inx_)
      {
        head_inx_ = -1;
        tail_inx_ = -1;
        return -1;
      }

      head_inx_ = (++head_inx_) % kMaxSize;

      return res;
    }

    void Print()
    {
      for(size_t i = 0; i < kMaxSize; i++)
      {
        cout << "el " << i << ": " << arr_[i] << endl;
      }
      cout << endl;
    }

    void Clear()
    {
      for(size_t i = 0; i < kMaxSize; i++)
      {
        arr_[i] = 0;
      }
      head_inx_ = -1;
      tail_inx_ = -1;
    }

    bool IsEmpty()
    {
      return head_inx_ == -1 && tail_inx_ == -1;
    }
};

struct Node
{
  Queue* queue;
  int prt;
  Node* next;

  Node(): prt(0), next(nullptr)
  {
    queue = new Queue();
  } 
};

class PriorityQueue
{
  public:
    Node* head_;

    PriorityQueue()
    {
      head_ = new Node();
    }
    ~PriorityQueue()
    {
      Clear();
      delete head_;
    }

    int Add(int prt, int data)
    {
      if(prt <= 0)
      {
        throw invalid_argument("Invalid priority: must be >= 1");
      }

      Node* node = GetNodeByPriority(prt);
      return node->queue->Add(data);
    }

    int Remove()
    {
      Node* iter = head_;
      while(iter && iter->queue->IsEmpty())
      {
        iter = iter->next;
      }
      if(!iter)
      {
        throw out_of_range("Unable to remove element: all queues are empty");
      }
      else
      {
        return iter->queue->Remove();
      }
    }

    Node* GetNodeByPriority(int prt)
    {
      Node* iter = head_;
      
      if(iter->prt > prt)
      {
        Node* new_node = new Node();
        new_node->prt = prt;
        new_node->next = iter;
        head_ = new_node;
        return head_;
      }

      while(iter->next && iter->next->prt < prt)
      {
        iter = iter->next;
      }
      if(iter->prt == prt)
      {
        return iter;
      }
      if(iter->next && iter->next->prt == prt)
      {
        return iter->next;
      }
      
      Node* new_node = new Node();
      new_node->prt = prt;
      new_node->next = iter->next;
      
      if(head_->prt == 0)
      {
        delete iter;
        head_ = new_node;
        return new_node;
      }
      
      iter->next = new_node;
      return new_node;
    }

    void Print()
    {
      Node* iter = head_;
      while(iter)
      {
        cout << "priority " << iter->prt << ":" << endl;
        iter->queue->Print();
        iter = iter->next;
      }
    }

    void Clear()
    {
      Node* iter = head_;
      while(iter)
      {
        Node* to_del = iter;
        iter = iter->next;
        delete to_del;
      }
      head_ = new Node();
    }

    bool IsEmpty()
    {
      Node* iter = head_;
      while(iter)
      {
        if(!iter->queue->IsEmpty())
        {
          return false;
        }
        iter = iter->next;
      }
      return true;
    }
};

TEST_CASE("Testing class Queue")
{
  Queue q;

  SUBCASE("Testing simple add & remove")
  {
    CHECK(q.Add(1) == 1);
    CHECK(q.Add(2) == 2);
    CHECK(q.Add(3) == 3);
    CHECK(q.Remove() == 1);
    CHECK(q.Remove() == 2);
    CHECK(q.Add(4) == 4);
    CHECK(q.Add(5) == 5);
    CHECK(q.Remove() == 3);
    CHECK(q.Add(6) == 6);
    CHECK(q.Add(7) == 7);
    CHECK(q.Remove() == 4);

    q.Print();
  }

  SUBCASE("Testing full")
  {
    CHECK(q.Add(1) == 1);
    CHECK(q.Add(1) == 1);
    CHECK(q.Add(1) == 1);
    CHECK(q.Add(1) == 1);
    CHECK(q.Add(1) == 1);
    CHECK_THROWS_AS(q.Add(1), out_of_range);
    CHECK(q.Remove() == 1);
    CHECK(q.Remove() == 1);
    CHECK(q.Add(1) == 1);
    CHECK(q.Add(1) == 1);
    CHECK_THROWS_AS(q.Add(1), out_of_range);
  }

  SUBCASE("Testing empty")
  {
    CHECK(q.IsEmpty() == true);
    CHECK_THROWS_AS(q.Remove(), out_of_range);
    
    q.Add(1);
    q.Clear();
    
    CHECK(q.IsEmpty() == true);
    CHECK_THROWS_AS(q.Remove(), out_of_range);

    q.Add(1);
    q.Add(1);
    q.Add(1);
    q.Remove();
    q.Remove();
    q.Remove();

    CHECK(q.IsEmpty() == true);
    CHECK_THROWS_AS(q.Remove(), out_of_range);
  }
}

TEST_CASE("Testing class PriorityQueue")
{
  PriorityQueue pq;

  SUBCASE("Testing simple add & remove")
  {
    CHECK(pq.Add(1, 1) == 1);
    CHECK(pq.Add(1, 2) == 2);
    CHECK(pq.Add(1, 3) == 3);
    CHECK(pq.Add(1, 7) == 7);
    CHECK(pq.Add(3, 3) == 3);
    CHECK(pq.Add(3, 4) == 4);
    CHECK(pq.Add(2, 3) == 3);
    CHECK_THROWS_AS(pq.Add(0, 0), invalid_argument);

    CHECK(pq.Remove());
    CHECK(pq.Remove());
    CHECK(pq.Remove());

    pq.Print();
  }

  SUBCASE("Testing full")
  {
    for(size_t i = 0; i < kMaxSize; i++)
    {
      pq.Add(1, i);
    }
    for(size_t i = 0; i < kMaxSize; i++)
    {
      pq.Add(2, i);
    }
    for(size_t i = 0; i < kMaxSize; i++)
    {
      pq.Add(3, i);
    }
    
    CHECK_THROWS_AS(pq.Add(1, 1), out_of_range);
    CHECK_THROWS_AS(pq.Add(2, 1), out_of_range);
    CHECK_THROWS_AS(pq.Add(3, 1), out_of_range);

    pq.Remove();
    pq.Add(1, 1);
    CHECK_THROWS_AS(pq.Add(1, 1), out_of_range);
  }

  SUBCASE("Testing empty")
  {
    CHECK(pq.IsEmpty() == true);
    CHECK_THROWS_AS(pq.Remove(), out_of_range);

    pq.Add(4, 1);
    pq.Add(1, 1);
    pq.Add(2, 1);
    pq.Remove();
    pq.Remove();
    pq.Remove();

    CHECK(pq.IsEmpty() == true);
    CHECK_THROWS_AS(pq.Remove(), out_of_range);
  }
}