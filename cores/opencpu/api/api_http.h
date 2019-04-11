/*
  BC66 - API
    Created on: 01.01.2019
    Author: Georgi Angelov

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA   
 */

#ifndef API_HTTP_H_
#define API_HTTP_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

typedef enum
{
	HTTPCLIENT_GET,
	HTTPCLIENT_POST,
	HTTPCLIENT_PUT,
	HTTPCLIENT_DELETE,
	HTTPCLIENT_HEAD
} HTTPCLIENT_REQUEST_TYPE;

typedef struct
{
	int socket;
	int remote_port;
	int response_code;
	char *header;
	char *auth_user;
	char *auth_password;
	uint8_t is_http;
	int method;
	unsigned int timeout_in_sec;
	int start_pos;
	int total_len;
	int retry_cnt;
	const char *server_cert;
	const char *client_cert;
	const char *client_pk;
	int server_cert_len;
	int client_cert_len;
	int client_pk_len;
	void *ssl;
} httpclient_t;

typedef struct
{
	uint8_t is_more;
	uint8_t is_chunked;
	int retrieve_len;
	int response_content_len;
	int content_block_len;
	int post_buf_len;
	int response_buf_len;
	int header_buf_len;
	char *post_content_type;
	char *post_buf;
	char *response_buf;
	char *header_buf;
} httpclient_data_t;

int httpclient_connect(httpclient_t *client, char *url);
int httpclient_close(httpclient_t *client);
int httpclient_send_auth(httpclient_t *client, char *send_buf, int *send_idx);
int httpclient_send_header(httpclient_t *client, char *url, int method, httpclient_data_t *client_data);
int httpclient_send_userdata(httpclient_t *client, httpclient_data_t *client_data);
int httpclient_send_request(httpclient_t *client, char *url, int method, httpclient_data_t *client_data);
int httpclient_recv_response(httpclient_t *client, httpclient_data_t *client_data);
int httpclient_get_response_code(httpclient_t *client);
int httpclient_common(httpclient_t *client, char *url, int method, httpclient_data_t *client_data);
int httpclient_post(httpclient_t *client, char *url, httpclient_data_t *client_data);

#endif /* API_HTTP_H_ */
