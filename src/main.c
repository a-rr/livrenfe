/* Copyright (c) 2016 Pablo G. Gallardo <pggllrd@gmail.com>
 *
 * This file is part of LivreNFE.
 *
 * LivreNFE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LivreNFE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LivreNFE.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "livrenfe.h"
#include "db_interface.h"
#include "errno.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int init(char *path);
int init_db(char *path);
char *get_livrenfepath();

int main(int argc, char **args) {
	fprintf(stdout, "LivreNFE version %s\n", VERSION_NAME);
	char *path = get_livrenfepath();
	DIR *dir = opendir(path);
	if(dir){
		char *p = strdup(path);
		strcat(p, "/livrenfe.db");
		if(access(p, F_OK) == -1){
			if(init_db(path)){
				fprintf(stderr, "livrenfe: couldn't create database\n");
				return -EFOL;
			}
		} else {
			set_db(p);
		}
	} else {
		if(init(path))
			return -EFOL;
	}
	return 0;
}

int init(char *path){
	if(mkdir(path, S_IRWXU)){
		fprintf(stderr, "livrenfe: couldn't create application folder\n");
		return -EFOL;
	}
	if(init_db(path))
		return -EFOP;
	return 0;
}

int init_db(char *path){
	strcat(path, "/livrenfe.db");
	fprintf(stdout, "livrenfe: creating database...\n");
	FILE *fp = fopen(path, "wb");
	if(fp == NULL){
		fprintf(stderr, "livrenfe: couldn't create database\n");
		return -EFOP;
	}
	if(fclose(fp)){
		fprintf(stderr, "livrenfe: couldn't create database\n");
		return -EFOP;
	}
	set_db(path);
	if(create_db())
		return -EFOP;
	return 0;
}

char *get_livrenfepath(){
	char *home_path = getenv("HOME");
	char *livrenfe_path = home_path;
	strcat(livrenfe_path, LIVRENFE_FOLDER_NAME);
	return livrenfe_path;
}
