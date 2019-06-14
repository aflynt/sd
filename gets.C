#include "sd.H"
// retrieval functions ("gets")

Cell Sp::get_cell(const int cnum)
{
  return vc[cnum];
}

void Sp::get_subBlock(const int sbi, const int sbj, vector<int> &vsb)
{
  int istart = 0;
  int jstart = 0;

  if (sbi < 1)
    istart = 0;
  else if (sbi < 2)
    istart = 3;
  else
    istart = 6;

  if (sbj < 1)
    jstart = 0;
  else if (sbj < 2)
    jstart = 3;
  else
    jstart = 6;

  for(int i = istart; i < istart+3; i++)
    for(int j = jstart; j < jstart+3; j++)
      vsb.push_back(opt1[i][j]);
}

void Sp::get_sb_cells(const int sbi, const int sbj, vector<int> &vsb)
{
  int istart = 0;
  int jstart = 0;

  if (sbi < 1)
    istart = 0;
  else if (sbi < 2)
    istart = 3;
  else
    istart = 6;

  if (sbj < 1)
    jstart = 0;
  else if (sbj < 2)
    jstart = 3;
  else
    jstart = 6;

  for(int i = istart; i < istart+3; i++)
    for(int j = jstart; j < jstart+3; j++)
      vsb.push_back(9*i + j);
}

void Sp::get_options(const int n)
{
  reset_options();

  // loop thru all cells
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
    {
      // get value in cell
      int val = puzzle[i][j];
      if (val == n)
      {
        opt1[i][j] = 2; // value itself
        rm_row(i,j);
        rm_col(i,j);
        rm_blk(i,j);
      }
      else if(val != 0)
        opt1[i][j] = 3; // taken
    }
  //print_options();
}

void Sp::reset_options()
{
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      opt1[i][j] = 1;  // all options open
}
