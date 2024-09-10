
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>


// struct dirent {
//     ino_t          d_ino;       /* inode number */
//     off_t          d_off;       /* offset to the next dirent */
//     unsigned short d_reclen;    /* length of this record */
//     unsigned char  d_type;      /* type of file; not supported
//                                    by all file system types */
//     char           d_name[256]; /* filename */
// };

void find_dirs(const char* dir_name,int show_f,int show_h){
  DIR* dir_stream;
  struct dirent* entries;
  dir_stream=opendir(dir_name);
  if(dir_stream==NULL){
    printf("Error : Can't open file, as it doesn't exist.");
    return;
  }
  while((entries=readdir(dir_stream))!=NULL){
    if(!show_h && entries->d_name[0]=='.'){
      continue;
    }
    if(show_f && entries->d_type==4){
      continue;
    }
    // printf("%d\n",entries->d_type);
    printf("%s\n",entries->d_name);
  }
  if(closedir(dir_stream)==-1){
    perror("Can't close directory");
  }
}

int main(int argc, char **argv) {
  char* dir_name="";
  int show_f=0;
  int show_h=0;
  for(int i=1;i<argc;i++){
    if(strcmp(argv[i],"-f")==0){
      show_f=1;
    }
    else if(strcmp(argv[i],"-h")==0){
      show_h=1;
    }
    else{
      dir_name=argv[i];
    }
  }
  find_dirs(dir_name,show_f,show_h);
  return 0;
}
