#include <stdio.h>


union fum {
  unsigned int inum;
  float fnum;
};

union dum{
  unsigned long int inum;
  double dnum;
};

void fprint(unsigned int a){
  int i;
  for ( i=31; i>=0; i--){
    ((a& ((unsigned int) 1 << i)) !=0) ? printf("1") : printf("0");
    if ((i==23) || (i==31)) printf(" ");
  }
  printf("\n");
}

void dprint(unsigned long int a){
  int i;
  for ( i=63; i>=0; i--){
    ((a& ((unsigned long int) 1 << i)) !=0) ? printf("1") : printf("0");
    if ((i==52) || (i==63)) printf(" ");
  }
  printf("\n");
}

int main(){
  union fum a1,a2,a3,a4;
  // a1.fnum=6.5;
  a2.fnum=1.23;
  a3.fnum=1.23;
  // a4.fnum=-31.567824;
  // printf("%f %d\n", a1.fnum, a1.inum );
  printf("%f %d\n", a2.fnum, a2.inum );
  printf("%f %d\n", a3.fnum, a3.inum );
  // printf("%f %d\n", a4.fnum, a4.inum );

  // fprint(a1.inum);
  fprint(a2.inum);
  fprint(a3.inum);
  // fprint(a4.inum);

  a1.fnum=a2.fnum+a3.fnum;
  printf("%f %d\n", a1.fnum, a1.inum );
  fprint(a1.inum);

  //
  // union dum d1,d2,d3,d4;
  // d1.dnum=6.5;
  // d2.dnum=31.567824;
  // d3.dnum=-31.567825;
  // d4.dnum=-31.567824;
  // printf("%lf %ld\n", d1.dnum, d1.inum );
  // printf("%lf %ld\n", d2.dnum, d2.inum );
  // printf("%lf %ld\n", d3.dnum, d3.inum );
  // printf("%lf %ld\n", d4.dnum, d4.inum );
  //
  // dprint(d1.inum);
  // dprint(d2.inum);
  // dprint(d3.inum);
  // dprint(d4.inum);


}
