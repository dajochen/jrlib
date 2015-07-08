#include "tDxfSpline.h"
#include "tPoint.h"

tDxfSpline::tDxfSpline(void *theOwner) : tAbstractSpline(theOwner)
{
    isClosed = false;
    degree = 3;
    hs = new tHermiteSpline(this);
    hs->setTension(1.);
    hs->setBias(1.);
}

tDxfSpline::~tDxfSpline()
{
    hs->releaseOwner(this);
}


iElement *tDxfSpline::intrface()
{
    if (iface == NULL){
        iface = new iDxfSpline(this);
    }
    return iface;
}

void tDxfSpline::refresh()
{
    hs->removeAllVertices();
    /*
    for (int i=0; i<nVertices(); i++){
        hs->addVertex(vertex(i));
    }*/

    if (nVertices()>2){
        UpdateControlPoints();
        updateXX();
    }
    /*
    if (data.degree<1 || data.degree>3) {
        RS_DEBUG->print("RS_Spline::update: invalid degree: %d", data.degree);
        return;
    }

    if (data.controlPoints.size() < data.degree+1) {
        RS_DEBUG->print("RS_Spline::update: not enough control points");
        return;
    }
*/
    // controlpoints berechnen.
}

tVector tDxfSpline::vectorAtAccurate(tReal t)
{
    return hs->vectorAt(t);//tVector(0,0,0);
}

double* tDxfSpline::GetMatrix(int iCount, double *dt)
{
    if(isClosed && iCount < 3) return NULL;
    if(!isClosed && iCount < 4) return NULL;

    int iDim = 0;
    if(isClosed) iDim = 5*iCount - 6; // n + 2*(n - 1) + 2*(n - 2)
    else iDim = 3*iCount - 8; // (n - 2) + 2*(n - 3)

    double *dRes = new double[iDim];

    double x1, x2, x3;

    if(isClosed)
    {
        double *pdDiag = dRes;
        double *pdDiag1 = &dRes[iCount];
        double *pdDiag2 = &dRes[2*iCount - 1];
        double *pdLastCol1 = &dRes[3*iCount - 2];
        double *pdLastCol2 = &dRes[4*iCount - 4];

        x1 = (1.0 - dt[0])*(1.0 - dt[0])/2.0;
        x3 = dt[0]*dt[0]/2.0;
        x2 = x1 + 2.0*dt[0]*(1.0 - dt[0]) + x3;

        pdDiag[0] = sqrt(x2);
        pdDiag1[0] = x3/pdDiag[0];
        pdLastCol1[0] = x1/pdDiag[0];

        x1 = (1.0 - dt[1])*(1.0 - dt[1])/2.0;
        x3 = dt[1]*dt[1]/2.0;
        x2 = x1 + 2.0*dt[1]*(1.0 - dt[1]) + x3;

        pdDiag2[0] = x1/pdDiag[0];

        pdDiag[1] = sqrt(x2 - pdDiag1[0]*pdDiag2[0]);
        pdDiag1[1] = x3/pdDiag[1];
        pdLastCol1[1] = -pdDiag2[0]*pdLastCol1[0]/pdDiag[1];

        for(int i = 2; i < iCount - 2; i++)
        {
            x1 = (1.0 - dt[i])*(1.0 - dt[i])/2.0;
            x3 = dt[i]*dt[i]/2.0;
            x2 = x1 + 2.0*dt[i]*(1.0 - dt[i]) + x3;

            pdDiag2[i - 1] = x1/pdDiag[i - 1];

            pdDiag[i] = sqrt(x2 - pdDiag1[i - 1]*pdDiag2[i - 1]);
            pdDiag1[i] = x3/pdDiag[i];
            pdLastCol1[i] = -pdDiag2[i - 1]*pdLastCol1[i - 1]/pdDiag[i];
        }
        x1 = (1.0 - dt[iCount - 2])*(1.0 - dt[iCount - 2])/2.0;
        x3 = dt[iCount - 2]*dt[iCount - 2]/2.0;
        x2 = x1 + 2.0*dt[iCount - 2]*(1.0 - dt[iCount - 2]) + x3;

        pdDiag2[iCount - 3] = x1/pdDiag[iCount - 3];

        pdDiag[iCount - 2] = sqrt(x2 - pdDiag1[iCount - 3]*pdDiag2[iCount - 3]);
        pdDiag1[iCount - 2] = (x3 - pdDiag2[iCount - 3]*pdLastCol1[iCount - 3])/pdDiag[iCount - 2];

        x1 = (1.0 - dt[iCount - 1])*(1.0 - dt[iCount - 1])/2.0;
        x3 = dt[iCount - 1]*dt[iCount - 1]/2.0;
        x2 = x1 + 2.0*dt[iCount - 1]*(1.0 - dt[iCount - 1]) + x3;

        pdLastCol2[0] = x3/pdDiag[0];
        double dLastColSum = pdLastCol1[0]*pdLastCol2[0];
        for(int i = 1; i < iCount - 2; i++)
        {
            pdLastCol2[i] = -pdLastCol2[i - 1]*pdDiag1[i - 1]/pdDiag[i];
            dLastColSum += pdLastCol1[i]*pdLastCol2[i];
        }

        pdDiag2[iCount - 2] = (x1 - pdDiag1[iCount - 3]*pdLastCol2[iCount - 3])/pdDiag[iCount - 2];

        dLastColSum += pdDiag1[iCount - 2]*pdDiag2[iCount - 2];
        pdDiag[iCount - 1] = sqrt(x2 - dLastColSum);
    }
    else
    {
        double *pdDiag = dRes;
        double *pdDiag1 = &dRes[iCount - 2];
        double *pdDiag2 = &dRes[2*iCount - 5];

        x3 = dt[0]*dt[0]/2.0;
        x2 = 2.0*dt[0]*(1.0 - dt[0]) + x3;
        pdDiag[0] = sqrt(x2);
        pdDiag1[0] = x3/pdDiag[0];

        for(int i = 1; i < iCount - 3; i++)
        {
            x1 = (1.0 - dt[i])*(1.0 - dt[i])/2.0;
            x3 = dt[i]*dt[i]/2.0;
            x2 = x1 + 2.0*dt[i]*(1.0 - dt[i]) + x3;

            pdDiag2[i - 1] = x1/pdDiag[i - 1];
            pdDiag[i] = sqrt(x2 - pdDiag1[i - 1]*pdDiag2[i - 1]);
            pdDiag1[i] = x3/pdDiag[i];
        }

        x1 = (1.0 - dt[iCount - 3])*(1.0 - dt[iCount - 3])/2.0;
        x2 = x1 + 2.0*dt[iCount - 3]*(1.0 - dt[iCount - 3]);
        pdDiag2[iCount - 4] = x1/pdDiag[iCount - 4];
        pdDiag[iCount - 3] = sqrt(x2 - pdDiag1[iCount - 4]*pdDiag2[iCount - 4]);
    }

    return(dRes);
}


