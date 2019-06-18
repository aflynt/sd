#include <iostream> //std::cout
#include <iomanip>  //std::setw
#include <vector>
#include <algorithm>
#include "cell.H"

using std::cout;
using std::endl;
using std::vector;
using std::setw;

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

// ctor given cell num
Cell::Cell(const int cn)
{
  // invariant is cell num must be >= 0 && < 81
  if(cn < 0 || cn > 80)
  {
    cell_num = -1;  //invalid default
    row      = -1;
    col      = -1;
    block    = -1;
    value    = -1;
  }
  else{
    cell_num = cn;
    row = cell_num / 9;
    col = cell_num % 9;

    int bi = row / 3;
    int bj = col / 3;

    block = 3*bi + bj;
    value = 0;
  }

  // pencil marks
  for(int i = 0; i < 9; i++)
    mark.push_back(i+1);
}

// ctor given row and column
Cell::Cell(const int r,const int c)
{
  // invariant is row and cols range from 0 to 8
  if(r < 0 || r > 8 || c < 0 || c > 8)
  {
    cell_num = -1;  //invalid default
    row      = -1;
    col      = -1;
    block    = -1;
    value    = -1;
  }
  else{
    cell_num = r * 9 + c;
    row = r;
    col = c;

    int bi = row / 3;
    int bj = col / 3;

    block = 3*bi + bj;
    value = 0;
  }

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

void Cell::set_value(const int n)
{
  // valid values for n are 1-9 for numbers and 0 if not found
  if(n < 1 || n > 9) // invalid value
  {
    value = 0;
    mark.clear(); // reset marks
    for(int i = 0; i < 9; i++)
      mark.push_back(i+1);
  }
  else
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

bool Cell::has_mark(const int mx)
{
  // check if cell has pencil mark [mx]
  vector<int>::iterator it;

  it = find(mark.begin(), mark.end(), mx);
  if(it != mark.end())
    return true;
  else
    return false;
}

void Cell::rm_cmark(const int mx)
{
  // remove pencil mark [mx] for cell i, j
  vector<int>::iterator it;

  it = find(mark.begin(), mark.end(), mx);
  if(it != mark.end()){
    //cout << "erasing pmark ["<< mx << "] for cell["<< cell_num <<"]\n";
    mark.erase(it);
  }
}
