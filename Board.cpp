#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <bitset>
 
using namespace std; 

typedef uint32_t cboard; //compressed board as a single integer
typedef uint32_t* lboard; //board as a 25x1 array


////////Basic Board functions///////////

/*
makes a move on a given compressed board and
returns the resulting compressed board
*/

bool valid_square(int m){
    return (m > -1) && (m < 25);
}

cboard make_move(cboard Board, int m){
  uint32_t move = 0;
  
  move = move | (1 << m);                                          //square pressed
  move = (valid_square(m+1) && m%5 != 4)? move | (1 << m+1): move; //square to the right
  move = (valid_square(m-1) && m%5 != 0)? move | (1 << m-1): move; //square to the left
  move = (valid_square(m+5))? move | (1 << m+5): move;             //square above
  move = (valid_square(m-5))? move | (1 << m-5): move;             //square below

  cboard result = Board ^ move;    // Make the move by flipping the 5 squares
  
  return result;
}

void print_board(cboard B){
    bitset<25> B2 = bitset<25>(B);
    
    for(int i = 0; i < 25; i++){
        if(i % 5 == 4){
            cout << B2[i] << endl;
        }
        else{
            cout << B2[i] << " ";
        }
    }
    cout << " " << endl;
}