#define RS_TOLERANCE 1.0e-10

void tDxfSpline::UpdateControlPoints()
{
    controlPoints.clear();
    //tList<tVector> controlPoints;
    int n = nVertices();

    if(isClosed && n < 3)
    {
        if(n > 0) controlPoints.append(vertex(0)->vector());
        if(n > 1) controlPoints.append(vertex(1)->vector());
        return;
    }

    if(isClosed && n < 4)
    {
        if(n > 0) controlPoints.append(vertex(0)->vector());
        if(n > 2)
        {
            tVector x1 = vertex(0)->vector(),
                    x2 = vertex(1)->vector(),
                    x3 = vertex(2)->vector();

            double dl1 = (x2 - x1).length();
            double dl2 = (x3 - x2).length();
            double dt = dl1/(dl1 + dl2);

            if(dt < RS_TOLERANCE || dt > 1.0 - RS_TOLERANCE)
                //return RS_Vector(false);
                controlPoints.append((x2 - x1*(1.0 - dt)*(1.0 - dt) - x3*dt*dt)*(1./dt/(1 - dt)/2.0));
        }
        if(n > 1) {
            controlPoints.append(vertex(n - 1)->vector());
        }
        return;
    }

    int iDim = 0;
    if(isClosed) {
        iDim = n;
    } else {
        iDim = n - 2;
    }

    double *dt = new double[iDim];
    double dl1, dl2;

    if(isClosed)  {
        dl1 = (vertex(n - 1)->vector() - vertex(0)->vector()).length();
        dl2 = (vertex(1)->vector()     - vertex(0)->vector()).length();
        dt[0] = dl1/(dl1 + dl2);
        for(int i = 1; i < iDim - 1; i++)
        {
            dl1 = dl2;
            dl2 = (vertex(i + 1)->vector() - vertex(i)->vector()).length();
            dt[i] = dl1/(dl1 + dl2);
        }
        dl1 = (vertex(n - 1)->vector() - vertex(n - 2)->vector()).length();
        dl2 = (vertex(0)->vector() - vertex(n - 1)->vector()).length();
        dt[iDim - 1] = dl1/(dl1 + dl2);
    } else {
        dl1 = (vertex(1)->vector() - vertex(0)->vector()).length();
        dl2 = (vertex(2)->vector() - vertex(1)->vector()).length();
        dt[0] = dl1/(dl1 + dl2/2.0);
        for(int i = 1; i < iDim - 1; i++)
        {
            dl1 = dl2;
            dl2 = (vertex(i + 2)->vector() - vertex(i + 1)->vector()).length();
            dt[i] = dl1/(dl1 + dl2);
        }
        dl1 = dl2;
        dl2 = (vertex(iDim)->vector() - vertex(iDim + 1)->vector()).length();
        dt[iDim - 1] = dl1/(dl1 + 2.0*dl2);
    }

    double *pdMatrix = GetMatrix(n, dt);

    if(!pdMatrix) return;
    tVector *dx = new tVector[iDim],
            *dx2 = new tVector[iDim];
    /*double *dx = new double[iDim];
    double *dy = new double[iDim];
    double *dx2 = new double[iDim];
    double *dy2 = new double[iDim];*/

    if(isClosed)
    {
        double *pdDiag = pdMatrix;
        double *pdDiag1 = &pdMatrix[n];
        double *pdDiag2 = &pdMatrix[2*n - 1];
        double *pdLastCol1 = &pdMatrix[3*n - 2];
        double *pdLastCol2 = &pdMatrix[4*n - 4];

        dx[0] = vertex(0)->vector() * (1./pdDiag[0]);
        //dx[0] = vertex(0).x/pdDiag[0];
        //dy[0] = vertex(0).y/pdDiag[0];
        for(int i = 1; i < iDim - 1; i++)
        {
            dx[i] = (vertex(i)->vector() - dx[i-1]*pdDiag2[i-1])*(1./pdDiag[i]);
            //dx[i] = (vertex(i).x - pdDiag2[i - 1]*dx[i - 1])/pdDiag[i];
            //dy[i] = (vertex(i).y - pdDiag2[i - 1]*dy[i - 1])/pdDiag[i];
        }

        dx[iDim-1] = vertex(iDim - 1)->vector() - dx[iDim - 2]*pdDiag2[iDim - 2];
        //dx[iDim - 1] = vertex(iDim - 1).x - pdDiag2[iDim - 2]*dx[iDim - 2];
        //dy[iDim - 1] = vertex(iDim - 1).y - pdDiag2[iDim - 2]*dy[iDim - 2];
        for(int i = 0; i < iDim - 2; i++)
        {
            dx[iDim-1] = dx[iDim-1] - (dx[i] * pdLastCol2[i]);
            //dx[iDim - 1] -= (dx[i]*pdLastCol2[i]);
            //dy[iDim - 1] -= (dy[i]*pdLastCol2[i]);
        }
        dx[iDim-1] = dx[iDim-1] * (1./pdDiag[iDim - 1]);
        //dx[iDim - 1] /= pdDiag[iDim - 1];
        //dy[iDim - 1] /= pdDiag[iDim - 1];

        dx2[iDim-1] = dx[iDim-1]*(1./pdDiag[iDim-1]);
        //dx2[iDim - 1] = dx[iDim - 1]/pdDiag[iDim - 1];
        //dy2[iDim - 1] = dy[iDim - 1]/pdDiag[iDim - 1];

        dx2[iDim-2] = (dx[iDim-2]-dx2[iDim-1]*pdDiag1[iDim-2])*(1./pdDiag[iDim - 2]);
        //dx2[iDim - 2] = (dx[iDim - 2] - pdDiag1[iDim - 2]*dx2[iDim - 1])/pdDiag[iDim - 2];
        //dy2[iDim - 2] = (dy[iDim - 2] - pdDiag1[iDim - 2]*dy2[iDim - 1])/pdDiag[iDim - 2];

        for(int i = iDim - 3; i >= 0; i--)
        {
            dx2[i] = (dx[i] - dx2[i + 1]*pdDiag1[i] - dx2[iDim - 1]*pdLastCol1[i])*(1./pdDiag[i]);
            //dx2[i] = (dx[i] - pdDiag1[i]*dx2[i + 1] - pdLastCol1[i]*dx2[iDim - 1])/pdDiag[i];
            //dy2[i] = (dy[i] - pdDiag1[i]*dy2[i + 1] - pdLastCol1[i]*dy2[iDim - 1])/pdDiag[i];
        }

        for(int i = 0; i < iDim; i++)
        {
            controlPoints.append(dx2[i]);
        }
    }
    else
    {
        double *pdDiag = pdMatrix;
        double *pdDiag1 = &pdMatrix[n - 2];
        double *pdDiag2 = &pdMatrix[2*n - 5];

        dx[0] = (vertex(1)->vector() - vertex(0)->vector()*(1.0-dt[0]) * (1.0 - dt[0]))*(1./pdDiag[0]);
        //dx[0] = (vertex(1).x - vertex(0).x*(1.0 - dt[0])*(1.0 - dt[0]))/pdDiag[0];
        //dy[0] = (vertex(1).y - vertex(0).y*(1.0 - dt[0])*(1.0 - dt[0]))/pdDiag[0];
        for(int i = 1; i < iDim - 1; i++)
        {
            dx[i] = (vertex(i + 1)->vector() - dx[i-1]*pdDiag2[i-1])*(1./pdDiag[i]);
            //dx[i] = (vertex(i + 1).x - pdDiag2[i - 1]*dx[i - 1])/pdDiag[i];
            //dy[i] = (vertex(i + 1).y - pdDiag2[i - 1]*dy[i - 1])/pdDiag[i];
        }

        dx[iDim-1] = ((vertex(iDim)->vector() - vertex(iDim + 1)->vector()*dt[n-3]*dt[n-3]) - dx[iDim-2]*pdDiag2[iDim-2])*(1./pdDiag[iDim-1]);
        //dx[iDim - 1] = ((vertex(iDim).x - vertex(iDim + 1).x*dt[n - 3]*dt[n - 3]) -
        //    pdDiag2[iDim - 2]*dx[iDim - 2])/pdDiag[iDim - 1];
        //dy[iDim - 1] = ((vertex(iDim).y - vertex(iDim + 1).y*dt[n - 3]*dt[n - 3]) -
        //    pdDiag2[iDim - 2]*dy[iDim - 2])/pdDiag[iDim - 1];

        dx2[iDim-1] = dx[iDim-1]*(1./pdDiag[iDim - 1]);
        //dx2[iDim - 1] = dx[iDim - 1]/pdDiag[iDim - 1];
        //dy2[iDim - 1] = dy[iDim - 1]/pdDiag[iDim - 1];

        for(int i = iDim - 2; i >= 0; i--)
        {
            dx2[i] = (dx[i]-dx2[i+1]*pdDiag1[i])*(1./pdDiag[i]);
            //dx2[i] = (dx[i] - pdDiag1[i]*dx2[i + 1])/pdDiag[i];
            //dy2[i] = (dy[i] - pdDiag1[i]*dy2[i + 1])/pdDiag[i];
        }

        controlPoints.append(vertex(0)->vector());
        for(int i = 0; i < iDim; i++)
        {
            controlPoints.append(dx2[i]);
        }
        controlPoints.append(vertex(n - 1)->vector());
    }

    delete[] pdMatrix;

    delete[] dt;

    //delete[] dy2;
    delete[] dx2;
    //delete[] dy;
    delete[] dx;
}

