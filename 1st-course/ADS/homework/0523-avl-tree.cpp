#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <vector>
using namespace std;

struct Node
{
  int key;
  Node* left;
  Node* right;
  size_t height;

  Node(int k): key(k), left(nullptr), right(nullptr), height(1) {}

  size_t GetHeight()
  {
    if(this == nullptr)
    {
      return -1;
    }
    return height;
  }
};

int Max(const int a, const int b)
{
  return a > b ? a : b;
}

class AVLTree
{
  Node* root_;

  Node* RightRotate(Node* n) // ll lr l t -> ll l t lr
  {
    Node* newr = n->left;
    Node* lr = newr->right;

    newr->right = n;
    n->left = lr;

    n->height = Max(n->left->GetHeight(), n->right->GetHeight()) + 1; 
    newr->height = Max(newr->left->GetHeight(), newr->right->GetHeight()) + 1; 
    
    return newr;
  }

  Node* LeftRotate(Node* n) // t r rl rr -> rl t r rr
  {
    Node* newr = n->right;
    Node* rl = newr->left;

    newr->left = n;
    n->right = rl;

    n->height = Max(n->left->GetHeight(), n->right->GetHeight()) + 1; 
    newr->height = Max(newr->left->GetHeight(), newr->right->GetHeight()) + 1; 
    
    return newr;
  }

  int GetBalance(Node* n)
  {
    if(n == nullptr)
    {
      return 0;
    }
    return n->left->GetHeight() - n->right->GetHeight();
  }

  Node* Add(Node* n, int key)
  {
    if(n == nullptr)
    {
      return(new Node(key));
    }

    if(key < n->key)
    {
      n->left = Add(n->left, key);
    }
    else if(key > n->key)
    {
      n->right = Add(n->right, key);
    }
    else
    {
      // key already exists
      return n;
    }

    n->height = Max(n->left->GetHeight(), n->right->GetHeight()) + 1;
    int balance = GetBalance(n);

    //left left
    if(balance > 1 && key < n->left->key)
    {
      return RightRotate(n);
    }

    //right right
    if(balance < -1 && key > n->right->key)
    {
      return LeftRotate(n);
    }

    //left right
    if(balance > 1 && key > n->left->key)
    {
      n->left = LeftRotate(n->left);
      return RightRotate(n);
    }

    //right left
    if(balance < -1 && key < n->right->key)
    {
      n->right = RightRotate(n->right);
      return LeftRotate(n);
    }

    return n;
  }

  Node* GetMin(Node* n)
  { 
    if(n == nullptr)
    { 
      return nullptr; 
    } 
    else if(n->left == nullptr)
    { 
      return n; 
    } 
    else
    { 
      return GetMin(n->left); 
    } 
  } 

  Node* Remove(Node* n, int key) 
  { 
    if(n == nullptr)
    { 
      return n; 
    } 
    else if(key < n->key)
    { 
      n->left = Remove(n->left, key); 
    } 
    else if(key > n->key)
    { 
      n->right = Remove(n->right, key); 
    } 
    
    else
    {
      if(n->left == nullptr && n->right == nullptr)
      {
        delete n; 
        n = nullptr; 
      } 
      
      else if(n->left == nullptr)
      { 
        Node* temp = n; 
        n = n->right; 
        delete temp; 
      } 
      
      else if(n->right == nullptr)
      { 
        Node* temp = n; 
        n = n->left; 
        delete temp; 
      } 
      
      else
      { 
        Node* temp = GetMin(n->right); 
        n->key = temp->key; 
        n->right = Remove(n->right, temp->key); 
      } 
    } 

    if(n != nullptr)
    { 
      n->height = max(n->left->GetHeight(), n->right->GetHeight()) + 1; 
      
      int balance = GetBalance(n);
      
      //left left
      if(balance > 1 && key < n->left->key)
      {
        return RightRotate(n);
      }

      //right right
      if(balance < -1 && key > n->right->key)
      {
        return LeftRotate(n);
      }

      //left right
      if(balance > 1 && key > n->left->key)
      {
        n->left = LeftRotate(n->left);
        return RightRotate(n);
      }

      //right left
      if(balance < -1 && key < n->right->key)
      {
        n->right = RightRotate(n->right);
        return LeftRotate(n);
      }
    } 

    return n; 
  } 

  Node* Find(Node* n, int key)
  {
    if(n == nullptr)
    { 
      throw invalid_argument("No such node exists"); 
    } 
    else if(key == n->key) 
    { 
      return n; 
    } 
    else if(key < n->key) 
    { 
      return Find(n->left, key); 
    } 
    else 
    { 
      return Find(n->right, key); 
    } 
  }

  vector<int> PreOrder(Node* n, vector<int>& res)
  {
    if(n != nullptr)
    {
      res.push_back(n->key);
      PreOrder(n->left, res);
      PreOrder(n->right, res);
    }
    return res;
  } 

  public:
    AVLTree(int k)
    {
      root_ = new Node(k);
    }

    void Add(int key)
    {
      root_ = Add(root_, key);
    }

    void Remove(int key)
    {
      root_ = Remove(root_, key);
    }

    Node* Find(int key)
    {
      return Find(root_, key);
    }

    vector<int> PreOrder(vector<int>& res)
    {
      return PreOrder(root_, res);
    }
};

TEST_CASE("Testing AVL Tree")
{
  SUBCASE("Test 1")
  {
    AVLTree t(1);
    t.Add(2);
    t.Add(3);

    vector<int> cor_res = { 2, 1, 3 };
    vector<int> res;
    res = t.PreOrder(res);
    for(size_t i = 0; i < res.size(); i++)
    {
      CHECK(res[i] == cor_res[i]);
    }

    CHECK(t.Find(2) != nullptr);
    CHECK_THROWS_AS(t.Find(13), invalid_argument);
  }

  SUBCASE("Test 2")
  {
    AVLTree t(16);
    t.Add(23);
    t.Add(7);
    t.Add(17);
    t.Add(18);

    vector<int> cor_res = { 16, 7, 18, 17, 23 };
    vector<int> res;
    res = t.PreOrder(res);
    for(size_t i = 0; i < res.size(); i++)
    {
      CHECK(res[i] == cor_res[i]);
    }

    CHECK(t.Find(23) != nullptr);
    CHECK_THROWS_AS(t.Find(13), invalid_argument);
  }

  SUBCASE("Test 3")
  {
    AVLTree t(-2);
    t.Add(-4);
    t.Add(5);
    t.Add(-5);
    t.Add(-3);
    t.Add(7);

    vector<int> cor_res = { -2, -4, -5, -3, 5, 7 };
    vector<int> res;
    res = t.PreOrder(res);
    for(size_t i = 0; i < res.size(); i++)
    {
      CHECK(res[i] == cor_res[i]);
    }

    CHECK(t.Find(-3) != nullptr);
    CHECK_THROWS_AS(t.Find(13), invalid_argument);
    
  }
}