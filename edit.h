#ifndef EDIT_H
#define EDIT_H

#include"return.h"

typedef struct _mp3file_edit
{
    char *e_mp3_file_name; // store the mp3 file name 
    FILE *e_fptr_mp3; // file pointer to mp3 file 
    char *e_mp3_sample_file_name; //file for duplicate details
    FILE *e_fptr_mp3_sample; // file pointer for duplicate file
    uint size_of_song_title; // size of song title
    uint size_of_artist_name; // size of artist name
    uint size_of_album_name; // size of album name
    uint size_of_year; // size of year
    uint size_of_content; // size of content
    uint size_of_comment; // size of comment
}E_MP3;

// check operation type
OperationType check_operation_type(char *argv[1]);

// function to open mp3 file 
Status edit_open_file(char *argv[4], E_MP3 *e_mp3);

// function to view file details
Status edit_file_details(char *argv[2], E_MP3 *e_mp3);

// function to copy initial 10 bytes of header data
Status e_skip_header_data(E_MP3 *e_mp3);

// checking/copy TIT2 tag
Status e_check_TIT2(E_MP3 *e_mp3);

// function to copy song title size 
uint edit_size_of_song_title(E_MP3 *e_mp3);

// function to copy song title
Status edit_song_title(E_MP3 *e_mp3);

// checking/copy TPE1
Status e_check_TPE1(E_MP3 *e_mp3);

// function to copy size of artist name
uint edit_artist_name_size(E_MP3 *e_mp3);

// function to copy artist name
Status edit_artist_name(E_MP3 *e_mp3);

// checking/copy TALB
Status e_check_TALB(E_MP3 *e_mp3);

// function to copy album name size
uint edit_album_name_size(E_MP3 *e_mp3);

// function to copy album name
Status edit_album_name(E_MP3 *e_mp3);

// checking/copy TYER
Status e_check_TYER(E_MP3 *e_mp3);

// function to copy year size 
uint edit_year_size(E_MP3 *e_mp3);

// function to copy year
Status edit_year(E_MP3 *e_mp3);

// cheacking/copy TCON
Status e_check_TCON(E_MP3 *e_mp3);

// function to copy content size
uint edit_content_size(E_MP3 *e_mp3);

// function to copy content
Status edit_content(E_MP3 *e_mp3);

// checking/copy COMM
Status e_check_COMM(E_MP3 *e_mp3);

// function to copy comment size
uint edit_comment_size(E_MP3 *e_mp3);

// function to copy comment
Status edit_commentE(E_MP3 *e_mp3);

// function to copy remaining data
Status copy_remaining_data_sample_file(E_MP3 *e_mp3);

// function to help call
Status help_operation();

// function to swap the number
void e_swap(int *num);

// funcion to modify size of song title
Status modify_size_of_song_title(char *argv[3],E_MP3 *e_mp3);

// function to modify song title
Status modify_song_title(char *argv[3], E_MP3 *e_mp3);

// function call to get the size of song title
uint getting_size_of_song_title(E_MP3 *e_mp3);

// function call to modify size of artist name
Status modify_size_of_artist_name(char *argv[3],E_MP3 *e_mp3);

// function call to modify artist name 
Status modify_artist_name(char *argv[3], E_MP3 *e_mp3);

// function call to get the size of artist name
uint getting_size_of_artist_name(E_MP3 *e_mp3);

// function call to modify album name
Status modify_size_of_album_name(char *argv[3],E_MP3 *e_mp3);

// function call to get album name size
uint getting_size_of_album_name(E_MP3 *e_mp3);

// function call to modify album name
Status modify_album_name(char *argv[3], E_MP3 *e_mp3);

// function call to modify size of year
Status modify_size_of_year(char *argv[3],E_MP3 *e_mp3);

// function call to get the size of year
uint getting_size_of_year(E_MP3 *e_mp3);

// function call to modify year
Status modify_year(char *argv[3], E_MP3 *e_mp3);

// function call to modify size of content
Status modify_size_of_content(char *argv[3],E_MP3 *e_mp3);

// function call to get the size of content
uint getting_size_of_content(E_MP3 *e_mp3);

// function call to modify content
Status modify_content(char *argv[3], E_MP3 *e_mp3);

// function call to modify size of comment size
Status modify_size_of_comment(char *argv[3],E_MP3 *e_mp3);

// function call to get size of comment
uint getting_size_of_comment(E_MP3 *e_mp3);

// function call to modify comment
Status modify_comment(char *argv[3], E_MP3 *e_mp3);

// function call to copy data from sample file to original file
Status copy_data_to_original_file(E_MP3 *e_mp3);

#endif
