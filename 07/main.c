/* 
 * File:   main.c
 * Author: radim
 *
 * Created on November 30, 2013, 10:55 AM
 */

#include <stdio.h>
#include <stdlib.h>
#define FREEV for(int i=0;i<n;i++)free(v1[i]);free(v1);for(int i=0;i<n;i++)free(v2[i]);free(v2);free(max);max=NULL;v1=NULL;v2=NULL;
#define WRONGINPUT printf("Nespravny vstup.\n");free(z);z=NULL;return(1);
int pocet;
int maxpocet;
int move;
int moveZ;
int mx;

/*
 * 
 */
void printX(int **pole, int n)
{
    printf(" = ");
    for(int i=0;i<n;i++)
    {
        if(i==(n-1))
            printf("%d x %d\n",pole[i][1],pole[i][0]);
        else
            printf("%d x %d + ",pole[i][1],pole[i][0]);
    }
}



void swap(int a, int b, int *pole) // prohozeni poli
{
    int tmp = pole[a];
    pole[a] = pole[b];
    pole[b] = tmp;
}

void sort(int start, int n,int *pole){ // serazeni
        if(start < n){
                int move = start;
                for(int i = start + 1; i < n; i++){
                if(pole[i] > pole[start]){
                swap(i, ++move, pole);
                }
                }
                swap(start, move, pole);
                sort(start, move, pole);
                sort(move + 1, n, pole);
        }
}

void xDiv(int *z,int o,int **vysledky,int *max)
{
    
    if(o>=z[moveZ+mx])
    {
            int i=0;
            while(i<max[moveZ+mx]&&((o-(i+1)*z[moveZ+mx])>=0))
                i++;
            o=o-i*z[moveZ+mx];
            if(i>0)
            {
                //printf("\n adding [%d]x[%d]times.",z[moveZ+mx],i);
                vysledky[move][0]=z[moveZ+mx];
                vysledky[move][1]=i;
                move++;
            }
            pocet=pocet+i;
            moveZ++;
            if(o==0||pocet>=maxpocet)
                return;
            xDiv(z,o,vysledky,max);
    }
    else
    {
        moveZ++;
        xDiv(z,o,vysledky,max);
    }
    
    return;
    
    // STARY NE PRILIS FUNKCNI ALGORITMUS
    
    /*printf("\n Recursion has started with o=%d move=%d moveZ=%d pocet=%d mXd=%d;",o,move,moveZ,pocet,moveXdiv);
    int tmp=o%z[moveZ+moveXdiv];
    if(tmp>0&&o>z[moveZ+moveXdiv])
    {
        vysledky[move][0]=z[moveZ+moveXdiv];
        vysledky[move][1]=o/z[moveZ+moveXdiv];
        move++;
        pocet=pocet+o/z[moveZ+moveXdiv];
        moveZ++;
        xDiv(z,tmp,vysledky);
    }
    else
    {
        if(o<z[moveZ+moveXdiv])
        {
            printf("\n Cant divide this o=%d z;=%d",o,z[moveZ+moveXdiv]);
            moveZ++;
            xDiv(z,tmp,vysledky);
        }
        else
        {
            vysledky[move][0]=z[moveZ+moveXdiv];
            vysledky[move][1]=o/z[moveZ+moveXdiv];
            move++;
            pocet=pocet+o/z[moveZ+moveXdiv];
        }
        
    }
    return;*/
}

