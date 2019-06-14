#include "sd.H"
// action methods (rm, clear, ...)
//
const int NCELLS = 81;
const int NPM = 9;

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



void Sp::clear_row_pair(const int cell0, const int cell1)
{
  cout << "clearing row pair\n";
  // rm pencil marks [mark] from row sharing [cell]
  const int m1 = pv[cell0][0];
  const int m2 = pv[cell0][1];
  const int cell_row  = cell0 / 9;

  for(int i = 0; i < pv.size(); i++)
  {
    int pv_row = i / 9;
    if( pv_row == cell_row && 
        i != cell0 &&
        i != cell1)//skip cell pair
    {
      vc[i].rm_cmark(m1);
      vc[i].rm_cmark(m2);
    }
  }
}

void Sp::clear_col_pair(const int cell0, const int cell1)
{
  cout << "clearing col pair\n";
  // rm pencil marks [mark] from row sharing [cell]
  const int m1 = pv[cell0][0];
  const int m2 = pv[cell0][1];
  const int cell_col  = cell0 % 9;

  for(int i = 0; i < pv.size(); i++)
  {
    if(i == cell0 || i == cell1) //skip cell pair
      continue;
    int pv_col = i % 9;
    if( pv_col == cell_col )
    {
      vc[i].rm_cmark(m1);
      vc[i].rm_cmark(m2);

    }
  }
}

void Sp::clear_blk_pair(const int cell0, const int cell1)
{
  // rm pencil marks [m12] from block sharing [cell]
  //
  cout << "clearing block pair\n";
  const int m1 = pv[cell0][0];
  const int m2 = pv[cell0][1];

  int block = find_block(cell0);

  // get block i j
  int bi = block / 3;
  int bj = block % 3;

  // starting corner for block
  int is = 3*bi;
  int js = 3*bj;

  for( int i = is; i < is+3; i++)
    for( int j = js; j < js+3; j++)
    {
      int pvcell = 9*i + j;
      if(pvcell != cell0 && pvcell != cell1)
      {
        vc[pvcell].rm_cmark(m1);
        vc[pvcell].rm_cmark(m2);
      }
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