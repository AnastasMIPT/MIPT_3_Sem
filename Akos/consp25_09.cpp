Виктор вадимович



1. Не забываем закрывать дескрипторы
2. Лучше sizeof от value, чем от type
3. O_CREAT и нет третьего аргумента -- open
4. размер константной строки лучше вычислять через sizeof



Файловая система.


Файловая система делится на блоки. Обычно блок - 4096 байт. Файл, даже пустой заниает как минимум один блок. 



ln -s zero.txt some_link.txt  // теперь some_link - ссылка на zero.txt
ls -l



От чего зависит размер символической ссылки? 
    В ссылке просто хранится путь до файла. Размер этого пути и определяет размер файла-ссылки.


Типы файлов:
    1. regular
    2. symlink
    3. block special file
    4. character special file // отличается от block тем, что нет произвольного доступа
    5. fifo
    6. socket
    7




/dev/stdout


ln dflsjfl.txt file2.txt  // второй тип ссылки file2.txt теперь другое имя для dflsjfl.txt, но в статах файла увеличится колво файлов

man unlink


#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int main (int argc, char* argv[]) {

    int fd = open (argv[1], O_RDONLY);

    char buffer[4096];
    ssize_t cnt = read (fd, buffer, sizeof (buffer));
    write (1, buffer, cnt);

    close (fd);

}


/etc/fstab

cd /dev/sda  //block special file
stat sda


dd if=ubunta.iso of=/dev/sda

/dev/tty   //character special file



man 2 stat  - записывает информацию о файле в специальную структуру.

struct stat {
               dev_t     st_dev;         /* ID of device containing file */
               ino_t     st_ino;         /* Inode number */
               mode_t    st_mode;        /* File type and mode */
               nlink_t   st_nlink;       /* Number of hard links */
               uid_t     st_uid;         /* User ID of owner */
               gid_t     st_gid;         /* Group ID of owner */
               dev_t     st_rdev;        /* Device ID (if special file) */
               off_t     st_size;        /* Total size, in bytes */
               blksize_t st_blksize;     /* Block size for filesystem I/O */
               blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */
};

lstat в отличие от stat не декадирует символическую ссылку.sizeof


Комментарии к задачам.
Во всех задачах main отсутствует!!!

0
1 подстава: проверяем регулярный ли файл. Не забывать о переполнении (uint64 good). размер берем из st_size.
2 
3 для этой задачи обязательно нужна задача 0. man 2 symlink; man 2 readlink 





Каталоги 
mkdir subdir 
для каталогов права x означают перейти в каталог. r прочитать список файлов . w создать новый каталог в файле.

ls -a показывает скрытые файлы
. и .. тоже файлы

абсолютный путь начинается со /

в /bin нет cd так как эта команда меняет состояние процесса

man getcwd
man chdir





Семинар 02.20

Использовать snprintf вместо sprintf


Отбражение файлов на память.alignas

Сегментная адресация.

Страничная адресация.

4096 байт - размер страницы
    указатель    |10|10|12|

/proc/self/maps





#include <sys/mman.h>
#include 


int main () {

    int fd = open (argv[1], O_RDONLY);

    char* bufer = mmap (NULL,          //address or null
                        4096,          // size
                        PROT_READ | PROT_WRITE,     // 
                        MAP_PRIVATE,    // страница доступна только текущему процессу
                        fd,            // open file or -1 если не используется отображение на файл
                        0               // offset
                        );
    if (MAP_FAILED == buffer) {
        perror ("mmap");
        exit (1);
    }


    buffer[0] = 'h';
    munmap (buffer, 4096);
    
    
    
    close (fd); 
}



man msync

ulimit -m 


1. mmap c read, обратить вниамание на ограничение по памяти (сделать отображение в файл) , strstr ()
2. 
3. Ограничение по памяти!! Создать текстовый файл мапим и работаем с файлом как с памятью, функция ftruncate. Тестовый вывод. Форматированный вывод.
4. односвязный список




9 октября .............................................................................................


ПРОЦЕССЫ


Атрибуты процесса


Команды
pivot_root
chroot /u_sr



