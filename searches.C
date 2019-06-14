#include "sd.H"
// searching methods

int Sp::find_block(const int cell)
{
  int crow = cell / 9;
  int ccol = cell % 9;

  int bi = 0;
  int bj = 0;

  if (crow < 3)
    bi = 0;
  else if (crow < 6)
    bi = 1;
  else
    bi = 2;

  if (ccol < 3)
    bj = 0;
  else if (ccol < 6)
    bj = 1;
  else
    bj = 2;

  int block = 3*bi + bj;

  return block;
  //cout << crow << " ";
  //cout << ccol << " ";
  //cout << block << "\n";
}

bool Sp::num_in_row(const int num, const int row)
{
  for(int j = 0; j < 9; j++)
    if( puzzle[row][j] == num )
      return true;
  return false;
}

bool Sp::num_in_col(const int num, const int col)
{
  for(int i = 0; i < 9; i++)
    if( puzzle[i][col] == num )
      return true;
  return false;
}

void Sp::report_num_in_row(const int num)
{
  for(int i = 0; i < 9; i++)
  {
    bool inrow = num_in_row(num, i);
    if (inrow)
      cout << num << " found in row " << i << endl;
  }
}

void Sp::report_num_in_col(const int num)
{
  for(int j = 0; j < 9; j++)
  {
    bool incol = num_in_col(num, j);
    if (incol)
      cout << num << " found in col " << j << endl;
  }
}

bool Sp::is_pair_match(const int c0, const int c1)
{
  // given cell numbers c0 and c1
  // match if both marks are the same
  // and only have two marks (assumed from caller?)
  int cell0_mark0 = vc[c0].get_mark(0);
  int cell0_mark1 = vc[c0].get_mark(1);
  int cell1_mark0 = vc[c1].get_mark(0);
  int cell1_mark1 = vc[c1].get_mark(1);

  bool isMatch = false;
  if(cell0_mark0 == cell1_mark0 &&
     cell0_mark1 == cell1_mark1 )
  {
    isMatch = true;
    cout << "[" << vc[c0].get_row();
    cout <<        vc[c0].get_col() << "] vs ";

    cout << "[" << vc[c1].get_row();
    cout <<        vc[c1].get_col() << "] ";

    cout <<            cell0_mark0;
    cout << " == "  << cell1_mark0;
    cout << " && " ;
    cout << "    "  << cell0_mark1;
    cout << " == "  << cell1_mark1;
    cout << endl;
  }

  return isMatch;
}

bool Sp::cell_has_mark(const int cell, const int mark)
{
  vector<int> imarks = vc[cell].get_marks();
  vector<int>::iterator it = find(imarks.begin(), imarks.end(), mark);
  if(it != imarks.end())
     return true;
  return false;
}
