#ifndef VIEW_H
#define VIEW_H

#include"return.h"
#include"edit.h"

typedef struct _mp3file_view
{
    char *v_mp3_file_name; // store the mp3 file name 
    FILE *v_fptr_mp3; // file pointer to mp3 file 
    uint size_of_song_title; // size of song title
    uint size_of_artist_name; // size of artist name
    uint size_of_album_name; // size of album name
    uint size_of_year; // size of year
    uint size_of_content; // size of content
    uint size_of_comment; // size of comment
}V_MP3;

// function to open file
Status view_open_file(char *argv[2], V_MP3 *v_mp3);

// function to view file datails
Status view_file_details(V_MP3 *v_mp3);

// function to skip initial 10 bytes of header data
Status skip_header_data(V_MP3 *v_mp3);

// checking TIT2 tag
Status v_check_TIT2(V_MP3 *v_mp3);

// checking size of artist name
uint view_size_of_song_title(V_MP3 *v_mp3);

// function to view song title
Status view_song_title(V_MP3 *v_mp3);

// checking TPE1
Status v_check_TPE1(V_MP3 *v_mp3);

// function to view size of artist name
uint view_artist_name_size(V_MP3 *v_mp3);

// function to view artist name
Status view_artist_name(V_MP3 *v_mp3);

// checking TALB
Status v_check_TALB(V_MP3 *v_mp3);

// function to view album name size
uint view_album_name_size(V_MP3 *v_mp3);

// function to view album name
Status view_album_name(V_MP3 *v_mp3);

// checking TYER
Status v_check_TYER(V_MP3 *v_mp3);

// function to view year size 
uint view_year_size(V_MP3 *v_mp3);

// function to view year
Status view_year(V_MP3 *v_mp3);

// cheacking TCON
Status v_check_TCON(V_MP3 *v_mp3);

// function to view content size
uint view_content_size(V_MP3 *v_mp3);

// function to view content
Status view_content(V_MP3 *v_mp3);

// checking COMM
Status v_check_COMM(V_MP3 *v_mp3);

// function to view comment size
uint view_comment_size(V_MP3 *v_mp3);

// function to view comment
Status view_comment(V_MP3 *v_mp3);

// function to swap number
void swap(int *num);

#endif
