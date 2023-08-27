// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #include "doctest.h"

#include <iostream>
#include <vector>

using namespace std;

struct Node
{
  Node* right;
  Node* down;
  size_t row;
  size_t col;
  int data;

  Node(): right(this), down(this), row(0), col(0), data(0) {}
};

class SparseMatrix
{
  vector<Node> rows_;
  vector<Node> cols_;

  Node* GetPrevByRow(size_t roww, size_t coll)
  {
    Node* row_prev = &rows_[roww];
    Node* iter = rows_[roww].right;
    
    while(iter != &rows_[roww])
    {
      if(iter->col < coll)
      {
        row_prev = iter;
        iter = iter->right;
      }
      else
      {
        break;
      }
    }

    return row_prev;
  }

  Node* GetPrevByCol(size_t roww, size_t coll)
  {
    Node* col_prev = &cols_[coll];
    Node* iter1 = cols_[coll].down;
    
    while(iter1 != &cols_[coll])
    {
      if(iter1->row < roww)
      {
        col_prev = iter1;
        iter1 = iter1->down;
      }
      else
      {
        break;
      }
    }

    return col_prev;
  }

  public:
    size_t row_cnt_;
    size_t col_cnt_;

    SparseMatrix(size_t rc, size_t cc): row_cnt_(rc), col_cnt_(cc)
    {
      rows_.resize(row_cnt_);
      cols_.resize(col_cnt_);

      for(size_t i = 0; i < row_cnt_; i++)
      {
        rows_[i].row = i;
      }
      for(size_t i = 0; i < col_cnt_; i++)
      {
        cols_[i].col = i;
      }
    }
    
    ~SparseMatrix()
    {
      Clear();
    }

    void AddEl(size_t roww, size_t coll, int data)
    {
      if(roww >= row_cnt_ || coll >= col_cnt_)
      {
        throw invalid_argument("Indexes are out of range");
      }

      Node* row_prev = GetPrevByRow(roww, coll);
      Node* col_prev = GetPrevByCol(roww, coll);

      if(row_prev->right->col == coll && col_prev->down->row == roww)
      {
        row_prev->right->data = data;
        return;
      }

      Node* new_el = new Node();
      new_el->row = roww;
      new_el->col = coll;
      new_el->data = data;
      
      new_el->right = row_prev->right;
      row_prev->right = new_el;
      
      new_el->down = col_prev->down;
      col_prev->down = new_el;
    }

    void RemoveEl(size_t roww, size_t coll)
    {
      if(roww >= row_cnt_ || coll >= col_cnt_)
      {
        throw invalid_argument("Indexes are out of range");
      }

      Node* row_prev = GetPrevByRow(roww, coll);
      Node* col_prev = GetPrevByCol(roww, coll);

      if(row_prev->right->col == coll && col_prev->down->row == roww)
      {
        Node* to_del = row_prev->right;
        row_prev->right = to_del->right;
        col_prev->down = to_del->down;
        delete to_del;
      }
    }

    int GetData(size_t roww, size_t coll)
    {
      if(roww >= row_cnt_ || coll >= col_cnt_)
      {
        throw invalid_argument("Indexes are out of range");
      }

      Node* row_prev = GetPrevByRow(roww, coll);
      Node* col_prev = GetPrevByCol(roww, coll);

      if(row_prev->right->col != coll || col_prev->down->row != roww)
      {
        throw out_of_range("No such element exists");
      }
      
      return row_prev->right->data;
    }

    void ChangeEl(size_t roww, size_t coll, int new_data)
    {
      if(roww >= row_cnt_ || coll >= col_cnt_)
      {
        throw invalid_argument("Indexes are out of range");
      }

      Node* row_prev = GetPrevByRow(roww, coll);
      Node* col_prev = GetPrevByCol(roww, coll);

      if(row_prev->right->col != coll || col_prev->down->row != roww)
      {
        throw out_of_range("No such element exists");
      }
      
      row_prev->right->data = new_data;
    }

    void Print()
    {
      Node* temp;
      for(size_t i = 0; i < row_cnt_; i++)
      {
        cout << "row " << i << ": ";
        temp = rows_[i].right;
        while(temp != &rows_[i])
        {
          cout << temp->data << " (col: " << temp->col << ") ";
          temp = temp->right;
        }
        cout << endl;
      }
    }

    bool IsEmpty()
    {
      for(size_t i = 0; i < row_cnt_; i++)
      {
        if(rows_[i].right != &rows_[i])
        {
          return false;
        }
      }

      return true;
    }

    void Clear()
    {
      for(size_t i = 0; i < row_cnt_; i++)
      {
        Node* iter = rows_[i].right;

        while(iter != &rows_[i])
        {
          Node* to_del = iter;
          iter = iter->right;
          delete to_del;
        }
      }

      rows_.clear();
      cols_.clear();
    }

