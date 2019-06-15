#include "sd.H"
// action methods (rm, clear, ...)

void Sp::rm_row(const int ipos, const int jpos)
{
  for(int j = 0; j < 9; j++)
    if(j != jpos)
      opt1[ipos][j] = 9;
}

void Sp::rm_col(const int ipos, const int jpos)
{
  for(int i = 0; i < 9; i++)
    if(i != ipos)
      opt1[i][jpos] = 9;
}

void Sp::rm_blk(const int ipos, const int jpos)
{
  int istart = 0;
  int jstart = 0;

  if (ipos < 3)
    istart = 0;
  else if (ipos < 6)
    istart = 3;
  else
    istart = 6;

  if (jpos < 3)
    jstart = 0;
  else if (jpos < 6)
    jstart = 3;
  else
    jstart = 6;

  for(int i = istart; i < istart+3; i++)
    for(int j = jstart; j < jstart+3; j++)
      if((i != ipos) && (j != jpos))
        opt1[i][j] = 9;
}

void Sp::rm_pin_row(const int cell, const int mark)
{
  // rm pencil mark [mark] from row sharing [cell]
  for(Cell& icell : vc)
    if ( icell.get_row() == vc[cell].get_row() )
      icell.rm_cmark(mark);
}

void Sp::rm_pin_col(const int cell, const int mark)
{
  // rm pencil mark [mark] from col sharing [cell]
  for(Cell& icell : vc)
    if ( icell.get_col() == vc[cell].get_col() )
      icell.rm_cmark(mark);
}

void Sp::rm_pin_blk(const int cell, const int mark)
{
  // rm pencil mark [mark] from cells in block sharing [cell]
  for(Cell& icell : vc)
    if ( icell.get_block() == vc[cell].get_block() )
      icell.rm_cmark(mark);
}

void Sp::clear_row_pair(const int cell0, const int cell1)
{
  cout << "clearing row pair\n";
  // rm pencil marks [mark] from row sharing [cell]
  // already determined that there are only 2 marks in both cells
  //const int m1 = vc[cell0].get_mark(0);
  //const int m2 = vc[cell1].get_mark(1);

  const int m1 = vc[cell0].get_mark(0);
  const int m2 = vc[cell0].get_mark(1);

  // loop over all cells
  for(Cell& icell : vc)
    if ( icell.get_row()      == vc[cell0].get_row() &&
         icell.get_cell_num() != cell0               &&
         icell.get_cell_num() != cell1  )
    {
      icell.rm_cmark(m1);
      icell.rm_cmark(m2);
    }
}

void Sp::clear_col_pair(const int cell0, const int cell1)
{
  cout << "clearing col pair\n";
  // rm pencil marks [mark] from col sharing [cell0 && cell1]
  const int m1 = vc[cell0].get_mark(0);
  const int m2 = vc[cell0].get_mark(1);
  //
  // loop over all cells
  for(Cell& icell : vc)
    if ( icell.get_col()      == vc[cell0].get_col() &&
         icell.get_cell_num() != cell0               &&
         icell.get_cell_num() != cell1  )
    {
      icell.rm_cmark(m1);
      icell.rm_cmark(m2);
    }
}

void Sp::clear_blk_pair(const int cell0, const int cell1)
{
  // rm pencil marks [m12] from block sharing [cell0 & cell1]
  cout << "clearing block pair\n";
  const int m1 = vc[cell0].get_mark(0);
  const int m2 = vc[cell0].get_mark(1);
  //
  // loop over all cells
  for(Cell& icell : vc)
    if ( icell.get_block()    == vc[cell0].get_block() &&
         icell.get_cell_num() != cell0                 &&
         icell.get_cell_num() != cell1  )
    {
      icell.rm_cmark(m1);
      icell.rm_cmark(m2);
    }
}

void Sp::wipe_col_but_spare_cells(const int col, const int mark, vector<int> sc)
{
  //rm marks in cells in row that are not in spared cell set sc
  // loop over cells in row
  for(int ci = col; ci <= 8*9*+col; ci+=9)
  {
    bool isSpared = false;
    for(int spared_cell : sc)
      if(ci == spared_cell)
        isSpared = true;

    if(!isSpared)
    {
      vc[ci].rm_cmark(mark);
      int row = ci / 9;
      int col = ci % 9;
      //cout << "wiping Rmark " << mark << " at cell " << row << col << endl;
    }
  }
}

void Sp::wipe_row_but_spare_cells(const int row, const int mark, vector<int> sc)
{
  //rm marks in cells in row that are not in spared cell set sc
  // loop over cells in row
  for(int ci = 9*row; ci < 9*(row+1); ci++)
  {
    bool isSpared = false;
    for(int spared_cell : sc)
      if(ci == spared_cell)
        isSpared = true;

    if(!isSpared)
    {
      vc[ci].rm_cmark(mark);
      int row = ci / 9;
      int col = ci % 9;
      //cout << "wiping Cmark " << mark << " at cell " << row << col << endl;
    }
  }
}

/*  RMM remove later (dont think its needed)
void Sp::rm_allpmarks(const int cell, const int num)
{
  // rm all pmarks in a given cell
  for(int i = 1; i < 10; i++)
    rm_pmark(cell, i);
    //if(i != num)
}

void Sp::rm_pmark(const int cell, const int num)
{
  // remove pencil mark [num] for cell i, j
  vector<int>::iterator it;

  it = find(pv[cell].begin(), pv[cell].end(), num);
  if(it != pv[cell].end()){
    //cout << "erasing pmark ["<< num << "] for cell["<< cell <<"]\n";
    pv[cell].erase(it);
  }
}
*/
