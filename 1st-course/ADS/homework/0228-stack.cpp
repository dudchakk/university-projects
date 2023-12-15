#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <stack>
using namespace std;

struct Item
{
	Item* prev;
	int data;
};

class Stack
{
	Item* top_;
	size_t size_;
	
	public:
		Stack(): top_(nullptr), size_(0) {}
		~Stack() { Clear(); }

		void Push(int data)
		{
			Item* t = new Item();
			t->prev = top_;
			t->data = data;
			top_ = t;
			size_++;
		}

		bool Pop()
		{
			if(IsEmpty()) 
			  return false;

			Item* t = top_;
			top_ = top_->prev;
			delete t;
			size_--;
			return true;
		}

		int Top() 
		{
			if((*this).IsEmpty())
			  throw underflow_error("Unable to get top element of the empty stack");
			
			return top_->data;
		}

		size_t Size() { return size_; }

		bool IsEmpty() { return size_ == 0; }

		void Clear() { while(Pop()) {} }
};

TEST_CASE("Testing class Stack")
{
  Stack stack;

	SUBCASE("Testing empty stack")
	{
		CHECK(stack.IsEmpty() == true);
		CHECK(stack.Size() == 0);
		CHECK(stack.Pop() == false);
		CHECK_THROWS_AS(stack.Top(), underflow_error);
	}

	SUBCASE("Testing push")
	{
		for(int i = 0; i < 5; i++)
		{
		  stack.Push(i);
			CHECK(stack.Top() == i);
		}
		CHECK(stack.IsEmpty() == false);
		CHECK(stack.Size() == 5);
	}

	SUBCASE("Testing pop")
	{
		for(int i = 0; i < 5; i++)
		  stack.Push(i);		
		for(int i = 0; i < 5; i++)
      stack.Pop();
		CHECK(stack.IsEmpty() == true);
		CHECK(stack.Size() == 0);
	}

	SUBCASE("Testing clear")
	{
		stack.Clear();
		CHECK(stack.Size() == 0);
		CHECK(stack.IsEmpty() == true);
		
		stack.Push(1);
		stack.Push(2);
		
		stack.Clear();
		CHECK(stack.Size() == 0);
		CHECK(stack.IsEmpty() == true);
	}
}

TEST_CASE("Testing STL stack")
{
  stack<int> stack;
	while(!stack.empty())
	  stack.pop();

	SUBCASE("Testing empty stack")
	{
		CHECK(stack.empty() == true);
		CHECK(stack.size() == 0);
	}

	SUBCASE("Testing push")
	{
		for(int i = 0; i < 5; i++)
		{
		  stack.push(i);
			CHECK(stack.top() == i);
		}
		CHECK(stack.empty() == false);
		CHECK(stack.size() == 5);
	}

	SUBCASE("Testing pop")
	{
		for(int i = 0; i < 5; i++)
		  stack.push(i);
		for(int i = 0; i < 5; i++)
      stack.pop();

		CHECK(stack.size() == 0);
		CHECK(stack.empty() == true);
	}
}