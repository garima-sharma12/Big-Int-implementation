/*BT20CSE040 Garima*/
/*CPL Assignment 2*/
/*Implement 'BigInt' data type with operations (+, -, *) for supporting 1024 bit ints.*/
#include<stdio.h>
#include<string.h>
#define SIZE 310             /*since 1024 bits hence maximum size is 310*/
#define MINUS -1             /* denotes negative sign*/
#define PLUS 1               /*denotes positive sign*/

/*defining struct for big integer*/
typedef struct bignum{
	char number[SIZE];
	int signbit;
	int lastdigit;
}BigInt;

BigInt subtract(BigInt num1, BigInt num2);  /*initialising method for subtraction to be used in addition*/

int max(int a, int b)	/*finding maximum*/				
{
	if(a>b)
	{
    return a;
    }
    else
    {
    return b;
	}
}


void initialize_num(BigInt *n)	/*initialise*/	
{
    n->number[SIZE-1]='\0';  /*pointer*/
    n->lastdigit=SIZE-1;     /*pointer to the end of n*/
}

void conversion_to_bigint(char num[],BigInt *n) /*convert the character array to bigint*/
{
	int i,j,k=0,length;
    if(num[0]=='-')	    /*storing sign*/							
    {
        n->signbit=MINUS;    
        k=1;
    }
    else
    {
    n->signbit=PLUS;
    }
    length=strlen(num);
    j=SIZE-1;
    n->number[SIZE-1]='\0';
    i=length-1;  
    /*if num stores '345' then i is 2 and num[i] will be 5*/
    while(i>=k)							
    {
        j--;
        n->number[j]=num[i]; /*starts storing from behind until it reaches the pointer to signbit*/
        i--;
    }
    n->lastdigit=j; /*will be 306 for this case*/
    
}
int compare_num(BigInt num1, BigInt num2)			/*comparing the two big inetgers*/
{
    if(num1.lastdigit<num2.lastdigit)      /*num1 is more than num2*/
    {
    return 0;
    }
    else if(num2.lastdigit<num1.lastdigit)   /*num2 is more than num1*/
    {
    return 1;
    }
    else
    {
        int i=num1.lastdigit;
        while(num1.number[i]==num2.number[i] && i<SIZE-1)
        {
            i++;
        }
        if (num1.number[i]>num2.number[i])
        {
        	return 0;
		}
		else
		{
			return 1;
		}
        
    }
}
void Print(BigInt num)	/*printing the big integer*/				
{
    if(num.signbit==MINUS)	/*print minus sign if negative number*/					 
    {
        printf("-");
    }
    
    for(int i=num.lastdigit;i<SIZE-1;i++)			
    {
        printf("%c",num.number[i]);
    }
}

BigInt add(BigInt num1, BigInt num2)	/*adding*/
{        
 BigInt b;                  /*stores result*/  
    initialize_num(&b);    /*creating memory*/
    
    
    if(num1.signbit==num2.signbit)    /*if both numbers are same sign*/
    {
        b.signbit=num1.signbit;
    }
    
    
    else
    {
        if(num1.signbit==PLUS && num2.signbit==MINUS)	/*if num1 is positive and num2 is negative*/
        {
            num2.signbit=PLUS;
            b=subtract(num1,num2);                      /*subtract num2 from num1 or vice versa depending on flag*/
            int flag=compare_num(num1,num2);				
            if(flag==1) 
			{           					
            b.signbit=MINUS;
            }
            else
            {
            b.signbit=PLUS;	
		    }
            return b;
        }
         else if(num1.signbit==MINUS && num2.signbit==PLUS)	  /*if num2 is positive but num1 is negative*/
        {
            num1.signbit=PLUS;
            b=subtract(num1,num2);
            int flag=compare_num(num1,num2);	
			if(flag==1)
			{
				b.signbit=PLUS;
			}		
			else
			{
				b.signbit=MINUS;
			}
            
            return b;
        }
    }

    int n,i,l,carry=0;
    l=max(num1.lastdigit,num2.lastdigit);
	i=SIZE-2;
	/*123+239   9+3=12=n carry=1 */
    while(i>=l)			
    {
        n=(num1.number[i]-'0')+(num2.number[i]-'0')+carry;
        (b.lastdigit)--;
        b.number[b.lastdigit]=48+n%10;
        carry=n/10;
        i--;
    }
if(num1.lastdigit<num2.lastdigit)		
    {
    	int i;
        while(i>=num1.lastdigit)
        {
            n=(num1.number[i]-'0')+carry;
            (b.lastdigit)--;
            b.number[b.lastdigit]=48+n%10;
            carry=n/10;
            i--;
        }

    }
    else if(num2.lastdigit<num1.lastdigit)		
    {
    	int i;
        while(i>=num2.lastdigit)
        {
            n=(num2.number[i]-'0')+carry;
            (b.lastdigit)--;
            b.number[b.lastdigit]=48+n%10;
            carry=n/10;
            i--;
        }
    }
    if(carry>0)
    {
        (b.lastdigit)--;
        b.number[b.lastdigit]=48+carry;
    }
    return b;
}


