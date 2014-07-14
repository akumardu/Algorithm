#include "stdio.h"

void elephant_n_candy()
{
	unsigned long long num_testcases,num_elephants,num_candy,each_elephant,sum_candy=0;
	int overflow = 0;
	scanf("%llu",&num_testcases);
	while(num_testcases--)
	{
		overflow = 0;
		sum_candy=0;
		scanf("%llu",&num_elephants);
		scanf("%llu",&num_candy);
		while(num_elephants--)
		{
			scanf("%llu",&each_elephant);
			sum_candy += each_elephant;
			if(sum_candy > num_candy)
			{
				overflow = 1;
				//break;
			}
		}
		if(overflow || sum_candy > num_candy)
			printf("No\n");
		else
			printf("Yes\n");
	}
}