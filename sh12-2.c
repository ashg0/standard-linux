#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    pid_t pid;
	char command[1024];
	char arg[1024];

	/*
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <command> <arg>\n", argv[0]);
        exit(1);
    }
	*/

	for(;;){
		printf("%s", "command$ ");
		fgets(command, 1024, stdin);
		for(int i=0; i<1024; i++) {
			if(command[i]=='\n'){
				command[i]='\0';
				break;
			}
		}
//		printf("%s", command);
		printf("%s", "arg$ ");
		fgets(arg, 1024, stdin);
		for(int i=0; i<1024; i++) {
			if(arg[i]=='\n'){
				arg[i]='\0';
				break;
			}
		}
//		printf("%s", arg);
		
    	pid = fork();
    	if (pid < 0) {
        	fprintf(stderr, "fork(2) failed\n");
        	exit(1);
    	}
    	if (pid == 0) { /* 子プロセス */
        	execl(command, command, arg, NULL);
        	/* execl()は成功したら戻らないので、戻ったらすべて失敗 */
        	perror(argv[1]);
        	exit(99);
    	}
    	else {          /* 親プロセス */
        	int status;
	
        	waitpid(pid, &status, 0);
/*
        	printf("child (PID=%d) finished; ", pid);
        	if (WIFEXITED(status))
            	printf("exit, status=%d\n", WEXITSTATUS(status));
        	else if (WIFSIGNALED(status))
            	printf("signal, sig=%d\n", WTERMSIG(status));
        	else
            	printf("abnormal exit\n");
        	exit(0);
*/
    	}
		
	}
}
