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
#include <time.h>

extern NFE *new_nfe();

extern ITEM *new_item();

extern PRODUTO *inst_produto(int codigo, char *desc, unsigned int ncm, unsigned int cfop, char *unidade_comercial, float valor, PRODUTO *p);

extern ITEM *inst_item(float valor, float quantidade, 
		unsigned int ordem, ITEM *);

extern ICMS *inst_icms(int origem, unsigned int tipo, float aliquota,
		float valor, ICMS *);

extern IMPOSTO *inst_imposto(ICMS *i, PIS *p, COFINS *c, IMPOSTO *);

extern int add_item(NFE *nfe, ITEM *i);

extern int rm_item(NFE *nfe, ITEM *i);

extern void set_chave(NFE *nfe);

extern int inst_nfe(int id_nfe, int id_mun, int id_uf, int ind_pag, int mod_nfe,
		int serie, int num_nf, int tipo, int local_destino, 
		int tipo_impressao, int tipo_emissao, int tipo_ambiente, 
		int finalidade, int consumidor_final, int presencial, int q_itens,
		int id_emit, char *ie_emit, int crt_emit, int id_mun_emit,
		int id_uf_emit, int cep_emit, int num_e_emit, int id_dest, 
		int t_ie_dest, int id_mun_dest, int id_uf_dest, int num_e_dest,
		int cod_nfe, int cep_dest, float dh_emis, float *dh_saida, float total,
		char *nome_mun, char *uf, char *nat_op, char *versao, 
		char *nome_emit, char *cnpj_emit, char *rua_emit,
		char *comp_emit, char *bairro_emit, char *mun_emit, char *uf_emit,
		char *nome_dest, char *cnpj_dest, char *rua_dest, 
		char *comp_dest, char *bairro_dest, char *mun_dest,
		char *uf_dest, char *chave, char div, char *ie_dest,
		char *tipo_doc_dest, NFE *nfe);
