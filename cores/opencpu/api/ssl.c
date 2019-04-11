/*

    MISSING FUNCTIONS

*/

#include <string.h>
#include "api.h"
#include "api_ssl.h"

void mbedtls_strerror(int ret, char *buf, size_t buflen)
{
	((void)ret);
	if (buflen > 0)
		buf[0] = '\0';
}

static inline size_t mbedtls_ssl_hdr_len(const mbedtls_ssl_context *ssl)
{
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if (ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM)
        return (13);
#else
    ((void)ssl);
#endif
    return (5);
}

static inline mbedtls_cipher_mode_t mbedtls_cipher_get_cipher_mode(const mbedtls_cipher_context_t *ctx)
{
    if (NULL == ctx || NULL == ctx->cipher_info)
        return MBEDTLS_MODE_NONE;
    return ctx->cipher_info->mode;
}

size_t mbedtls_ssl_get_bytes_avail(const mbedtls_ssl_context *ssl)
{
    return (ssl->in_offt == NULL ? 0 : ssl->in_msglen);
}

int mbedtls_ssl_get_record_expansion(const mbedtls_ssl_context *ssl)
{
    size_t transform_expansion;
    const mbedtls_ssl_transform *transform = ssl->transform_out;
#if defined(MBEDTLS_ZLIB_SUPPORT)
    if (ssl->session_out->compression != MBEDTLS_SSL_COMPRESS_NULL)
        return (MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE);
#endif
    if (transform == NULL)
        return ((int)mbedtls_ssl_hdr_len(ssl));
    switch (mbedtls_cipher_get_cipher_mode(&transform->cipher_ctx_enc))
    {
    case MBEDTLS_MODE_GCM:
    case MBEDTLS_MODE_CCM:
    case MBEDTLS_MODE_STREAM:
        transform_expansion = transform->minlen;
        break;
    case MBEDTLS_MODE_CBC:
        transform_expansion = transform->maclen + mbedtls_cipher_get_block_size(&transform->cipher_ctx_enc);
        break;
    default:
        //MBEDTLS_SSL_DEBUG_MSG(1, ("should never happen"));
        return (MBEDTLS_ERR_SSL_INTERNAL_ERROR);
    }
    return ((int)(mbedtls_ssl_hdr_len(ssl) + transform_expansion));
}

int mbedtls_ssl_conf_psk(mbedtls_ssl_config *conf, const unsigned char *psk, size_t psk_len, const unsigned char *psk_identity, size_t psk_identity_len)
{
    if (psk == NULL || psk_identity == NULL)
        return (MBEDTLS_ERR_SSL_BAD_INPUT_DATA);
    if (psk_len > MBEDTLS_PSK_MAX_LEN)
        return (MBEDTLS_ERR_SSL_BAD_INPUT_DATA);
    /* Identity len will be encoded on two bytes */
    if ((psk_identity_len >> 16) != 0 ||
        psk_identity_len > MBEDTLS_SSL_MAX_CONTENT_LEN)
    {
        return (MBEDTLS_ERR_SSL_BAD_INPUT_DATA);
    }
    if (conf->psk != NULL || conf->psk_identity != NULL)
    {
        mbedtls_free(conf->psk);
        mbedtls_free(conf->psk_identity);
        conf->psk = NULL;
        conf->psk_identity = NULL;
    }
    if ((conf->psk = (unsigned char *)mbedtls_calloc(1, psk_len)) == NULL ||
        (conf->psk_identity = (unsigned char *)mbedtls_calloc(1, psk_identity_len)) == NULL)
    {
        mbedtls_free(conf->psk);
        mbedtls_free(conf->psk_identity);
        conf->psk = NULL;
        conf->psk_identity = NULL;
        return (MBEDTLS_ERR_SSL_ALLOC_FAILED);
    }
    conf->psk_len = psk_len;
    conf->psk_identity_len = psk_identity_len;
    memcpy(conf->psk, psk, conf->psk_len);
    memcpy(conf->psk_identity, psk_identity, conf->psk_identity_len);
    return (0);
}

