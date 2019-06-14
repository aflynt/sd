#include "sd.H"
// checking methods

const int NCELLS = 81;
const int NPM = 9;

bool isOne(int i) {return ((i == 1) ? true : false);}

bool Sp::chk4_1inRow(const int num)
{
  vector<int> nv;
  bool isUpdated = false;

  // check rows
  for(int i = 0; i < 9; i++)
  {
    nv.clear();
    // loop thru columns
    for(int j = 0; j < 9; j++)
      nv.push_back(opt1[i][j]);

    // count options
    int cnt = count_if(nv.begin(), nv.end(), isOne);
    //cout << "row: " << i << " has [" << cnt <<"] options\n";
    if(cnt == 1) // if only 1 option (num goes at 1)
    {
      isUpdated = true;
      for(int j = 0; j < 9; j++) // find 1's location
        if(opt1[i][j] == 1)
        {
          cout << "putting [" << num << "]";
          cout << " at ij = " << i << j << '\n';
          puzzle[i][j] = num;
        }
    }
  }
  return isUpdated;
}

bool Sp::chk4_1inCol(const int num)
{
  vector<int> nv;
  bool isUpdated = false;

  // check columns
  for(int j = 0; j < 9; j++)
  {
    nv.clear();
    // loop thru rows
    for(int i = 0; i < 9; i++)
      nv.push_back(opt1[i][j]);

    // count options
    int cnt = count_if(nv.begin(), nv.end(), isOne);
    //cout << "col: " << j << " has [" << cnt <<"] options\n";
    if(cnt == 1) // if only 1 option (num goes at 1)
    {
      isUpdated = true;
      for(int i = 0; i < 9; i++)
        if(opt1[i][j] == 1)
        {
          cout << "putting [" << num << "]";
          cout << " at ij = " << i << j << '\n';
          puzzle[i][j] = num;
        }
    }
  }
  return isUpdated;
}

bool Sp::chk4_1pmark()
{
  bool isfound = false;

  for(int icell = 0; icell < NCELLS; icell++)
  {
    if(vc[icell].get_mark_cnt() == 1) // only 1 value it could be
    {
      int row   = vc[icell].get_row();
      int col   = vc[icell].get_col();
      int value = vc[icell].get_last_mark();
      cout << "[" << row << "," << col << "] has only ["<< value <<"]\n";
      vc[icell].set_value(value);
      puzzle[row][col] = value;
      isfound = true;
    }
  }
  return isfound;
}

bool Sp::chk4_1pinBlk()
{
  bool isUpdated = false;

  // check block rows
  for(int i = 0; i < 3; i++)
  {
    // check block cols
    for(int j = 0; j < 3; j++)
    {
      vector<vector<int> > smc;//marks with cell
      smc.resize(10);

      vector<int> sbc;
      get_sb_cells(i,j,sbc); // put subblock-cells in sbc
      //print_sb(i,j);

      for(int im = 1; im <= NPM ; im++)     // loop over: marks
        for(int jc = 0; jc < sbc.size(); jc++) // loop over: cells
          if(cell_has_mark(jc, im))
            smc[im].push_back(jc); //put cell in smc vector

      isUpdated = process_smc(smc);
    }
  }
  return isUpdated;
}

void Sp::chk_pmarks()
{
  // loop thru all cells
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
    {
      int cell = i*9 + j;
      int val = puzzle[i][j];
      if(val != 0)
      {
        // set value for my cell
        vc[cell].set_value(val);

        // work on other cell's marks
        //rm_allpmarks(cell, val); // rm all in known cell RMM
        rm_pin_row(cell, val);
        rm_pin_col(cell, val);
        rm_pin_blk(cell, val);
      }
    }

  chk4_1pmark();
}

