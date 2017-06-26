/*
  Copyright (c) 2017
  Gustavo Rodriguez-Rivera
  All rights reserved. 

This work was developed by the author(s) at Purdue University
during 2004-2017.
 
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
//
// gethttp:
//   Example program that shows how to use openttp.
//   It gets the URL passed as argument
//
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "openhttp.h"
#include "SimpleHTMLParser.h"

void
printUsage()
{
  fprintf( stderr, "  Usage: gethttp [-h|-t|-a] url\n");
  fprintf( stderr, "  Example: gethttp https://www.cs.purdue.edu/\n");
}

////////////////// HTML Parser to print the content //////////////////

class HTMLParserPrintContent : public SimpleHTMLParser {
public:
	void onContentFound(char c);
};

void
HTMLParserPrintContent::onContentFound(char c) {
	printf("%c",c);
}

////////////////// HTML Parser to print the href in anchors //////////////////

class HTMLParserPrintHrefs : public SimpleHTMLParser {
public:
	void onAnchorFound(char * url);
};

void
HTMLParserPrintHrefs::onAnchorFound(char * url) {
	printf("%s\n",url);
}

int
main( int argc, char ** argv )
{
  const char * option;
  char * url;
  
  if ( argc == 1) {
	  printUsage();
	  exit(1);	  
  }
  else if (argc == 2) {
	  option = "";
	  url = argv[1];
  }
  else { 
	  // There is an option
	  option = argv[1];
	  url = argv[2];
  }
  
  // Process the arguments
  if ( !strcmp(option,"-h") ) {
	  printUsage();
	  exit(1);
  }
  
  if ( !strcmp(option,"") ) {
	  // show document
	  int n;
	  char * buffer = fetchHTML( url, &n);
	  if (buffer != NULL) {
		  fwrite(buffer, n, 1, stdout);
	  }
  } else if ( !strcmp(option,"-t") ) {
	  // Eliminate tags
	  int n;
	  char * buffer = fetchHTML( url, &n);
	  if (buffer==NULL) {
		  fprintf(stderr, "*** Cannot open URL\n");
		  exit(1);
	  }
	  HTMLParserPrintContent htmlContent;
	  htmlContent.parse(buffer, n);
  } else if ( !strcmp(option,"-a") ) {
	  // Eliminate tags
	  int n;
	  char * buffer = fetchHTML( url, &n);
	  if (buffer==NULL) {
		  fprintf(stderr, "*** Cannot open URL\n");
		  exit(1);
	  }
	  HTMLParserPrintHrefs htmlHrefs;
	  htmlHrefs.parse(buffer, n);
  }

  if ( *argv == NULL ) {
    // Print usage also if no URL after the arguments
    printUsage();
    exit(1);
  }
}

