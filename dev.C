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

void Sp::chk4_paired_marks()
{
  // for each block, find mark that occurs only in 1 row or 1 col

  //  /*

  for(int iblock=0; iblock < 9; iblock++) // loop over subblocks
  {
    cout <<  "iblock = " << iblock;

    vector<Cell> blockset;

    // build sub-block
    for( auto& ci : vc)
      if( ci.get_block() == iblock )
         blockset.push_back(ci);

    //build mark_in_row vector
    vector<vector<int>> mark_in_row;
    vector<vector<int>> mark_in_col;
    for(int mi=0; mi < 10; mi++)
    {
      mark_in_row.pushback(mi);
      mark_in_col.pushback(mi);
    }

    for(int im = 1; im < 10; im++)  //mark loop
    {
      for( auto& bci : blockset)
      {
        for(int jr = 0; jr < 9; jr++)  //row loop
          if(bci.has_mark(im) && bci.get_row() == jr)
            mark_in_row[im].push_back(jr);

        for(int jc = 0; jc < 9; jc++)  //col loop
          if(bci.has_mark(im) && bci.get_col() == jc)
            mark_in_col[im].push_back(jc);
      }
    }

    for (auto mr : mark_in_row)
      cout << "mr = " << mr << " with:" <<;
      for (auto rr : mr)
        cout << "" << rr ;
  }

#if 0
  }
    // sort house
    std::sort(blockset.begin(), blockset.end());
    auto it = std::unique(blockset.begin(), blockset.end());
    blockset.resize(std::distance(blockset.begin(), it));


    //cout << "Before: ";
    //cx.print_values();
    //
    // use house
    for( auto& icell : blockset)
    {
      // find value that house already has
      int hval = icell.get_value();

      // remove house value from target cell's marks
      cx.rm_cmark(hval);
    }

   // */
    // check what target cell looks like now
    //
    //cout << "After : ";
    //cx.print_values();
#endif
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
