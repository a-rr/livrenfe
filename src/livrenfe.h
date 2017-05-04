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
 * */

#ifndef	LIVRENFE_H
#define	LIVRENFE_H

#include <time.h>
#include <gtk/gtk.h>

#define	VERSION_NAME		"0.1.0"
#define	VERSION_COUNTER		1
#define VERSION_TITLE		"Tartagal"
#define LIVRENFE_COPYRIGHT	"© 2016, 2017 Pablo G. Gallardo"
#define	LIVRENFE_FOLDER_NAME	"/.livrenfe"
#define	LIVRENFE_DB		"/livrenfe.db"
#define LIVRENFE_COMMENT	"Emissor Código Aberto de Notas Fiscais Eletrónicas"
#define LIVRENFE_WEBSITE	"https://github.com/pablogallardo/livrenfe"
#define LIVRENFE_TITLE		"LivreNFE"

#define CANCELAMENTO_TYPE	110111
#define	CARTA_CORRECAO_TYPE	110110

#define	AMBIENTE_PRODUCAO	1
#define	AMBIENTE_HOMOLOGACAO	2

#define	DEFAULT_AMBIENTE	AMBIENTE_HOMOLOGACAO
#define	DEFAULT_CERT_TYPE	2

typedef int evento_t;

/*
 * City information
 */
typedef struct {
	const char *uf;
	const char *municipio;
	unsigned int codigo;
	unsigned int cod_uf;
} MUNICIPIO;

/*
 * NFE identification
 */
typedef struct {
	MUNICIPIO *municipio;
	unsigned int id_nfe;
	const char *nat_op;
	enum t_ind_pag {A_VISTA, A_PRAZO, OUTRO} ind_pag;
	enum t_mod {MOD_NFE=55, MOD_NFCE=65} mod;
	int serie;
	unsigned int num_nf;
	time_t dh_emis;
	time_t *dh_saida;
	enum t_tipo {TIPO_ENTRADA=0,TIPO_SAIDA=1} tipo;
	enum t_local_destino {DEST_INTERNA=1,DEST_INTERESTADUAL=2,DEST_EXTERIOR=3} local_destino;
	enum t_tipo_impressao {IMP_NONE=0,IMP_RET=1,IMP_PAI=2,IMP_SIMP=3,IMP_NFCE=4,IMP_NFCE_MSG=5}
		tipo_impressao;
	enum t_tipo_emissao {TE_NORMAL=1, TE_FS=2, TE_SCAN=3, TE_DPEC=4, TE_FSDA=5, TE_SVCAN=6, 
		TE_SVCRS=7, TE_OFFLINE_NFCE=9} tipo_emissao;
	enum t_tipo_ambiente {PRODUCAO=1, HOMOLOGACAO=2} tipo_ambiente;
	enum t_finalidade {FIN_NORMAL=1, FIN_COMPLEMENTAR=2, FIN_AJUSTE=3, FIN_RETORNO=4}
	finalidade;
	enum t_consumidor_final {NAO=0, SIM=1} consumidor_final;
	enum t_presencial {PRE_NA=0, PRE_PRESENCIAL=1, PRE_INTERNET=2, PRE_TELEATENDIMENTO=3,
		PRE_NFCE_ED=4, PRE_OUTRO=5} presencial;
	const char *versao;
	char div;
	char *chave;
	int cod_nfe;
} IDNFE;

/*
 * Country information
 */
typedef struct {
	unsigned int codigo;
	const char *nome;
} PAIS;

/*
 * Address information
 */
typedef struct {
	const char *rua;
	unsigned int num;
	const char *complemento;
	const char *bairro;
	MUNICIPIO *municipio;
	unsigned int cep;
	PAIS *pais;
} ENDERECO;

/*
 * Issuer information
 */
typedef struct {
	int id;
	const char *nome;
	const char *inscricao_estadual;
	ENDERECO *endereco;
	enum t_crt {CRT_SNAC=1, CRT_SNAC_EXC=2, CRT_NORMAL=3} crt;
	const char *cnpj;
} EMITENTE;

/*
 * Recipient information
 */
typedef struct {
	int id;
	const char *nome;
	ENDERECO *endereco;
	enum t_tipo_ie {CONT_AV=1, CONT_IS=2, NAO_CONT=9} tipo_ie;
	const char *cnpj;
	const char *tipo_doc;
	const char *inscricao_estadual;
} DESTINATARIO;

/*
 * Product information
 */
typedef struct {
	int id;
	const char *codigo;
	const char *descricao;
	unsigned int ncm;
	unsigned int cfop;
	const char *unidade_comercial;
	float valor;
} PRODUTO;

/*
 * ICMS tax
 */
typedef struct {
	enum t_origem {NACIONAL=0, E_ID=1, E_AI=2} origem;
	unsigned int tipo;
	float aliquota;
	float valor;
} ICMS;

