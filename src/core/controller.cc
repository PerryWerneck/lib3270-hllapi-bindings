/*
 * "Software pw3270, desenvolvido com base nos códigos fontes do WC3270  e X3270
 * (Paul Mattes Paul.Mattes@usa.net), de emulação de terminal 3270 para acesso a
 * aplicativos mainframe. Registro no INPI sob o nome G3270.
 *
 * Copyright (C) <2008> <Banco do Brasil S.A.>
 *
 * Este programa é software livre. Você pode redistribuí-lo e/ou modificá-lo sob
 * os termos da GPL v.2 - Licença Pública Geral  GNU,  conforme  publicado  pela
 * Free Software Foundation.
 *
 * Este programa é distribuído na expectativa de  ser  útil,  mas  SEM  QUALQUER
 * GARANTIA; sem mesmo a garantia implícita de COMERCIALIZAÇÃO ou  de  ADEQUAÇÃO
 * A QUALQUER PROPÓSITO EM PARTICULAR. Consulte a Licença Pública Geral GNU para
 * obter mais detalhes.
 *
 * Você deve ter recebido uma cópia da Licença Pública Geral GNU junto com este
 * programa;  se  não, escreva para a Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA, 02111-1307, USA
 *
 * Este programa está nomeado como - e possui - linhas de código.
 *
 * Contatos:
 *
 * perry.werneck@gmail.com	(Alexandre Perry de Souza Werneck)
 * erico.mendonca@gmail.com	(Erico Mascarenhas Mendonça)
 *
 */

 #include "private.h"

/*--[ Globals ]--------------------------------------------------------------------------------------*/

 static TN3270::Host	* hllapi_host		= nullptr;
 static time_t			  hllapi_timeout	= 120;
 std::string		  	  hllapi_lasterror	= "";

/*--[ Implement ]------------------------------------------------------------------------------------*/

 HLLAPI_API_CALL hllapi_init(LPSTR id)
 {
 	trace("%s(%s)",__FUNCTION__,id);

	try
	{
		if(hllapi_host)
			delete hllapi_host;

		hllapi_host = new TN3270::Host(*id ? id : nullptr,nullptr,hllapi_timeout);

	}
	catch(std::exception &e)
	{
		hllapi_lasterror = e.what();
		return HLLAPI_STATUS_SYSTEM_ERROR;
	}

 	return HLLAPI_STATUS_SUCCESS;

 }

 HLLAPI_API_CALL hllapi_deinit(void)
 {
 	trace("%s()",__FUNCTION__);

 	try
 	{
		if(hllapi_host)
		{
			delete hllapi_host;
			hllapi_host = NULL;
		}

	}
	catch(std::exception &e)
	{
		hllapi_lasterror = e.what();
		return HLLAPI_STATUS_SYSTEM_ERROR;
	}

 	return HLLAPI_STATUS_SUCCESS;
 }

 TN3270::Host & getSession() {

 	if(!hllapi_host) {
		throw runtime_error("Not initialized");
 	}

 	return *hllapi_host;

 }

 HLLAPI_API_CSTR hllapi_get_last_error() {
 	return hllapi_lasterror.c_str();
 }

