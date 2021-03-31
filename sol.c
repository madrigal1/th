#include <stdio.h> 
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define ss 40	//size of single word
//#define ds 99171 //words
#define ds 3
//99,171
int res =0; // total no of palindromix words
char dict[ds][ss];

#define MAX_CHARS 10000
// safe_usub -- perform safe unsigned subtraction
size_t safe_usub (size_t x, size_t y) {
  return x > y ? x - y : y - x ;
}

char* str_reverse (const char* const str) {
  if (!str) { return NULL; }

  size_t len = strnlen(str, MAX_CHARS);
  char*  new = malloc( sizeof(char) * len );

  size_t i;
  for (i = 0; i < len; i++) {
    new[i] = str[ safe_usub(i + 1, len) ];
  }

  new[i] = 0;

  return new;
}


struct pair {
	int start;
	int end;
};
struct pair indexes[26];


//5794
int checkpalindromic(char *s) {
	s = str_reverse(s);
	for(int i=0;i<ds;i++){
		if(strcmp(s,dict[i]) == 0){
			//printf("%s %s %d\n",dict[i],s,res); //this one
			return 1;
		}
	}
	return 0;
}


void check(char x) {
	x = tolower(x);
	for(int i=0;i<ds;i++){
		char first_char = tolower(dict[i][0]);
		if(x == first_char){
			if(checkpalindromic(dict[i])){
				res++;
			}
		} else {
			indexes[x-'a'].end = i-1;  
		}	
	}	
}

void init() {
	freopen("words.txt","r",stdin);
	char str[40];
	for(int i=0;i<ds;i++){
		scanf("%s",str);
		strcpy(dict[i],str);
	}	
}

int main() {
	freopen("output.txt","w",stdout);
	char alpha = 'a';
	init();
	for(int i=0;i<1;i++) {
		//printf("%c",alpha);
		indexes[i].start = i;
		check(alpha);
		 alpha++;
	}
	printf("%d",res);
	return 0;
}
