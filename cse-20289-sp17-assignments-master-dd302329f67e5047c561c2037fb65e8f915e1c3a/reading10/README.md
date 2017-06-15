Reading 10
==========

1. 
    pid_t child = fork(); //example system call
    if (child == -1) //if it failed...
    {
	strerror(errno); //evaluate the error number (need to include errno.h)
	return 1;
    }

2. fd = open("myfile", O_WRONLY | O_TRUNC);

3.  fd = open("myfile", O_RDONLY);
    lseek(fd, 10, SEEK_SET);

4.  fd = open(dirpath, O_RDONLY, O_DIRECTORY)
    if(fd == -1)
    {
	printf("Error: %s is not a directory\n",dirpath)
	return 1;
    }
    else
	... // do directory things

5. fork();

6. functions exec(), execl(), execv(), etc can replace a process. e.g.:
    execl("/bin/ls", "-ahl");
    
7. To tell a process to terminate:
    from the shell: 
	kill -SIGINT $PID
    within other process (can only communicate to processes of same user):
	pthread_kill(id, SIGINT); // sends the signal SIGINT to the thread with given id

8. wait(&status); //waits until child finishes, its exit status is returned through the status argument

	