umask 

Команды
ps -список всех процессов
ps -aux 
ps - a
top
cd /proc


Каталоги по PID
PID - proces id
В таких каталогах много инфы.



->(R)Running<->(S)Suspended

->Running<->(T) Stoped
->Running<->(D)Disk Suspended

в (Z)Zombie можно прийти из любого кроме Disk Suspended

Команда 
fg <номер процесса>

sleep (10); // R->S


man shed_yield


Создание процесса pid_t resut = fork ()


#include "stdio.h"
#include "sys/types.h"
#include "stdlib.h"
#include "sys/wait.h"
#include "unistd.h"

return value fork ()
pid_t = 0 если мы выполняемся внутри дочернего процесса
-1 - error

int main () {
    const char S[] = "Hello";

    printf ("%s ", S);
    fflush (stdout);
    pid_t pid = fork ();
    if (0 == pid) {
        puts ("I'm a son\n");
        sleep (1);
        exit (1); // 0 <= status < 255
    } else if (0 < pid) {
        puts ("I'm parent");
        int status = 0;
        wait (&status);
    }
    write (1,S, sizeof(S)-1);


}

man waitpid
man kill
int kill ();




habr fork() может потерпеть неудачу: это важно


_exit - системный вызов
exit - функция выхода, сбрасывающая беферы, вызывающая системный вызов _exit

не все виртуальные страницы дублирются для процессов.

Команда pstree 


killall forkbomb

ulimit -a


Типовые ошибки по 3
-Wl, --wrap
__real__
__wrap__
PATH_MAX
[NAME_MAX+1] - максимальная длина имени каталога
..............................................................
0. fork_bomb do {} while (-1 == pid)
1. должен быть именно пробел, не забыть про fflush().
2. через exit_status возвращаем значение  

hexdump

xxd -r













...................................................................
Семинар


по задачам 5
Проблемы с буфкризацией scanf
Первый процесс вызывает сканф и только после этого форк. 


Приаедение типов в СИ. 




Системный вызов exec
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
int main (int argc, char* argv[]) {
    char* program = argv[1];
    char* args[argc];
    for (int i = 0; i < argc; ++i) {
        args[i-1] = argv[i];
    }
    args[argc - 1] = NULL;


    pid_t pid = fork ();

    if (0 == pid) {
        set_stack_limit ();

        // ls -l -a
        
        
        
        // execlp ("ls", "ls", "-l", "a", NULL))
        // perror ("exec");
        // exit (1);
        



        
        execvp (program, args);
        perror ("exec");
        exit (1);

    } else if (-1 == pid) {
        perror ("fork");
        exit (1);
    } else if (pid > 0) {
        int status = -1;
        waitpid (pid, &status, 0);
    }
}

void set_stack_limit (uint64_t new_stk_size);





exec(l\v)(p)(e)

setenv () 

man strtoull

getrlimit
setrlimit

ptrace()

strace ls



whereis ulimit


clang-format -i file.c


0. Прочитать строку и кормить ее питону. fork не нужен
python3 --help
python3 -c

1. нужен fork чтобы скомпилровать

2. формат cgi можно почитать в docs python org


Ошибки:

Лишние инклюды - плохо, нужно использовать snprintf вместо sprintf.


...........................................................................

Межпроцессные взаимодействия


#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>


int main (int argc, char** argv) {
    int fd = atoi (argv[1]);
    const char String[] = "Hello\n";

    write (fd, String, sizeof(String) - 1);
}

dup2 (fd, 1) // ??? 1->fd

man dup2
man 2 pipe

7-1

#include <unistd.h>
#include <sys/wait.h>

pid_t launch (char* cmd, char* arg, int in_fd, int out_fd) {
    pid_t pid fork ();

    if (0 == pid) {
        if (0 != in_fd)  dup2 (in_fd, 0);
        if (1 != out_fd) dup2 (out_fd, 1);
        close (in_fd); close (out_fd);
        execlp (cmd, cmd, arg, NULL);
        _exit (0);
    }
}

