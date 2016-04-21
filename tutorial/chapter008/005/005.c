#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

void action(DIR *);

int main (int argc, char **argv) {
    DIR *dp;
    
    if (argc == 1) {
        dp = opendir(".");
        action(dp);
    }

    else {
        while (--argc > 0) {
            dp = opendir(*++argv);
            action(dp);
        }
    }
    
    return 0;
}

void  action(DIR * dp) {
    struct dirent *ep;
    struct stat st;

    if (dp != NULL) {
        while ((ep = readdir(dp)) > 0) {
            if ((strcmp(ep->d_name, ".") == 0) ||(strcmp(ep->d_name, "..") == 0))
                continue;
            
            if (stat(ep->d_name, &st) < 0) {
                fprintf(stderr, "Couln'd fetch information about %s", ep->d_name);
                break;     
            }
          
                printf("Information for %s\n", ep->d_name);
                printf("---------------------------\n");
                printf("File Size: \t\t%lu bytes\n", st.st_size);
                printf("Number of Links: \t%lu\n", st.st_nlink);
                printf("File inode: \t\t%lu\n", st.st_ino);
 
                printf("File Permissions: \t");
                printf((S_ISDIR(st.st_mode)) ? "d" : "-");
                printf((st.st_mode & S_IRUSR) ? "r" : "-");
                printf((st.st_mode & S_IWUSR) ? "w" : "-");
                printf((st.st_mode & S_IXUSR) ? "x" : "-");
                printf((st.st_mode & S_IRGRP) ? "r" : "-");
                printf((st.st_mode & S_IWGRP) ? "w" : "-");
                printf((st.st_mode & S_IXGRP) ? "x" : "-");
                printf((st.st_mode & S_IROTH) ? "r" : "-");
                printf((st.st_mode & S_IWOTH) ? "w" : "-");
                printf((st.st_mode & S_IXOTH) ? "x" : "-");
                printf("\n\n");
        }
        
        closedir (dp);
    }
  
    else
        fprintf(stderr, "Couldn't open the directory");
}