const char *mbedtls_ssl_get_version(const mbedtls_ssl_context *ssl)
{
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if (ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM)
    {
        switch (ssl->minor_ver)
        {
        case MBEDTLS_SSL_MINOR_VERSION_2:
            return ("DTLSv1.0");
        case MBEDTLS_SSL_MINOR_VERSION_3:
            return ("DTLSv1.2");
        default:
            return ("unknown (DTLS)");
        }
    }
#endif
    switch (ssl->minor_ver)
    {
    case MBEDTLS_SSL_MINOR_VERSION_0:
        return ("SSLv3.0");
    case MBEDTLS_SSL_MINOR_VERSION_1:
        return ("TLSv1.0");
    case MBEDTLS_SSL_MINOR_VERSION_2:
        return ("TLSv1.1");
    case MBEDTLS_SSL_MINOR_VERSION_3:
        return ("TLSv1.2");
    default:
        return ("unknown");
    }
}

const char *mbedtls_ssl_get_ciphersuite(const mbedtls_ssl_context *ssl)
{
    if (ssl == NULL || ssl->session == NULL)
        return (NULL);
    return mbedtls_ssl_get_ciphersuite_name(ssl->session->ciphersuite);
}

int mbedtls_ssl_set_hostname(mbedtls_ssl_context *ssl, const char *hostname)
{
    size_t hostname_len;
    if (hostname == NULL)
        return (MBEDTLS_ERR_SSL_BAD_INPUT_DATA);
    hostname_len = strlen(hostname);
    if (hostname_len + 1 == 0)
        return (MBEDTLS_ERR_SSL_BAD_INPUT_DATA);
    if (hostname_len > MBEDTLS_SSL_MAX_HOST_NAME_LEN)
        return (MBEDTLS_ERR_SSL_BAD_INPUT_DATA);
    ssl->hostname = (char *)mbedtls_calloc(1, hostname_len + 1);
    if (ssl->hostname == NULL)
        return (MBEDTLS_ERR_SSL_ALLOC_FAILED);
    memcpy(ssl->hostname, hostname, hostname_len);
    ssl->hostname[hostname_len] = '\0';
    return (0);
}

const mbedtls_x509_crt *mbedtls_ssl_get_peer_cert(const mbedtls_ssl_context *ssl)
{
    if (ssl == NULL || ssl->session == NULL)
        return (NULL);
    return (ssl->session->peer_cert);
}

void mbedtls_ssl_conf_verify(mbedtls_ssl_config *conf, int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *), void *p_vrfy)
{
    conf->f_vrfy = f_vrfy;
    conf->p_vrfy = p_vrfy;
}

void ssl_set_timer(mbedtls_ssl_context *ssl, uint32_t millisecs);
unsigned long mbedtls_timing_get_timer(struct mbedtls_timing_hr_time *val, int reset)
{
    unsigned long delta;
    struct timeval offset;
    struct _hr_time *t = (struct _hr_time *)val;
    gettimeofday(&offset, NULL);
    if (reset)
    {
        t->start.tv_sec = offset.tv_sec;
        t->start.tv_usec = offset.tv_usec;
        return (0);
    }
    delta = (offset.tv_sec - t->start.tv_sec) * 1000 + (offset.tv_usec - t->start.tv_usec) / 1000;
    return (delta);
}

void mbedtls_ssl_set_timer_cb(mbedtls_ssl_context *ssl, void *p_timer, mbedtls_ssl_set_timer_t *f_set_timer, mbedtls_ssl_get_timer_t *f_get_timer)
{
    ssl->p_timer = p_timer;
    ssl->f_set_timer = f_set_timer;
    ssl->f_get_timer = f_get_timer;
    ssl_set_timer(ssl, 0);
}

void mbedtls_timing_set_delay(void *data, uint32_t int_ms, uint32_t fin_ms)
{
    mbedtls_timing_delay_context *ctx = (mbedtls_timing_delay_context *)data;
    ctx->int_ms = int_ms;
    ctx->fin_ms = fin_ms;
    if (fin_ms != 0)
        (void)mbedtls_timing_get_timer(&ctx->timer, 1);
}

int mbedtls_timing_get_delay(void *data)
{
    mbedtls_timing_delay_context *ctx = (mbedtls_timing_delay_context *)data;
    unsigned long elapsed_ms;
    if (ctx->fin_ms == 0)
        return (-1);
    elapsed_ms = mbedtls_timing_get_timer(&ctx->timer, 0);
    if (elapsed_ms >= ctx->fin_ms)
        return (2);
    if (elapsed_ms >= ctx->int_ms)
        return (1);
    return (0);
}