#ifndef CELL_H
#define CELL_H

#include <vector>

class Cell
{
  public:
    // Semiregular:
    // constructors
    Cell();                          //default constructor
    Cell(const int cn);              //constructor
    Cell(const int r, const  int c); //constructor
    Cell(const Cell& x);             //copy constructor
    ~Cell() {}                       // destructor
    Cell& operator=(const Cell& x);   // copy assign

    // Regular
    friend
    bool operator==(const Cell& x, const Cell& y) {
      return x.cell_num == y.cell_num;
    }
    friend
    bool operator!=(const Cell& x, const Cell& y) {
       return !(x == y);
    }
    //
    // TotallyOrdered
    friend
    bool operator<(const Cell& x, const Cell& y) {
      return x.cell_num < y.cell_num;
    }
    friend
    bool operator>(const Cell& x, const Cell& y) {
      return y < x;
    }
    friend
    bool operator<=(const Cell& x, const Cell& y) {
      return !(y < x);
    }
    friend
    bool operator>=(const Cell& x, const Cell& y) {
      return !(x < y);
    }

    void set_value(const int n);

    int  get_value() const { return value; }
    int  get_row() const { return row; }
    int  get_col() const { return col; }
    int  get_block() const { return block; }
    int  get_cell_num() const { return cell_num; }
    int  get_mark_cnt()  const {return mark.size(); }
    int  get_mark(const int n) const  { if(mark.size() > n ) return mark[n]; else return 0; }
    int  get_last_mark()  const {return mark.back(); }
    std::vector<int> get_marks() const { return mark;}
    void rm_cmark(const int num);
    bool has_mark(const int mx);

    void print_values();

  private:
    int cell_num;
    int row;
    int col;
    int block;
    int value;
    std::vector<int> mark;
};

#endif