/**
 * Generates B-Spline open knot vector with multiplicity
 * equal to the order at the ends.
 */
void tDxfSpline::knot(int num, int order, int knotVector[]) {
    knotVector[1] = 0;
    for (int i = 2; i <= num + order; i++) {
        if ( (i > order) && (i < num + 2) ) {
            knotVector[i] = knotVector[i-1] + 1;
        } else {
            knotVector[i] = knotVector[i-1];
        }
    }
}

/**
 * Generates rational B-spline basis functions for an open knot vector.
 */
void tDxfSpline::rbasis(int c, double t, int npts, int x[], double h[], double r[]) {

    int nplusc;
    int i,k;
    double d,e;
    double sum;
    //double temp[36];

    nplusc = npts + c;

    double* temp = new double[nplusc+1];

    // calculate the first order nonrational basis functions n[i]
    for (i = 1; i<= nplusc-1; i++) {
        if (( t >= x[i]) && (t < x[i+1]))
            temp[i] = 1;
        else
            temp[i] = 0;
    }

    /* calculate the higher order nonrational basis functions */

    for (k = 2; k <= c; k++) {
        for (i = 1; i <= nplusc-k; i++) {
            // if the lower order basis function is zero skip the calculation
            if (temp[i] != 0)
                d = ((t-x[i])*temp[i])/(x[i+k-1]-x[i]);
            else
                d = 0;
            // if the lower order basis function is zero skip the calculation
            if (temp[i+1] != 0)
                e = ((x[i+k]-t)*temp[i+1])/(x[i+k]-x[i+1]);
            else
                e = 0;

            temp[i] = d + e;
        }
    }

    // pick up last point
    if (t == (double)x[nplusc]) {
        temp[npts] = 1;
    }

    // calculate sum for denominator of rational basis functions
    sum = 0.;
    for (i = 1; i <= npts; i++) {
        sum = sum + temp[i]*h[i];
    }

    // form rational basis functions and put in r vector
    for (i = 1; i <= npts; i++) {
        if (sum != 0) {
            r[i] = (temp[i]*h[i])/(sum);
        } else
            r[i] = 0;
    }

    delete[] temp;
}



