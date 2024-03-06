#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int fp1, fp2, n;
	char buf1[20];
	char buf2[20];
	printf("Enter data to be written to file:");
	scanf("%s",buf1);
	fp1 = open("file.txt", O_CREAT | O_WRONLY, 0777);
	write(fp1, buf1, strlen(buf1));
	printf("Writing done\n");
	fp2 = open("file.txt", O_RDONLY);
	n = read(fp2, buf2, 20);
	buf2[n] = '\0';
	printf("Content read: %s\n", buf2);
	close(fp1);
	close(fp2);

	return 0;
}


// #include <stdio.h>
// #include <fcntl.h>
// #include <unistd.h>

// int main() {
//     // Create a new file

//  int fd = open("test.txt", O_WRONLY);
//     // Write to the file
//     write(fd, "Hello, File Manipulation!\n", 26);

//    fd = open("test.txt", O_RDONLY);

//     // Read and print the content
//     char buffer[100];
//     read(fd, buffer, 99);
//     buffer[99] = '\0';
//     printf("File Content: %s\n", buffer);

//     // Close the file
//     close(fd);

//     return 0;
// }


