#include <iostream> //std::cout
#include <iomanip>  //std::setw
#include <vector>
#include <algorithm>
#include "cell.H"

using std::cout;
using std::endl;
using std::vector;
using std::setw;

// ctor given row and column
Cell::Cell(const int r,const int c)
{
  cell_num = r * 9 + c;
  row = r;
  col = c;

  int bi = row / 3;
  int bj = col / 3;

  block = 3*bi + bj;

  //value = a.get_Prc(row, col);
  //if(value != 0) // has a value
  //  mark.clear();

  value = 0;

  for(int i = 0; i < 9; i++)
    mark.push_back(i+1);
}

// default ctor
Cell::Cell()
{
  cell_num = -1;  //invalid default
  row      = -1;
  col      = -1;
  block    = -1;
  value    = -1;

  for(int i = 0; i < 9; i++)
    mark.push_back(i+1);
}

// copy ctor
Cell::Cell(const Cell& x)
{
  cell_num = x.cell_num;
  row      = x.row;
  col      = x.col;
  block    = x.block;
  value    = x.value;
  mark     = x.mark;
}

// copy assign
Cell& Cell::operator=(const Cell& x)
{
  cell_num = x.cell_num;
  row      = x.row;
  col      = x.col;
  block    = x.block;
  value    = x.value;
  mark     = x.mark;
  return *this;
}

// ctor given cell num
Cell::Cell(const int cn)
{
  cell_num = cn;
  row = cell_num / 9;
  col = cell_num % 9;

  int bi = row / 3;
  int bj = col / 3;

  block = 3*bi + bj;

  //value = a.get_Prc(row, col);
  //if(value != 0) // has a value
  //  mark.clear();

  value = 0;

  for(int i = 0; i < 9; i++)
    mark.push_back(i+1);
}

void Cell::set_value(const int n)
{
  value = n;
  if(n != 0)  // cell has found its value
    mark.clear(); // marks no longer needed
}

void Cell::print_values()
{
  cout << "cell = "   << setw(2) << cell_num;
  cout << " RC = "    <<            row << col;
  cout << " block = " << setw(2) << block;
  cout << " value = " << setw(2) << value;
  cout << " marks:";
  for(int mi : mark)
    cout << " " << mi ;
  cout << endl;
}

void Cell::rm_cmark(const int num)
{
  // remove pencil mark [num] for cell i, j
  vector<int>::iterator it;

  it = find(mark.begin(), mark.end(), num);
  if(it != mark.end()){
    //cout << "erasing pmark ["<< num << "] for cell["<< cell_num <<"]\n";
    mark.erase(it);
  }
}
