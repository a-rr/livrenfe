/* Copyright (c) 2016 Pablo G. Gallardo <pggllrd@gmail.com>
 *
 * This file is part of LivreNFE.
 *
 * LibreNFE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibreNFE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LivreNFE.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "gen_xml.h"
#include "errno.h"
#include <stdio.h>
#include <string.h>
#include <libxml/xmlwriter.h>

int gen_inf_nfe(xmlTextWriterPtr, t_nfe *);
int _gen_ide(xmlTextWriterPtr, t_nfe *);
int _gen_emit(xmlTextWriterPtr, t_nfe *);
int _gen_dest(xmlTextWriterPtr, t_nfe *);
int _gen_det(xmlTextWriterPtr, t_nfe *);
int is_cpf(char *);

char *generate_xml(t_nfe *nfe) {

	int rc;
	xmlTextWriterPtr writer;
	xmlBufferPtr buf;

	buf = xmlBufferCreate();
	if (buf == NULL) 
		return NULL;

	writer = xmlNewTextWriterMemory(buf, 0);
	if (writer == NULL)
		return NULL;

	rc = gen_inf_nfe(writer, nfe);
	if (rc < 0)
		return NULL;
	
	return buf->content;
}

int gen_inf_nfe(xmlTextWriterPtr writer, t_nfe *nfe){

	int rc;
	rc = xmlTextWriterStartElement(writer, BAD_CAST "nfeProc");
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteAttribute(writer, BAD_CAST "versao",
			BAD_CAST NFE_VERSAO);	
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterStartElement(writer, BAD_CAST "NFe");
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterStartElement(writer, BAD_CAST "infNFe");
	if (rc < 0)
		return -EXML;
	char *id = malloc(strlen(nfe->idnfe.chave) + strlen(ID_PREFIX));
	strcpy(id, ID_PREFIX);
	strcat(id, nfe->idnfe.chave);
	rc = xmlTextWriterWriteAttribute(writer, BAD_CAST "Id",
		BAD_CAST nfe->idnfe.chave);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteAttribute(writer, BAD_CAST "versao",
		BAD_CAST NFE_VERSAO);
	if (rc < 0)
		return -EXML;
	
	rc = _gen_ide(writer, nfe);
	if (rc < 0)
		return -EXML;

	rc = _gen_emit(writer, nfe);
	if (rc < 0)
		return -EXML;

	rc = _gen_dest(writer, nfe);
	if (rc < 0)
		return -EXML;




	return 0;
}

int _gen_ide(xmlTextWriterPtr writer, t_nfe *nfe){

	int rc;

	rc = xmlTextWriterStartElement(writer, BAD_CAST "ide");
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "cUF",
			"%d", nfe->idnfe.municipio.cod_uf);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "cNF",
			"%d", nfe->idnfe.id_nfe);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "natOp",
			"%s", nfe->idnfe.nat_op);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "indPag",
			"%d", nfe->idnfe.ind_pag);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mod",
			"%d", nfe->idnfe.mod);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "serie",
			"%d", nfe->idnfe.serie);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "nNF",
			"%d", nfe->idnfe.num_nf);
	if (rc < 0)
		return -EXML;
	
	char buffer[26];
	struct tm *tm_info;
	tm_info = localtime(&(nfe->idnfe.dh_emis));
	strftime(buffer, 26, "%Y-%m-%dT%H:%M:%S-03:00", tm_info);

	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "dhEmi",
			"%s", buffer);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "tpNF",
			"%d", nfe->idnfe.tipo);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "idDest",
			"%d", nfe->idnfe.local_destino);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "cMunFG",	
			"%d", nfe->idnfe.municipio.codigo);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "tpImp",	
			"%d", nfe->idnfe.tipo_impressao);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "tpEmis",
			"%d", nfe->idnfe.tipo_emissao);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "cDV",
			"%s", &(nfe->idnfe.div));
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "tpAmb",
			"%d", nfe->idnfe.tipo_ambiente);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "finNFe",
			"%d", nfe->idnfe.finalidade);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "indFinal",
			"%d", nfe->idnfe.consumidor_final);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "indPres",
			"%d", nfe->idnfe.presencial);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "procEmi",
			"%d", 3);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "verProc",
			"%s", nfe->idnfe.versao);
	if (rc < 0)
		return -EXML;

	rc = xmlTextWriterEndElement(writer);
	if (rc < 0)
		return -EXML;
	return 0;
}

int _gen_emit(xmlTextWriterPtr writer, t_nfe *nfe){

	int rc;

	rc = xmlTextWriterStartElement(writer, BAD_CAST "emit");
	if (rc < 0)
		return -EXML;
	
	if (is_cpf(nfe->emitente.id))
		rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "CPF",
				"%s", nfe->emitente.id);
	else
		rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "CNPJ",
				"%s", nfe->emitente.id);
	if (rc < 0)
		return -EXML;
	
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "xNome",
			"%s", nfe->emitente.nome);
	if (rc < 0)
		return -EXML;

	rc = xmlTextWriterStartElement(writer, BAD_CAST "enderEmit");
	if (rc < 0)
		return -EXML;

	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "xLgr",
			"%s", nfe->emitente.endereco.rua);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "nro",
			"%d", nfe->emitente.endereco.num);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "xBairro",
			"%s", nfe->emitente.endereco.bairro);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "cMun",
			"%d", nfe->emitente.endereco.municipio.codigo);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "xMun",
			"%s", nfe->emitente.endereco.municipio.municipio);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "UF",
			"%s", nfe->emitente.endereco.municipio.uf);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "CEP",
			"%d", nfe->emitente.endereco.cep);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "cPais",
			"%d", nfe->emitente.endereco.pais.codigo);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "xPais",
			"%s", nfe->emitente.endereco.pais.nome);
	if (rc < 0)
		return -EXML;
		
	rc = xmlTextWriterEndElement(writer);
	if (rc < 0)
		return -EXML;
	
	if (nfe->emitente.inscricao_estadual) {
		rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "IE",
				"%s", nfe->emitente.inscricao_estadual);
		if (rc < 0)
			return -EXML;
	}
	
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "CRT",
				"%d", nfe->emitente.crt);
	if (rc < 0)
		return -EXML;
	
	rc = xmlTextWriterEndElement(writer);
	if (rc < 0)
		return -EXML;
	return 0;
}

int _gen_dest(xmlTextWriterPtr writer, t_nfe *nfe){

	int rc;

	rc = xmlTextWriterStartElement(writer, BAD_CAST "dest");
	if (rc < 0)
		return -EXML;
	
	if (is_cpf(nfe->destinatario.id))
		rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "CPF",
				"%s", nfe->destinatario.id);
	else
		rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "CNPJ",
				"%s", nfe->destinatario.id);
	if (rc < 0)
		return -EXML;
	
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "xNome",
			"%s", nfe->destinatario.nome);
	if (rc < 0)
		return -EXML;

	rc = xmlTextWriterStartElement(writer, BAD_CAST "enderDest");
	if (rc < 0)
		return -EXML;

	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "xLgr",
			"%s", nfe->destinatario.endereco.rua);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "nro",
			"%d", nfe->destinatario.endereco.num);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "xBairro",
			"%s", nfe->destinatario.endereco.bairro);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "cMun",
			"%d", nfe->destinatario.endereco.municipio.codigo);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "xMun",
			"%s", nfe->destinatario.endereco.municipio.municipio);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "UF",
			"%s", nfe->destinatario.endereco.municipio.uf);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "cPais",
			"%d", nfe->destinatario.endereco.pais.codigo);
	if (rc < 0)
		return -EXML;
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "xPais",
			"%s", nfe->destinatario.endereco.pais.nome);
	if (rc < 0)
		return -EXML;
		
	rc = xmlTextWriterEndElement(writer);
	if (rc < 0)
		return -EXML;
	
	rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "indIEDest",
			"%d", nfe->destinatario.tipo_ie);
	if (rc < 0)
		return -EXML;
	
	rc = xmlTextWriterEndElement(writer);
	if (rc < 0)
		return -EXML;
	return 0;
}

int is_cpf(char *v) {
	int i = strlen(v);
	if (i == 11)
		return 1;
	return 0;
}
