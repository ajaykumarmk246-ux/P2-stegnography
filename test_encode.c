#include <stdio.h>
#include "encode.h"
#include "types.h"

int main(int argc,char *argv[])
{
    EncodeInfo encInfo;
    //->call check_operation_type(argv[1][1])==e_encode
    /*
    ->call read_and_validate_encode_args(char *argv[], EncodeInfo *encIn)==e_succes
       =>call do_encoding((&EncodeInfo *encInfo)
    */

    return 0;
}
operation type check operation_type(char opt);
{
/*
*check opt is 'e'
return e_encode
*check opt is 'd'
return e_decode
*else
return e_unsupported
*/
if(opt=='e')
{
    return e_encode;
}
else if(opt=='d')
{
    return e_decode;
}
else
{
return e_unsupported;
}
}
