/* Provide SSL/TLS functions to ESP32 with Arduino IDE
*
* Adapted from the ssl_client1 example of mbedtls.
*
* Original Copyright (C) 2006-2015, ARM Limited, All Rights Reserved, Apache 2.0 License.
* Additions Copyright (C) 2017 Evandro Luis Copercini, Apache 2.0 License.
*/

#include "interface.h"

#include <lwip/err.h>
#include <lwip/sockets.h>
#include <lwip/netdb.h>

#include "nbSSL.h"
#include "nbGenericClass.h"

const char *pers = "bc66-tls";

static int handle_error(int err)
{
    if (err == -30848)
        return err;
    log_e("Code: -0x%04X", -err);
    return err;
}

void ssl_init(sslclient_context *ssl_client)
{
    if (ssl_client)
    {
        mbedtls_ssl_init(&ssl_client->ssl_ctx);         //memset
        mbedtls_ssl_config_init(&ssl_client->ssl_conf); //memset
        mbedtls_ctr_drbg_init(&ssl_client->drbg_ctx);   //memset & mutex
    }
}

int start_ssl_client(sslclient_context *ssl_client, const char *host, uint32_t port, const char *rootCABuff, const char *cli_cert, const char *cli_key, const char *pskIdent, const char *psKey)
{
    char hints[512];
    int ret, flags, timeout;
    int enable = 1;

    log_v("Starting socket");
    ssl_client->socket = -1;

    ssl_client->socket = lwip_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ssl_client->socket < 0)
    {
        log_e("opening socket");
        return ssl_client->socket;
    }