/*
 * PIS tax
 */
typedef struct {
	float aliquota;
	unsigned int quantidade;
	const char *nt;
} PIS;

/* 
 * COFINS tax
 */
typedef struct {
	float aliquota;
	unsigned int quantidade;
	const char *nt;
} COFINS;

/* 
 * IPI tax
 */
typedef struct {
	int sit_trib;
	const char *classe;
	const char *codigo;
} IPI;

/*
 * Tax information
 */
typedef struct {
	ICMS *icms;
	PIS *pis;
	COFINS *cofins;
	IPI *ipi;
} IMPOSTO;

typedef struct ITEM ITEM;

/*
 * Items
 */
struct ITEM {
	PRODUTO *produto;
	IMPOSTO *imposto;
	unsigned int ordem;
	unsigned int quantidade;
	float valor;
	ITEM *pointer; //next item
};

/*
 * Transportation information
 */
typedef struct {
	enum t_modfrete {FRETE_EMITENTE=0, FRETE_DESTINATARIO=1, 
		FRETE_TERCEIROS=2, FRETE_SEM=9}
		modfrete;
} TRANSP;

/* 
 * SEFAZ record information
 */
typedef struct {
	const char *dh_recib;
	const char *numero;
	int cod_status;
	const char *xml;
	const char *xmot;
} PROTOCOLO;

/*
 * Complete NFE information
 */
typedef struct {
	IDNFE *idnfe;
	EMITENTE *emitente;
	DESTINATARIO *destinatario;
	ITEM *itens;
	unsigned int q_itens;
	float total;
	TRANSP *transp;
	PROTOCOLO *protocolo;
	const char *xml;
	int canceled;
	const char *inf_ad_fisco;
	const char *inf_ad_contrib;
} NFE;

typedef struct LOTE_ITEM LOTE_ITEM;

/**
 * List items
 */
struct LOTE_ITEM{
	NFE *nfe;
	LOTE_ITEM *next;
};

/**
 * NFE Lote
 */
typedef struct {
	unsigned int id;
	const char *recibo;
	unsigned int qtd;
	LOTE_ITEM *nfes;
	const char *xml_response;
} LOTE;

/**
 * Evento
 */
typedef struct {
	const char *id;
	int seq;
	NFE *nfe;
	evento_t type;
	int cStat;
	const char *xmot;
	const char *protocolo;
	const char *xml;
	const char *xml_response;
} EVENTO;

/**
 * Evento cancelamento
 */
typedef struct {
	EVENTO evento;
	const char *justificativa;
} EVENTO_CANCELAMENTO;

/**
 * List evento items
 */
typedef struct LOTE_EVENTO_ITEM LOTE_EVENTO_ITEM;
struct LOTE_EVENTO_ITEM {
	EVENTO *evento;
	LOTE_EVENTO_ITEM *next;
};

/**
 * Eventos Lote
 */
typedef struct {
	unsigned int id;
	const char *recibo;
	unsigned int qtd;
	LOTE_EVENTO_ITEM *eventos;
	const char *xml_response;
} LOTE_EVENTO;

/**
 * URLs for preferences window
 */
typedef struct {
	const char *recepcaoevento_prod;
	const char *recepcaoevento_cert;
	const char *nfeconsultacadastro_prod;
	const char *nfeconsultacadastro_cert;
	const char *nfeinutilizacao_prod;
	const char *nfeinutilizacao_cert;
	const char *nfeconsultaprotocolo_prod;
	const char *nfeconsultaprotocolo_cert;
	const char *nfestatusservico_prod;
	const char *nfestatusservico_cert;
	const char *nferetautorizacao_prod;
	const char *nferetautorizacao_cert;
	const char *nfeautorizacao_prod;
	const char *nfeautorizacao_cert;
} PREFS_URLS;

/**
 * Urls
 */
typedef struct {
	char *recepcaoevento;
	char *nfeconsultacadastro;
	char *nfeinutilizacao;
	char *nfeconsultaprotocolo;
	char *nfestatusservico;
	char *nferetautorizacao;
	char *nfeautorizacao;
} URLS;

/**
 * User preferences
 */
typedef struct {
	URLS *urls;
	char *public_key;
	char *private_key;
	char *card_reader_lib;
	int ambiente;
	int cert_type;
} PREFS;


#define LIVRENFE_TYPE	(livrenfe_get_type())
#define	LIVRENFE_APP(obj)	(G_TYPE_CHECK_INSTANCE_CAST ((obj), LIVRENFE_TYPE, Livrenfe))

typedef struct _Livrenfe Livrenfe;
typedef struct _LivrenfeClass LivrenfeClass;

GType livrenfe_get_type(void);
Livrenfe *livrenfe_new(void);

#endif
