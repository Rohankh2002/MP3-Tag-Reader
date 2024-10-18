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
#include"return.h"
#include<string.h>
#include"view.h"


Status view_open_file(char *argv[2], V_MP3 *v_mp3)
{
    v_mp3->v_mp3_file_name = argv[2];

    v_mp3->v_fptr_mp3 = fopen(v_mp3->v_mp3_file_name,"r+w");

    if(v_mp3->v_fptr_mp3 == NULL)
    {
        printf("Error: unable to open file %s\n",v_mp3->v_mp3_file_name);
        return failure;
    }

    return success;
}

Status view_file_details(V_MP3 *v_mp3)
{
    if(skip_header_data(v_mp3) != success)
    {
        return failure;
    }

    if(v_check_TIT2(v_mp3) != success)
    {
        return failure;
    }

    v_mp3->size_of_song_title = view_size_of_song_title(v_mp3);

    if(view_song_title(v_mp3) != success)
    {
        return failure;
    }
    
    if(v_check_TPE1(v_mp3) != success)
    {
        return failure;
    }
    
    v_mp3->size_of_artist_name = view_artist_name_size(v_mp3);

    if(view_artist_name(v_mp3) != success)
    {
        return failure;
    }

    if(v_check_TALB(v_mp3) != success)
    {
        return failure;
    }

    v_mp3->size_of_album_name = (view_album_name_size(v_mp3));

    if(view_album_name(v_mp3) != success)
    {
        return failure;
    }

    if(v_check_TYER(v_mp3) != success)
    {
        return failure;
    }

    v_mp3->size_of_year = (view_year_size(v_mp3));

    if(view_year(v_mp3)  != success)
    {
        return failure;
    }

    if(v_check_TCON(v_mp3)  != success)
    {
        failure;
    }

    v_mp3->size_of_content = (view_content_size(v_mp3));

    if(view_content(v_mp3) != success)
    {
        return failure;
    }

    if(v_check_COMM(v_mp3) != success)
    {
        return failure;
    }

    v_mp3->size_of_comment = (view_comment_size(v_mp3));

    if(view_comment(v_mp3) != success)
    {
        return failure;
    }
    return success;
}

Status skip_header_data(V_MP3 *v_mp3)
{
    fseek(v_mp3->v_fptr_mp3,10,SEEK_SET);

    return success;
}

Status v_check_TIT2(V_MP3 *v_mp3)
{
    char _TIT2[4];

    fread(_TIT2,4,1,v_mp3->v_fptr_mp3);

    if(strcmp(_TIT2,"TIT2") != 0)
    {
        return failure;
    }

    return success;
}

uint view_size_of_song_title(V_MP3 *v_mp3)
{
    int song_title_size = 0;

    fread(&song_title_size,4,1,v_mp3->v_fptr_mp3);
    
    swap(&song_title_size);

    return song_title_size;
}

Status view_song_title(V_MP3 *v_mp3)
{
    char song_title[v_mp3->size_of_song_title];

    fseek(v_mp3->v_fptr_mp3,3,SEEK_CUR);

    fread(song_title,v_mp3->size_of_song_title-1,1,v_mp3->v_fptr_mp3);

    song_title[v_mp3->size_of_song_title-1] = '\0';

    printf("INFO:   SONG TITLE   :    %s\n",song_title);

    return success;
}

Status v_check_TPE1(V_MP3 *v_mp3)
{
    char _TPE1[4];

    fread(_TPE1,4,1,v_mp3->v_fptr_mp3);

    _TPE1[4] = '\0';

    if(strcmp(_TPE1,"TPE1") != 0)
    {
        return failure;
    }

    return success;
}

uint view_artist_name_size(V_MP3 *v_mp3)
{
    int artist_name_size = 0;

    fread(&artist_name_size,4,1,v_mp3->v_fptr_mp3);

    swap(&artist_name_size);

    return artist_name_size;
}

Status view_artist_name(V_MP3 *v_mp3)
{
    char artist_name[v_mp3->size_of_artist_name];

    fseek(v_mp3->v_fptr_mp3,3,SEEK_CUR);

    fread(artist_name,v_mp3->size_of_artist_name-1,1,v_mp3->v_fptr_mp3);

    artist_name[v_mp3->size_of_artist_name-1] = '\0';

    printf("INFO:   ARTIST NAME  :    %s\n",artist_name);

    return success;
}

