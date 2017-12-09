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
#include <pwd.h>
#include <grp.h>
#include <sys/shm.h>

int modsm(int id, uid_t uid, gid_t gid, int mode)
{
	struct shmid_ds shm;

#ifdef _DEBUG
	printf("\n");
	printf("id:   %d\n", id);
	printf("uid:  %d\n", uid);
	printf("gid:  %d\n", gid);
	printf("mode: %.3o\n", mode);
#endif

	if(shmctl(id, IPC_STAT, &shm) == -1)
	{
		fprintf(stderr, "shmctl stat error\n");
		return -1;
	}

	if(uid != -1)
	{
		shm.shm_perm.uid = uid;
	}

	if(gid != -1)
	{
		shm.shm_perm.gid = gid;
	}

	if(mode != -1)
	{
		shm.shm_perm.mode = mode;
	}

	if(shmctl(id, IPC_SET, &shm) == -1)
	{
		fprintf(stderr, "shmctl set error\n");
		return -1;
	}

	return 1;
}

void usage(char *name)
{
	fprintf(stderr, "Usage: %s <shmid(s)> -u <user> -g <group> -m <mode>\n", name);
}

int main(int argc, char **argv)
{
	int c, i;
	char *id = NULL;
	char *username = NULL;
	char *group = NULL;
	char *mode = NULL;
	struct passwd *pass;
	struct group *grp;

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
				username = malloc(strlen(optarg));
				strcpy(username, optarg);
				break;
			
			case 'g':
				group = malloc(strlen(optarg));
				strcpy(group, optarg);
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

	if(username)
		pass = getpwnam(username);

	if(group)
		grp = getgrnam(group);

#ifdef _DEBUG
	if(username)
		printf("user:  %s, uid: %d\n", username, pass->pw_uid);
	if(group)
		printf("group:  %s, gid: %d\n", group, grp->gr_gid);
	if(mode)
		printf("mode: %s, %.3o\n", mode, strtoul(mode, NULL, 8));
#endif

	for(i=optind; i<argc; i++)
	{
#ifdef _DEBUG
		printf("shmid: %s\n", argv[i]);	
#endif
		if(modsm((int)strtoul(argv[i], NULL, 10), 
			username ? pass->pw_uid : -1, 
			group ? grp->gr_gid : -1, 
			mode ? (int)strtoul(mode, NULL, 8) : -1) == -1)
		{
			fprintf(stderr, "setting id: %s, uid: %s, gid: %s, mode: %s failed\n",
				argv[i], username, group, mode);
				return EXIT_FAILURE;
		}
	}

	if(username)
		free(username);

	if(group)
		free(group);

	if(mode)
		free(mode);

	return EXIT_SUCCESS;
}
