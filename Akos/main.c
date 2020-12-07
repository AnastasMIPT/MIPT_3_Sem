

#define FUSE_USE_VERSION 30 // API version 3.0
#define _FILE_OFFSET_BITS 64

#include <dirent.h>
#include <errno.h>
#include <fuse.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//#define DEBUG
//#include "../MyLib/debug_info.h"

const size_t MaxNumFiles = 1024;

struct MyFile {
    char path[PATH_MAX];
};

struct FileSystem {
    size_t dirs_num;
    struct MyFile* files;

} FileSystem;

void filesystem_open(char* directories)
{
    //DEB_INFO
    size_t num_of_dir = 0;
    for (char* str_p = directories; *str_p; str_p++) {
        if (*str_p == ':') {
            num_of_dir++;
        }
    }
    num_of_dir++;
    //printf ("dir_num = %lu\n", num_of_dir);
    //DEB_INFO
    FileSystem.files = calloc(num_of_dir, sizeof(struct MyFile));
    FileSystem.dirs_num = num_of_dir;

    char* dir_p = directories;
    for (size_t i = 0; i < num_of_dir; ++i) {
        char* delim = strchr(dir_p, ':');

        if (delim)
            *delim = '\0';
        //printf ("dir_p = %s\n", dir_p);
        realpath(dir_p, FileSystem.files[i].path);
        //printf ("f_path = %s\n", FileSystem.files[i].path);
        delim++;
        dir_p = delim;
    }

    //DEB_INFO
    //printf ("f_dir_num = %lu\n", FileSystem.dirs_num);
    for (size_t i = 0; i < FileSystem.dirs_num; ++i) {
        //DEB_INFO
        //printf ("i = %lu, path = %s\n", i, FileSystem.files[i].path);
    }
}

char* GetMostRecentFile(
    const char* rel_path,
    char* res_path_buf) //const std::string& rel_path)
{
    if (!res_path_buf)
        return NULL;

    ssize_t dir_id = -1;
    struct timespec recent_time = {0};

    for (size_t i = 0; i < FileSystem.dirs_num; ++i) {
        strcpy(res_path_buf, FileSystem.files[i].path);
        strcat(res_path_buf, rel_path);
        struct stat st;
        if (0 == stat(res_path_buf, &st) &&
            recent_time.tv_sec < st.st_mtim.tv_nsec) {
            recent_time.tv_sec = st.st_mtim.tv_nsec;
            dir_id = i;
        }
    }

    if (-1 == dir_id) {
        return NULL;
    }

    strcpy(res_path_buf, FileSystem.files[dir_id].path);
    strcat(res_path_buf, rel_path);
    return res_path_buf;
}

int my_stat(const char* path, struct stat* st, struct fuse_file_info* fi)
{
    char most_resent_path[PATH_MAX];
    if (!GetMostRecentFile(path, most_resent_path)) {
        return -ENOENT;
    }

    memset(st, 0, sizeof(struct stat));

    int status = stat(most_resent_path, st);

    if (S_ISREG(st->st_mode)) {
        st->st_mode = S_IFREG | 0444;
    }
    if (S_ISDIR(st->st_mode)) {
        st->st_mode = S_IFDIR | 0555;
    }
    return status;
}

int my_readdir(
    const char* path,
    void* out,
    fuse_fill_dir_t filler,
    off_t off,
    struct fuse_file_info* fi,
    enum fuse_readdir_flags flags)
{
    char dir_files[MaxNumFiles][NAME_MAX];
    size_t dir_files_num = 0;

    filler(out, ".", NULL, 0, 0);
    filler(out, "..", NULL, 0, 0);

