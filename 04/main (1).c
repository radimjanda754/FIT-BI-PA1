/* 
 * File:   main.c
 * Author: radim
 *
 * Created on November 9, 2013, 11:07 AM
 */

#include <stdio.h>
#include <stdlib.h>
#define FREE free(h);free(alt);free(s);alt=NULL;h=NULL;s=NULL;

/*
 * 
 */

double finish (double vd, int * s,int tmp2,int * alt, int * h,int min)
{
    int sum=0;
    //printf("vd=%f sum=%d, tmp2=%d\n",vd,sum,tmp2);
    for (int i = 0;i<=tmp2; i++)
    {
        if((alt[i]+h[i])>min)
        {
            sum=sum+s[i];
        }
    }
    //printf("vd=%f sum=%d, finish returnuje %f\n",vd,sum,(double)vd/sum);
    return((double)vd/sum);
}

void swap(int * a, int * b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(int argc, char** argv) {
    int n = 0;
    int vin = 0;
    double vd = 0;
    double vysledek = 0;
    int tmp1 = 0;
    int tmp2 = 0;
    
    printf("Zadejte pocet nadrzi:\n");
    if (scanf("%d",&n)==0||n<1||n>200000)
    {
        printf("Nespravny vstup.\n");
        return(1);
    }
    
    int *alt=(int *)malloc(sizeof(int)*n);
    int *h=(int *)malloc(sizeof(int)*n);
    int *s=(int *)malloc(sizeof(int)*n);
    int totalv=0;
    
    printf("Zadejte parametry nadrzi:\n");
    for(int i = 0;i<n;i++)
    {
        if (scanf("%d %d %d %d",&alt[i],&h[i],&tmp1,&tmp2)<4||h[i]<1||tmp1<1||tmp2<1)
        {
                printf("Nespravny vstup.\n");
                FREE
                return(1);
        }
        
        s[i]=tmp1*tmp2;
        totalv=totalv+(s[i]*h[i]);
        int k=i;
        while(k>0&&((alt[k]<alt[k-1])||(alt[k]==alt[k-1]&&h[k]<h[k-1])))
        {
            swap(&alt[k],&alt[k-1]);
            swap(&h[k],&h[k-1]);
            swap(&s[k],&s[k-1]);
            k--;
        }
    }
    printf("Zadejte objem vody:\n");
    while(n>0)
    {
    int check;
    check=scanf("%d",&vin);
    if (check==EOF)
    {
        FREE
        return(0);
    }
    if (check!=1||vin<0)
    {
        printf("Nespravny vstup.\n");
        FREE
        return(1);
    }
    if (vin==0)
    {
        printf("Prazdne.\n");
        continue;
    }
    if (vin==totalv)
    {
        tmp1=alt[0];
        for (int i=0;i<n;i++)
        {
            if((alt[i]+h[i])>tmp1)
                tmp1=alt[i]+h[i];
        }
        printf("h = %f\n",(double)tmp1);
        continue;
    }
    if (vin>totalv)
    {
        printf("Pretece.\n");
        continue;
    }
    
    vd=vin;
    double prevvd;
    tmp1=alt[0];
    tmp2=0;
    int min=alt[0]+h[0];
    int minchanged;
    int bicyklprotection=0;
    while(vd>0&&tmp2<n)
    {
        //printf("cyklus has startyd vd=%f min=%d max=%d tmp2=%d totalv=%d alt[tmp2+1]=%d ",vd,tmp1,min,tmp2,totalv,alt[tmp2+1]);
        prevvd=vd;
        minchanged=0;
        while(((tmp2+1)<n)&&(alt[tmp2+1]==tmp1))
            tmp2++;
        //printf("newtmp2=%d\n",tmp2);
        for(int i = 0;i<=tmp2;i++)
        {
            if (((alt[i]+h[i])>tmp1)&&(((alt[i]+h[i])<alt[tmp2+1])||((tmp2+1)>=n))&&(minchanged==0||((alt[i]+h[i])<min)))
            {
                minchanged=1;
                min=alt[i]+h[i];
            }
        }
        //printf("minchanged = %d ",minchanged);
        if(minchanged!=1&&(tmp2+1)<n)
            min=alt[tmp2+1];
        
        //printf("max changed to %d\n",min);
        
        for(int i = 0;i<=tmp2;i++)
        {
                if((h[i]+alt[i])>tmp1)
                {
                    vd=vd-((s[i]*h[i])*(((double)min-tmp1)/(double)h[i]));
                    bicyklprotection=0;
                }
        }
        
        if (vd==0)
        {
            vysledek=min;
            break;
        }
        if (vd<0)
        {
            //printf("before finish vd=%f prevvd=%f\n",vd,prevvd);
            vysledek=tmp1+finish(prevvd,s,tmp2,alt,h,tmp1);
            break;
        }
        
        //printf("min changed to %d (prevmin = %d)\n",min,tmp1);
        tmp1=min;
        if(minchanged!=1&&(prevvd-vd)<0.0000000000001)
            min=alt[tmp2]+h[tmp2];
    }   
    printf("h = %f\n",vysledek);
    } 
        
        
        
    /*
    for(int i = 0;i<n;i++)
    {
        printf("%d %d %d\n",alt[i],h[i],v[i]);
    }*/
    
    
    FREE
    return (EXIT_SUCCESS);
}

