#include<iostream>
#include<stdio.h>
#include<time.h>
#include <omp.h>
using namespace std;

#define N 1000

void Simple()
{
	#pragma omp parallel num_threads(5)
	{
	   cout << "Thread\n";
	}
}

void SharedAndPrivte()
{
	int v1=0,v2=0,v3=0;
	#pragma omp parallel private(v1, v2) shared(v3) num_threads(3)
	{
		v1=v2=0;
		cout << "hi\n";
		v1++;
		v2++;
		v3++;
	}
	cout << v1 << " " << v2 << " " << v3 << endl;

}
void AtomicTest()
{
	int count = 0;
	#pragma omp parallel num_threads(500)
	{
	   cout << "Thread\n";
      #pragma omp atomic
      count++;
	   
	}
	cout << count << endl;

}


void OpenMPFunctions()
{
	int num;
	#pragma omp parallel num_threads(5) private(num)
	{
		num = omp_get_thread_num();
		cout << "Thread" << num << endl;
	}
}

void WorkShareUsingFor()  
{
	int i, chunk;
	float a[1000], b[1000], c[1000];

	/* Some initializations */
	for (i=0; i < 1000; i++)
	  a[i] = b[i] = i * 1.0;
	chunk = 50;

	#pragma omp parallel shared(a,b,c,chunk) private(i) num_threads(5)
	{

	  #pragma omp for schedule(dynamic,chunk) nowait
		  for (i=0; i < 1000; i++){
				c[i] = a[i] + b[i];
		  }
	} 
}

void WorkSharingUsingSections()
{
	int i;
	float a[N], b[N], c[N];

/* Some initializations */
	for (i=0; i < N; i++)
		a[i] = b[i] = i * 1.0;

	#pragma omp parallel shared(a,b,c) private(i) num_threads(2)
	{

		#pragma omp sections nowait
		{

			#pragma omp section
			{	for (i=0; i < N/2; i++){
					c[i] = a[i] + b[i];
				cout << "t1\n";
			}
			}
			#pragma omp section
			{	for (i=N/2; i < N; i++){
					c[i] = a[i] + b[i];
					cout << "t2\n";}
			}
		}  /* end of sections */

	}  /* end of parallel section */


}

void CriticalTest()
{
	int x;
	x = 0;

	#pragma omp parallel shared(x) 
	{

		#pragma omp critical 
		{
		x = x + 1;
		}

	} 
}


int  a, b, i, tid;
float x;
 
#pragma omp threadprivate(a, x)

void TLSTest()
{

  //omp_set_dynamic(0);
 
  printf("1st Parallel Region:\n");
#pragma omp parallel private(b,tid) num_threads(3)
  {
	  tid = omp_get_thread_num();
	  a = tid;
	  b = tid;
	  x = 1.1 * tid +1.0;
	  printf("Thread %d:   a,b,x= %d %d %f\n",tid,a,b,x);
	  }  /* end of parallel section */
	 
	  printf("************************************\n");
	  printf("Master thread doing serial work here\n");
	  printf("************************************\n");
	 
	  printf("2nd Parallel Region:\n");
	#pragma omp parallel private(tid)
	  {
		  tid = omp_get_thread_num();
		  printf("Thread %d:   a,b,x= %d %d %f\n",tid,a,b,x);
	  }  /* end of parallel section */
}

void ReductionTest()
{
	int   i, n, chunk;
	float a[100], b[100], result;

	/* Some initializations */
	n = 100;
	chunk = 10;
	result = 0.0;
	for (i=0; i < n; i++)
	  {
	  a[i] = i * 1.0;
	  b[i] = i * 2.0;
	  }

	#pragma omp parallel for default(shared) private(i) schedule(static,chunk)  reduction(+:result) num_threads(3) 

	  for (i=0; i < n; i++)
		result = result + (a[i] * b[i]);

	printf("Final result= %f\n",result);

}
void main()
{
	//omp_set_num_threads(100);
	test5();
}