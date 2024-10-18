/*
    Name : Rohan K H
    Sec  : 24018 I
    Date : 16/10/2024
    Description : The MP3 Tag Reader project in C is a utility that reads and displays metadata from MP3 audio files. 
                  It utilizes the ID3 tagging standard to extract information such as song title, artist, album, and track number. 
                  The project emphasizes efficient file handling and parsing techniques to ensure quick access to tags. 
                  Designed for educational purposes, it serves as a practical introduction to file I/O and data structures in C programming.
*/

#include<stdio.h>
#include"edit.h"
#include"return.h"
#include<string.h>

OperationType check_operation_type(char *argv[1])
{
    // checking operation type as edit
    if(strcmp(argv[1], "-e") == 0)
    {
        return edit;
    }
    else if(strcmp(argv[1], "-v") == 0)  // checking operation type as view
    {
        return view;
    }
    else if(strcmp(argv[1],"--help") == 0)  // checking operation type as help
    {
        return help;
    }
    else  // deafult operation type
    {
        return invalid;
    }
}

// function declaration for open files
Status edit_open_file(char *argv[4], E_MP3 *e_mp3)
{
    // storing file name in the structure member of file name
    e_mp3->e_mp3_file_name = argv[4];

    // opening file in read mode
    e_mp3->e_fptr_mp3 = fopen(e_mp3->e_mp3_file_name,"r");

    if(e_mp3->e_fptr_mp3 == NULL)
    {
        // Error message
        printf("Error: unable to open file %s\n",e_mp3->e_mp3_file_name);
        return failure;
    }
    //printf("%d and %s\n",ftell(mp3->fptr_mp3),mp3->mp3_file_name);
    e_mp3->e_mp3_sample_file_name = "sample.mp3";
    
    // opening sample file for read and write operation
    e_mp3->e_fptr_mp3_sample = fopen(e_mp3->e_mp3_sample_file_name,"w");

    if(e_mp3->e_fptr_mp3_sample == NULL)
    {
        // Error message
        printf("Error: unable to open file %s\n",e_mp3->e_mp3_sample_file_name);
    }

    return success;
}