void tDxfSpline::knotu(int num, int order, int knotVector[]) {
    int nplusc,/*nplus2,*/i;

    nplusc = num + order;
//    nplus2 = num + 2;

    knotVector[1] = 0;
    for (i = 2; i <= nplusc; i++) {
        knotVector[i] = i-1;
    }
}


void tDxfSpline::rbsplinu(int npts, int k, int p1,
                         double b[], double h[], double p[]) {

    int i,j,icount,jcount;
    int i1;
    //int x[30];		/* allows for 20 data points with basis function of order 5 */
    int nplusc;

    double step;
    double t;
    //double nbasis[20];
//    double temp;


    nplusc = npts + k;

    int* x = new int[nplusc+1];
    double* nbasis = new double[npts+1];

    /*  zero and redimension the knot vector and the basis array */

    for(i = 0; i <= npts; i++) {
        nbasis[i] = 0.0;
    }

    for(i = 0; i <= nplusc; i++) {
        x[i] = 0;
    }

    /* generate the uniform periodic knot vector */

    knotu(npts,k,x);

    /*
        printf("The knot vector is ");
        for (i = 1; i <= nplusc; i++){
                printf(" %d ", x[i]);
        }
        printf("\n");

        printf("The usable parameter range is ");
        for (i = k; i <= npts+1; i++){
                printf(" %d ", x[i]);
        }
        printf("\n");
    */

    icount = 0;

    /*    calculate the points on the rational B-spline curve */

    t = k-1;
    step = ((double)((npts)-(k-1)))/((double)(p1-1));

    for (i1 = 1; i1<= p1; i1++) {

        if ((double)x[nplusc] - t < 5e-6) {
            t = (double)x[nplusc];
        }

        rbasis(k,t,npts,x,h,nbasis);      /* generate the basis function for this value of t */
        /*
                        printf("t = %f \n",t);
                        printf("nbasis = ");
                        for (i = 1; i <= npts; i++){
                                printf("%f  ",nbasis[i]);
                        }
                        printf("\n");
        */
        for (j = 1; j <= 3; j++) {      /* generate a point on the curve */
            jcount = j;
            p[icount+j] = 0.;

            for (i = 1; i <= npts; i++) { /* Do local matrix multiplication */
//                temp = nbasis[i]*b[jcount];
//                p[icount + j] = p[icount + j] + temp;
                p[icount + j] += nbasis[i]*b[jcount];
                /*
                                                printf("jcount,nbasis,b,nbasis*b,p = %d %f %f %f %f\n",jcount,nbasis[i],b[jcount],temp,p[icount+j]);
                */
                jcount = jcount + 3;
            }
        }
        /*
                        printf("icount, p %d %f %f %f \n",icount,p[icount+1],p[icount+2],p[icount+3]);
        */
        icount = icount + 3;
        t = t + step;
    }

    delete[] x;
    delete[] nbasis;
}


