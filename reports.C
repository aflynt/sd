#include "sd.H"
// reporting methods (print xyz)

void Sp::print_puzzle()
{
  //print puzzle[i][j]

  cout << "PUZ 0 1 2   3 4 5   6 7 8"   << endl;
  for(int i = 0; i < 9; i++)
  {
    if(i%3 == 0)
      cout << "  +-------+-------+-------+" << endl;
    cout << i << " ";
    for(int j = 0; j < 9; j++)
    {
      int val = puzzle[i][j];
      if(j%3 == 0)
        cout << "| ";
      if(val == 0)
        cout << "." << " ";
      else
        cout << val << " ";
    }
    cout << "| " << endl;
  }
   cout << "  +-------+-------+-------+" << endl;
}

void Sp::print_2Dmarks()
{
  // print number of marks in each cell
  cout << "MKs 0 1 2   3 4 5   6 7 8"   << endl;
  cout << "  +-------+-------+-------+" << endl;
  // loop over cells
  for(int i = 0; i < vc.size(); i++){
    if((i)%9 == 0)
      cout << i/9 << " " ;

    if(i%3 == 0)
      cout << "| ";

    int nmarks = vc[i].get_mark_cnt();
    if(nmarks == 0)
      cout << "." << " ";
    else
      cout << nmarks << " ";

    if((i+1)%9 == 0)
      cout << "|" << endl;
    if((i+1)%27 == 0)
      cout << "  +-------+-------+-------+" << endl;
  }
}

void Sp::print_options()
{
  // print options from opt[i][j] array
  cout << "OPT 0 1 2   3 4 5   6 7 8"   << endl;
  for(int i = 0; i < 9; i++)
  {
    if(i%3 == 0)
      cout << "  +-------+-------+-------+" << endl;
    cout << i << " ";
    for(int j = 0; j < 9; j++)
    {
      int val = opt1[i][j];
      if(j%3 == 0)
        cout << "| ";
      if(val == 3)
        cout << "*" << " ";
      else if(val == 1)
        cout << "." << " ";
      else if(val == 9)
        cout << "x" << " ";
      else
        cout << "#" << " ";
    }
    cout << "| " << endl;
  }
   cout << "  +-------+-------+-------+" << endl;
}

void Sp::print_mcv_vals()
{
  // print mark cell values
  // mark[1-9] has jcells
  update_mcv();
  for(int im = 1; im < mcv.size(); im++)
  {
    cout << "mark[" << im << "]: ";
    //for(int icell : mcv[im])
    for(int jc = 0; jc < mcv[im].size(); jc++)
    {
      int icell = mcv[im][jc];
      int row = icell / 9;
      int col = icell % 9;
      cout << " " <<  row  << col ;
    }
    cout << endl;
  }
}

void Sp::print_cell_marks()
{
  //print pencil vector values for each cell
  for(int icell = 0; icell < vc.size(); icell++)
  {
    //int row = icell / 9;
    //int col = icell % 9;
    int row = vc[icell].get_row();
    int col = vc[icell].get_col();

    cout << "rc=" << row << col;
    for(int j = 0; j < vc[icell].get_mark_cnt(); j++)
    {
      cout << " " << vc[icell].get_mark(j);
    }
    cout << endl;
  }
}

void Sp::print_sb(const int sbi, const int sbj)
{
  // print sub-block given subrow i , subcol j
  // sbi[0-2] sbj[0-2]
  int is = 3*sbi;
  int js = 3*sbj;

  for(int i = is; i < is+3; i++)
  {
    cout << endl;
    for(int j = js; j < js+3; j++)
      cout << puzzle[i][j];
  }
    cout << endl;
}
