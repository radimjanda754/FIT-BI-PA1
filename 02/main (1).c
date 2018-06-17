/* 
 * File:   main.c
 * Author: radim
 *
 * Created on October 26, 2013, 7:12 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * 
 */
int prvocisla[500];
int k=0;

void rozklad(int a)
{
    // Vypocet prvocisel podle algoritmu, ktery jsme si ukazovali na proseminari
    int asqrt=sqrt(a);
    while (asqrt >= 2)
    {
        if ((a%asqrt) == 0)
        {
                rozklad(asqrt);
                rozklad(a/asqrt);
                return;
        }
        asqrt=asqrt-1;
     }
    
    // Kontrola zda-li se cislo jiz nenachazi v poli, pokud ne je do nej prirazeno
    int fail=0;
    for(int i=0;i<=k;i++)
    {
        if (prvocisla[i]==a)
        {
            fail=1;
            break;
        }
    }
    if(fail==0)
    {
        prvocisla[k]=a;
        k=k+1;
    }
}

int main(int argc, char** argv) {
    printf("Zadejte n:\n");
    int n;
    int newn;
    int v;
    
    // Kontrola vstupu
    v = scanf("%d",&n);
    if (v<1||n<1)
    {
        printf("Nespravny vstup.\n");
        return(1);
    }
    
    rozklad(n);
    
    // Vypocet funkce
    double nd=n;
    for (int i=0;i<k;i++)
    {
        nd=nd*(1-((double)1/prvocisla[i]));
    }
    newn=nd;
    
    if(n==1)
        printf("phi(1) = 1\n");
    else
        printf("phi(%d) = %d\n",n,newn);
    
    return (EXIT_SUCCESS);
}

