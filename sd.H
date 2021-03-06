#include <iostream> //std::cout
#include <fstream>  //std::filebuf, std::ifstream
#include <cmath>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "cell.H"
using namespace std;

int minVal(const vector<Cell>& vc);

//To do
// [1] 2 remove pv vector<vector<int>>
// [ ] 3 where do i use the wipe_rc_but_spare_cells() ??
// [ ] 4 rm globals

class Sp
{
  public:
    // sd.c
    Sp(); // default ctor defined
    void read_puzzle(ifstream& ifs);

    // reports.c
    void print_puzzle();
    void print_options();
    void print_2Dmarks();
    void print_mcv_vals();
    void print_cell_marks();
    void print_sb(const int sbi, const int sbj);

    // searches.c
    bool num_in_row(const int num, const int row);
    bool num_in_col(const int num, const int col);

    void report_num_in_row(const int num);
    void report_num_in_col(const int num);

    bool is_pair_match(const int c0, const int c1);
    bool cell_has_mark(const int cell, const int mark);


    // gets.c
    Cell get_cell(const int cnum);
    void get_subBlock(const int sbi, const int sbj, vector<int> &vsb);
    void get_sb_cells(const int sbi, const int sbj, vector<int> &vsb);
    int get_Prc(const int row, const int col){return puzzle[row][col];}

    void get_options(const int n);
    void reset_options();

    // checks.c
    bool chk4_1inRow(const int num);
    bool chk4_1inCol(const int num);
    bool chk4_1inBlk(const int num);
    void chk_pmarks();
    bool chk4_1pmark();
    bool chk4_2pinBlk();
    bool chk4_1pinBlk();
    void cross_check_num(const int n);
    bool process_smc(vector<vector<int> > &smc);
    void update_mcv();

    void check_houses();
    bool chk4_paired_marks();

    // actions.c
    void rm_row(const int ipos, const int jpos);
    void rm_col(const int ipos, const int jpos);
    void rm_blk(const int ipos, const int jpos);
    void wipe_row_but_spare_cells(const int row,
                                  const int mark, vector<int> sc);
    void wipe_col_but_spare_cells(const int col,
                                  const int mark, vector<int> sc);

    void rm_pin_row(const int cell, const int num);
    void rm_pin_col(const int cell, const int num);
    void rm_pin_blk(const int cell, const int num);
    // RMM void rm_allpmarks(const int cell, const int num);
    // RMM void rm_pmark(const int cell, const int num);

    void clear_row_pair(const int cell0, const int cell1);
    void clear_col_pair(const int cell0, const int cell1);
    void clear_blk_pair(const int cell0, const int cell1);
    void cmg_mcb(const int mark, const  int col, const int block);
    bool isPossible(const int row, const int col, const int num);
    int solve();

  private:
    int puzzle[9][9];
    int opt1[9][9];          //options 2D array
    vector<Cell> vc;
};

