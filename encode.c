#include <stdio.h>
#include "encode.h"
#include "types.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encIn)
{
    /*
    -> check argv[2] have ".bmp" as last 4 char
      *If not, print error msg, return e_failure
    encInfo->src_image_fname=argv[2]
    enInfo->secret_fname=argv[3]
    -> check argv[4] == NULL

       enInfo-> stego_image_fname = "output.bmp"
     -> else
        *validate argv[4] is ".bmp"
           ->if not print error msg,return e_failure
           *encInfo -> stego_Image_fname=argv[4]

    -> call open_files(encInfo)==e_failure
    return e_failure
    */

}
Status open_files(EncodeInfo *encInfo)
{
    /*
    ->open encInfo-> src_Image_fname file in read mode
      *If ret value is NULL, print error msg,return e_failure
      fptr_src_image = fopen()

      ->open encInfo-> secret_file file in read mode
      *If ret value is NULL, print error msg,return e_failure
      fptr_secrete = fopen()

      ->open encInfo-> stego_image_fname file in write mode
      fptr_stego_image = fopen()

    ->return e_succes

    */

}
Status do_encoding(EncodeInfo *encInfo)
{
    /*
    //call check_capacity(encInfo)==e_failure
       print error msg, return e_failure

       //call copy_bmp_header(fptr_src_image,*fptr_dest_image)==
       print error msg,return e_failure

       //  call encode_magic_string (MAGIC_STRING , encodeInfo *encInfo)==e_failure
       print error msg,return e_failure

       // call encode_secret_file

    */
}
Status check_capacity(EncodeInfo *encInfo)
{
    /*
    -> call get_image_size_for_bmp(encode ->fptr_src_image)
      image_capacity =get_image_size()
      -> call get_file-size(encode -> fptr_secrete)
       size_secrete_file = get_file_size()

      -> check (14 = size_secrete_file)=0)> image_capacity
       return e_failure

       -> return e_successes
    */
}
uint get_file_size(FILE *fptr)
{
   /*
   -> move the offset in last pos
   -> return ftell()
   */
}
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    /*
    -> move the file pointer to the size_SET
    -> declare the buff[54]
    -> Read 54 bytes from src file
    -> write 54 bytes to dest file

    -> return e_successes
    */

}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
  
    /*
    declare a buffer of 8 bytes
    -> loop for (length of magic_string) 2 times
    read 8 byte from the src file into buffer
   encode_bute_to_lsb(magic_string[1],buffer),
   write the encoded buff to output_file

   -> return e_successes
  */

}
Status encode_byte_to_lsb(char data, char *image_buffer)
{
    /*
    for(int i=7;i>=0;i++)
    {
    -> get the ith bit set or not
      => if set, set the lsb of image_buffer[]
      => if clear, clear the lsb of image_buffer[]
    }
    */

}
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    /*
    -> char *dot = strchr(secrete_file_name, '.')
    -> strcpy(extn_secret_file, dot)
    -> Declare a buff[32]

    -> Read 32 bytes from src file into buff

    -> call encode_size_to_ lsb(strlen(extn_secret_file),buff)

    */
}
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    /*
    for(int i=32;i>0;i++)
    {
    -> get the ith bit set or not
      => if set, set the lsb of image_buffer[]
      => if clear, clear the lsb of image_buffer[]

    */
}