    SparseMatrix AddMatrixes(SparseMatrix &other)
    {
      if(row_cnt_ != other.row_cnt_ || col_cnt_ != other.col_cnt_)
      {
        throw invalid_argument("Invalid matrix sizes");
      }

      SparseMatrix res(row_cnt_, col_cnt_);
  
      for(size_t i = 0; i < row_cnt_; i++)
      {
        Node* iter1 = rows_[i].right;
        Node* iter2 = other.rows_[i].right;
        
        while(iter1 != &rows_[i] && iter2 != &other.rows_[i])
        {
          if(iter1->col < iter2->col)
          {
            res.AddEl(i, iter1->col, iter1->data);
            iter1 = iter1->right;
          }
          else if(iter2->col < iter1->col)
          {
            res.AddEl(i, iter2->col, iter2->data);
            iter2 = iter2->right;
          }
          else
          {
            res.AddEl(i, iter1->col, iter1->data + iter2->data);
            iter1 = iter1->right;
            iter2 = iter2->right;
          }
        }

        if(iter1 == &rows_[i])
        {
          while(iter2 != &other.rows_[i])
          {
            res.AddEl(i, iter2->col, iter2->data);
            iter2 = iter2->right;
          }
        }
        else if(iter2 == &rows_[i])
        {
          while(iter1 != &rows_[i])
          {
            res.AddEl(i, iter1->col, iter1->row);
            iter1 = iter1->right;
          }
        }
      }

      return res;
    }

    SparseMatrix MultiplyMatrixes(SparseMatrix other)
    {
      if(col_cnt_ != other.row_cnt_)
      {
        throw invalid_argument("Invalid matrix sizes");
      }

      SparseMatrix res(row_cnt_, other.col_cnt_);

      for(size_t i = 0; i < row_cnt_; i++)
      {
        for(size_t j = 0; j < other.col_cnt_; j++)
        {
          Node* iter2 = other.cols_[j].down;
          Node* iter1 = rows_[i].right;
          
          int cell_res = 0;
          
          while(iter1 != &rows_[i] && iter2 != &other.cols_[j])
          {
            if(iter1->col == iter2->row)
            {
              cell_res += iter1->data * iter2->data;
              iter1 = iter1->right;
              iter2 = iter2->down;
            }
            else
            {
              (iter1->col < iter2->row) ? (iter1 = iter1->right) : (iter2 = iter2->down);
            }
          }
          res.AddEl(i, j, cell_res);
        }
      }

      return res;
    }
};

int main()
{
  SparseMatrix m1(2, 3);
  SparseMatrix m2(3, 3);

  m1.AddEl(0, 1, 1);
  m1.AddEl(1, 1, 2);
  //m1.Print();

  cout << "\n";

  m2.AddEl(1, 0, 2);
  m2.AddEl(1, 2, 1);
  m2.AddEl(2, 0, 1);
  m2.AddEl(2, 1, 3);
  //m2.Print();

  SparseMatrix res = m1.MultiplyMatrixes(m2);
  res.Print();

//   SparseMatrix m1(3, 4);
//   SparseMatrix m2(3, 4);

//   m1.AddEl(0, 1, 1);
//   m1.AddEl(1, 2, 1);
//   m1.AddEl(2, 1, 1);
//   m1.AddEl(2, 2, 1);
// //  m1.Print();

//   cout << "\n";

//   m2.AddEl(0, 2, 2);
//   m2.AddEl(1, 2, 2);
//   m2.AddEl(2, 1, 2);
//   m2.AddEl(2, 3, 2);
// //  m2.Print();

//   SparseMatrix res = m1.AddMatrixes(m2);
//   res.Print();
}





// TEST_CASE("Testing sparse matrix")
// {
//   SparseMatrix sp(5, 5);

//   SUBCASE("Testing add")
//   {
//     sp.AddEl(3, 2, 1);
//     sp.AddEl(0, 2, 9);
//     sp.AddEl(4, 1, 7);

//     CHECK(sp.GetData(3, 2) == 1);
//     CHECK(sp.GetData(0, 2) == 9);
//     CHECK(sp.GetData(4, 1) == 7);

//     sp.AddEl(4, 1, 6);
//     CHECK(sp.GetData(4, 1) == 6);
//     sp.AddEl(4, 1, 5);
//     CHECK(sp.GetData(4, 1) == 5);

//     sp.Print();
//   }

//   SUBCASE("Testing remove")
//   {
//     sp.AddEl(3, 2, 1);
//     sp.AddEl(0, 2, 9);
//     sp.AddEl(4, 1, 7);
    
//     sp.RemoveEl(0, 2);
//     sp.RemoveEl(4, 1);
//     sp.RemoveEl(4, 1);
    
//     CHECK_THROWS_AS(sp.GetData(0, 2), out_of_range);
//     CHECK_THROWS_AS(sp.GetData(4, 1), out_of_range);
//   }

//   SUBCASE("Testing get data & change")
//   {
//     sp.AddEl(3, 2, 1);
//     sp.AddEl(0, 2, 9);
//     sp.AddEl(4, 1, 7);

//     sp.ChangeEl(3, 2, 7);
//     sp.ChangeEl(3, 2, 9);
//     sp.ChangeEl(4, 1, 0);

//     CHECK(sp.GetData(3, 2) == 9);
//     CHECK(sp.GetData(4, 1) == 0);
//   }

//   SUBCASE("Testing exceptions")
//   {
//     CHECK_THROWS_AS(sp.AddEl(6, 7, 0), invalid_argument);
//     CHECK_THROWS_AS(sp.AddEl(10, 9, 0), invalid_argument);
//     CHECK_THROWS_AS(sp.AddEl(4, 7, 0), invalid_argument);
//     CHECK_THROWS_AS(sp.AddEl(6, 2, 0), invalid_argument);

//     CHECK_THROWS_AS(sp.GetData(0, 2), out_of_range);
//     CHECK_THROWS_AS(sp.ChangeEl(4, 1, 8), out_of_range);
//   }   

//   SUBCASE("Testing is empty")
//   {
//     CHECK(sp.IsEmpty() == true);
//   }
// }