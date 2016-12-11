#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "interactive.h"

void waitForEnter() {
	while (_kbhit())
		_getch();
	while (_getch()!=13);
}

char choice(char variant[]) {
	while (_kbhit())
		_getch();
	char key;
	do
		key = _getch();
	while (!strchr(variant, key));
	printf("%c\n", key);
	return key;
}

char *toRU(const char *s) {
	char *b = (char *)malloc(sizeof(char)*strlen(s));
	unsigned int i=0;
	for (i; s[i]!=0; i++)
		if ((s[i]>='А')&&(s[i]<='п')) {
			b[i] = s[i]+192;
		} else if ((s[i]>='р')&&(s[i]<='я'))
			b[i] = s[i]-16;
		else if (s[i]=='№')
			b[i] = -4;
		else if (s[i]=='Ё')
			b[i] = -16;
		else if (s[i]=='ё')
			b[i] = -15;
		else
			b[i] = s[i];
	b[i] = 0;
	return b;
}

char *intToStr(int n) {
	const int maxlen=7;
	char *str = (char *)calloc(maxlen, sizeof(char));
		/*
		  calloc(), в отличие от malloc(), заполняет выделенную память нулями;
		  calloc() рассчитан на создание массивов.
		*/
	bool minus = (n<0)? true:false;
	if (n==0)
		strcpy(str, "0");
	else {
		int d, pos=maxlen-1;
		while (n>0) {
			d = n%10;
			str[pos] = d+'0';
			--pos;
			n /= 10;
		}
	}
	if (minus)
		str[0] = '-';
	while (!str[minus])
		for (int i=minus; i<maxlen; i++)
			str[i] = str[i+1];
	return str;
}

// Возвращает true, если 3 принятых числа располагаются в порядке возрастания или убывания
bool inOrder(const int a, const int b, const int c) {
	return (((a>=b)&&(b>=c))||((a<=b)&&(b<=c)));
}

// Приводит строку к нижнему регистру
char *lowerCase(char *word) {
	for (int i=0; word[i]; i++)
		if (inOrder('A', word[i], 'Z'))
			word[i] += 'a'-'A';
		else if (inOrder('А', word[i], 'Я'))
			word[i] += 'а'-'А';
		else if (word[i]=='Ё')
			word[i] = 'ё';
	return word;
}
