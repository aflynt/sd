#include <vector>

class Cell
{
  public:
    Cell(const int cn);
    Cell(const int r, const  int c);
    void set_value(const int n);

    int  get_value(){ return value; }
    int  get_row(){ return row; }
    int  get_col(){ return col; }
    int  get_block(){ return block; }
    int  get_cell_num(){ return cell_num; }
    int  get_mark_cnt() {return mark.size(); }
    int  get_mark(const int n) {return mark[n]; }
    int  get_last_mark() {return mark.back(); }
    std::vector<int> get_marks(){ return mark;}
    void rm_cmark(const int num);

    void print_values();

  private:
    int cell_num;
    int row;
    int col;
    int block;
    int value;
    std::vector<int> mark;
};
