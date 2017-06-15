Reading 10 - Grading
========================
**Score**: 3.25/4

**Grader**: Mimi Chen


Deductions
------------------
(-0.25) You need to call printf or fprintf stderr(errno) because stderr(errno) would only give you a string

		fprintf(stderr, "%s\n", stderr(errno));


(-0.25) If you try to open the dir, it could fail because you do not have permission to open it. You want to perform lstat and S_ISDIR on it 

		struct stat s;
		lstat(path, &s); // stat is OK too
		S_ISDIR(s.st_mode);

(-0.25) In walk.c, you need to check the return status of opendir to see if it failed


Comments
------------------