/**
 * Generates a rational B-spline curve using a uniform open knot vector.
 */
void tDxfSpline::rbspline(int npts, int k, int p1,
                         double b[], double h[], double p[]) {

    int i,j,icount,jcount;
    int i1;
    //int x[30]; /* allows for 20 data points with basis function of order 5 */
    int nplusc;

    double step;
    double t;
    //double nbasis[20];
//    double temp;

    nplusc = npts + k;

    int* x = new int[nplusc+1];
    double* nbasis = new double[npts+1];

    // zero and redimension the knot vector and the basis array

    for(i = 0; i <= npts; i++) {
        nbasis[i] = 0.0;
    }

    for(i = 0; i <= nplusc; i++) {
        x[i] = 0;
    }

    // generate the uniform open knot vector
    knot(npts,k,x);

    icount = 0;

    // calculate the points on the rational B-spline curve
    t = 0;
    step = ((double)x[nplusc])/((double)(p1-1));

    for (i1 = 1; i1<= p1; i1++) {

        if ((double)x[nplusc] - t < 5e-6) {
            t = (double)x[nplusc];
        }

        // generate the basis function for this value of t
        rbasis(k,t,npts,x,h,nbasis);

        // generate a point on the curve
        for (j = 1; j <= 3; j++) {
            jcount = j;
            p[icount+j] = 0.;

            // Do local matrix multiplication
            for (i = 1; i <= npts; i++) {
//                temp = nbasis[i]*b[jcount];
//                p[icount + j] = p[icount + j] + temp;
                p[icount + j] +=  nbasis[i]*b[jcount];
                jcount = jcount + 3;
            }
        }
        icount = icount + 3;
        t = t + step;
    }

    delete[] x;
    delete[] nbasis;
}

