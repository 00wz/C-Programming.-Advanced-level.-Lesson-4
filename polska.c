#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define BUFFER_SIZE 255
#define INPUT_SIZE 255
#define STACK_SIZE 255

char oper[STACK_SIZE] = {0};
int oend=0;

void push(char v)
{
	oper[oend++] = v;
}

char pop()
{
	if(oend<=0 || oend>=BUFFER_SIZE)
	{
		 fprintf(stderr,"Stack overflow\n");
		 exit(1);
	}
	return oper[--oend];
}

bool emptyStack()
{
	return oend==0;
}
bool isOperator(char c)
{
	return c=='&' || c=='|' || c=='^';
}
int priority(char c)
{
	if(c=='|')
	return 1;
	if(c=='^')
	return 2;
	if(c=='&')
	return 3;
	return 0;
}

bool tryGetNumFromCharArray( char arr[], int pos, int* result)
{
	if(!(arr[pos] <= '9' && arr[pos] >= '0'))
	{
		return false;
	} 
	else
	{
		*result = arr[pos]-'0';
	}
	while(arr[++pos] <= '9' && arr[pos] >= '0')
	{
		*result *= 10;
		*result += arr[pos]-'0';
	}
	return true;
}

int main(void)
{
	int srsPos=0, pos=0;
	char answer[BUFFER_SIZE]={0};
	char input[INPUT_SIZE];
	printf("Input infix string: ");
	scanf("%[^\n]", input);
	while( input[srsPos] != 0)
	{
		int p=0;
		int number;
		if(tryGetNumFromCharArray(input, srsPos, &number))
		{
			sprintf(answer+pos,"%d %n",number,&p);
			pos += p;
			srsPos += p;
		}
		else
		{
			if(isOperator(input[srsPos]))
			{
				while( !emptyStack() )
				{
					char top = pop();
					int p=0; 
					if(priority(top)>=priority(input[srsPos]))
					{
						sprintf(answer+pos,"%c %n",top,&p);
						pos += p;
					}
					else
					{
						push(top);
						break;
					}
				}
				push(input[srsPos]);
			}
			else if( input[srsPos]=='(' )
			{
				push(input[srsPos]);
			}
			else if( input[srsPos]==')' )
			{
				char tmp;
				while( (tmp=pop()) != '(' )
				{
					int p=0;
					sprintf(answer+pos,"%c %n",tmp,&p);
					pos += p;
				}
			}
			srsPos++;
		}
	}
	while( !emptyStack() )
	{
		int p=0;
		sprintf(answer+pos,"%c %n", pop(), &p);
		pos += p;
	}
	printf("Answer: %s\n",answer);
	return 0;
}
