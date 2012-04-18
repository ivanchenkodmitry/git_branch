#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define CWD_LEN 1000
#define BRIGHT 1
#define DARK 2
#define RED 31
#define GREEN 32


int main(int argc, char *argv[])
{
struct stat s;
FILE * head_file;
int l =0;
char head_str[CWD_LEN];
char cwd[CWD_LEN];
getcwd(cwd, CWD_LEN);

/*printf("%c[%d;%dm", 0x1B, BRIGHT, GREEN);*/
for (int i=CWD_LEN;i>=0 ; i--){
    if (cwd[i]=='/'){
        strcat(cwd, "/.git/HEAD");
        if(stat(cwd, &s) == 0) {
            head_file = fopen(cwd, "r");
            if (!fread(head_str, sizeof(char), CWD_LEN , head_file))
                printf("HEAD is empty");
            for (l = 0; ; l++){
                if (head_str[l]=='\0')
                    break;
            }
            for (int j=l ;j>=0; j--){
                if (head_str[j]=='/'){
                    for (int k = j+1 ; (k<CWD_LEN-1) && (head_str[k] !='\0') && (head_str[k] !='\n') ; k++){
                        printf("%c", head_str[k]);
                    }
                    break;
                }
            }
            break;
        }
        cwd[i]='\0';
    }
}
/*printf("%c[%dm", 0x1B, 0);*/
return 0; 
}

