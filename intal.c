#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"



static void swap(char *str1, char *str2) 
{ 
  char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char)); 
  strcpy(temp, str1); 
  strcpy(str1, str2); 
  strcpy(str2, temp); 
  free(temp); 
} 



// INTAL_COMPARE

int intal_compare(const char* intal1, const char* intal2)
{

    int len1=strlen(intal1);
    int len2=strlen(intal2);

    if(len1>len2)
    {
        return 1;
    }

    if(len2>len1)
    {
        return -1;
    }

    int i;
    for(i=0;i<len1;i++)
    {
        if(intal1[i]>intal2[i])
        {
            return 1;
        }

        if(intal2[i]>intal1[i])
        {
            return -1;
        }
    }

    return 0;
    

}



// INTAL_MULTIPLY

char* intal_multiply(const char* intal1, const char* intal2)
{
    

    if(!strcmp("0",intal1) || !strcmp("0",intal2))
    {
        char *res=(char*)malloc(sizeof(char)*2);
        strcpy(res,"0");
        return res;
    }

    int len1=strlen(intal1);
    int len2=strlen(intal2);

    //char *result=(char*)malloc(sizeof(char)*(len1+len2));
    char *result=(char*)malloc(sizeof(char)*(len1+len2+1));
    memset(result,'0',(len1+len2));

    int len=(len1+len2);
    int i,j,carry,n1,n2,sum;

    int index_1=0;
    int index_2=0;

    for(i=len1-1;i>=0;i--)
    {
        carry=0;
        n1=intal1[i]-'0';

        index_2=0;

        for(j=len2-1;j>=0;j--)
        {   
            n2=intal2[j]-'0';

            sum= (n1*n2) + (result[len-1-index_1-index_2]-'0') + carry;

            result[len-1-index_1-index_2] = (sum%10) + '0';
            carry=sum/10;
            index_2++;

        }

        if(carry>0)
        {
            result[len-1-index_1-index_2] = ((result[len-1-index_1-index_2]-'0')+carry)+'0';
        }

        index_1++;



    }

    result[len]='\0';

    int k=0;
    for(i=0;i<len;i++)
    {
        if(result[i]=='0')
        {
            ++k;
        }

        else
            break;
    }

    //char *answer=result+k;

    char *final_result=(char*)malloc(sizeof(char)*(len+1-k));
    strcpy(final_result,result+k);


    free(result);
    result=NULL;


    return final_result;
    
}



// INTAL_ADD


char* intal_add(const char* intal1, const char* intal2)
{
	int len1;
	int len2;

	len1=strlen(intal1);
	len2=strlen(intal2);

	int max=len1;

	if(len2>len1)
		max=len2;

	char intall1[max+1];
	char intall2[max+1];

	strcpy(intall1,intal1);
	strcpy(intall2,intal2);

	if(strlen(intall1)>strlen(intall2))
	{
		swap(intall1,intall2);

	}

	len1=strlen(intall1);
	len2=strlen(intall2);


	int diff=len2-len1;
	//printf("\nDIFFERENCE IN LENGTH IS: %d",diff);

	//char *result=malloc(sizeof(char*)*(len2+2));

	char *result=(char*)malloc(sizeof(char)*(len2+2));
	//char *answer;

	int carry=0;


	int index=(len2+1);

	for (int i=len1-1; i>=0; i--) 
    { 
    	int sum=((intall1[i]-'0')+(intall2[i+diff]-'0')+carry);
    	result[--index]=((sum%10)+'0');
    	carry=sum/10;
    } 

    for(int i=(diff-1);i>=0;i--)
    {
    	int sum=((intall2[i]-'0')+carry);
    	result[--index]=((sum%10)+'0');
    	carry=sum/10;

    }

    if(carry)
    {
    	result[--index]=(carry+'0');
    	result[len2+1]='\0';
    	return result;

    }

    
    else
    {
    	result[len2+1]='\0';
    	
    	char *final_result=malloc(sizeof(char*)*(len2+1));
    	strcpy(final_result,result+1);

    	free(result);
    	result=NULL;

    	return final_result;



    }

    
}


// INTAL_DIFF


