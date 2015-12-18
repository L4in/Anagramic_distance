/*
 * For Sarah.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Please input two words\n");
		return 0;
	}

	int testee_lenght = strlen(argv[2]);
	int reference_lenght = strlen(argv[1]);

	int result_size = 0;

	if (testee_lenght < reference_lenght)
		{
			result_size = reference_lenght;
		}
	else {
		result_size = testee_lenght;
	}


	char *result = malloc(result_size*sizeof(char));


	closest_anagram(argv[1], argv[2], result);

	printf("%d\n", levenshtein(argv[1], result));

	free(result);

	return 0;

}