Status v_check_TALB(V_MP3 *v_mp3)
{
    char _TALB[4];

    fread(_TALB,4,1,v_mp3->v_fptr_mp3);

    if(strcmp(_TALB,"TALB") != 0)
    {
        return failure;
    }

    return success;
}

uint view_album_name_size(V_MP3 *v_mp3)
{
    int album_name_size = 0;

    fread(&album_name_size,4,1,v_mp3->v_fptr_mp3);

    swap(&album_name_size);

    return album_name_size;
}

Status view_album_name(V_MP3 *v_mp3)
{
    char album_name[v_mp3->size_of_album_name];

    fseek(v_mp3->v_fptr_mp3,3,SEEK_CUR);

    fread(album_name,v_mp3->size_of_album_name-1,1,v_mp3->v_fptr_mp3);

    album_name[v_mp3->size_of_album_name-1] = '\0';

    printf("INFO:   ALBUM NAME   :    %s\n",album_name);

    return success;
}

Status v_check_TYER(V_MP3 *v_mp3)
{
    char _TYER[4];

    fread(_TYER,4,1,v_mp3->v_fptr_mp3);

    if(strcmp(_TYER,"TYER") != 0)
    {
        return failure;
    }
     
    return success;
}

uint view_year_size(V_MP3 *v_mp3)
{
    int year_size = 0;

    fread(&year_size,4,1,v_mp3->v_fptr_mp3);

    swap(&year_size);

    return year_size;
}

Status view_year(V_MP3 *v_mp3)
{
    char year[v_mp3->size_of_year];

    fseek(v_mp3->v_fptr_mp3,3,SEEK_CUR);

    fread(year,v_mp3->size_of_year-1,1,v_mp3->v_fptr_mp3);

    year[v_mp3->size_of_year-1] = '\0';

    printf("INFO:   YEAR         :    %s\n",year);

    return success;
}

Status v_check_TCON(V_MP3 *v_mp3)
{
    char _TCON[4];

    fread(_TCON,4,1,v_mp3->v_fptr_mp3);

    if(strcmp(_TCON,"TCON")  != 0)
    {
        return failure;
    }

    return success;
}

uint view_content_size(V_MP3 *v_mp3)
{
    int content_size = 0;

    fread(&content_size,4,1,v_mp3->v_fptr_mp3);

    swap(&content_size);

    return content_size;
}

Status view_content(V_MP3 *v_mp3)
{
    char content[v_mp3->size_of_content];

    fseek(v_mp3->v_fptr_mp3,3,SEEK_CUR);

    fread(content,v_mp3->size_of_content-1,1,v_mp3->v_fptr_mp3);

    content[v_mp3->size_of_content-1] = '\0';

    printf("INFO:   CONTENT      :    %s\n",content);

    return success;
}

Status v_check_COMM(V_MP3 *v_mp3)
{
    char _COMM[4];

    fread(_COMM,4,1,v_mp3->v_fptr_mp3);

    if(strcmp(_COMM,"COMM") != 0)
    {
        return failure;
    }

    return success;
}

uint view_comment_size(V_MP3 *v_mp3)
{
    int comment_size = 0;

    fread(&comment_size,4,1,v_mp3->v_fptr_mp3);

    swap(&comment_size);

    return comment_size;
}

Status view_comment(V_MP3 *v_mp3)
{
    char comment[v_mp3->size_of_comment];

    fseek(v_mp3->v_fptr_mp3,3,SEEK_CUR);

    fread(comment,v_mp3->size_of_comment-1,1,v_mp3->v_fptr_mp3);

    comment[v_mp3->size_of_comment-1] = '\0';

    printf("INFO:   COMMENT      :    %s\n",comment);

    return success;
}

void swap(int *num)
{
    *num = ((*num & 0x000000ff) << 24) | ((*num & 0x0000ff00) << 8)  | ((*num & 0x00ff0000) >> 8)  | ((*num & 0xff000000) >> 24);
}
