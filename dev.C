#include "sd.H"

int check_random()
{
  cout << "this is great\n";
}

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
