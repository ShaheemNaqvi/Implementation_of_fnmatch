#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fnmatch.h>

#define MAX_KEYS 1000

int binarysearch(char ** keyArray, const char * key, int lineNum)
{
	int mid = 0;
	int begin = 0;
	int end = lineNum;

	while(begin <= end) // Implementing binary search
	{
		mid = begin + ((end - begin)/2) ;
		int ret = strcmp(keyArray[mid], key);
		if(0 == ret) // Key found, return the location
		{
			return mid;
		}
		else
		{
			if(ret < 1)
				begin = mid + 1;
			else
				end = mid - 1;
		}
	}

	printf("Key %s is not present in the input file.\n", key);
	return -1;
}

int main(int argc, char ** argv)
{
	const char * key = argv[2];
	const char * file  = argv[3];
    int lineNum = 0;
	int offset = 0;
	int i = 0;
	char * keyArray[MAX_KEYS]; // Array to store keys of input
	int offsetArray[MAX_KEYS]; // Array to store offset of start of the line
	char * line = NULL;
	char * token = NULL;
    size_t len = 0;
    size_t read;
    int loc;

	memset(offsetArray, 0, MAX_KEYS * sizeof(int));
	FILE * fp = fopen(file, "r");//Open file
	if(NULL == fp)
	{
		printf("Input file not found.\n");
		return -1;
	}	
	
	while ((read = getline(&line, &len, fp)) != -1) //Read line one by one
	{
		if(strstr(line, ",")) 
		{
			token = strtok(line, ","); // store the first token
			int tokLen = strlen(token);
			keyArray[lineNum] = (char *)malloc((tokLen + 1) * sizeof(char));
			strcpy(keyArray[lineNum],token);
		}
		else
		{
			keyArray[lineNum] = (char *)malloc((read + 1) * sizeof(char));
			strncpy(keyArray[lineNum], line, read -1); // -1 is to remove the trailing '\n'
		}

		offsetArray[lineNum] = offset;
		lineNum++;
		offset += read;
    }

	lineNum -= 1;
	//Search for the key in file
	for(i = 0; i <= lineNum; i++) /* cleanup the memory allocated for key array */
	{
		loc = fnmatch(keyArray[i],key,0);
	}
    
	if(loc >= 0) // Match found
	{
		fseek(fp, offsetArray[loc], SEEK_SET);
		getline(&line, &len, fp);
		printf("%s", line);
	}

    fclose(fp);
    if (line)
        free(line); //free lines

	for(i = 0; i <= lineNum; i++) // clean the memory
	{
		free(keyArray[i]);
	}	

	return 0;
}
