//  CSCIx239 library
//  Tayvian Wallace
#include "CSCIx229.h"

//
//  Check for OpenGL errors and print to stderr
//
void ErrCheck(const char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}
