/*
 * ext_api_http.h
 *
 *  Created on: 17.10.2018
 *      Author: Georgi Angelov
 */

#ifndef EXT_API_HTTP_H_
#define EXT_API_HTTP_H_


#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

typedef enum {
    HTTPCLIENT_GET,
    HTTPCLIENT_POST,
    HTTPCLIENT_PUT,
    HTTPCLIENT_DELETE,
    HTTPCLIENT_HEAD
} HTTPCLIENT_REQUEST_TYPE;

typedef struct {
	int socket;
	int remote_port;
	int response_code;
	char * header;
	char * auth_user;
	char * auth_password;
	uint8_t is_http;
	int method;
	const unsigned char * server_cert;
	const unsigned char * client_cert;
	const unsigned char * client_pk;
	int server_cert_len;
	int client_cert_len;
	int client_pk_len;
	void * ssl;
} httpclient_t;

typedef struct {
	uint8_t is_more;
	uint8_t is_chunked;
	int retrieve_len;
	int response_content_len;
	int content_block_len;
	int post_buf_len;
	int response_buf_len;
	int header_buf_len;
	char * post_content_type;
	char * post_buf;
	char * response_buf;
	char * header_buf;
} httpclient_data_t;

int httpclient_connect(httpclient_t * client, char * url);
int httpclient_close(httpclient_t * client);
int httpclient_send_auth(httpclient_t * client, char * send_buf, int * send_idx);
int httpclient_send_header(httpclient_t * client, char * url, int method, httpclient_data_t * client_data);
int httpclient_send_userdata(httpclient_t * client, httpclient_data_t * client_data);
int httpclient_send_request(httpclient_t *client, char * url, int method, httpclient_data_t * client_data);
int httpclient_recv_response(httpclient_t * client, httpclient_data_t * client_data);
int httpclient_get_response_code(httpclient_t *client);
int httpclient_common(httpclient_t *client, char *url, int method, httpclient_data_t *client_data);
int httpclient_post(httpclient_t *client, char *url, httpclient_data_t *client_data);


#endif /* EXT_API_HTTP_H_ */
