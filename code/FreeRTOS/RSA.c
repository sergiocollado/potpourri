#include "RSA.h"
/*
The RSA algorithm is based in the fact that the factorization of a large number is a complex operation, 
that is, it takes time. So the algorithm strength totally relies in how big are the numbers.
*/
bool set_q(long int val)
{
	bool result = false;
	if (prime(val))
	{
		q = val;
		result = true;
	}
	return result;
}

long int get_q(void)
{
	return q;
}

//checks if the given number is a prime number.
int prime(long int pr)
{
    int i;
    j=sqrt((double)pr);
    for(i =2; i <=j; i++)
    {
        if(pr% i==0)
            return 0;
    }
    return 1;
}
void ce()
{
    int k;
    k=0;
    for(icounter =2; icounter <t; icounter++)
    {
        if(t% icounter ==0)
            continue;
        flag=prime(icounter);
        if(flag==1 && icounter!=p && icounter!=q)
        {
            e[k]= icounter;
            flag=cd(e[k]);
            if(flag>0)
            {
                d[k]=flag;
                k++;
            }
            if(k==99)
                break;
        }
    }
}

long int cd(long int x)
{
    long int k=1;
    while(1)
    {
        k=k+t;
        if(k%x==0)
            return(k/x);
    }
}
void encrypt()
{
    long int pt,ct,key=e[0],k,len;
	icounter =0;
	len = sizeof(msg) / sizeof(msg[0]); // strlen(msg);

	//printf("\nTHE  MESSAGE IS\n");
	//for (icounter = 0; icounter <100; icounter++)
	//	printf("%c", msg[icounter]);

    while(icounter <100) // !=len)
    {
        pt=m[icounter];
        pt=pt-96;
        k=1;
        for(j=0;j<key;j++)
        {
            k=k*pt;
            k=k%n;
        }
        temp[icounter]=k;
        ct=k+96;
        en[icounter]=ct;
		icounter++;
    }
    //en[icounter]=-1;
    //printf("\nTHE ENCRYPTED MESSAGE IS\n");
    //for(icounter =0;en[icounter]!=-1; icounter++)
	//printf("%c",en[icounter]);
}
void decrypt()
{
    long int pt,ct,key=d[0],k;
	icounter =0;
    while( icounter < 100) //en[icounter]!=-1)
    {
        ct=temp[icounter];
        k=1;
        for(j=0;j<key;j++)
        {
            k=k*ct;
            k=k%n;
        }
        pt=k+96;
        m[icounter]=pt;
		icounter++;
    }
   // m[icounter]=-1;
   // printf("\nTHE DECRYPTED MESSAGE IS\n");
   // for(icounter =0;m[icounter]!=-1; icounter++)
     //  printf("%c",m[icounter]);
}
