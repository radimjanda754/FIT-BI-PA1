/* 
 * File:   main.c
 * Author: radim
 *
 * Created on November 27, 2013, 1:24 PM
 */

#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#endif /* __PROGTEST__ */

int incheck (const char * (*replace)[2]) 
{       // Vstupni kontrola a zjisteni poctu nahrazovanych slov.
    int n=-1;
    int tmp1=0;
    int tmp2=0;
    while(replace[n+1][0]!=NULL&&replace[n+1][1]!=NULL)
        n++;
    
    for(int i=0;i<=n;i++)
    {
        if(strlen(replace[i][0])==0)
        {
            return(-2);
        }
        for(int i2=i+1;i2<=n;i2++)
        {
            if(replace[i][0][0]==replace[i2][0][0])
            {
                tmp1=strlen(replace[i][0]);
                tmp2=strlen(replace[i2][0]);
                if(tmp1>tmp2)
                {
                    if(strncmp(replace[i][0],replace[i2][0],tmp2)==0)
                        n=-2;
                }
                else
                {
                    if(strncmp(replace[i][0],replace[i2][0],tmp1)==0)
                        n=-2;
                }
            }   
        }
    }
    // Pokud n=-2, kontrola selhala. Pokud n=-1, zadna slova k nahrazeni. Pokud n>=0, n=pocet slov k nahrazeni
    return(n);
}

char * newSpeak ( const char * text, const char * (*replace)[2] )
 {
    int n=0; // Pocet nahrazovacich slov, popr chybovi indikator
    
    n=incheck(replace);
    
    if(n==-2)
    {
        return(NULL);
    }
    
    int txtlen=strlen(text);
    
    if(txtlen==0)
    {
       
       char *zerostring=NULL;
       zerostring=(char*)malloc(sizeof(char));
       zerostring[0]='\0';
       return(zerostring);
    }
    
    int rpnum=-1; // Pomocna promena ukazujuci cislo nahrazovaciho slova
    int tmp=0; // Pomocna promena pro ulozeni strlen(nahrazovane slovo)
    int tmpS=0; // Pomocna promena pro ulozeni strlen(nahrazovaci slovo)
    char *s=NULL;
    int move=0; // Posun retezce text
    int moveS=0; // Posun noveho retezce
    

    
    if(n==-1)
    {
        s=(char*)malloc(sizeof(char)*(txtlen+1));
        if(!s)
        {
            return(NULL);
        }
        for(int i=0;i<txtlen;i++)
            s[i]=text[i];
        s[txtlen]='\0';
        return(s);
    }
    
    while(move<txtlen)
    {
        rpnum=-1;
        for(int i=0;i<=n;i++)
        {
            if(text[move]==replace[i][0][0])
            {
                //printf("Character %c match at %d\n",text[move],move);
                tmp=strlen(replace[i][0]);
                if((tmp+move)<=txtlen)
                {
                    //printf("%c %s %d %d",text[move],replace[i][0],tmp,move);
                    //printf(" %d\n",strncmp(text+move,replace[i][0],tmp));
                        if(strncmp(text+move,replace[i][0],tmp)==0)
                        {
                            //printf("Replacing for %s\n",replace[i][0]);
                                rpnum=i;
                                break;
                        }
                }
            }
        }
        if(rpnum==-1)
        {
            s=(char*)realloc(s,sizeof(char)*(moveS+2));
            if(!s)
            {
                return(NULL);
            }
            s[moveS]=text[move];
            //printf("+[%c]",text[move]);
            move++;
            moveS++;
        }
        else
        {
            tmpS=strlen(replace[rpnum][1]);
            s=(char*)realloc(s,sizeof(char)*(moveS+2+tmpS));
            if(!s)
            {
                return(NULL);
            }
            for(int i=0;i<tmpS;i++)
            {
                s[moveS]=replace[rpnum][1][i];
                moveS++;
            }
            //printf("+[%s]",replace[rpnum][1]);
            move=move+tmp;
        }
        //printf("%c",text[move]);
    }
    
    s[moveS]='\0';
    
    
    //printf("\n%d %s\n",moveS,s);
    //printf("%c",s[8]);
    return (s);
 }


#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
 {
   char * res;

   const char * d1 [][2] = {
     { "murderer", "termination specialist" },
     { "failure", "non-traditional success" },
     { "specialist", "person with certified level of knowledge" },
     { "dumb", "cerebrally challenged" },
     { "teacher", "voluntary knowledge conveyor" },
     { "evil", "nicenest deprived" },
     { "incorrect answer", "alternative answer" },
     { "student", "client" },
     { NULL, NULL }
    };


   const char * d2 [][2] = {
     { "fail", "suboptimal result" },
     { "failure", "non-traditional success" },
     { NULL, NULL }
    };


   res = newSpeak ( "Everybody is happy.", d1 );
   /* res = "Everybody is happy."*/
   free ( res );

   res = newSpeak ( "The student answered an incorrect answer.", d1 );
   /* res = "The client answered an alternative answer."*/
   free ( res );

   res = newSpeak ( "He was dumb, his failure was expected.", d1 );
   /* res = "He was cerebrally challenged, his non-traditional success was expected."*/
   free ( res );

   res = newSpeak ( "The evil teacher became a murderer.", d1 );
   /* res = "The nicenest deprived voluntary knowledge conveyor became a termination specialist."*/
   free ( res );

   res = newSpeak ( "Devil's advocate.", d1 );
   /* res = "Dnicenest deprived's advocate."*/
   free ( res );

   res = newSpeak ( "Hello.", d2 );
   /* res = NULL */

   return 0;
 }
#endif /* __PROGTEST__ */