    char buf_path[PATH_MAX];
    for (size_t i = 0; i < FileSystem.dirs_num; ++i) {
        strncpy(buf_path, FileSystem.files[i].path, PATH_MAX);
        strcat(buf_path, path);
        DIR* f_dir = opendir(buf_path);
        if (f_dir != NULL) {

            struct dirent* dir_data = readdir(f_dir);
            while (dir_data != NULL) {
                size_t j = 0;
                for (; j < dir_files_num; ++j) {
                    if (0 == strcmp((*dir_data).d_name, dir_files[j]))
                        break;
                }
                if (j == dir_files_num) {
                    strcpy(dir_files[j], (*dir_data).d_name);
                    dir_files_num++;
                }
                dir_data = readdir(f_dir);
            }
        }
        closedir(f_dir);
    }

    for (size_t i = 0; i < dir_files_num; i++) {
        filler(out, dir_files[i], NULL, 0, 0);
    }
    return 0;
}

int my_read(
    const char* path,
    char* out,
    size_t size,
    off_t off,
    struct fuse_file_info* fi)
{
    char newest_path[PATH_MAX] = "";
    
    char buf_path[PATH_MAX];
    struct timespec time_of_last_modification = {0};
    for (size_t i = 0; i < FileSystem.dirs_num; ++i) {
        strncpy(buf_path, FileSystem.files[i].path, PATH_MAX);
        strcat(buf_path, path);

        struct stat stats;
        // remember file if it is newer than the last one found
        if (0 == stat(buf_path, &stats) &&
            time_of_last_modification.tv_sec < stats.st_mtim.tv_sec) {
            time_of_last_modification = stats.st_mtim;
            strcpy(newest_path, buf_path);
        }
    }

    if (newest_path == "") {
        return -ENOENT;
    }
    struct stat stats;
    stat(newest_path, &stats);
    if (off >= stats.st_size) {
        return 0;
    }
    FILE* cur_file = fopen(newest_path, "r");
    fseek(cur_file, off, SEEK_CUR);
    fread(out, 1, stats.st_size, cur_file);
    fseek(cur_file, -(off + stats.st_size), SEEK_CUR);
    return stats.st_size;
}

int my_open(const char* path, struct fuse_file_info* fi)
{
    char newest_path[PATH_MAX] = "";
    //printf ("allow\n");

    char buf_path[PATH_MAX];
    struct timespec time_of_last_modification = {0};
    for (size_t i = 0; i < FileSystem.dirs_num; ++i) {
        strncpy(buf_path, FileSystem.files[i].path, PATH_MAX);
        strcat(buf_path, path);

        struct stat stats;
        if (0 == stat(buf_path, &stats) &&
            time_of_last_modification.tv_sec < stats.st_mtim.tv_sec) {
            time_of_last_modification = stats.st_mtim;
            strcpy(newest_path, buf_path);
        }
    }

    if (newest_path == "") {
        return -ENOENT;
    }
    // using bitwise & to check file access mode
    return (O_RDONLY == ((*fi).flags & O_ACCMODE)) ? 0 : -EACCES;
}

void filesystem_close()
{
    free(FileSystem.files);
}

struct fuse_operations operations = {.readdir = my_readdir,
                                     .read = my_read,
                                     .getattr = my_stat,
                                     .open = my_open};

int main(int argc, char** argv)
{
    // arguments to be preprocessed before passing to /sbin/mount.fuse3
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    //printf ("allou\n");

    typedef struct {
        char* dirs;
    } my_options_t;

    my_options_t my_options;
    memset(&my_options, 0, sizeof(my_options));

    struct fuse_opt opt_specs[] = {
        {"--src %s", offsetof(my_options_t, dirs), 0}, {NULL, 0, 0}};
    //DEB_INFO
    fuse_opt_parse(&args, &my_options, opt_specs, NULL);
    //DEB_INFO
    filesystem_open(my_options.dirs);

    // run daemon
    int ret = fuse_main(
        args.argc,
        args.argv,   // arguments to be passed to /sbin/mount.fuse3
        &operations, // pointer to callback functions
        NULL         // optional pointer to user-defined data
    );

    filesystem_close();

    return ret;
}