void tDxfSpline::updateXX() {

    //RS_DEBUG->print("RS_Spline::update");

    //clear();

    //if (isUndone()) {
    //    return;
    //}


    //resetBorders();

    //QList<RS_Vector> tControlPoints = data.controlPoints;

    /*???
    if (isClosed) {
        for (int i=0; i<data.degree; ++i) {
            controlPoints.append(data.controlPoints.at(i));
        }
    }
    */

    int i;
    int npts = controlPoints.count();
    // order:
    int k = degree+1;
    // resolution:
    int p1 = 8 * npts; // ???

    double* b = new double[npts*3+1];
    double* h = new double[npts+1];
    double* p = new double[p1*3+1];

    i = 1;
    for (int it = 0; it < controlPoints.count(); ++it) {
        b[i] = controlPoints.at(it).x;
        b[i+1] = controlPoints.at(it).y;
        b[i+2] = 0.0;

        //RS_DEBUG->print("RS_Spline::update: b[%d]: %f/%f", i, b[i], b[i+1]);
        i+=3;
    }

    // set all homogeneous weighting factors to 1.0
    for (i=1; i <= npts; i++) {
        h[i] = 1.0;
    }

    for (i = 1; i <= 3*p1; i++) {
        p[i] = 0.0;
    }

    if (isClosed) {
        rbsplinu(npts,k,p1,b,h,p);
    } else {
        rbspline(npts,k,p1,b,h,p);
    }

    //RS_Vector prev(false);
    //tVector prev(0,0,0);
    //bool hasPrev = false;
    for (i = 1; i <= 3*p1; i=i+3) {
        /*if (hasPrev) {
            RS_Line* line = new RS_Line(this,
                                        RS_LineData(prev, RS_Vector(p[i], p[i+1])));
            line->setLayer(NULL);
            line->setPen(RS_Pen(RS2::FlagInvalid));
            addEntity(line);
        }*/
        //prev = RS_Vector(p[i], p[i+1]);
        //hasPrev = true;
        hs->addVertex(new tPoint(NULL, p[i],p[i+1], 0));
        //minV = RS_Vector::minimum(prev, minV);
        //maxV = RS_Vector::maximum(prev, maxV);
    }

    delete[] b;
    delete[] h;
    delete[] p;
}