int main () {

    int pipe_fds[2];
    pipe (pipe_fds);

    pid_t ls = launch ("ls", "-a", 0, pipe_fds[1]);
    pid_t grep = launch ("grep", "m", pipe_fds[0], 1);

    close (pipe_fds[0]); close (pipe_fds[1]);
    
    wait (0); wait (0);

}

<-|0    1|<-


1. dup2 (IN, 0)
IN>CMD|read

2. gcc | 
eer - поток

3. 1*3

4. 





#include <stdio.h>
#include <unistd.h>

int main () {

}


#include <signal.h>

ps aux -A | grep a.out

^Z - ставит на паузу
fg - снимает с паузы

^C - останавливает процесс

abort () - аналог команды kill = kill (getpid(), SIGABRT);

Ctrl + \ - завершение процесса и ...
Это нужно для тестировщиков.

SIGHUB - обрыв соедения (перечитать config)
SIGINT - Ctrl + C
SIGQUIT - Ctrl + \

/usr/sbin/sysctl kernel.core_pattern ...

SIGKILL - убийство
SIGTERM - завершение работы
SIGSTOP - 

системный вызов signal

gcc -g abc.c

gdbserver  :1234 a.out


в другой вкладке 
gdb
file a.out
target remote localhost:1234

#include <signal.h>

void handler (int signum) {
    printf ("Get signal %d\n", signum);
}

void handler_with_three_arg (int signum, siginfo_t* info, void* context) {

}

int main () 
{
    struct sigaction sa {
        .__sigaction_handler.sa_sigaction =handler_with_three_arg;
        .sa_flags = SA_RESTART | SA_SIGINFO;
    };
    sigaction (SIGINT, &sa, NULL);
    while (1) {
        pause ();
    }

}

SA_NODEFER


killall -SIGKILL a.out

#define _D_DEFAULT_SOURSE
#define _GNU_SOURCE


sigaction () вместо signal ()


man 7 signal-safety    !!!!!!!!!!!!!!!  - функции которые можно использовать внутри обработчика 
_POSIX_REALTIME_SIGNALS

Более правильно в функции обработке синалов делать все очень быстро. 


sigatomic_t signum_recived = -1;

маски сигналов

sigprocmask
pause
sigsaspend
signalfd
sigqueue

0. fflush сразу после вывода
1. проставлять только флаги в обр-ке сигналов
2. 
3. обработчик с тремя арг sigqueue 








int my_readdir(
    const char* path,
    void* buf,
    fuse_fill_dir_t filler,
    off_t offset,
    struct fuse_file_info* fi)
{


    // std::vector<fs::path> dirs;
    // for (auto& root : roots) {
    //     fs::path full_path = root / path;
    //     if (fs::exists(full_path) &&
    //         fs::is_directory(fs::directory_entry(full_path).status())) {
    //         dirs.push_back(full_path);
    //         std::cout << "dir match: " << full_path << std::endl;
    //     }
    // }

    char dirs[FileSystem.dirs_num][PATH_MAX] = {};
    size_t dir_num = 0;
    char buf_path[PATH_MAX] = {};

    for (size_t i = 0; i < FileSystem.dirs_num; ++i) {
        strncpy (buf_path, FileSystem.files[i].path, PATH_MAX);
        strcat  (buf_path, path);
        
        struct stat st;
        stat(buf_path, &st);
        
        if (0 == access (buf_path, F_OK) && S_ISDIR (st.st_mode)) {
            strncpy (dirs[dir_num], buf_path, PATH_MAX);
            dir_num++;
        }
    }



    // if (dirs.size() == 0) {
    //     return -ENOENT; // no dirs found
    // }
    if (0 == dir_num) {
        return -ENOENT;
    }

    // two mandatory entries: the directory itself and its parent
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);

    // std::unordered_set<std::string> added;

    // for (auto& dir : dirs) {
    //     for (auto& entity : fs::directory_iterator(dir)) {
    //         std::string filename(fs::path(entity).filename().c_str());
    //         if (added.count(filename) == 0) {
    //             added.insert(filename);
    //             filler(buf, filename.data(), NULL, 0);
    //         }
    //     }
    // }


    return 0; // success
}
