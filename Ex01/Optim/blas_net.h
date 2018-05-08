#include "f2c.h"
int scopy_(integer *n, real *sx, integer *incx, real *sy, integer *incy);
int scopy(integer n, real *sx, integer incx, real *sy, integer incy) 
{
return(scopy_(&n, sx, &incx, sy, &incy));
}
doublereal sdot_(integer *n, real *sx, integer *incx, real *sy, integer *incy);
real sdot(integer n, real *sx, integer incx, real *sy, integer incy)
{
return((real)sdot_(&n, sx, &incx, sy, &incy));
}
int saxpy_(integer *n, real *sa, real *sx, integer *incx,
        real *sy, integer *incy);
int saxpy(integer n, real sa, real *sx, integer incx, real *sy, integer incy)
{
return(saxpy_(&n, &sa, sx, &incx, sy, &incy));
}
int sscal_(integer *n, real *sa, real *sx, integer *incx);
int sscal(integer n, real sa, real *sx, integer incx) {
return(sscal_(&n, &sa, sx, &incx));
}
/* */
int sgemv_(char *trans, integer *m, integer *n, real *alpha,
        real *a, integer *lda, real *x, integer *incx, real *beta, real *y,
        integer *incy);
int sgemv(char *trans, integer m, integer n, real alpha,
        real *a, integer lda, real *x, integer incx, real beta, real *y,
        integer incy)
{
return(sgemv_("N", &m, &n, &alpha, a, &lda, x, &incx, &beta, y, &incy));
}
