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

#include "db.h"
#include "errno.h"
#include <glib-2.0/glib.h>
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

int db_exec(char *sql, char **err){
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int rc;
	const char *tail_sql;

	rc = sqlite3_open(db_file, &db);
	if(rc)
		return -ESQL;

	do{
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail_sql);
		if(rc != SQLITE_OK)
			return -ESQL;
		rc = sqlite3_step(stmt);
		if(rc != SQLITE_DONE)
			return -ESQL;
		rc = sqlite3_finalize(stmt);
		if(rc != SQLITE_OK)
			return -ESQL;
		sql = strdup(tail_sql);
	} while(!tail_sql);

	sqlite3_close(db);
	return 0;
}
