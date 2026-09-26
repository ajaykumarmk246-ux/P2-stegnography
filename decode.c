#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "types.h"
#include"common.h"

//-------------------------------------------------------------------------------//

Status read_and_validate_decode_args(char *argv[], EncodeInfo *encInfo)
{
    // CLA validation
    for(int i=2;i<3;i++)
    {
        if(argv[i]==NULL)
        {
            printf("\nInvalid input\n");
            printf("\n-------- SAMPLE INPUTS --------\n");
            printf("\n./a.out -e source_file.bmp secret_file.txt [output_file(.bmp .py .txt)]\n");
            printf("./a.out -d source_file.bmp [output_file(.bmp .py .txt)]\n");
            printf("\n");
            return e_failure;
        }
    }

    //check ".bmp" exatention at last
    char *dot=strrchr(argv[2],'.');
    if(dot==NULL || strcmp(dot,".bmp")!=0)
    {
        printf("\nSource image file extention should me \".bmp\"..\n");
            return e_failure;
            //if not ".bp extaction is not there" return e_failure
    }
    encInfo->src_image_fname=argv[2];  

    //check out file is given or not
    if(argv[3]!=NULL)
    {
         char name_buffer[20];
        sscanf(argv[3],"%[^.]",name_buffer);
        strcat(name_buffer,".txt");
        encInfo->stego_image_fname=name_buffer;
}
    else
    {
        encInfo->stego_image_fname="decoded_info.txt";
    }

    printf("\nAll validation are passed successfully...\n");

    //open three file(source,output)
    if(open_decode_files(encInfo)==e_failure)
    {
        printf("\nFile doesn't open..\n");
        return e_failure;
    }

    return e_success;
}

//-------------------------------------------------------------------------------//

Status open_decode_files(EncodeInfo *encInfo)
{
    // source file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname,"r");
    if(encInfo->fptr_src_image==NULL)
    {
        printf("Error : Source file is not Opened..\n");
        return e_failure;
    }
    
    //output file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname,"w");
    if(encInfo->fptr_stego_image==NULL)
    {
        printf("Error : output file is not Opended..\n");
        return e_failure;
    }

    printf("\nFiles opened successfully...\n");
    return e_success;
}

//-------------------------------------------------------------------------------//

Status do_decoding(EncodeInfo *encInfo)
{
    fseek(encInfo->fptr_src_image,54,SEEK_SET);
    printf("\n%lu\n",ftell(encInfo->fptr_src_image));

    // decode magic string
    if(decode_magic_string(MAGIC_STRING , encInfo)==e_failure)
    {
        printf("\nError : unable to decode magic string..\n");
        return e_failure;
    }

    // decode file extention size
    if(decode_secret_file_extn_size(encInfo)==e_failure)
    {
        printf("\nError : unable to decode secret file extention size..\n");
        return e_failure;
    }

    // decode file extention 
    if(decode_secret_file_extn(encInfo)==e_failure)
    {
        printf("\nError : unable to decode secret file extention..\n");
        return e_failure;
    }

    // decode file size
    if(decode_secret_file_size(encInfo)==e_failure)
    {
        printf("\nError : unable to decode secret file size..\n");
        return e_failure;
    }

    // decode file data
    if(decode_secret_file_data(encInfo)==e_failure)
    {
        printf("\nError : unable to decode secret file data..\n");
        return e_failure;
    }
    return e_success;
}

//-------------------------------------------------------------------------------//

Status decode_byte_to_lsb(char *image_buffer, unsigned char *data)
{
    int j=7;
    *data=0;
    for(int i=0;i<8;i++)
    {
        // get the lsb bit set or not
        if(image_buffer[i] & 1) // set the ith bit of data
        {
            *data = (*data) | (1<<j);
        }
        j--;
    }

    return e_success;
}

//-------------------------------------------------------------------------------//

Status decode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    char de_magic_buffer[2];
    char image_buffer[8];

    for(int i=0;i<2;i++)
    {
        char data=0;
        
        fread(image_buffer,8,1,encInfo->fptr_src_image);

        decode_byte_to_lsb(image_buffer,&data);

        printf("\n magic str = %c\n",data);
        de_magic_buffer[i]=data;
    }
    de_magic_buffer[2]='\0';

    if(strcmp(de_magic_buffer,magic_string)!=0)
    {
        printf("\nError : Magic string doesnt match\n");
        return e_failure;
    }
    return e_success;
}

//-------------------------------------------------------------------------------//

Status decode_size_to_lsb(char *image_buffer,int *data)
{
    int j=31;
    for(int i=0;i<32;i++)
    {
        // get the lsb bit set or not
        if(image_buffer[i] & 1) // set the ith bit of data
        {
            *data = (*data) | (1<<j) ;
        }
        j--;
    }

    return e_success;
}

//-------------------------------------------------------------------------------//

Status decode_secret_file_extn_size( EncodeInfo *encInfo)
{

    char buffer[32];
    int extn_size=0;
    //read 32 bytes from src_file into buffer
    fread(buffer,32,1,encInfo->fptr_src_image);
    
    //decode_size_to_lsb(strlen(extn_scr_file),buffer)
    if(decode_size_to_lsb(buffer,&extn_size)==e_failure)
    {
        printf("\nError : secret file extention decoding failed..\n");
        return e_failure;
    }
    printf("\n%d\n",extn_size);
    if(extn_size!=4)
    {
        printf("Error : secret file extention doesnot match");
        return e_failure;
    }
    
    printf("\nsecret file extention size decoded successfully...\n");
    return e_success;
}

//-------------------------------------------------------------------------------//

Status decode_secret_file_extn(EncodeInfo *encInfo)
{
  char buffer[8];
  char extn[4];
    for(int i=0;i<4;i++)
    {
        char data=0;
        //read 8 bytes from src_image
        fread(buffer,8,1,encInfo->fptr_src_image);

        //decode_byte_to_lsb
        decode_byte_to_lsb(buffer,&data);

        extn[i]=data;
    }  
    extn[4]='\0';
    printf("\n%s\n",extn);

    if(strcmp(extn,".txt")!=0)
    {
        printf("\nError : secret file extention doesnt match..\n");
        return e_failure;
    }
    printf("\nsecret file extention decoded successfully...\n");
    return e_success;
}

//-------------------------------------------------------------------------------//

Status decode_secret_file_size(EncodeInfo *encInfo)
{
    char buffer[32];

    int data=0;
    // read 32 bytes from src image to buffer
    fread(buffer,32,1,encInfo->fptr_src_image);

    // decode size to lsb
    decode_size_to_lsb(buffer,&data);

   encInfo->size_secret_file=data;

    printf("\n%ld\n",encInfo->size_secret_file);

    printf("\nsecret file size decoded successfully...\n");
    return e_success;
}

//-------------------------------------------------------------------------------//

Status decode_secret_file_data(EncodeInfo *encInfo)
{
    char buffer[8];
    char output[50];
    int i=0;
    char data;

    for(i=0;i<encInfo->size_secret_file;i++)
    {
        //read 8 bytes from src_image
       fread(buffer,8,1,encInfo->fptr_src_image);

        //decode_byte_to_lsb
        decode_byte_to_lsb(buffer,&data);

        output[i]=data;
        
       fwrite(&data,1,1,encInfo->fptr_stego_image);
    }
    output[i+1]='\0';
    printf("\n%s\n",output);

    printf("\nSecret file data decoded successfully...\n");
    return e_success;
}

//-------------------------------------------------------------------------------//