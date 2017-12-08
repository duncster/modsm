/*
Copyright © 2017 Duncan Hughes <duncster@gmail.com>

This work is free. You can redistribute it and/or modify it under the
terms of the Do What The Fuck You Want To Public License, Version 2,
as published by Sam Hocevar:

        DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
                    Version 2, December 2004 

 Copyright (C) 2004 Sam Hocevar <sam@hocevar.net> 

 Everyone is permitted to copy and distribute verbatim or modified 
 copies of this license document, and changing it is allowed as long 
 as the name is changed. 

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 

  0. You just DO WHAT THE FUCK YOU WANT TO.
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>


void usage(char *name)
{
	fprintf(stderr, "Usage: %s <key(s)> -u <user> -g <group> -m <mode>\n", name);
}

int main(int argc, char **argv)
{
	int c, i;
	char *key = NULL;
	char *uid = NULL;
	char *gid = NULL;
	char *mode = NULL;

	if(argc < 2)
	{
		usage(argv[0]);
		return EXIT_SUCCESS;
	}

	while((c = getopt (argc, argv, "hu:g:m:")) != -1)
	{
		switch(c)
		{
			case 'u':
				uid = malloc(strlen(optarg));
				strcpy(uid, optarg);
				break;
			
			case 'g':
				gid = malloc(strlen(optarg));
				strcpy(gid, optarg);
				break;
			case 'm':
				mode = malloc(strlen(optarg));
				strcpy(mode, optarg);
				break;
			case 'h':
				usage(argv[0]);
				return EXIT_SUCCESS;
				break;
			default:
				break;				
		}
	}

	printf("uid:  %s\n", uid);
	printf("gid:  %s\n", gid);
	printf("mode: %s\n", mode);

	for(i=optind; i<argc; i++)
		printf("key: %s\n", argv[i]);	

	if(uid)
		free(uid);

	if(gid)
		free(gid);

	if(mode)
		free(mode);

	return EXIT_SUCCESS;
}