char* intal_diff(const char* intal1, const char* intal2)
{

	int len1;
	int len2;

	len1=strlen(intal1);
	len2=strlen(intal2);

	int max=len1;

	if(len2>len1)
		max=len2;

	char intall1[max+1];
	char intall2[max+1];

	strcpy(intall1,intal1);
	strcpy(intall2,intal2);



    if(intal_compare(intall1,intall2)==-1)
    {
        swap(intall1,intall2);
    }

    len1=strlen(intall1);
    len2=strlen(intall2);

    int gap=len1-len2;





    char *result1=(char*)malloc(sizeof(char)*(len1+1));

    if(strcmp("0",intall1)==0 && strcmp("0",intall2)==0)
    {
    	strcpy(result1,"0");
    	return result1;
    }

    
    
    int index=len1;
    int borrow=0;

    int i;

    for(i=(len2-1);i>=0;i--)
    {
        
        int diff=(intall1[i+gap]-'0')-(intall2[i]-'0')-borrow;
    

        if(diff<0)
        {
            diff=diff+10;
            borrow=1;
        }

        else{
            borrow=0;
        }



        result1[--index]=(diff+'0');

        

    }



    int j;
    for(j=(gap-1);j>=0;j--)
    {
        //printf(".");
        
        int diff=(intall1[j]-'0')-borrow;

        if(diff<0)
        {
            diff=diff+10;
            borrow=1;
        }

        else{
            borrow=0;
        }

        result1[--index]=(diff+'0');

        
    }



    
    int k=0;
    for(int i=0;i<len1;i++)
    {
        if(result1[i]=='0')
        {
            ++k;
        }

        else
            break;
    }

    result1[len1]='\0';

    
    char *final_result=(char*)malloc(sizeof(char)*(len1+1-k));
    strcpy(final_result,result1+k);


    free(result1);
    result1=NULL;


    return final_result;
    


    


}


// INTAL_MOD

static char *repeated_subtraction(char *num1,char *num2)
{

	char *inter;

	while(intal_compare(num1,num2)==1)
	{
		inter=intal_diff(num1,num2);
		strcpy(num1,inter);
		
		free(inter);
		inter=NULL;
	}

	if(intal_compare(num1,num2)==0)
	{

		return "0";
	}

	else
	{

		return num1;
	}

}


char* intal_mod(const char* intal1, const char* intal2)
{

	
	int len1;
	int len2;

	len1=strlen(intal1);
	len2=strlen(intal2);

	int max=len1;

	if(len2>len1)
		max=len2;

	char num1[max+1];
	char num2[max+1];

	strcpy(num1,intal1);
	strcpy(num2,intal2);

	char inter[max+1];
    strcpy(inter,intal2);


   


    char *result=(char*)malloc(sizeof(char)*(len2+1));


    int k=0;
    while(intal_compare(intal1,strcat(inter,"0"))!=-1)
    {
        ++k;
        strcpy(num2,strcat(num2,"0"));
        
    }


    
    
    strcpy(result,repeated_subtraction(num1,num2));
    int len=strlen(num2);


    int i=0;
    while(k!=0)
    {
        num2[len-1-i]='\0';
        ++i;
        --k;
        
        strcpy(result,repeated_subtraction(result,num2));
    }


    return result;

   



}


// INTAL_MIN

int intal_min(char **arr, int n)
{

    char result[1001];

    int index=0;

    strcpy(result,arr[0]);

    for(int i=1;i<n;i++)
    {
        if(intal_compare(result,arr[i])==1)
        {
            index=i;
            strcpy(result,arr[i]);
        }

    }

    //free(result);

    return index;
}


//	INTAL_MAX

int intal_max(char **arr, int n)
{
    //char *result=(char*)malloc(sizeof(char)*1001);

    char result[1001];

    int index=0;
    strcpy(result,arr[0]);
    for(int i=1;i<n;i++)
    {
        if(intal_compare(result,arr[i])==-1)
        {
            index=i;
            strcpy(result,arr[i]);
        }

    }

    //free(result);

    return index;
}



// INTAL_SEARCH

