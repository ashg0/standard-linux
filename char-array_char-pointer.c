#include <stdio.h>

int main() {
	char *buf1 = "hello";
	char buf2[1024] = "hello";
	int array[5];
	printf("array=%p : &array=%p\n", array, &array);

	printf("%p\n", buf1);
	//putchar(*buf1);putchar('\n');
	//putchar(buf1[0]);putchar('\n');
	//printf("%p\n", &buf1[0]);

	printf("%p\n", buf2);
	//putchar(buf2[0]);putchar('\n');
	//putchar(*buf2);putchar('\n');
	//printf("%p\n", &buf2[0]);

	printf("%p\n", &buf1);
	printf("%p\n", &buf2);
/*
	printf("%s\n", buf1);
	printf("%s\n", buf2);
	printf("%s\n", &buf2[0]);

	printf("%s\n", buf1+1);
	printf("%s\n", buf2+1);

	printf("%d\n", buf1);
	printf("%d\n", buf2);
	printf("%d\n", *buf1);
	printf("%d\n", *buf2);
*/
	return 0;
}