// function declaration for edit file details
Status edit_file_details(char *argv[2], E_MP3 *e_mp3)
{
    // function call to copy initial 10 bytes of data from source file to sample file
    if(e_skip_header_data(e_mp3) != success)
    {
        return failure;
    }

    // function call to copy initial  TIT2 from source file to sample file
    if(e_check_TIT2(e_mp3) != success)
    {
        return failure;
    }


    if(strcmp(argv[2],"-t") == 0)
    {
        // function call to modify song title size
        if(modify_size_of_song_title(argv, e_mp3) != success)
        {
            return failure;
        }
    
        int size   = getting_size_of_song_title(e_mp3);  // function call to getting song title size

        // copying 3 bytes of data (flag) from source file to sample file
        char read[3];
        fread(read,3,1,e_mp3->e_fptr_mp3);
        fwrite(read,3,1,e_mp3->e_fptr_mp3_sample);


        if(modify_song_title(argv, e_mp3) != success)
        {
            return failure;
        }

        fseek(e_mp3->e_fptr_mp3,size-1,SEEK_CUR);

    }
    else // function call to copy song title size and song title from source file to sample file
    {
        e_mp3->size_of_song_title = edit_size_of_song_title(e_mp3);

        // copying 3 bytes of data (flag) from source file to sample file
        char read[3];
        fread(read,3,1,e_mp3->e_fptr_mp3);

        fwrite(read,3,1,e_mp3->e_fptr_mp3_sample);

        if(edit_song_title(e_mp3) != success)
        {
            return failure;
        }
    }

    // function call to copy TPE1 from source file to sample file
    if(e_check_TPE1(e_mp3) != success)
    {
        return failure;
    }

    if(strcmp(argv[2],"-a") == 0)
    {
        if(modify_size_of_artist_name(argv, e_mp3) != success)
        {
            return failure;
        }

        int size   = getting_size_of_artist_name(e_mp3); 

        // copying 3 bytes of data (flag) from source file to sample file
        char read[3];
        fread(read,3,1,e_mp3->e_fptr_mp3);
        fwrite(read,3,1,e_mp3->e_fptr_mp3_sample);

        if(modify_artist_name(argv, e_mp3) != success)
        {
            return failure;
        }

        fseek(e_mp3->e_fptr_mp3,size-1,SEEK_CUR);
    }
    else // function call to copy artist name size and artist name from source file to destination file
    {
        e_mp3->size_of_artist_name = edit_artist_name_size(e_mp3);

        // copying 3 bytes of data (flag) from source file to sample file
        char read[3];
        fread(read,3,1,e_mp3->e_fptr_mp3);

        fwrite(read,3,1,e_mp3->e_fptr_mp3_sample);

        if(edit_artist_name(e_mp3) != success)
        {
            return failure;
        }

    }

    // function call to copy TALB from source file to destination file
    if(e_check_TALB(e_mp3) != success)
    {
        return failure;
    }

    if(strcmp(argv[2],"-A") == 0)
    {
        if(modify_size_of_album_name(argv, e_mp3) != success)
        {
            return failure;
        }

        int size   = getting_size_of_album_name(e_mp3); 

        // copying 3 bytes of data (flag) from source file to sample file
        char read[3];
        fread(read,3,1,e_mp3->e_fptr_mp3);
        fwrite(read,3,1,e_mp3->e_fptr_mp3_sample);

        if(modify_album_name(argv, e_mp3) != success)
        {
            return failure;
        }

        fseek(e_mp3->e_fptr_mp3,size-1,SEEK_CUR);
    }
    else // function call to copy album name size and album name from source file to destination file
    {
        e_mp3->size_of_album_name = edit_album_name_size(e_mp3);

        // copying 3 bytes of data (flag) from source file to sample file
        char read[3];
        fread(read,3,1,e_mp3->e_fptr_mp3);

        fwrite(read,3,1,e_mp3->e_fptr_mp3_sample);

        if(edit_album_name(e_mp3) != success)
        {
            return failure;
        }
    }

    // function call to copy TYER from source file to destination file
    if(e_check_TYER(e_mp3) != success)
    {
        return failure;
    }

    if(strcmp(argv[2],"-y") == 0)
    {
        if(modify_size_of_year(argv, e_mp3) != success)
        {
            return failure;
        }

        int size   = getting_size_of_year(e_mp3); 

        // copying 3 bytes of data (flag) from source file to sample file
        char read[3];
        fread(read,3,1,e_mp3->e_fptr_mp3);
        fwrite(read,3,1,e_mp3->e_fptr_mp3_sample);

        if(modify_year(argv, e_mp3) != success)
        {
            return failure;
        }

        fseek(e_mp3->e_fptr_mp3,size-1,SEEK_CUR);
    }
    else // function call to year size and year from source file to destination file
    {
        e_mp3->size_of_year = edit_year_size(e_mp3);

        // copying 3 bytes of data (flag) from source file to sample file
        char read[3];
        fread(read,3,1,e_mp3->e_fptr_mp3);

        fwrite(read,3,1,e_mp3->e_fptr_mp3_sample);

        if(edit_year(e_mp3) != success)
        {
            return failure;
        }
    }

    // function call to copy TCON from source file to destination file
    if(e_check_TCON(e_mp3) != success)
    {
        return failure;
    }

    if(strcmp(argv[2],"-m") == 0)
    {
        if(modify_size_of_content(argv, e_mp3) != success)
        {
            return failure;
        }

        int size   = getting_size_of_content(e_mp3); 

        // copying 3 bytes of data (flag) from source file to sample file
        char read[3];
        fread(read,3,1,e_mp3->e_fptr_mp3);
        fwrite(read,3,1,e_mp3->e_fptr_mp3_sample);

        if(modify_content(argv, e_mp3) != success)
        {
            return failure;
        }

        fseek(e_mp3->e_fptr_mp3,size-1,SEEK_CUR);   
    }
    else // function call to copy content size and content from source file to destination file
    {
        e_mp3->size_of_content = edit_content_size(e_mp3);

        // copying 3 bytes of data (flag) from source file to sample file
        char read[3];
        fread(read,3,1,e_mp3->e_fptr_mp3);

        fwrite(read,3,1,e_mp3->e_fptr_mp3_sample);

        if(edit_content(e_mp3) != success)
        {
            return failure;
        }

    }

    // function call to copy COMM from source file to destination file
    if(e_check_COMM(e_mp3) != success)
    {
        return failure;
    }

    if(strcmp(argv[2],"-c") == 0)
    {
        if(modify_size_of_comment(argv, e_mp3) != success)
        {
            return failure;
        }

        int size   = getting_size_of_comment(e_mp3); 

        // copying 3 bytes of data (flag) from source file to sample file
        char read[3];
        fread(read,3,1,e_mp3->e_fptr_mp3);
        fwrite(read,3,1,e_mp3->e_fptr_mp3_sample);

        if(modify_comment(argv, e_mp3) != success)
        {
            return failure;
        }

        fseek(e_mp3->e_fptr_mp3,size-1,SEEK_CUR);
    }
    else // function call to comment size and comment from source file to destination file
    {
        e_mp3->size_of_comment = edit_comment_size(e_mp3);

        // copying 3 bytes of data (flag) from source file to sample file
        char read[3];
        fread(read,3,1,e_mp3->e_fptr_mp3);

        fwrite(read,3,1,e_mp3->e_fptr_mp3_sample);

        if(edit_commentE(e_mp3) != success)
        {
            return failure;
        }
    }

    printf("INFO: Loading.......  Please wait!!\n");

    // function call to copy remaining data from source file to destination file
    if(copy_remaining_data_sample_file(e_mp3) != success)
    {
        return failure;
    }

    // function call to copy all data to original file
    if(copy_data_to_original_file(e_mp3) != success)
    {
        return failure;
    }

    return success;
}

