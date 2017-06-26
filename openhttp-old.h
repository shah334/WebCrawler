/*
  Copyright (c) 2004
  Gustavo Rodriguez-Rivera
  All rights reserved. 

This work was developed by the author(s) at Purdue University
during 2004.
 
Redistribution and use in source and binary forms are permitted provided that
this entire copyright notice is duplicated in all such copies.  No charge,
other than an "at-cost" distribution fee, may be charged for copies,
derivations, or distributions of this material without the express written
consent of the copyright holders. Neither the name of the University, nor the
name of the author may be used to endorse or promote products derived from
this material without specific prior written permission.

THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR ANY PARTICULAR PURPOSE.
*/

//
// Definitions to use openhttp
//

#include <stdio.h>

#ifndef OPENHTTP_H
#define OPENHTTP_H

enum {
  MaxURLLength = 512,
  MaxLineLength = 1024
};

//
// Connect to an HTTP server and fetch the HTML document and places it into memory.
// The memory is allocated dynamically. The content has to be of type text/html.
// or it returns NULL. The memory should be freed calling free() when no longer in use.
//
// Parameters:
//   url: points to the URL to fetch.
//   n:   Is a pointer that oints to an int where the size of the document is placed.
//
// Result:
//   It returns a pointer in memory where the document was placed.
//   Also, *n will contain the size of the document.
//   If there is an error it returns NULL
char * fetchHTML( const char * url, int * n);

#endif