BigInt subtract(BigInt num1, BigInt num2)     /*subtraction*/
{
	BigInt b;
    initialize_num(&b);
    
    
    if(num1.signbit!=num2.signbit)				/*checking the possibility of both numbers being of opposite signs/same signs.*/
    {                                           /*and thus assigning the final sign to the output*/
        if(num1.signbit==PLUS && num2.signbit==MINUS)		
        {
            num2.signbit=PLUS;								
            b=add(num1,num2);
            return b;
        }
        else if(num1.signbit==MINUS && num2.signbit==PLUS)	 
        {
            num1.signbit=PLUS;								
            b=add(num1,num2);
            b.signbit=MINUS;								
            return b;
        }
    }
    else										
    {
        int flag=compare_num(num1,num2);			
        if(flag==1)
        {
            if(num1.signbit==PLUS)
            {
            b.signbit=MINUS;
            }
            else
            {
            b.signbit=PLUS;
            }
            BigInt temp;
            initialize_num(&temp);
            temp=num1;
            num1=num2;
            num2=temp;
            
        }
        else
        {
            b.signbit=num1.signbit;
        }
        int sub,i,carry;
        carry=0;
        i=SIZE-2;
        while(i>=num2.lastdigit)		 
        {
            sub=((num1.number[i]-'0')-(num2.number[i]-'0'))-carry;      /*carry is subtracted because it is borrowed */
            if(sub<0)							
            {
                sub=sub+10;
                carry=1;   
            }
            else								
            {
                carry=0;
            }
            (b.lastdigit)--;					
            b.number[b.lastdigit]=48+sub;
            i--;
        }

        for(;i>=num1.lastdigit;i--)
        {
            sub=(num1.number[i]-'0')-carry;		
            if(sub<0)
            {
                sub=sub+10;
                carry=1;
            }
            (b.lastdigit)--;
            b.number[b.lastdigit]=48+sub;
        }
    }
    return b;
}
BigInt multiply(BigInt num1,BigInt num2)    /*multiply*/
{
    BigInt b;
    initialize_num(&b);
    int mult[SIZE];    /*iniitialising integer array to store the result*/
    int i,j;
    i=0;
    while(i<SIZE)
    {
        mult[i]=0;
        i++;
    }

    if(num1.signbit!=num2.signbit)        /*checking sign of the numbers*/
	{		
    b.signbit=MINUS;
    }
    else		
	{						
    b.signbit=PLUS;
    }

    int flag=compare_num(num1,num2);		
    if(flag==1)                          /*num2 greater than num1*/
    {
        BigInt temp;
        initialize_num(&temp);
        temp=num1;
        num1=num2;
        num2=temp;
    }

    int carry,sum,n1,n2,m1,m2;
    carry=0;
    m1=0;
    m2=0;
    for(i=SIZE-2;i>=num2.lastdigit;i--)
    {
        carry=0;
        n1=num2.number[i]-'0';
        m1=0;
        for(j=SIZE-2;j>=num1.lastdigit;j--)
        {
            n2=num1.number[j]-'0';

            sum=(n1*n2) + mult[m1+m2] + carry;
            carry=sum/10;

            mult[m1+m2]=sum%10;
            m1++;
        }

        if(carry>0)
        mult[m1+m2]+=carry;

        m2++;
    }

    i=SIZE-1;
    while(i>-1 && mult[i]==0)
    i--;

    j=i;
    if(i==-1)
    {
        (b.lastdigit)--;
        b.number[b.lastdigit]='0';
    }
    else
    {
        for(i=0;i<=j;i++)
        {
            (b.lastdigit)--;
            b.number[b.lastdigit]=48+mult[i];
        }
    }
    return b;
}



int main()
{   
    char num_1[SIZE];
    printf("Enter first Number: ");
    scanf("%s",num_1);									
    char num_2[SIZE];
    printf("Enter second Number: ");
    scanf("%s",num_2);	
    
    BigInt num1,num2,sum,diff,prod;
    initialize_num(&num1);	
    conversion_to_bigint(num_1,&num1);
    initialize_num(&num2);
    conversion_to_bigint(num_2,&num2);
    
    initialize_num(&sum);
    initialize_num(&diff);
    initialize_num(&prod);
    
    sum=add(num1,num2);
	printf("\nAdding the two numbers: ");			
    Print(sum);

    diff=subtract(num1,num2);
	printf("\nSubtracting the two numbers: ");			
    Print(diff);
    
    prod=multiply(num1,num2);
	printf("\nMultiplying the two numbers: ");			
    Print(prod);
}