Status help_operation() // Displaying help operation for the user
{
    printf("-----------------| HELP MENU |-------------------\n");
    printf("1. -v -> to view mp3 file contents\n");
    printf("2. -e -> to edit mp3 file contents\n");
    printf("\t 2.1. -t -> to edit song title\n");
    printf("\t 2.2. -a -> to edit artist name\n");
    printf("\t 2.3. -A -> to edit album name\n");
    printf("\t 2.4. -y -> to edit year\n");
    printf("\t 2.5. -m -> to edit content\n");
    printf("\t 2.6. -c -> to edit comment\n");
    printf("-------------------------------------------------\n");
    return success;
}

// function declaration to copy initial 10 bytes of data to sample file
Status e_skip_header_data(E_MP3 *e_mp3)
{
    char header[10];
    fread(header,10,1,e_mp3->e_fptr_mp3);
    fwrite(header,10,1,e_mp3->e_fptr_mp3_sample);
    return success;
}

// function declaration to copy  TIT2 to sample file
Status e_check_TIT2(E_MP3 *e_mp3)
{
    char _TIT2[4];
    // reading TIT2 from the source file 
    fread(_TIT2,4,1,e_mp3->e_fptr_mp3);

    // writing TIT2 to sample file
    fwrite(_TIT2,4,1,e_mp3->e_fptr_mp3_sample);
    return success;
}


// function declaration to copy song title size to sample file
uint edit_size_of_song_title(E_MP3 *e_mp3)
{
    int song_title_size = 0;

    // reading song title size from source file
    fread(&song_title_size,4,1,e_mp3->e_fptr_mp3);

    // writing song title size to sample file
    fwrite(&song_title_size,4,1,e_mp3->e_fptr_mp3_sample);

    e_swap(&song_title_size);

    return song_title_size;
}

