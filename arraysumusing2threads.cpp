
#include <iostream>
#include <pthread.h>
#include<bits/stdc++.h>

using namespace std;
vector<int>a;
int sum[2] = { 0 };
int part=0;
void* sum_array(void* arg)
{

	 part++;
	int thread_part =part;

	for (int i =(thread_part-1)*a.size()/2; i < (thread_part*a.size())/2; i++)
		sum[thread_part-1] += a[i];
		return NULL;
}

// Driver Code
int main()
{
    
    int n;
cout<<"enter the size of array"<<endl;
cin>>n;
cout<<"enter the elements of array"<<endl;

for(int i=0;i<n;i++)
 {
 int x;
 cin>>x;
 a.push_back(x);
 }


	pthread_t threads[2];

	
	for (int i = 0; i <2; i++)
		pthread_create(&threads[i], NULL, sum_array, (void*)NULL);

	
	for (int i = 0; i <2; i++)
		pthread_join(threads[i], NULL);

	
	int total_sum = 0;
	for (int i = 0; i <2; i++)
		{total_sum += sum[i];
		cout<<"Sum of thread"<<i<<"="<<sum[i]<<endl;}

	cout << "sum is " << total_sum << endl;

	return 0;
}

