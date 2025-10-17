#include <stdio.h>

struct student{
    int num;
    char name[12];
    double score;
};


void scan(struct student *p, int n)
{
	for(int i = 0; i<n; i++)
	{
		scanf("%d %s %lf", &(*(p + i)).num, &(*(p + i)).name, &(*(p + i)).score);
	}
}

void print(struct student *p,int n)
{

	for(int j = 0; j < n; j++)
	{
		printf("%d %s %0.1f\n", (*(p + j)).num, (*(p + j)).name, (*(p + j)).score);
	}
}