// function declaration to copy song title to sample file
Status edit_song_title(E_MP3 *e_mp3)
{
    char song_title[e_mp3->size_of_song_title];

    // reading song title from source file
    fread(song_title,e_mp3->size_of_song_title-1,1,e_mp3->e_fptr_mp3);

    // writing song title to sample file 
    fwrite(song_title,e_mp3->size_of_song_title-1,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to copy TPE1 to sample file
Status e_check_TPE1(E_MP3 *e_mp3)
{
    char _TPE1[4];

    // reading TPE1 from source file
    fread(_TPE1,4,1,e_mp3->e_fptr_mp3);

    // writing TPE1 to sample file
    fwrite(_TPE1,4,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to copy artist name size to sample file
uint edit_artist_name_size(E_MP3 *e_mp3)
{
    int size_of_artist_name = 0;

    // reading artist name size from source file
    fread(&size_of_artist_name,4,1,e_mp3->e_fptr_mp3);

    // writing artsist name size to the sample file
    fwrite(&size_of_artist_name,4,1,e_mp3->e_fptr_mp3_sample);

    e_swap(&size_of_artist_name);

    return size_of_artist_name;
}

// function declaration to copy artist name to sample file
Status edit_artist_name(E_MP3 *e_mp3)
{
    char artist_name[e_mp3->size_of_artist_name];

    // reading artist name from source file
    fread(artist_name,e_mp3->size_of_artist_name-1,1,e_mp3->e_fptr_mp3);

    // writing artist name to sample file 
    fwrite(artist_name,e_mp3->size_of_artist_name-1,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to copy TALB to sample file
Status e_check_TALB(E_MP3 *e_mp3)
{
    char _TALB[4];
    
    // reading TALB from source file
    fread(_TALB,4,1,e_mp3->e_fptr_mp3);

    // writing TALB to sample file
    fwrite(_TALB,4,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to copy album name size to sample file
uint edit_album_name_size(E_MP3 *e_mp3)
{
    int size_of_album_name = 0;

    // reading album name size from source file
    fread(&size_of_album_name,4,1,e_mp3->e_fptr_mp3);

    // writing album name size to sample file
    fwrite(&size_of_album_name,4,1,e_mp3->e_fptr_mp3_sample);

    e_swap(&size_of_album_name);

    return size_of_album_name;
}

// function declaration to copy album name to sample file
Status edit_album_name(E_MP3 *e_mp3)
{
    char album_name[e_mp3->size_of_album_name];

    // reading album name from source file
    fread(album_name,e_mp3->size_of_album_name-1,1,e_mp3->e_fptr_mp3);

    // writing album name to sample file
    fwrite(album_name,e_mp3->size_of_album_name-1,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to copy TYER to sample file
Status e_check_TYER(E_MP3 *e_mp3)
{
    char _TYER[4];

    // reading TYER from source file 
    fread(_TYER,4,1,e_mp3->e_fptr_mp3);

    // writing TYER to sample file
    fwrite(_TYER,4,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to copy year size to sample file
uint edit_year_size(E_MP3 *e_mp3)
{
    int size_of_year = 0;

    // reading year size from the source file
    fread(&size_of_year,4,1,e_mp3->e_fptr_mp3);

    // writing year size to sample file
    fwrite(&size_of_year,4,1,e_mp3->e_fptr_mp3_sample);

    e_swap(&size_of_year);

    return size_of_year;
}

// function declaration to copy year to sample file
Status edit_year(E_MP3 *e_mp3)
{
    char year[e_mp3->size_of_year];

    // reading year from source file
    fread(year,e_mp3->size_of_year-1,1,e_mp3->e_fptr_mp3);

    // writing year to sample file
    fwrite(year,e_mp3->size_of_year-1,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to copy TCON to sample file
Status e_check_TCON(E_MP3 *e_mp3)
{
    char _TCON[4];

    // reading TCON from source file
    fread(_TCON,4,1,e_mp3->e_fptr_mp3);

    // writing TCON to the sample file
    fwrite(_TCON,4,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to copy content size to sample file
uint edit_content_size(E_MP3 *e_mp3)
{
    int size_of_content = 0;

    // reading content size from source file
    fread(&size_of_content,4,1,e_mp3->e_fptr_mp3);

    // writing content size to sample file
    fwrite(&size_of_content,4,1,e_mp3->e_fptr_mp3_sample);

    e_swap(&size_of_content);

    return size_of_content;
}

// function declaration to copy content to sample file
Status edit_content(E_MP3 *e_mp3)
{
    char content[e_mp3->size_of_content];

    // reading content from the source file
    fread(content,e_mp3->size_of_content-1,1,e_mp3->e_fptr_mp3);

    // writing content to the sample file
    fwrite(content,e_mp3->size_of_content-1,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to copy COMM to sample file
Status e_check_COMM(E_MP3 *e_mp3)
{
    char _COMM[4];

    // reading COMM from source file 
    fread(_COMM,4,1,e_mp3->e_fptr_mp3);

    // writing COMM to sample file
    fwrite(_COMM,4,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to copy comment size to sample file
uint edit_comment_size(E_MP3 *e_mp3)
{
    int size_of_comment = 0;

    // reading comment size from source file
    fread(&size_of_comment,4,1,e_mp3->e_fptr_mp3);

    // writing comment size to sample file
    fwrite(&size_of_comment,4,1,e_mp3->e_fptr_mp3_sample);

    e_swap(&size_of_comment);

    return size_of_comment;
}

// function declaration to copy comment to sample file
Status edit_commentE(E_MP3 *e_mp3)
{
    char comment[e_mp3->size_of_comment];

    // reading comment from source file
    fread(comment,e_mp3->size_of_comment-1,1,e_mp3->e_fptr_mp3);

    // writing comment to sample file
    fwrite(comment,e_mp3->size_of_comment-1,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to get the size of song title
uint getting_size_of_song_title(E_MP3 *e_mp3)
{
    int song_title_size = 0;

    // reading song title size from the source file
    fread(&song_title_size,4,1,e_mp3->e_fptr_mp3);

    e_swap(&song_title_size);

    return song_title_size;
}

// function declarartion to modify song title and copy to sample file
Status modify_size_of_song_title(char *argv[3],E_MP3 *e_mp3)
{
    uint size = strlen(argv[3])+1;

    e_swap(&size);

    fwrite(&size,4,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

Status modify_song_title(char *argv[3], E_MP3 *e_mp3)
{
    char song_title[strlen(argv[3])];

    strcpy(song_title,argv[3]);

    fwrite(song_title,strlen(argv[3]),1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declarartion to modify artist name size  and copy to sample file
Status modify_size_of_artist_name(char *argv[3],E_MP3 *e_mp3)
{
    uint size = strlen(argv[3])+1;

    e_swap(&size);

    fwrite(&size,4,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to get the size of artist name
uint getting_size_of_artist_name(E_MP3 *e_mp3)
{
    int artist_name_size = 0;

    // reading artist name size from the source file
    fread(&artist_name_size,4,1,e_mp3->e_fptr_mp3);

    e_swap(&artist_name_size);

    return artist_name_size;
}

// function declarartion to modify artist name and copy to sample file
Status modify_artist_name(char *argv[3], E_MP3 *e_mp3)
{
    char artist_name[strlen(argv[3])];

    strcpy(artist_name,argv[3]);

    fwrite(artist_name,strlen(argv[3]),1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declarartion to modify album name size and copy to sample file
Status modify_size_of_album_name(char *argv[3],E_MP3 *e_mp3)
{
    uint size = strlen(argv[3])+1;

    e_swap(&size);

    fwrite(&size,4,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to get the size of album name
uint getting_size_of_album_name(E_MP3 *e_mp3)
{
    int album_name_size = 0;

    // reading album name size from the source file
    fread(&album_name_size,4,1,e_mp3->e_fptr_mp3);

    e_swap(&album_name_size);

    return album_name_size;
}

// function declarartion to modify album name and copy to sample file
Status modify_album_name(char *argv[3], E_MP3 *e_mp3)
{
    char album_name[strlen(argv[3])];

    strcpy(album_name,argv[3]);

    fwrite(album_name,strlen(argv[3]),1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declarartion to modify size of year and copy to sample file
Status modify_size_of_year(char *argv[3],E_MP3 *e_mp3)
{
    uint size = strlen(argv[3])+1;

    e_swap(&size);

    fwrite(&size,4,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to get the size of year
uint getting_size_of_year(E_MP3 *e_mp3)
{
    int year_size = 0;

    // reading year size from the source file
    fread(&year_size,4,1,e_mp3->e_fptr_mp3);

    e_swap(&year_size);

    return year_size;
}

// function declarartion to modify year and copy to sample file
Status modify_year(char *argv[3], E_MP3 *e_mp3)
{
    char year[strlen(argv[3])];

    strcpy(year,argv[3]);

    fwrite(year,strlen(argv[3]),1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declarartion to modify size of content and copy to sample file
Status modify_size_of_content(char *argv[3],E_MP3 *e_mp3)
{
    uint size = strlen(argv[3])+1;

    e_swap(&size);

    fwrite(&size,4,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to get the size of content
uint getting_size_of_content(E_MP3 *e_mp3)
{
    int content_size = 0;

    // reading content size from the source file
    fread(&content_size,4,1,e_mp3->e_fptr_mp3);

    e_swap(&content_size);

    return content_size;
}

// function declarartion to modify content and copy to sample file
Status modify_content(char *argv[3], E_MP3 *e_mp3)
{
    char content[strlen(argv[3])];

    strcpy(content,argv[3]);

    fwrite(content,strlen(argv[3]),1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declarartion to modify size of comment and copy to sample file
Status modify_size_of_comment(char *argv[3],E_MP3 *e_mp3)
{
    uint size = strlen(argv[3])+1;

    e_swap(&size);

    fwrite(&size,4,1,e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declaration to get the size of comment
uint getting_size_of_comment(E_MP3 *e_mp3)
{
    int comment_size = 0;
    // reading comment size from the source file
    fread(&comment_size,4,1,e_mp3->e_fptr_mp3);

    e_swap(&comment_size);

    return comment_size;
}

// function declarartion to modify comment and copy to sample file
Status modify_comment(char *argv[3], E_MP3 *e_mp3)
{
    char comment[strlen(argv[3])];

    strcpy(comment,argv[3]);

    fwrite(comment,strlen(argv[3]),1,e_mp3->e_fptr_mp3_sample);
    
    return success;
}

// function declarartion to swap the hex number to lsb side
void e_swap(int *num)
{
    *num = ((*num & 0x000000ff) << 24) | ((*num & 0x0000ff00) << 8)  | ((*num & 0x00ff0000) >> 8)  | ((*num & 0xff000000) >> 24);
}

// function declarartion to copy the remaining data  to sample file
Status copy_remaining_data_sample_file(E_MP3 *e_mp3)
{
    char buffer[1];
    char ch;

    while((ch = fread(buffer,sizeof(char),1,e_mp3->e_fptr_mp3)) >0)
    {
        //writing reamining data to destination image 
        fwrite(buffer,sizeof(char),1,e_mp3->e_fptr_mp3_sample);

    }

    fclose(e_mp3->e_fptr_mp3);
    fclose(e_mp3->e_fptr_mp3_sample);

    return success;
}

// function declarartion to copy all the data back to the original source file
Status copy_data_to_original_file(E_MP3 *e_mp3)
{
    e_mp3->e_fptr_mp3 = fopen(e_mp3->e_mp3_file_name,"r+w");

    if(e_mp3->e_fptr_mp3 == NULL)
    {
        printf("Error\n");
    }

    e_mp3->e_fptr_mp3_sample = fopen("sample.mp3", "r");

    if(e_mp3->e_fptr_mp3_sample == NULL)
    {
        printf("Error 1 \n");
    }
    
    char buffer[1];
    char ch;

    fseek(e_mp3->e_fptr_mp3,0,SEEK_SET);

    fseek(e_mp3->e_fptr_mp3_sample,0,SEEK_SET);

    while((ch = fread(buffer,sizeof(char),1,e_mp3->e_fptr_mp3_sample)) >0)
    {
        //writing reamining data to destination image 
        fwrite(buffer,sizeof(char),1,e_mp3->e_fptr_mp3);

    }

    fclose(e_mp3->e_fptr_mp3);
    fclose(e_mp3->e_fptr_mp3_sample);

    return success;
}

