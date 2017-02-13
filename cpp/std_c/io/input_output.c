#include <stdio.h>

int main(){
	// input output one char
	int c;
	printf("Enter a value :");
	c = getchar( );
	printf("\nYou entered: ");
	putchar( c );

	// input output one line
	char str[100];
	printf("Enter a value :");
	gets( str );
	printf("\nYou entered: ");
	puts( str );

	// input output based on format
	char str[100];
	int i;
	printf("Enter a value :");
	scanf("%s %d", str, &i);
	printf("\nYou entered: %s %d ", str, i);

	return 0;
}
