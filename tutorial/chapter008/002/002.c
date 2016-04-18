#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */
#define PERMS 0666

typedef struct _iobuf {
    int cnt; /* characters left */
    char *ptr; /* next character position */
    char *base; /* location of buffer */
    int flag; /* mode of file access */
    int fd; /* file descriptor */
}FILE;

enum _flags {
    _READ = 02, /* file open for reading */
    _WRITE = 04, /* file open for writing */
    _EOF = 05, /* EOF has occurred on this file */
    _ERR = 06 /* error occurred on this file */
};

FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr */
    { 0, (char *)0, (char *)0, _READ, 0 },
    { 0, (char *)0, (char *)0, _WRITE, 1 },
    { 0, (char *)0, (char *)0, _WRITE, 2 }
};

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)
#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

FILE *fileopen(char *name, char *mode);
int _fillbuf(FILE *);
void _flushbuf(int, FILE *);
void _fflush (FILE *);
void fileclose(int);

int main(int argc, char *argv[]) {
    int c;
    FILE *api = stdin, *apo = stdout;

    if (argc > 1)
        api = fileopen(argv[1], "r");
    if (argc > 2)
        apo = fileopen(argv[2], "w");

    while ((c = getc(api)) != EOF)
        putc(c, apo);
    
    _fflush(apo);
    //fileclose(api->fd);
    //fileclose(apo->fd);

    return 0;
}
 
FILE *fileopen(char *name, char *mode){
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (fp->flag == 0)
            break;

    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);

    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
            lseek(fd, 0L, 2);
    }
    
    else
        fd = open(name, O_RDONLY, 0);

    if (fd == -1)
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

int _fillbuf(FILE *fp){
    if (fp->flag != _READ)
        return EOF;

    fp->ptr = fp->base = (char *) malloc(BUFSIZ);
    fp->cnt = read(fp->fd, fp->ptr, BUFSIZ);
    
    if (--fp->cnt < 0)
        return EOF;
    
    return (unsigned char) *fp->ptr++;
}

void _flushbuf(int c, FILE *fp) {
    if (fp->flag == _WRITE) {
        if (fp->base == NULL) {
            fp->ptr = fp->base = (char *) malloc(BUFSIZ);
            fp->cnt = BUFSIZ - 1;  
        }

        *fp->ptr++ = c;
    }

    else
        write(2, "Couldn't write to file", BUFSIZ);
}

void _fflush(FILE *fp) {    
    int i;

    if (fp->base != NULL) 
        i = write(fp->fd, fp->base, BUFSIZ - fp->cnt);

    fp->cnt = 0;
    fp->ptr = NULL;
    free(fp->base);
    fp->flag = 0;
    fp->fd = 0;
}

void fileclose(int fd) {
    int i;

    i = close(fd);
}
