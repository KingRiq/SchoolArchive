//-----------------------------------------     
// NAME: Eriq Hampton      
// STUDENT NUMBER: 785280     
// COURSE: COMP 2160, SECTION: A01     
// INSTRUCTOR: Wang     
// ASSIGNMENT: assignment 1, QUESTION: question 1     
//      
// REMARKS: Tests two algorithms for powering.    
//------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count;
  static double power1( double base, int index )
  {
    double retValue;
    
    if( index == 0 )
    {
      retValue = 1;
    }
    else
    {
      retValue = base * power1( base, index-1 );
      count++; 
    }
		
    return retValue;
  }
  
  static double power2( double base, int index )
  {
    double retValue;
    double temp;
    
    if( index == 0 )
    { 
      retValue = 1;
    }
    else if( index%2 == 1 )
    {
      retValue = base * power2( base, index-1 );
      count++;
    }
    else
    {
      temp = power2( base, index/2 );
      retValue = temp*temp;
      count++;
    }
		
    return retValue;
  }
int main()
{
   
    double base []= { 1.4, 1.3, 1.2, 1.1 };
    int index []= { 5, 20, 63, 73 };
    double value;
    
    printf( "\nTest two algorithms for powering\n" ); // in C the values are diffent because of rounding
    for( int i=0 ; i<sizeof(base)/sizeof(base[0]);
		    i++ ) 
    {
      count = 0;
      value = power1( base[i], index[i] );
      printf("1: %lf ^ %d = %lf , used %d multiples\n", base[i], index[i], value, count);
      
      count = 0;
      value = power2( base[i], index[i] );
      printf("2: %lf ^ %d = %lf , used %d multiples\n", base[i], index[i], value, count);
      //printf("%lu", sizeof(base)/sizeof(base[0])); assumed test printf statement to check value of length 
    }
		
    printf( "\nEnd of processing" );
}
