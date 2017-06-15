#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>


int main()
{
    DIR* dir = opendir(".");
    struct dirent* file;
    while((file = readdir(dir)))
    {
	char* name = file->d_name;

	if(strcmp(name,".") == 0 || strcmp(name,"..") == 0)
	    continue;

	struct stat st;
	stat(name,&st);

	printf("%s %d\n",file->d_name,(int)st.st_size);
	
    }

    closedir(dir);

    return 0;
}
