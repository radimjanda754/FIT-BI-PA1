/* 
 * File:   main.c
 * Author: radim
 *
 * Created on November 16, 2013, 12:02 PM
 */

#include <stdio.h>
#include <stdlib.h>
#define WRONGINPUT printf("Nespravny vstup.\n");free(matice);matice=NULL;free(vysledky);vysledky=NULL;return (1);
int total=0; // Soucet prvku matice
int x=0; // Sirka matice

/*
 * 
 */

int count(int lx,int ly,int rx,int ry, int * matice) {
    int tmp=0;
    for (int i=ly;i<=ry;i++)
    {
        for (int ik=lx;ik<=rx;ik++)
        {
            tmp=tmp+matice[i*(x+1)+ik];
            //printf("+[%d]",matice[i*(x+1)+ik]);
        }
    }
    return(tmp);
}

int main(int argc, char** argv) {
    
    // DEKLARACE PROMENYCH -----------------------------------------------------
    int *matice=NULL; // Ukazatel na matici
    int *vysledky=NULL; // Ukazatel na vysledky
    int start=1; // Pomocna promena u vstupu
    int allocated=0; // Pomocna promena pro alokaci u vstupu
    int in = 0; // Ciselny vstup
    int xtmp=0; // Pomocna promena pro sirku u vstupu
    int y=0; // Vyska matice
    int v=0; // Pomocna promena pro vstup
    char tmp; // Znakovi vstup
    printf("Zadejte matici:\n");
    
    // VSTUP -------------------------------------------------------------------
    while (v!=EOF)
    {
        v=scanf("%d%c",&in,&tmp);
        if(v==EOF)
            break;
        if (v==2&&in>0&&(tmp==','||tmp=='\n'))
        {
            xtmp++;
            if(xtmp>x&&start==0)
            {
                WRONGINPUT
            }
            
            if(start==0&&allocated==0)
            {
                matice=(int*)realloc(matice,sizeof(int)*(x)*(y+1));
                allocated=1;
            }
            if(start==1)
                matice=(int*)realloc(matice,sizeof(int)*(xtmp));
            
            if (start==1)
            {
                //printf("TOTAL[%d]+[%d]=[%d]\n",total,in,total+in);
                total=total+in;
                matice[(xtmp-1)]=in;
            }
            else
            {
                //printf("TOTAL[%d]+[%d]=[%d]\n",total,in,total+in);
                total=total+in;
                matice[(xtmp-1)+y*x]=in;
            }
                    
            if(tmp=='\n'&&start==0)
            {
                if(xtmp<x)
                {
                        WRONGINPUT
                }
                xtmp=0;
                y++;
                allocated=0;
            }
            
            if(tmp=='\n'&&start==1)
            {
                x=xtmp;
                xtmp=0;
                y++;
                start=0;
            }
        }
        else
        {
            WRONGINPUT
        }
    }
    
    y=y-1;
    x=x-1;
    if (y<0||x<0||(x<1&&y<1)) // Osetreni pokud vyska nebo sirka matice neni alespon 2
    {
        WRONGINPUT
    }
    
    
    // HODNE NAIVNI ALGORITMUS -------------------------------------------------
    int n=1; // Pocet vysledku
    int diff=999999999;
    int o=0;
    int c=0;
    int starts=0;
    int startv=0;
    if ((x>60)&&(y>50)) // "speed boost", if u know what i mean
    {
        starts=x/2;
        startv=y/2;
    }
    
    for (int sirka=starts;sirka<=(x+1);sirka++)
    {
        for (int vyska=startv;vyska<=(y+1);vyska++)
        {
            for (int x2=0;(x2+sirka)<=x;x2++)
            {
                for (int y2=0;(y2+vyska)<=y;y2++)
                {
                    //if(vyska==0&&sirka==0)
                    //    continue;
                    //printf("LU:[%d,%d] RD:[%d,%d] = ",x2,y2,x2+sirka,y2+vyska);
                    //printf("%d \n",count(x2,y2,x2+sirka,y2+vyska,matice));
                    c=count(x2,y2,x2+sirka,y2+vyska,matice);
                    o=total-c;
                    //printf ("o=%d diff=%d o-c=%d\n",o,diff,abs(o-c));
                    if(abs(o-c)==diff)
                    {
                        //printf(" ----- SAVING == \n");
                        n++;
                        vysledky=(int*)realloc(vysledky,sizeof(int)*n*6);
                        vysledky[0+(n-1)*6]=sirka+1;
                        vysledky[1+(n-1)*6]=vyska+1;
                        vysledky[2+(n-1)*6]=x2;
                        vysledky[3+(n-1)*6]=y2;
                        vysledky[4+(n-1)*6]=c;
                        vysledky[5+(n-1)*6]=o;
                    }
                    if(abs(o-c)<diff)
                    {
                        //printf(" ----- SAVING < \n");
                        n=1;
                        vysledky=(int*)realloc(vysledky,sizeof(int)*n*6);
                        vysledky[0]=sirka+1;
                        vysledky[1]=vyska+1;
                        vysledky[2]=x2;
                        vysledky[3]=y2;
                        vysledky[4]=c;
                        vysledky[5]=o;
                        diff=abs(o-c);
                    }

                }
            }
        }
    }
    
    diff=0;
    printf("Vysledku: %d\n",n);
    while (diff<n)
    {
        printf("%d x %d @ (%d, %d): %d : %d\n",vysledky[0+(diff)*6],vysledky[1+(diff)*6],vysledky[2+(diff)*6],vysledky[3+(diff)*6],vysledky[4+(diff)*6],vysledky[5+(diff)*6]);
        diff++;
    }
    
    
    free(matice);matice=NULL;free(vysledky);vysledky=NULL;
    return (EXIT_SUCCESS);
}

