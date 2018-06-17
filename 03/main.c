/* 
 * File:   main.c
 * Author: radim
 *
 * Created on November 5, 2013, 9:48 PM
 */

#ifndef __PROGTEST__
#include <stdio.h>
#endif /* __PROGTEST__ */

int cmpClock ( long long int y1, long long int m1, long long int d1, long long int h1, long long int i1,
                  long long int y2, long long int m2, long long int d2, long long int h2, long long int i2) // Porovnani casu
{
    int itsk=0;
        if (y2>y1)
        {
            itsk=1;
        }
        else
        {
            if (m1>m2)
            {
                return(0);
            }
            else
            {
                if (m2>m1)
                {
                itsk=1;
                }
                else
                {
                    if (d2<d1)
                    {
                        return(0);
                    }
                    else
                    {
                        if(d1<d2)
                        {
                            itsk=1;
                        }
                        else
                        {
                            if(h2<h1)
                            {
                                return(0);
                            }
                            else
                            {
                                if(h1<h2)
                                {
                                    itsk=1;
                                }
                                else
                                {
                                    if(i2<i1)
                                    {
                                        return(0);
                                    }
                                    else
                                    {
                                        if(i2>i1)
                                        {
                                            itsk=1;
                                        }
                                        if(i1==i1)
                                        {
                                            itsk=1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return(itsk);
}

int DinM(long long int i,long long int y) // Zjisteni poctu dnu v mesici i
{
    if (i==1)
        return(31);
    if (i==2)
    {
        if (y%4000==0)
        {
            return(28);
        }
        else
        {
            if(y%400==0)
            {
                return(29);
            }
            else
            {
                if(y%100==0)
                {
                    return(28);
                }
                else
                {
                    if(y%4==0)
                        return(29);
                    else
                        return(28);
                }
            }
        }
        return(28);
    }
    if (i==3)
        return(31);
    if (i==4)
        return(30);
    if (i==5)
        return(31);
    if (i==6)
        return(30);
    if (i==7)
        return(31);
    if (i==8)
        return(31);
    if (i==9)
        return(30);
    if (i==10)
        return(31);
    if (i==11)
        return(30);
    if (i==12)
        return(31);
    return(0);
}

long long int converttod( long long int * y, long long int * m, long long int cmp)
{
    long long int d = 0;
    int tmp=0;
    while (*m>1)
    {
        d=d+DinM((*m-1),*y);
        *m=*m-1;
    }
    while (*y>0&&*y>cmp)
    {
        tmp=DinM(2,(*y-1));
        if (tmp==29)
            d=d+366;
        else
            d=d+365;
        *y=*y-1;
    }
    return(d);
}

int cuckooClock ( long long int y1, long long int m1, long long int d1, long long int h1, long long int i1,
                  long long int y2, long long int m2, long long int d2, long long int h2, long long int i2, 
                  long long int * cuckoo )
 {
    // ULTRA KONTROLA
    int itsk=0;
    if (m1<1||m1>12||m2<1||m2>12)
        return(0);
    if (h1<0||h1>23||h2<0||h2>23)
        return(0);
    if (i1<0||i1>59||i2<0||i2>59)
        return(0);
    if (y1<1600||y2<1600)
        return(0);
    if (y2<y1)
        return(0);
    if (d1<1||d1>DinM(m1,y1))
        return(0);
    if (d2<1||d2>DinM(m2,y2))
        return(0);
    itsk=cmpClock(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2);
    if(itsk==0)
        return(0);
    // KONEC ULTRA KONTROLY
    
    int tmp=0;
    long long int diff=0;
    *cuckoo = 0;
    
    // Vypocet cuckoo podle dnu
    d2=d2+converttod(&y2,&m2,y1);
    d1=d1+converttod(&y1,&m1,y1);
    diff=d2-(d1+1);
    if (diff>=1)
    {
        *cuckoo=*cuckoo+(180*diff);
        d2=d2-diff;
    }
    
    // Pocatecni nastaveni cuckoo
    if (i1==0&&i1<=i2)
    {
          if (h1==0)
                tmp=12;
          else
          {
                if (h1>=13)
                        tmp=h1-12;
                else
                        tmp=h1;
          }
          *cuckoo=*cuckoo+tmp;
    }
    if (i1==30&&i1<=i2)
    {
          *cuckoo=*cuckoo+1;
    }

            
   while(cmpClock(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2)==1)
    {
        // Cast 1. (pro minuty <0,30) )
        if (i1>=0&&i1<30)
        {
            i1=i1+30;
            if (cmpClock(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2)==0)
            {
                i1=30;
                if (cmpClock(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2)==0)
                    break;
                *cuckoo=*cuckoo+1;
                break;
            }
            *cuckoo=*cuckoo+1;
        }
        
        // Cast 2. (pro minuty <30,60) )
        if (i1>=30)
        {
            i1=i1+30;
            i1=i1-60;
            h1++;
            if (h1==24)
            {
                h1=0;
                d1++;
                if (cmpClock(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2)==0)
                {
                    i1=0;
                    if (cmpClock(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2)==0)
                        break;
                    *cuckoo=*cuckoo+24;
                    break;
                }
            }
            if (cmpClock(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2)==0)
            {
                i1=0;
                if (cmpClock(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2)==0)
                    break;
                if (h1==0)
                    tmp=12;
                else
                {
                        if (h1>=13)
                                tmp=h1-12;
                        else
                                tmp=h1;
                }
                *cuckoo=*cuckoo+tmp;
                break;
            }
            if (h1==0)
                tmp=12;
            else
            {
                if (h1>=13)
                        tmp=h1-12;
                else
                        tmp=h1;
            }
            *cuckoo=*cuckoo+tmp;
        }
    }
    return(1);
 }

#ifndef __PROGTEST__
int main ( int argc, char * argv [] ) 
 {
   long long int cuckoo;
   int res;

   res = cuckooClock ( 2013, 10,  1, 13, 15,
                       2013, 10,  1, 18, 45, &cuckoo );
   /* res = 1, cuckoo = 26 */

   res = cuckooClock ( 2013, 10,  1, 13, 15,
                       2013, 10,  2, 11, 20, &cuckoo );
   /* res = 1, cuckoo = 165 */

   res = cuckooClock ( 2013,  1,  1, 13, 15,
                       2013, 10,  5, 11, 20, &cuckoo );
   /* res = 1, cuckoo = 49845 */

   res = cuckooClock ( 2012,  1,  1, 13, 15,
                       2012, 10,  5, 11, 20, &cuckoo );
   /* res = 1, cuckoo = 50025 */

   res = cuckooClock ( 1900,  1,  1, 13, 15,
                       1900, 10,  5, 11, 20, &cuckoo );
   /* res = 1, cuckoo = 49845 */

   res = cuckooClock ( 2013, 10,  1,  0,  0,
                       2013, 10,  1, 12,  0, &cuckoo );
   /* res = 1, cuckoo = 102 */

   res = cuckooClock ( 2013, 10,  1,  0, 15,
                       2013, 10,  1,  0, 25, &cuckoo );
   /* res = 1, cuckoo = 0 */

   res = cuckooClock ( 2013, 10,  1, 12,  0,
                       2013, 10,  1, 12,  0, &cuckoo );
   /* res = 1, cuckoo = 12 */

   res = cuckooClock ( 2013, 11,  1, 12,  0,
                       2013, 10,  1, 12,  0, &cuckoo );
   /* res = 0, cuckoo = N/A */

   res = cuckooClock ( 2013, 10, 32, 12,  0,
                       2013, 11, 10, 12,  0, &cuckoo );
   /* res = 0, cuckoo = N/A */

   res = cuckooClock ( 2100,  2, 29, 12,  0,
                       2100,  2, 29, 12,  0, &cuckoo );
   /* res = 0, cuckoo = N/A */

   res = cuckooClock ( 2400,  2, 29, 12,  0,
                       2400,  2, 29, 12,  0, &cuckoo );
   /* res = 1, cuckoo = 12 */

   return 0;
 }
#endif /* __PROGTEST__ */
