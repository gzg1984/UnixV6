#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
extern void exit(int);
/*
 * cp oldfile newfile
 */

main(argc,argv)
char **argv;
{
	struct stat target_stat;
	struct stat source_stat;
	static char buf[1024];
	static char bp_a[128];
	int fold, fnew, n;
	register char *p1, *p2, *bp;
	int mode;

	if(argc != 3) {
		write(1, "Usage: cp oldfile newfile\n", 26);
		exit(1);
	}
	if((fold = open(argv[1], 0)) < 0) {
		write(1, "Cannot open old file.\n", 22);
		exit(1);
	}
	fstat(fold, &source_stat);
	mode = source_stat.st_mode;
	/* is target a directory? */
	if (stat(argv[2], &target_stat)>=0 && S_ISDIR(target_stat.st_mode)) {
		p1 = argv[1];
		p2 = argv[2];
		bp = bp_a;
		while(*bp++ = *p2++);
		bp[-1] = '/';
		p2 = bp;
		while(*bp = *p1++)
			if(*bp++ == '/')
				bp = p2;
		argv[2] = bp_a;
	}
	if (stat(argv[2], &target_stat) >= 0) {
		if (target_stat.st_dev==source_stat.st_dev 
			&& target_stat.st_ino==source_stat.st_ino) {
			write(1, "Copying file to itself.\n", 24);
			exit(1);
		}
	}
	if ((fnew = creat(argv[2], mode)) < 0) {
		write(1, "Can't create new file.\n", 23);
		exit(1);
	}
	while(n = read(fold,  buf,  512)) {
	if(n < 0) {
		write(1, "Read error\n", 11);
		exit(1);
	} else
		if(write(fnew, buf, n) != n){
			write(1, "Write error.\n", 13);
			exit(1);
		}
	}
	exit(0);
}
