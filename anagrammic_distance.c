/*
 * For Sarah.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

/*
 * Stolen off the Internet. I assume no responsibility over it.
 * Takes two strings and returns a number.
 */

int levenshtein(char *s1, char *s2)
{
	unsigned int s1len, s2len, x, y, lastdiag, olddiag;
	s1len = strlen(s1);
	s2len = strlen(s2);
	unsigned int column[s1len+1];
	for (y = 1; y <= s1len; y++)
		column[y] = y;
	for (x = 1; x <= s2len; x++) {
		column[0] = x;
		for (y = 1, lastdiag = x-1; y <= s1len; y++) {
			olddiag = column[y];
			column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
			lastdiag = olddiag;
		}
	}
	return(column[s1len]);
}

char* closest_anagram(char *reference, char *testee, char* result)
{
	int reference_lenght = strlen(reference);
	int testee_lenght = strlen(testee);
	int i = 0, j = 0;

	for (i = 0; i < testee_lenght; i++)
	{
		result[i] = 'X';
	}

	//Matching the most possible letters
	for(i = 0; i < reference_lenght; i++)
	{
		for (j = 0; j < testee_lenght; j++)
		{
			if (reference[i] == testee[j])
			{
				//Matching letter found, removing the matching and start creating the anagram
				result[i] = testee[j];
				testee[j] = ' ';
				break;
			}
		}
	}

	return result;
}

void calculate_anagrammic_distance(char* reference, char* testee)
{

	int testee_lenght = strlen(testee);
	int reference_lenght = strlen(reference);

	int result_size = 0;

	if (testee_lenght < reference_lenght)
	{
		result_size = reference_lenght;
	}
	else {
		result_size = testee_lenght;
	}


	char *result = malloc(result_size*sizeof(char));


	closest_anagram(reference, testee, result);

	printf("Distance: > %d\n", levenshtein(reference, result));

	free(result);
}

void lowercase(char* string)
{
	int i = 0;

	for (i = 0; string[i]; i ++)
	{
		string[i] = tolower(string[i]);
	}

}

int main (int argc, char* argv[])
{
	printf("Anagrammic distance software v0.2\n");

	int proceed = 1;
	char reference[25];
	char testee[25];

	while (proceed)
	{
		printf("1:> ");
		scanf("%s", reference);
		lowercase(reference);

		printf("2:> ");
		scanf("%s", testee);
		lowercase(reference);

		calculate_anagrammic_distance(reference, testee);
	}

	return 0;
}
