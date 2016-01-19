//
// test13.el: test unknown tokens (not an error, each unknown
// token should be returned)
//

A = malloc(100);  // oops, wrong language :-)
A[0] = 01230;  

for(i=0; i<sizeof(A); ++i)
{
  A[i] += i;
  << A[i];
}