int intal_search(char **arr, int n, const char* key)
{
    //int result;

    int i=0;
    while(i!=n)
    {
        if(strcmp(arr[i],key)==0)
            return i;

        ++i;
    }


    return -1;

}



// INTAL_SORT

static int merge(char **arr, int left_start, int left_end, int right_start, int right_end)
{

    int left_length = left_end - left_start;
    int right_length = right_end - right_start;


    char left_half[left_length][1001];
    char right_half[right_length][1001];

    int r = 0;
    int l = 0;
    int i = 0;


    for (i = left_start; i < left_end; i++, l++)
    {
        strcpy(left_half[l], arr[i]);
    }


    for (i = right_start; i < right_end; i++, r++)
    {
        strcpy(right_half[r], arr[i]);
    }


    for ( i = left_start, r = 0, l = 0; l < left_length && r < right_length; i++)
    {
         
        if(intal_compare(left_half[l],right_half[r])!=1)
        { 
            strcpy(arr[i], left_half[l++]); 
        }
        
        else 
        { 
            strcpy(arr[i], right_half[r++]);
        }
    }


    for ( ; l < left_length; i++, l++) 
    { 
        strcpy(arr[i], left_half[l]); 
    }

    for ( ; r < right_length; i++, r++) 
        
    { 
        strcpy(arr[i], right_half[r]); 
        
    }
    
    return 0;
}



static int mergesort_inter(int left, int right, char **arr) 
{
    if (right - left <= 1)
    {
        return 0;
    }


    int left_start  = left;
    int left_end    = (left+right)/2;
    int right_start = left_end;
    int right_end   = right;


    mergesort_inter( left_start, left_end, arr);

    mergesort_inter( right_start, right_end, arr);

    merge(arr, left_start, left_end, right_start, right_end);

    return 1;
}



void intal_sort(char **arr, int n) 
{
    mergesort_inter(0, n, arr);
}



// INTAL_BINSEARCH


int intal_binsearch(char **arr, int n, const char* key)
{
    //intal_sort(arr,n);

    int res=-1;
    int low = 0;
    int high = (n - 1);


    while (low <= high)
    {

        int mid = (low + high)/2;  

        if (intal_compare(key,arr[mid])==0)
        {
            res=mid;
            high=(mid-1);
        }

        else if (intal_compare(key,arr[mid])==-1)
            high = (mid - 1);

        else
            low = (mid + 1);
    }

    return res;
}




// INTAL_GCD

char* intal_gcd(const char* intal1, const char* intal2)
{

    int len1;
	int len2;

	len1=strlen(intal1);
	len2=strlen(intal2);

	int max=len1;

	if(len2>len1)
		max=len2;

	char intall1[max+1];
	char intall2[max+1];

	strcpy(intall1,intal1);
	strcpy(intall2,intal2);

	char *result=(char*)malloc(sizeof(char)*(max+1));
	char *inter;

	while(strcmp("0",intall2)!=0)
	{
		inter=intal_mod(intall1,intall2);
		strcpy(intall1,intall2);
		strcpy(intall2,inter);
		free(inter);
		inter=NULL;
	}

	strcpy(result,intall1);

	return result;
}





// INTAL_FACTORIAL

char* intal_factorial(unsigned int n)
{

	char *result;

	if(n==0 || n==1)
	{
		char *res=(char*)malloc(sizeof(char)*2);
		strcpy(res,"1");
		return res;
	}

	else
	{
	
		char num[11];

		result=intal_multiply("1","1");

		for(int i=2;i<=n;i++)
		{
			int len=strlen(result);
			char *inter=(char*)malloc(sizeof(char)*(len+1));
			strcpy(inter,result);
			sprintf(num,"%u",i);
			free(result);
			result=NULL;

			result=intal_multiply(inter,num);
			free(inter);
			inter=NULL;
		}
	}


	return result;




}


// INTAL_FIBONACCI

