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
#include<string.h>
#include"return.h"
#include"edit.h"
#include"view.h"
int main(int argc, char *argv[])
{
    // taking variable for the defined structure (edit and view)
    E_MP3 e_mp3;
    V_MP3 v_mp3;

    if(argc == 1 && (strcmp(argv[0],"./a.out") == 0)) 
    {
        // Erro message for insufficient argument 
        printf("ERROR: ./a.out : INSUFFICIENT ARGUMENT\n");
        printf("INFO: USAGE\n");
        printf("INFO: To view please pass lik: ./a.out -v <mp3filename>\n");
        printf("INFO: To edit please pass like: ./a.out -e -t/-a/-A/-y/-m/-c changing_text <mp3filename>\n");
        printf("INFO: To get help please pass like: ./a.out --help\n");
    }
    else if(argc > 1 && argc < 6)
    {
        // function call for edit option
        if(check_operation_type(argv) == edit)
        {
            // Displaying user message as edit
            printf("INFO: User option is edit\n");

            // validating edit option argument as -t/-a/-A/-y/-m/-c
            if((edit_open_file(argv, &e_mp3) == success) && ((strcmp(argv[2],"-t") == 0) || (strcmp(argv[2],"-a") == 0) || (strcmp(argv[2],"-A") == 0) || (strcmp(argv[2],"-y") == 0) || (strcmp(argv[2],"-m") == 0) || (strcmp(argv[2],"-c") == 0)))
            {
                // opening given file 
                printf("INFO: Opened %s file successfully\n",e_mp3.e_mp3_file_name);
                if(edit_file_details(argv, &e_mp3) == success)
                {
                    // edited the user option successfully
                    printf("INFO: Edited file successfully\n");
                    return 0;
                }
            }
            else
            {
                // Error message for Invalid argument
                printf("Error: Invalid argument\n");
                printf("INFO: To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text <mp3filename>\n");
                return 0;
            }
        }
        else if(check_operation_type(argv) == view) // function call for view option 
        {
            // Displaying user option
            printf("INFO: User option is view\n");

            // opening required files for view operation
            if(view_open_file(argv, &v_mp3) == success)
            {
                printf("INFO: Opened %s file successfully\n",v_mp3.v_mp3_file_name);
                if(view_file_details(&v_mp3) == success)
                {
                    // view operation done successfully
                    printf("INFO: Viewed file successfully\n");
                    return 0;
                }
            }
            return 0;
        }
        else if(check_operation_type(argv) == help) // function call for help operation
        {
            printf("INFO: user option is help\n");
            // help operation perfoemed successfully
            if(help_operation() == success)
            return 0;
        }
        else if(check_operation_type(argv) == invalid) // function call to check invalid user argument
        {
            // Displaying erro message for anvalid arguments
            printf("ERROR: ./a.out : INVALID ARGUMENT\n");
            printf("INFO: USAGE\n");
            printf("INFO: To view please pass lik: ./a.out -v <mp3filename>\n");
            printf("INFO: To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text <mp3filename>\n");
            printf("INFO: To get help please pass like: ./a.out --help\n");
        }
    }  
    else
    {
        // Error message for Too many arguments
        printf("INFO: Too many arguments\n");
        printf("INFO: To view please pass lik: ./a.out -v <mp3filename>\n");
        printf("INFO: To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text <mp3filename>\n");
        printf("INFO: To get help please pass like: ./a.out --help\n");
    } 
    return 0;
}
