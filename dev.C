#include "sd.H"


// dev zone
void Sp::check_houses()
{
  // find house given cell
  // house is all cells in same block or row or col
  for( auto& cx : vc)
  {
    vector<Cell> ch;

    // build house
    for( auto& ci : vc)
    {
      if(ci == cx) continue; //skip self
      if(ci.get_row()   == cx.get_row() ||
         ci.get_col()   == cx.get_col() ||
         ci.get_block() == cx.get_block() )
         ch.push_back(ci); //shared house
    }


    // sort house
    std::sort(ch.begin(), ch.end());
    auto it = std::unique(ch.begin(), ch.end());
    ch.resize(std::distance(ch.begin(), it));


    //cout << "Before: ";
    //cx.print_values();
    //
    // use house
    for( auto& icell : ch)
    {
      // find value that house already has
      int hval = icell.get_value();

      // remove house value from target cell's marks
      cx.rm_cmark(hval);
    }
    // check what target cell looks like now
    //
    //cout << "After : ";
    //cx.print_values();
  }
}

void Sp::cmg_mcb(const int mark, const int col, const int block)
{
  // clear mark given mark col block
  // rm [mark] in [col]umn for blocks not in [block]
  for( auto& ci : vc)
    if( ci.get_col()   == col   &&
        ci.get_block() != block )
       ci.rm_cmark(mark);
}

bool Sp::chk4_paired_marks()
{
  // for each block, find mark that occurs only in 1 row or 1 col

  //  /*

  for(int iblock=0; iblock < 9; iblock++) // loop over subblocks
  {
    cout <<  "iblock = " << iblock << endl;

    vector<Cell> blockset;

    // build sub-block
    for( auto& ci : vc)
      if( ci.get_block() == iblock )
         blockset.push_back(ci);

    //build mark_in_row vector
    vector<vector<int>> mr;
    vector<vector<int>> mc;
    mr.resize(10);
    mc.resize(10);

    // build mark in row[mark][row]
    // m[1] = 1 2 3 4 ..
    // m[2] = 1
    // m[3] = 1 2 3
    for(int im = 1; im < 10; im++)  //mark loop
    {
      for( auto& bci : blockset)
      {
        for(int jr = 0; jr < 9; jr++)  //row loop
          if(bci.has_mark(im) && bci.get_row() == jr)
            mr[im].push_back(jr);

        for(int jc = 0; jc < 9; jc++)  //col loop
          if(bci.has_mark(im) && bci.get_col() == jc)
            mc[im].push_back(jc);
      }
    }

    // find unique set of rows && cols
    for(int i = 1; i < mr.size(); i++)
    {
      std::sort(mr[i].begin(), mr[i].end());
      auto itr = std::unique(mr[i].begin(), mr[i].end());
      mr[i].resize(std::distance(mr[i].begin(), itr));

      std::sort(mc[i].begin(), mc[i].end());
      auto itc = std::unique(mc[i].begin(), mc[i].end());
      mc[i].resize(std::distance(mc[i].begin(), itc));
    }
    //
    // print mr set
    //for(int i = 1; i < mr.size(); i++)
    //{
    //  if(mr[i].size() == 0) continue;
    //  cout << "mr [" << i << "] =>";
    //  for (auto rr : mr[i])
    //    cout << " " << rr ;
    //  cout << endl;
    //}

    // print mc set
    for(int i = 1; i < mc.size(); i++)
    {
      if(     mc[i].size() == 0) continue;
      else if(mc[i].size() == 1)
      {
        int hm = i;
        int hc = mc[i][0];
        int hb = iblock;
        cmg_mcb(hm, hc, hb);
        cout << "HIT on MCB= "
             << " " << hm
             << " " << hc
             << " " << hb
             << endl;
        return true;
      }
      //cout << "mc [" << i << "] =>";
      //for (auto rr : mc[i])
      //  cout << " " << rr ;
      //cout << endl;
    }
  }
  return false;
}

bool Sp::isPossible(const int row, const int col, const int num)
{
  // cant put num in rc if it is already in row, col, block
  Cell tcell(row,col);
  // check row
  for(auto& c: vc)
    if(c.get_row()   == row ||
       c.get_col()   == col ||
       c.get_block() == tcell.get_block())
    {
      if(c.get_value() == num)
        return false;
    }
  return true;
}

int minVal(const vector<Cell>& vc)
{
  int m = 10;
  for(auto& c: vc){
    int val = c.get_value();
    if(val < m){
      m = val;
    }
  }
  return m;
}


int Sp::solve()
{
  // iterate through each cell
  for(auto& c: vc){
    if (c.get_value() == 0){
      // try all the numbers
      for(int n=1; n<10; n++){
        // put value if possible
        if(isPossible(c.get_row(), c.get_col(), n)){
          c.set_value(n);
          // solve recursively
          int s = solve();

          // didnt work. backtrack
          if (s==1 && minVal(vc) < 1){
            c.set_value(0);
          }
        }
      }
      return 1;
    }
  }
  return 0;
}


#if 0
bool Sp::is_mark_on_1blk_row()
{
  // check for pencil marks in a single block row
  vector<int> cellhit;
  vector<vector<int> > nv; //number vector
  bool isUpdated = false;

  // loop over: block rows
  for(int bi = 0; bi < 3; bi++)
  {
    // loop over: block cols
    for(int bj = 0; bj < 3; bj++)
    {
      cellhit.clear();
      nv.clear();
      int is = 3*bi;
      int js = 3*bj;

      // loop over: cells in block
      for(int i = is; i < is+3; i++)
        for(int j = js; j < js+3; j++)
        {
          int icell = i*9 + j;
          int row = icell / 9;
          int col = icell % 9;
          // loop over: pencil marks
          for(int k = 1; k <= 9; k++)
          {
            for(int pm : pv[icell])
            {
              if(pm == k)
            }

          }
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
#endif
