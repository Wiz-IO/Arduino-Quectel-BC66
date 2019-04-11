/* Provide SSL/TLS functions to ESP32 with Arduino IDE
 * by Evandro Copercini - 2017 - Apache 2.0 License
 * https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFiClientSecure 
 */

#ifndef ARD_SSL_H
#define ARD_SSL_H

#include "interface.h"

#define LOG_SSL   "SSL "

#ifdef LOG_SSL
#   define log_e(FORMAT, ...)   LOG_E(LOG_SSL FORMAT, ##__VA_ARGS__)
#   define log_v(FORMAT, ...)   LOG_V(LOG_SSL FORMAT, ##__VA_ARGS__)
#   define log_d(FORMAT, ...)   LOG_D(LOG_SSL FORMAT, ##__VA_ARGS__)
#   define log_i(FORMAT, ...)   LOG_I(LOG_SSL FORMAT, ##__VA_ARGS__)
#   define log_w(FORMAT, ...)   LOG_W(LOG_SSL FORMAT, ##__VA_ARGS__)
#else
#   define log_e(FORMAT, ...)   
#   define log_v(FORMAT, ...)   
#   define log_d(FORMAT, ...)   
#   define log_i(FORMAT, ...)   
#   define log_w(FORMAT, ...)   
#endif


typedef struct sslclient_context {
    int socket;
    mbedtls_ssl_context ssl_ctx;
    mbedtls_ssl_config ssl_conf;

    mbedtls_ctr_drbg_context drbg_ctx;
    mbedtls_entropy_context entropy_ctx;

    mbedtls_x509_crt ca_cert;
    mbedtls_x509_crt client_cert;
    mbedtls_pk_context client_key;

    unsigned long handshake_timeout;
} sslclient_context;

void ssl_init(sslclient_context *ssl_client);
int start_ssl_client(sslclient_context *ssl_client, const char *host, uint32_t port, const char *rootCABuff, const char *cli_cert, const char *cli_key, const char *pskIdent, const char *psKey);
void stop_ssl_socket(sslclient_context *ssl_client, const char *rootCABuff, const char *cli_cert, const char *cli_key);
int data_to_read(sslclient_context *ssl_client);
int send_ssl_data(sslclient_context *ssl_client, const uint8_t *data, uint16_t len);
int get_ssl_receive(sslclient_context *ssl_client, uint8_t *data, int length);
bool verify_ssl_fingerprint(sslclient_context *ssl_client, const char* fp, const char* domain_name);
bool verify_ssl_dn(sslclient_context *ssl_client, const char* domain_name);

#endif