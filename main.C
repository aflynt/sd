#include "sd.H"

int main(int argc, char * argv[])
{
  if (argc != 2){cout << "Name a file!\n";
    return 1;}

  ifstream ifs;
  ifs.open(argv[1], std::ofstream::in);
  if(!ifs.is_open()){
    cout << "error no file open\n";
    return 1;}

  Sp a;
  a.read_puzzle(ifs);
  a.print_puzzle();
  a.solve();
  a.print_puzzle();

#if 0
  cout << "pick a cell: (r,c) and num\n";
  int rr, cc, num;
  while ((cin >> rr >> cc >> num) && rr > -1)
  {
    cout << "POSSIBLE = " << a.isPossible(rr,cc,num) << endl;
    a.print_puzzle();
  }

  int nc = 1;
  for(int nc = 1; nc < 10; nc++)
  //while ((cin >> nc) && nc > 0)
  {
    cout << "=== Looking for "<< nc << "\n";
    cout << "=================\n";
    a.print_puzzle();
    a.print_2Dmarks();

    //int bar;
    //cin >> bar;
    int rr=0, cc=0, num=1;
    cout << "pick a cell: (r,c) and num\n";
    while ((cin >> rr >> cc >> num) && rr > -1)
    {
      //Cell cn(rr,cc);
      int cell = rr * 9 + cc;
      Cell cn = a.get_cell(cell);
      //a.find_house(cn);
      cout << "POSSIBLE = " << a.isPossible(rr,cc,num) << endl;
      //cc.print_values();
    }

    a.check_houses();
    a.get_options(nc);
    a.chk_pmarks();

    if(a.chk4_1pinBlk()){ /*continue;*/; }
    if(a.chk4_2pinBlk()){ /*continue;*/; }
    //if(a.chk4_paired_marks()){ nc = 0; continue; }
    if(a.chk4_1inRow(nc)){ nc = 0; continue; }
    if(a.chk4_1inCol(nc)){ nc = 0; continue; }
    if(a.chk4_1inBlk(nc)){ nc = 0; continue; }


    cout << "give a num [1-9] (or <= 0 to quit)\n";
  }
#endif

  // Final Actions
  //a.print_puzzle();
  //a.print_cell_marks();


  return 0;
}
      //Cell* cp = &cn;
      //cp->print_values();
      //Cell cb = cn;
      //Cell cc;
      //cc = cb;
      //cn.print_values();
      //cb.print_values();

      // testing for less than
      //cout << "c"
      //     << cn.get_cell_num()
      //     << " <= c"
      //     << cb.get_cell_num()
      //     << "?[" << (cn <= cb) << "]\n";
      //cb = a.get_cell(cell-1);
      //cout << "c"
      //     << cn.get_cell_num()
      //     << " <= c"
      //     << cb.get_cell_num()
      //     << "?[" << (cn <= cb) << "]\n";

      //vector<int> imarks = cn.get_marks();
      //cout << "imarks:";
      //for (int im : imarks)
      //  cout << " " << im;
      //cout << endl;