#if 0
    IPAddress srv((uint32_t)0);
    if (!nbGenericClass::hostByName(host, srv))
    {
        log_e("hostByName");
        return -1;
    }
    log_v("Host: %s ( %s:%d )", host, srv.toString().c_str(), (int)port); // www.howsmyssl.com ( 35.227.42.200 )

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = srv;
    serv_addr.sin_port = htons(port);
    if (lwip_connect(ssl_client->socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0)
    {
        timeout = 30000;
        lwip_setsockopt(ssl_client->socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
#if 0        
        lwip_setsockopt(ssl_client->socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
        lwip_setsockopt(ssl_client->socket, IPPROTO_TCP, TCP_NODELAY, &enable, sizeof(enable));
        lwip_setsockopt(ssl_client->socket, SOL_SOCKET, SO_KEEPALIVE, &enable, sizeof(enable));
#endif
        log_v("Connected to Server: %s", srv.toString().c_str());
    }
    else
    {
        log_e("Connect to Server failed!");
        return -1;
    }
    lwip_fcntl(ssl_client->socket, F_SETFL, lwip_fcntl(ssl_client->socket, F_GETFL, 0) | O_NONBLOCK);
#else
    mbedtls_net_context net_ctx;
    char str_port[10];
    snprintf(str_port, 10, "%lu", port);
    ret = mbedtls_net_connect(&net_ctx, host, str_port, 0);
    if (ret)
    {
        log_e("Connect to Server failed!");
        return -1;
    }
    ssl_client->socket = net_ctx.fd;
#endif

    mbedtls_entropy_init(&ssl_client->entropy_ctx); //memset, mutex, sha512, add

    log_v("Seeding the random number generator");
    ret = mbedtls_ctr_drbg_seed(&ssl_client->drbg_ctx, mbedtls_entropy_func, &ssl_client->entropy_ctx, (const unsigned char *)pers, strlen(pers)); //max [48]
    if (ret < 0)
        return handle_error(ret);

    log_v("Setting up the SSL/TLS structure...");
    ret = mbedtls_ssl_config_defaults(&ssl_client->ssl_conf, MBEDTLS_SSL_IS_CLIENT, MBEDTLS_SSL_TRANSPORT_STREAM, MBEDTLS_SSL_PRESET_DEFAULT);
    if (ret != 0)
        return handle_error(ret);

    if (rootCABuff != NULL)
    {
        log_v("Loading CA cert");
        mbedtls_x509_crt_init(&ssl_client->ca_cert); //memset
        mbedtls_ssl_conf_authmode(&ssl_client->ssl_conf, MBEDTLS_SSL_VERIFY_REQUIRED);
        ret = mbedtls_x509_crt_parse(&ssl_client->ca_cert, (const unsigned char *)rootCABuff, strlen(rootCABuff) + 1);
        mbedtls_ssl_conf_ca_chain(&ssl_client->ssl_conf, &ssl_client->ca_cert, NULL);
        //mbedtls_ssl_conf_verify(&ssl_client->ssl_conf, NULL, NULL); //not used
        if (ret < 0)
        {
            log_e("mbedtls_x509_crt_parse");
            return handle_error(ret);
        }
    }
    else if (pskIdent != NULL && psKey != NULL)
    {
        log_v("Setting up PSK");
        // convert PSK from hex to binary
        if ((strlen(psKey) & 1) != 0 || strlen(psKey) > 2 * MBEDTLS_PSK_MAX_LEN)
        {
            log_e("pre-shared key not valid hex or too long");
            return -1;
        }
        unsigned char psk[MBEDTLS_PSK_MAX_LEN];
        size_t psk_len = strlen(psKey) / 2;
        for (int j = 0; j < strlen(psKey); j += 2)
        {
            char c = psKey[j];
            if (c >= '0' && c <= '9')
                c -= '0';
            else if (c >= 'A' && c <= 'F')
                c -= 'A' - 10;
            else if (c >= 'a' && c <= 'f')
                c -= 'a' - 10;
            else
                return -1;
            psk[j / 2] = c << 4;
            c = psKey[j + 1];
            if (c >= '0' && c <= '9')
                c -= '0';
            else if (c >= 'A' && c <= 'F')
                c -= 'A' - 10;
            else if (c >= 'a' && c <= 'f')
                c -= 'a' - 10;
            else
                return -1;
            psk[j / 2] |= c;
        }
        // set mbedtls config
        ret = mbedtls_ssl_conf_psk(&ssl_client->ssl_conf, psk, psk_len, (const unsigned char *)pskIdent, strlen(pskIdent));
        if (ret != 0)
        {
            log_e("mbedtls_ssl_conf_psk returned %d", ret);
            return handle_error(ret);
        }
    }
    else
    {
        mbedtls_ssl_conf_authmode(&ssl_client->ssl_conf, MBEDTLS_SSL_VERIFY_NONE);
        log_i("WARNING: Use certificates for a more secure communication!");
    }

    if (cli_cert != NULL && cli_key != NULL)
    {
        mbedtls_x509_crt_init(&ssl_client->client_cert); //memset
        mbedtls_pk_init(&ssl_client->client_key);        //memset

        log_v("Loading CRT cert");
        ret = mbedtls_x509_crt_parse(&ssl_client->client_cert, (const unsigned char *)cli_cert, strlen(cli_cert) + 1);
        if (ret < 0)
            return handle_error(ret);

        log_v("Loading client private key");
        ret = mbedtls_pk_parse_key(&ssl_client->client_key, (const unsigned char *)cli_key, strlen(cli_key) + 1, NULL, 0);

        if (ret != 0)
            return handle_error(ret);

        mbedtls_ssl_conf_own_cert(&ssl_client->ssl_conf, &ssl_client->client_cert, &ssl_client->client_key);
    }

    log_v("Setting hostname for TLS session...");
    if ((ret = mbedtls_ssl_set_hostname(&ssl_client->ssl_ctx, host)) != 0) //mbedtls_calloc [host_len]
        return handle_error(ret);

    mbedtls_ssl_conf_rng(&ssl_client->ssl_conf, mbedtls_ctr_drbg_random, &ssl_client->drbg_ctx); //set func

    if ((ret = mbedtls_ssl_setup(&ssl_client->ssl_ctx, &ssl_client->ssl_conf)) != 0) //calloc in[6477] out[6477]
        return handle_error(ret);

    mbedtls_ssl_set_bio(&ssl_client->ssl_ctx, &ssl_client->socket, mbedtls_net_send, mbedtls_net_recv, NULL); //set func

    log_v("Performing the handshake");
    unsigned long handshake_start_time = millis();
    while ((ret = mbedtls_ssl_handshake(&ssl_client->ssl_ctx)) != 0)
    {
        if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
            return handle_error(ret);
        if ((millis() - handshake_start_time) > ssl_client->handshake_timeout)
            return -1;
        //vTaskDelay(1);
    }

    if (cli_cert != NULL && cli_key != NULL)
    {
        log_d("Protocol is %s Ciphersuite is %s", mbedtls_ssl_get_version(&ssl_client->ssl_ctx), mbedtls_ssl_get_ciphersuite(&ssl_client->ssl_ctx));
        if ((ret = mbedtls_ssl_get_record_expansion(&ssl_client->ssl_ctx)) >= 0)
        {
            log_d("Record expansion is %d", ret);
        }
        else
        {
            log_w("Record expansion is unknown (compression)");
        }
    }

    log_v("Verifying peer X.509 certificate...");
    if ((flags = mbedtls_ssl_get_verify_result(&ssl_client->ssl_ctx)) != 0)
    {
        //bzero(hints, sizeof(hints));
        mbedtls_x509_crt_verify_info(hints, sizeof(hints), "  ! ", flags);
        log_e("Verification info: %s", hints);
        stop_ssl_socket(ssl_client, rootCABuff, cli_cert, cli_key); //It's not safe continue.
        return handle_error(ret);
    }
    else
    {
        log_v("Certificate verified.");
    }

    if (rootCABuff != NULL)
        mbedtls_x509_crt_free(&ssl_client->ca_cert);
    if (cli_cert != NULL)
        mbedtls_x509_crt_free(&ssl_client->client_cert);
    if (cli_key != NULL)
        mbedtls_pk_free(&ssl_client->client_key);

    return ssl_client->socket;
}

void stop_ssl_socket(sslclient_context *ssl_client, const char *rootCABuff, const char *cli_cert, const char *cli_key)
{
    //log_v("Cleaning connection.");
    if (ssl_client->socket >= 0)
    {
        lwip_close(ssl_client->socket);
        ssl_client->socket = -1;
    }
    mbedtls_ssl_free(&ssl_client->ssl_ctx);
    mbedtls_ssl_config_free(&ssl_client->ssl_conf);
    mbedtls_ctr_drbg_free(&ssl_client->drbg_ctx);   //once or boom
    mbedtls_entropy_free(&ssl_client->entropy_ctx); //once or boom
}

int data_to_read(sslclient_context *ssl_client)
{
    int ret, res;
    ret = mbedtls_ssl_read(&ssl_client->ssl_ctx, NULL, 0);
    //log_e("RET: %i", ret); //for low level debug
    res = mbedtls_ssl_get_bytes_avail(&ssl_client->ssl_ctx);
    //log_e("RES: %i", res); //for low level debug
    if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE && ret < 0)
        return handle_error(ret);
    return res;
}

int send_ssl_data(sslclient_context *ssl_client, const uint8_t *data, uint16_t len)
{
    int ret = -1;
    while ((ret = mbedtls_ssl_write(&ssl_client->ssl_ctx, data, len)) <= 0)
    {
        if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
        {
            log_e("write %d bytes", len);
            return handle_error(ret);
        }
    }
    //DMP("(WR)", data, len);
    len = ret;
    return ret;
}

int get_ssl_receive(sslclient_context *ssl_client, uint8_t *data, int length)
{
    //log_d("Reading response..."); //for low level debug
    int ret = mbedtls_ssl_read(&ssl_client->ssl_ctx, data, length);
    //log_v("%d bytes read", ret); //for low level debug
    return ret;
}

static bool parseHexNibble(char pb, uint8_t *res)
{
    if (pb >= '0' && pb <= '9')
    {
        *res = (uint8_t)(pb - '0');
        return true;
    }
    else if (pb >= 'a' && pb <= 'f')
    {
        *res = (uint8_t)(pb - 'a' + 10);
        return true;
    }
    else if (pb >= 'A' && pb <= 'F')
    {
        *res = (uint8_t)(pb - 'A' + 10);
        return true;
    }
    return false;
}

// Verifies certificate provided by the peer to match specified SHA256 fingerprint
bool verify_ssl_fingerprint(sslclient_context *ssl_client, const char *fp, const char *domain_name)
{
    // Convert hex string to byte array
    uint8_t fingerprint_local[32];
    int len = strlen(fp);
    int pos = 0;
    for (size_t i = 0; i < sizeof(fingerprint_local); ++i)
    {
        while (pos < len && ((fp[pos] == ' ') || (fp[pos] == ':')))
        {
            ++pos;
        }
        if (pos > len - 2)
        {
            log_d("pos:%d len:%d fingerprint too short", pos, len);
            return false;
        }
        uint8_t high, low;
        if (!parseHexNibble(fp[pos], &high) || !parseHexNibble(fp[pos + 1], &low))
        {
            log_d("pos:%d len:%d invalid hex sequence: %c%c", pos, len, fp[pos], fp[pos + 1]);
            return false;
        }
        pos += 2;
        fingerprint_local[i] = low | (high << 4);
    }
    // Get certificate provided by the peer
    const mbedtls_x509_crt *crt = mbedtls_ssl_get_peer_cert(&ssl_client->ssl_ctx);
    if (!crt)
    {
        log_d("could not fetch peer certificate");
        return false;
    }
    // Calculate certificate's SHA256 fingerprint
    uint8_t fingerprint_remote[32];
    mbedtls_sha256_context sha256_ctx;
    mbedtls_sha256_init(&sha256_ctx);
    mbedtls_sha256_starts(&sha256_ctx, false);
    mbedtls_sha256_update(&sha256_ctx, crt->raw.p, crt->raw.len);
    mbedtls_sha256_finish(&sha256_ctx, fingerprint_remote);
    // Check if fingerprints match
    if (memcmp(fingerprint_local, fingerprint_remote, 32))
    {
        log_d("fingerprint doesn't match");
        return false;
    }
    // Additionally check if certificate has domain name if provided
    if (domain_name)
        return verify_ssl_dn(ssl_client, domain_name);
    else
        return true;
}

// Checks if peer certificate has specified domain in CN or SANs
bool verify_ssl_dn(sslclient_context *ssl_client, const char *domain_name)
{
    //TODO
    return false;
}