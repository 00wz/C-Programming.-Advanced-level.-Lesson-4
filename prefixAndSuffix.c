#include <stdio.h>
#include <string.h>
#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define SIZE 50

void zFunction2 (char *s, int z[])
{
	int n = strlen(s);
	for (int i=1, l=0, r=0; i<n; ++i)
	{
		if (i <= r)
		{
			z[i] = MIN (r-i+1, z[i-l]);
		}
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
		{
			++z[i];
		}
		if (i+z[i]-1 > r)
		{
			
			l = i, r = i+z[i]-1;
		}
	}
}

int main(int argc, char **argv)
{
	char t[SIZE] = {0}, p[SIZE] = {0};
	char s[SIZE+SIZE] = {0};
	int z[SIZE+SIZE] = {0};
	printf("Input word with suffix: ");
	scanf("%s",t);
	printf("Input word with prefix: ");
	scanf("%s",p);
	size_t tlen = strlen(t);
	size_t plen = strlen(p);
	size_t zlen = tlen + plen;
	sprintf(s,"%s%s",p,t);
	zFunction2(s,z);
	size_t i=plen;
	for(; i<zlen; i++)
	{
		if(z[i] == zlen - i)
		{
			break;
		}
	}
	printf("%d\n", zlen - i);

	return 0;
}

