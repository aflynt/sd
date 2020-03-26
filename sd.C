#include "sd.H"

// default constructor
Sp::Sp()
{
  // Set all puzzle positions to 0. No value taken
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      puzzle[i][j] = 0;

  // set all options to 1. 1 == ??
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
      opt1[i][j] = 1;

  // initialize Cells
  for(int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++)
    {
      Cell cn(i,j);
      vc.push_back(cn);
    }
}

void Sp::read_puzzle(ifstream& ifs)
{
  string delim = "+";
  size_t pos = 0;
  string line;

  int ii = 0;
  int jj = 0;

  // loop thru rows (aka "i")
  for(int i=0; getline(ifs, line);i++ ){

    // skip comment lines
    if( (pos = line.find(delim)) != std::string::npos)
      continue;

    // loop through line (aka "j")
    jj=0;
    for(int j = 0; j < line.size();j++)
    {
      char c = line[j];
      if(ispunct(c)) // skip non-numbers
        ; //cout << '|' ;
      else           // put numbers into array
      {
        puzzle[ii][jj ] = atoi(&c);
        int cell = ii*9 + jj;
        vc[cell].set_value( puzzle[ii][jj] );
        jj++;
      }
    }
    ii++;
  }
}

