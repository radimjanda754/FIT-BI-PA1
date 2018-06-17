/* 
 * File:   main.c
 * Author: radim
 *
 * Created on October 19, 2013, 8:15 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592653589793238462643383279502884

/*
 * 
 */
double vzdalenost(double x1,double x2,double y1, double y2){
    return(sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
}

double prekryv(double r1,double r2, double rx){
    double p1=r1*r1;
    double cos1=acos((rx*rx+r1*r1-r2*r2)/(2*rx*r1));
    double p2=r2*r2;
    double cos2=acos((rx*rx+r2*r2-r1*r1)/(2*rx*r2));
    double p3=0;
    if (((-rx+r1+r2)*(rx+r1-r2)*(rx-r1+r2)*(rx+r1+r2))>0)
        p3=0.5*(sqrt((-rx+r1+r2)*(rx+r1-r2)*(rx-r1+r2)*(rx+r1+r2)));
    return(p1*cos1+p2*cos2-p3);
}
int porov(double a, double b){
    double tmp;
    if (a>b)
        tmp=b;
    else
        tmp=a;
    
    if(fabs(fabs(a)-fabs(b))<(0.000001*tmp))
        return(1);
    return(0);
}

int main(int argc, char** argv) {
    double x1,x2,y1,y2,r1,r2,rx,tmp;
    int v=0;

    printf("Zadejte parametry kruznice #1:\n");
    v=scanf("%lf%lf%lf",&x1,&y1,&r1);
    if(v<3||r1<=0)
    {
        printf("Nespravny vstup.\n");
        return(0);
    }
    printf("Zadejte parametry kruznice #2:\n");
    v=scanf("%lf%lf%lf",&x2,&y2,&r2);
    if(v<3||r2<=0)
    {
        printf("Nespravny vstup.\n");
        return(0);
    }
    rx=vzdalenost(x1,x2,y1,y2);
    if (porov(fabs(x1),fabs(x2))==1&&porov(fabs(y1),fabs(y2))&&porov(r1,r2))
    {
        tmp=((2*r1)*(2*r1)*PI)/4;
        printf("Kruznice splyvaji, prekryv: %f\n",tmp);
        return(0);
    }
    if (porov(r1,rx+r2))
    {
        tmp=0;
        if ((prekryv(r1,r2,rx))>0.000000)
                tmp=prekryv(r1,r2,rx);
        printf("Vnitrni dotyk, kruznice #2 lezi uvnitr kruznice #1, prekryv: %f\n",tmp);
        return(0);
    }
    if (porov(r2,rx+r1))
    {
        tmp=0;
        if ((prekryv(r1,r2,rx))>0.000000)
                tmp=prekryv(r1,r2,rx);
        printf("Vnitrni dotyk, kruznice #1 lezi uvnitr kruznice #2, prekryv: %f\n",tmp);
        return(0);
    }
    if (r2<r1&&(rx+r2)<r1)
    {
        tmp=((2*r2)*(2*r2)*PI)/4;
        printf("Kruznice #2 lezi uvnitr kruznice #1, prekryv: %f\n",tmp);
        return(0);
    }
    if (r1<r2&&(rx+r1)<r2)
    {
        tmp=((2*r1)*(2*r1)*PI)/4;
        printf("Kruznice #1 lezi uvnitr kruznice #2, prekryv: %f\n",tmp);
        return(0);
    }
    if (porov(rx,(r1+r2)))
    {
        printf("Vnejsi dotyk, zadny prekryv.\n");
        return(0);
    }
    if (rx>(r1+r2))
    {
        printf("Kruznice lezi vne sebe, zadny prekryv.\n");
        return(0);
    }
    printf("Kruznice se protinaji, prekryv: %f\n",prekryv(r1,r2,rx));
    return (EXIT_SUCCESS);
}