char* intal_fibonacci(unsigned int n)
{

	char *a=(char*)malloc(sizeof(char)*2);
	strcpy(a,"0");
	char *b=(char*)malloc(sizeof(char)*2);
	strcpy(b,"1");
	char *c;

	if(n==0)
	{
		free(b);
		return a;
	}

	else if(n==1)
	{
		free(a);
		return b;
	}

	else
	{
		for(int i=2;i<=n;i++)
		{
			c=intal_add(a,b);
			free(a);
			a=NULL;
			a=(char*)malloc(sizeof(char)*(strlen(b)+1));
			strcpy(a,b);
			free(b);
			b=NULL;
			b=(char*)malloc(sizeof(char)*(strlen(c)+1));
			strcpy(b,c);
			free(c);
			c=NULL;
		}
	}

	free(a);
	a=NULL;

	return b;

}

//	INTAL_POW

char* intal_pow(const char* intal1, unsigned int n)
{

	if(strcmp("0",intal1)==0 && n>0)
	{
		char *res_0=(char*)malloc(sizeof(char)*2);
		strcpy(res_0,"0");
		return res_0;
	}

	char *res=intal_multiply("1","1");

	int len1=strlen(intal1);

	char *intall1=(char*)malloc(sizeof(char)*(len1+1));
	strcpy(intall1,intal1);
	

	while(n>0)
	{
		if(n%2)
		{
			char *inter=(char*)malloc(sizeof(char)*(strlen(res)+1));
			strcpy(inter,res);
			free(res);
			res=NULL;
			res=intal_multiply(inter,intall1);
			free(inter);
			inter=NULL;

		}

		char *temp=intal_multiply(intall1,intall1);
		free(intall1);
		intall1=NULL;
		intall1=(char*)malloc(sizeof(char)*(strlen(temp)+1));
		strcpy(intall1,temp);
		free(temp);
		temp=NULL;

		n>>=1;

	}

	free(intall1);
	intall1=NULL;

	return res;



}

static int min(int a, int b) 
{ 
    return (a<b)? a: b; 
} 







// INTAL_BINCOEFF

char* intal_bincoeff(unsigned int n, unsigned int k)
{
	if(k==0)
	{
		char *result=(char*)malloc(sizeof(char)*2);
		strcpy(result,"1");
		return result;
	}



	int len = (k+1);

	char **a = (char**) malloc(len * sizeof(char*));

	a[0] = (char*) malloc(1001 * sizeof(char));
	strcpy(a[0],"1");

	for(int i = 1; i < len; i++) 
	{
		a[i] = (char*) malloc(1001 * sizeof(char));
		strcpy(a[i],"0");
	}


	for(int i=1; i<=n ; i++)
	{
		for(int j=min(i,k); j>0 ;j--)
		{

			char *inter;
			inter=intal_add(a[j],a[j-1]);
			strcpy(a[j],inter);
			free(inter);
			inter=NULL;
		}
	}

	char *res=(char*)malloc(sizeof(char)*(strlen(a[k]+1)));
	strcpy(res,a[k]);


	for(int i = 0; i < len; i++) 
	{
		free(a[i]);
	}
	free(a);


	return res;



}





char* coin_row_problem(char **arr, int n)
{
  char** a = (char**)malloc((n + 1) * sizeof(char*));
  a[0] = (char*)malloc(2 * sizeof(char));
  a[0][0] = '0';
  a[0][1] = '\0';

  for(int i = 0; i < n; ++i)
  {
    a[i + 1] = (char*)malloc(sizeof(char)*(strlen(arr[i]) + 1));
    strcpy(a[i + 1], arr[i]);
  }

  for(int i = 2; i < n + 1; ++i)
  {
    char* val = intal_add(arr[i -1], a[i - 2]);
    if(intal_compare(val, a[i - 1]) > 0)
    {
      char* tmp = a[i];
      a[i] = val;
      free(tmp);
    }
    else
   {
      free(a[i]);
      a[i] = (char*) malloc(sizeof(char)*(strlen(a[i - 1]) + 1));
      strcpy(a[i], a[i - 1]);
      free(val);
    }
  }

  char* result = (char*)malloc(sizeof(char)*(strlen(a[n]) + 1));
  strcpy(result, a[n]);

  for(int i = 0; i < n + 1; ++i)
  {
    free(a[i]);
  }
  free(a);

  return result;

}

