#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <windows.h>


long SizeOfFile (int fd);


struct Item
{
    int value;
    uint32_t next_pointer;
};


int main (int argc, char* argv[]) {




    HANDLE input_file = CreateFileA (argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
    int f_in = open (argv[1], O_RDONLY);
    
    if (-1 == f_in) {   
        return 0;
    }

    long file_size = SizeOfFile (f_in);
    if (0 == file_size) return 0;

    char* buf_in = (char*) calloc (file_size, sizeof (char));

    ssize_t n_read = read (f_in, buf_in, file_size);
    


    int num_syb = 0;

    int val = *((int*) buf_in);
    printf ("%d ", val);
    //buf_out_ptr += num_syb;


    uint32_t next_el = *((uint32_t*) (buf_in + sizeof(int)));
    
    while (next_el != 0) {
        val = *((int*) (buf_in + next_el));
        printf ("%d ", val);
        //buf_out_ptr += num_syb;

        next_el = *((uint32_t*) (buf_in + next_el + sizeof (int)));
    }

    
    close (f_in);
    free (buf_in);
    //free (buf_out);

    return 0;
}



/*! Функция, определяющая размер файла
*
*	@param [in] NameOfFile Имя файла
*
*	@return Размер файла
*
*/
long SizeOfFile (int fd)
{
    long FileSize = lseek (fd, 0, SEEK_END);
    lseek (fd, 0, SEEK_SET);

    return FileSize;
}