bool Sp::chk4_1inBlk(const int num)
{
  vector<int> nv;
  bool isUpdated = false;

  // check block rows
  for(int i = 0; i < 3; i++)
  {
    // check block cols
    for(int j = 0; j < 3; j++)
    {
      nv.clear();
      get_subBlock(i,j,nv); // put in nv

      // count options
      int cnt = count_if(nv.begin(), nv.end(), isOne);
      //cout << "subblock: "<<i<<j<<" has ["<<cnt<<"] options\n";
      if(cnt == 1) // if only 1 option (num goes at 1)
      {
        isUpdated = true;
        // find 1's location
        for(int si = i*3; si < 3*(i+1); si++)
         for(int sj = j*3; sj < 3*(j+1); sj++)
          if(opt1[si][sj] == 1){
            cout << "putting [" << num << "]";
            cout << " at ij = " << si << sj << '\n';
            puzzle[i][j] = num;
          }
      }
    }
  }
  return isUpdated;
}

bool Sp::chk4_2pinBlk()
{
  // check for 2 pencil marks in a cell from block
  vector<int> cellhit;
  vector<vector<int> > nv;
  bool isUpdated = false;

  // check block rows
  for(int bi = 0; bi < 3; bi++)
  {
    // check block cols
    for(int bj = 0; bj < 3; bj++)
    {
      cellhit.clear();
      nv.clear();
      int is = 3*bi;
      int js = 3*bj;
      for(int i = is; i < is+3; i++)
        for(int j = js; j < js+3; j++)
        {
          int icell = i*9 + j;
          if(pv[icell].size() == 2) // store pairs
          {
            nv.push_back(pv[icell]);
            cellhit.push_back(icell);
          }
        }

      // check pair of cells
      if(cellhit.size() == 2)
      {
          int c0 = cellhit[0];
          int c1 = cellhit[1];

          if(is_pair_match(c0, c1))
          {
            isUpdated = true;
            int row0 = c0 / 9;
            int row1 = c1 / 9;
            int col0 = c0 % 9;
            int col1 = c1 % 9;

            if(row0 == row1)
              clear_row_pair(c0, c1);
            if(col0 == col1)
              clear_col_pair(c0, c1);
            clear_blk_pair(c0, c1);
          }
      }
    }
  }

  return isUpdated;
}

void Sp::cross_check_num(const int n)
{
  // loop thru all cells
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
    {
      // get value in cell
      int val = puzzle[i][j];
      if (val == n)  // found n at cell ij
      {
        int cell = 9*i+j;
        int row = i;
        int col = j;

        vc[cell].set_value(val);

        opt1[i][j] = 2; // value itself
        rm_row(i,j);
        rm_col(i,j);
        rm_blk(i,j);
      }
    }
}

bool Sp::process_smc(vector<vector<int> > &smc)
{
  int inRow[9];
  int inCol[9];

  bool flag = false;

  for(int im = 1; im < smc.size(); im++)     // loop over: marks
  {
    for(int i = 0; i < 9; i++){ // reset flags
      inRow[i] = 0;
      inCol[i] = 0;
    }
    for(int jc = 0; jc < smc[im].size(); jc++) // loop over: cells
    {
      int row = jc / 9;
      int col = jc % 9;
      inRow[row] = 1;
      inCol[col] = 1;
    }

    int rowsum = 0;
    int colsum = 0;
    // sum up rows and columns for each mark
    for(int i = 0; i < 9; i++){
      rowsum += inRow[i];
      colsum += inCol[i];
    }
    if(rowsum == 1)
    {
      //cout << "only 1 row for mark: " << im << endl;
      for(int i = 0; i < 9; i++){
        if(inRow[i] == 1) // wipe row
          wipe_row_but_spare_cells(i,im,smc[im]);
      }
    }
    if(colsum == 1)
    {
      //cout << "only 1 col for mark: " << im << endl;
      for(int i = 0; i < 9; i++){
        if(inCol[i] == 1) // wipe column
          wipe_col_but_spare_cells(i,im,smc[im]);
      }
    }
    //
  }
  return flag;
}

void Sp::update_mcv()
{
  for(auto mark : mcv)
      mark.clear();

  for(int im = 1; im <= NPM ; im++)     // loop over: marks
    for(int jc = 0; jc < NCELLS ; jc++) // loop over: cells
      if(cell_has_mark(jc, im))
        mcv[im].push_back(jc); //put cell in mcv
}