int main(int argc, char** argv) {
    int n;
    int * z=NULL;
    printf("Zadejte pocet zavazi:\n");
    if(scanf("%d",&n)<1||n<1)
    {
        printf("Nespravny vstup.\n");
        return(1);
    }
    
    z=(int*)malloc(sizeof(int)*n);
    
    int in;
    int jedna=0;
    
    printf("Zadejte hmotnosti zavazi:\n");
    for(int i=0;i<n;i++)
    {
        if(scanf("%d",&in)==0||in<1)
        {
            WRONGINPUT
        }
        
        z[i]=in;
        if(in==1)
            jedna=1;
        
        for(int i2=0;i2<i;i2++)
        {
            if(z[i2]==z[i])
            {
                WRONGINPUT
            }
        }
    }
    if(jedna==0)
    {
        WRONGINPUT
    }
    
    sort(0,n,z);
    int go;
    int **v1=NULL;
    int **v2=NULL;
    int *max=NULL;
    int n1;
    v1=(int**)malloc(sizeof(int*)*(n+1));
    for(int i=0;i<n;i++)
        v1[i]=(int*)malloc(sizeof(int)*2);
    v2=(int**)malloc(sizeof(int*)*(n+1));
    for(int i=0;i<n;i++)
        v2[i]=(int*)malloc(sizeof(int)*2);
    max=(int*)malloc(sizeof(int*)*(n+1));
    
    printf("Zadejte hledanou hmotnost:\n");
    int v=0;
    while(v!=EOF)
    {
        v=scanf("%d",&in);
        if(v==0||in<=0)
        {
            FREEV
            WRONGINPUT
        }
        if(v==EOF)
            break;
        
        
        mx=0;
        
        while(z[mx]>in)
            mx++;
        
        for(int i=0;i<n;i++)
            max[i]=9999999;
        
        move=0;
        moveZ=0;
        pocet=0;
        maxpocet=999999999;
        xDiv(z,in,v1,max);
        maxpocet=pocet;
        n1=move;
        
        int tmpn=0;
        
        for(int i=0;i<n;i++)
        {
            //printf("\n Trying %d / %d = %d ",in,z[i],in/z[i]);
            if((in/z[i]>=45||z[i]==1)&&i<10)
            {
                //printf("%d / %d = %d",in,z[i],in/z[i]);
                tmpn=i;
                break;
            }
        }
        
        //printf("\n tmpn set to %d",tmpn);
        
        for(int i=0;i<tmpn;i++)
            max[i]=0;
        
        go=0;
        
        //printf("While getting ready to start go=%d tmpn=%d max[tmpn]=%d mx=%d",go,tmpn,max[tmpn],mx);
        
        while(max[tmpn]<10000000&&maxpocet>1&&max[mx]<10000000)
        {
            //printf("\n While started TL: ");
            //for(int i=0;i<n;i++)
            //    printf("%d ",max[i]);
            //printf("| maxpocet=%d",maxpocet);
                
            if(max[mx]>(in/z[mx]))
            {
                for(int i=mx;i<tmpn;i++)
                {
                    if(max[i]>(in/z[i]))
                    {
                        max[i]=0;
                        max[i+1]++;
                        //printf("\n %d=0 %d++",go+i,go+i+1);
                    }
                }
            }

                move=0;
                moveZ=0;
                pocet=0;
                xDiv(z,in,v2,max);
                if(pocet<maxpocet)
                {
                    for(int i=0;i<n;i++)
                    {
                        v1[i][0]=v2[i][0];
                        v1[i][1]=v2[i][1];
                        maxpocet=pocet;
                        n1=move;
                    }
                }
            
            
            max[mx]++;
            
            //STARY NE PRILIS FUNKCNI ALGORITMUS
            
            /*
            printf("\n WhileGO has started;");
            move=0;
            moveZ=0;
            pocet=0;
            xDiv(z,in,v1);
            n1=move;
            printf("\n Recursion ending with move=%d moveZ=%d pocet=%d mXd=%d;",move,moveZ,pocet,moveXdiv);
            tmppocet=pocet;
            moveXdiv++;
            if(moveXdiv<n)
            {
                printf("\n moveXdiv<n has started;");
                move=0;
                moveZ=0;
                pocet=0;
                xDiv(z,in,v2);
                n2=move;
                printf("\n Recursion ending with move=%d moveZ=%d pocet=%d mXd=%d tmpp=%d;",move,moveZ,pocet,moveXdiv,tmppocet);
                if(moveXdiv==n)
                {
                    printf("\n Ending cuz movexDiv==n;");
                    if(tmppocet>pocet)
                        printX(v2,n2);
                    else
                        printX(v1,n1);
                    break;
                }
            }
            else
            {
                printf("\n Ending cuz moveXdiv!<n;");
                printX(v1,n1);
                break;
            }
            
            if(pocet>tmppocet||pocet==tmppocet)
            {
                printf("\n Ending cuz pocet>tmp;");
                printX(v1,n1);
                break;
            }*/
        }
        //printf("\n While ended: ");
        //    for(int i=0;i<n;i++)
        //        printf("%d ",max[i]);
        //    printf("| maxpocet=%d",maxpocet);
        printX(v1,n1);
        
    }
    
    free(z);
    FREEV
    z=NULL;
    return (EXIT_SUCCESS);
}

