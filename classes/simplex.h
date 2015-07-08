#ifndef SIMPLEX_H_
#define SIMPLEX_H_

class jrObjectiveFunction
{
public:
  virtual double evaluate(double uv[2]) const = 0;
};


void nelderMeadMinimumSearch( jrObjectiveFunction const & of,
    int n,
    double start[],
    double xmin[],
    double step[],
    double *ynewlo,
    int *icount,
    int *numres,
    int *ifault,
    double reqmin = 1.0e-8,
    int konvge = 10,
    int kcount = 500);

//void nelderMeadMinimumSearch ( ObjectiveFunction const &of,
//              int n,
//              double start[],
//              double xmin[],
//              double *ynewlo,
//              double reqmin,
//              double step[],
//              int konvge, int kcount,
//        int *icount,
//              int *numres,
//              int *ifault );


#endif /* SIMPLEX_H_ */
