//
// Created by Даниил on 19.09.2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char * argv[]) {
  FILE *fi, *fo;
  struct example{
    int i;
    char s[100];
  } st;
if (argc <2) exit(1);
if ((fi=fopen(argv[1],"r"))==NULL) exit(2);
if ((fo=fopen(argv[2],"w"))==NULL) exit(3);
while (fscanf(fi,"%d %s", &st.i, &st.s)!= EOF)
fprintf(fo, "%s %d\n", st.s, st.i );
fclose(fi); 
fclose(fo);
    return 0;
}
