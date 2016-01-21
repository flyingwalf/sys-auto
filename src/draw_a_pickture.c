/********************************************************************************/
/* This framework is from                                                       */
/* http://codegolf.stackexchange.com/questions/35569/tweetable-mathematical-art */
/* And I've just copy the framework and a sample for furether play
/* Just remember to comple it with -lm option to make the match function take effect */
/* Have fun!!!!                                                                 */
/********************************************************************************/

#include <math.h>
#include <tgmath.h>
#include <stdlib.h>
#include <stdio.h>

#define DIM 1024
#define DM1 (DIM-1)
#define _sq(x) ((x)*(x)) // square
#define _cb(x) abs((x)*(x)*(x)) // absolute value of cube
#define _cr(x) (unsigned char)(pow((x),1.0/3.0)) // cube root

#define MARTIN
#define MAX_PRINT 20

#if defined VOID
unsigned char RD(int i,int j){
   // YOUR CODE HERE
    return 0;
}
unsigned char GR(int i,int j){
   // YOUR CODE HERE
    return 0;
}
unsigned char BL(int i,int j){
   // YOUR CODE HERE
    return 0;
}
#endif

#if defined MARTIN
unsigned char RD(int i,int j){
    return (char)(_sq(cos(atan2(j-512,i-512)/2))*255);
}

unsigned char GR(int i,int j){
    return (char)(_sq(cos(atan2(j-512,i-512)/2-2*acos(-1)/3))*255);
}

unsigned char BL(int i,int j){
    return (char)(_sq(cos(atan2(j-512,i-512)/2+2*acos(-1)/3))*255);
}
#endif

void pixel_write(int,int);
FILE *fp;
int main(){
    fp = fopen("MathPic.ppm","wb");
    fprintf(fp, "P6\n%d %d\n255\n", DIM, DIM);
    int i, j;
    for(j=0;j<DIM;j++)
        for(i=0;i<DIM;i++)
            pixel_write(i,j);
    fclose(fp);
    return 0;
}

void pixel_write(int i, int j){
    static unsigned char color[3];
    color[0] = RD(i,j)&255;
    color[1] = GR(i,j)&255;
    color[2] = BL(i,j)&255;
    fwrite(color, 1, 3, fp);
}
