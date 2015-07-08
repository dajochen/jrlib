/*
 * tMartrix.h
 *
 *  Created on: 22.01.2010
 *      Author: Jochen
 */
//
//       Matrix
//   |  1 2 3 . . . n |
//   | 1    .         |
//   | 2    .         |
//   | 3    .         |
//   | .    .         |
//   | .    .         |
//   | .    .         |
//   | n. A[n][3] . n |
//

#ifndef TMARTRIX_H_
#define TMATRIX_H_

#include <math.h>
#include "classes/jrTypes.h"

class tMatrix {
  tReal* data;
  int fni, fnj;
  void clear(void);

public:
  tMatrix();
  //tMatrix(const tMatrix& rhs);
  tMatrix(int ni,int nj);
  void setSize(const int ni, const int nj);
  void init(void);
  int ni(void) const;
  int nj(void) const;
  virtual ~tMatrix();
  tReal at(int i, int j) const;
  void setAt(int i, int j, tReal value);
  void multiply(tReal);
  tMatrix transpose(void);
  tMatrix inverse(void);
  tMatrix& operator= (const tMatrix& rhs);

//  tMatrix operator= (tMatrix RHS);
};

#endif /* TMARTRIX_H_ */
