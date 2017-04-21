/* Copyright (c) 2016, 2017 Pablo G. Gallardo <pggllrd@gmail.com>
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

#ifndef	DBI_H
#define	DBI_H

#define DB_VERSION	1

#include "livrenfe.h"
#include <gtk/gtk.h>


typedef struct {
	char *recepcaoevento_prod;
	char *recepcaoevento_cert;
	char *nfeconsultacadastro_prod;
	char *nfeconsultacadastro_cert;
	char *nfeinutilizacao_prod;
	char *nfeinutilizacao_cert;
	char *nfeconsultaprotocolo_prod;
	char *nfeconsultaprotocolo_cert;
	char *nfestatusservico_prod;
	char *nfestatusservico_cert;
	char *nferetautorizacao_prod;
	char *nferetautorizacao_cert;
	char *nfeautorizacao_prod;
	char *nfeautorizacao_cert;
} URLS;

typedef struct {
	URLS *urls;
	char *public_key;
	char *private_key;
	char *card_reader_lib;
	int ambiente;
	int tipo_cert;
} PREFS;

/**
 * Creates an empty app DB
 */
extern int create_db();

/**
 * Materialize NFE
 */
extern int register_nfe(NFE *);

/**
 * Materialize EVENTO 
 */
extern int register_evento(EVENTO *);

/**
 * Set db path
 */
extern int set_db(char *);

/**
 * Get opened NFEs for GTKTreeView
 */
extern GtkListStore *get_list_nfe();

/**
 * Get UF list
 */
extern GtkListStore *db_list_uf();

/**
 * Get Municipios from UF
 */
extern GtkListStore *db_list_municipios(char *);

/**
 * Get NFE from DB
 */
extern NFE *get_nfe(int);

/**
 * Get ISSUER from DB
 */
extern EMITENTE *get_emitente(int id);

/**
 * Get WebService URL
 */
extern char *get_ws_url(char *service, int ambiente, char **url_header,
	char **url_body);

/**
 * Set emitente info
 */
extern int set_emitente(EMITENTE *e);

/**
 * Get next lote ID
 */
extern int get_lote_id();

/**
 * Save lote on DB
 */
extern int db_save_lote(LOTE *lote);

/**
 * Save lote evento on DB
 */
extern int db_save_lote_evento(LOTE_EVENTO *lote);

/**
 * Get Webservice ID
 */
extern int get_url_id(char *service);

/**
 * Get preferences data
 */
extern PREFS *get_prefs();

#endif
