/*
 * ext_api_ssl.h
 *
 *  Created on: 17.10.2018
 *      Author: Georgi Angelov
 */

#ifndef EXT_API_SSL_H_
#define EXT_API_SSL_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

typedef enum {
	MBEDTLS_CIPHER_NONE = 0x0,
	MBEDTLS_CIPHER_NULL = 0x1,
	MBEDTLS_CIPHER_AES_128_ECB = 0x2,
	MBEDTLS_CIPHER_AES_192_ECB = 0x3,
	MBEDTLS_CIPHER_AES_256_ECB = 0x4,
	MBEDTLS_CIPHER_AES_128_CBC = 0x5,
	MBEDTLS_CIPHER_AES_192_CBC = 0x6,
	MBEDTLS_CIPHER_AES_256_CBC = 0x7,
	MBEDTLS_CIPHER_AES_128_CFB128 = 0x8,
	MBEDTLS_CIPHER_AES_192_CFB128 = 0x9,
	MBEDTLS_CIPHER_AES_256_CFB128 = 0xA,
	MBEDTLS_CIPHER_AES_128_CTR = 0xB,
	MBEDTLS_CIPHER_AES_192_CTR = 0xC,
	MBEDTLS_CIPHER_AES_256_CTR = 0xD,
	MBEDTLS_CIPHER_AES_128_GCM = 0xE,
	MBEDTLS_CIPHER_AES_192_GCM = 0xF,
	MBEDTLS_CIPHER_AES_256_GCM = 0x10,
	MBEDTLS_CIPHER_CAMELLIA_128_ECB = 0x11,
	MBEDTLS_CIPHER_CAMELLIA_192_ECB = 0x12,
	MBEDTLS_CIPHER_CAMELLIA_256_ECB = 0x13,
	MBEDTLS_CIPHER_CAMELLIA_128_CBC = 0x14,
	MBEDTLS_CIPHER_CAMELLIA_192_CBC = 0x15,
	MBEDTLS_CIPHER_CAMELLIA_256_CBC = 0x16,
	MBEDTLS_CIPHER_CAMELLIA_128_CFB128 = 0x17,
	MBEDTLS_CIPHER_CAMELLIA_192_CFB128 = 0x18,
	MBEDTLS_CIPHER_CAMELLIA_256_CFB128 = 0x19,
	MBEDTLS_CIPHER_CAMELLIA_128_CTR = 0x1A,
	MBEDTLS_CIPHER_CAMELLIA_192_CTR = 0x1B,
	MBEDTLS_CIPHER_CAMELLIA_256_CTR = 0x1C,
	MBEDTLS_CIPHER_CAMELLIA_128_GCM = 0x1D,
	MBEDTLS_CIPHER_CAMELLIA_192_GCM = 0x1E,
	MBEDTLS_CIPHER_CAMELLIA_256_GCM = 0x1F,
	MBEDTLS_CIPHER_DES_ECB = 0x20,
	MBEDTLS_CIPHER_DES_CBC = 0x21,
	MBEDTLS_CIPHER_DES_EDE_ECB = 0x22,
	MBEDTLS_CIPHER_DES_EDE_CBC = 0x23,
	MBEDTLS_CIPHER_DES_EDE3_ECB = 0x24,
	MBEDTLS_CIPHER_DES_EDE3_CBC = 0x25,
	MBEDTLS_CIPHER_BLOWFISH_ECB = 0x26,
	MBEDTLS_CIPHER_BLOWFISH_CBC = 0x27,
	MBEDTLS_CIPHER_BLOWFISH_CFB64 = 0x28,
	MBEDTLS_CIPHER_BLOWFISH_CTR = 0x29,
	MBEDTLS_CIPHER_ARC4_128 = 0x2A,
	MBEDTLS_CIPHER_AES_128_CCM = 0x2B,
	MBEDTLS_CIPHER_AES_192_CCM = 0x2C,
	MBEDTLS_CIPHER_AES_256_CCM = 0x2D,
	MBEDTLS_CIPHER_CAMELLIA_128_CCM = 0x2E,
	MBEDTLS_CIPHER_CAMELLIA_192_CCM = 0x2F,
	MBEDTLS_CIPHER_CAMELLIA_256_CCM = 0x30,
} mbedtls_cipher_type_t;

typedef enum {
	MBEDTLS_PK_NONE = 0x0, MBEDTLS_PK_RSA = 0x1, MBEDTLS_PK_ECKEY = 0x2, MBEDTLS_PK_ECKEY_DH = 0x3, MBEDTLS_PK_ECDSA = 0x4, MBEDTLS_PK_RSA_ALT = 0x5, MBEDTLS_PK_RSASSA_PSS = 0x6,
} mbedtls_pk_type_t;

typedef enum {
	MBEDTLS_MD_NONE = 0x0, MBEDTLS_MD_MD2 = 0x1, MBEDTLS_MD_MD4 = 0x2, MBEDTLS_MD_MD5 = 0x3, MBEDTLS_MD_SHA1 = 0x4, MBEDTLS_MD_SHA224 = 0x5, MBEDTLS_MD_SHA256 = 0x6, MBEDTLS_MD_SHA384 = 0x7, MBEDTLS_MD_SHA512 = 0x8, MBEDTLS_MD_RIPEMD160 = 0x9,
} mbedtls_md_type_t;

typedef enum {
	MBEDTLS_OPERATION_NONE = 0xFF, MBEDTLS_DECRYPT = 0x0, MBEDTLS_ENCRYPT = 0x1,
} mbedtls_operation_t;

typedef enum {
	MBEDTLS_KEY_EXCHANGE_NONE = 0x0,
	MBEDTLS_KEY_EXCHANGE_RSA = 0x1,
	MBEDTLS_KEY_EXCHANGE_DHE_RSA = 0x2,
	MBEDTLS_KEY_EXCHANGE_ECDHE_RSA = 0x3,
	MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA = 0x4,
	MBEDTLS_KEY_EXCHANGE_PSK = 0x5,
	MBEDTLS_KEY_EXCHANGE_DHE_PSK = 0x6,
	MBEDTLS_KEY_EXCHANGE_RSA_PSK = 0x7,
	MBEDTLS_KEY_EXCHANGE_ECDHE_PSK = 0x8,
	MBEDTLS_KEY_EXCHANGE_ECDH_RSA = 0x9,
	MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA = 0xA,
	MBEDTLS_KEY_EXCHANGE_ECJPAKE = 0xB,
} mbedtls_key_exchange_type_t;

typedef enum {
	MBEDTLS_CIPHER_ID_NONE = 0x0, MBEDTLS_CIPHER_ID_NULL = 0x1, MBEDTLS_CIPHER_ID_AES = 0x2, MBEDTLS_CIPHER_ID_DES = 0x3, MBEDTLS_CIPHER_ID_3DES = 0x4, MBEDTLS_CIPHER_ID_CAMELLIA = 0x5, MBEDTLS_CIPHER_ID_BLOWFISH = 0x6, MBEDTLS_CIPHER_ID_ARC4 = 0x7,
} mbedtls_cipher_id_t;

typedef int (*mbedtls_ssl_recv_t)(void *, uint8_t *, size_t);
typedef int (*mbedtls_ssl_recv_timeout_t)(void *, uint8_t *, size_t, uint32_t);
typedef int (*mbedtls_ssl_send_t)(void *, const uint8_t *, size_t);

typedef struct {
	int tag;
	size_t len;
	uint8_t *p;
} mbedtls_asn1_buf;
typedef mbedtls_asn1_buf mbedtls_x509_buf;

typedef struct mbedtls_asn1_named_data {
	mbedtls_asn1_buf oid;
	mbedtls_asn1_buf val;
	struct mbedtls_asn1_named_data *next;
	uint8_t next_merged;
} mbedtls_asn1_named_data __attribute__((aligned(4)));
typedef mbedtls_asn1_named_data mbedtls_x509_name;

typedef struct {
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
} mbedtls_x509_time;

typedef struct {
	uint8_t *buf;
	size_t buflen;
	uint8_t *info;
} mbedtls_pem_context;

typedef enum {
	MBEDTLS_PK_DEBUG_NONE = 0x0, MBEDTLS_PK_DEBUG_MPI = 0x1, MBEDTLS_PK_DEBUG_ECP = 0x2,
} mbedtls_pk_debug_type;

typedef enum {
	MBEDTLS_MODE_NONE = 0x0, MBEDTLS_MODE_ECB = 0x1, MBEDTLS_MODE_CBC = 0x2, MBEDTLS_MODE_CFB = 0x3, MBEDTLS_MODE_OFB = 0x4, MBEDTLS_MODE_CTR = 0x5, MBEDTLS_MODE_GCM = 0x6, MBEDTLS_MODE_STREAM = 0x7, MBEDTLS_MODE_CCM = 0x8,
} mbedtls_cipher_mode_t;

typedef struct {
	mbedtls_pk_debug_type type;
	const uint8_t *name;
	void *value;
} mbedtls_pk_debug_item;

typedef struct {
	mbedtls_pk_type_t type;
	const uint8_t *name;
	size_t (*get_bitlen)(const void *);
	int (*can_do)(mbedtls_pk_type_t);
	int (*verify_func)(void *, mbedtls_md_type_t, const uint8_t *, size_t, const uint8_t *, size_t);
	int (*sign_func)(void *, mbedtls_md_type_t, const uint8_t *, size_t, uint8_t *, size_t *, int (*)(void *, uint8_t *, size_t), void *);
	int (*decrypt_func)(void *, const uint8_t *, size_t, uint8_t *, size_t *, size_t, int (*)(void *, uint8_t *, size_t), void *);
	int (*encrypt_func)(void *, const uint8_t *, size_t, uint8_t *, size_t *, size_t, int (*)(void *, uint8_t *, size_t), void *);
	int (*check_pair_func)(const void *, const void *);
	void *(*ctx_alloc_func)(void);
	void (*ctx_free_func)(void *);
	void (*debug_func)(const void *, mbedtls_pk_debug_item *);
} mbedtls_pk_info_t;

typedef struct {
	const mbedtls_pk_info_t *pk_info;
	void *pk_ctx;
} mbedtls_pk_context;

typedef struct mbedtls_asn1_sequence {
	mbedtls_asn1_buf buf;
	struct mbedtls_asn1_sequence *next;
} mbedtls_asn1_sequence;
typedef mbedtls_asn1_sequence mbedtls_x509_sequence;

typedef struct mbedtls_x509_crt {
	mbedtls_x509_buf raw;
	mbedtls_x509_buf tbs;
	int version;
	mbedtls_x509_buf serial;
	mbedtls_x509_buf sig_oid;
	mbedtls_x509_buf issuer_raw;
	mbedtls_x509_buf subject_raw;
	mbedtls_x509_name issuer;
	mbedtls_x509_name subject;
	mbedtls_x509_time valid_from;
	mbedtls_x509_time valid_to;
	mbedtls_pk_context pk;
	mbedtls_x509_buf issuer_id;
	mbedtls_x509_buf subject_id;
	mbedtls_x509_buf v3_ext;
	mbedtls_x509_sequence subject_alt_names;
	int ext_types;
	int ca_istrue;
	int max_pathlen;
	unsigned int key_usage;
	mbedtls_x509_sequence ext_key_usage;
	uint8_t ns_cert_type;
	mbedtls_x509_buf sig;
	mbedtls_md_type_t sig_md;
	mbedtls_pk_type_t sig_pk;
	void *sig_opts;
	struct mbedtls_x509_crt *next;
} mbedtls_x509_crt;

typedef struct mbedtls_x509_crl_entry {
	mbedtls_x509_buf raw;
	mbedtls_x509_buf serial;
	mbedtls_x509_time revocation_date;
	mbedtls_x509_buf entry_ext;
	struct mbedtls_x509_crl_entry *next;
} mbedtls_x509_crl_entry;

typedef struct mbedtls_x509_crl {
	mbedtls_x509_buf raw;
	mbedtls_x509_buf tbs;
	int version;
	mbedtls_x509_buf sig_oid;
	mbedtls_x509_buf issuer_raw;
	mbedtls_x509_name issuer;
	mbedtls_x509_time this_update;
	mbedtls_x509_time next_update;
	mbedtls_x509_crl_entry entry;
	mbedtls_x509_buf crl_ext;
	mbedtls_x509_buf sig_oid2;
	mbedtls_x509_buf sig;
	mbedtls_md_type_t sig_md;
	mbedtls_pk_type_t sig_pk;
	void *sig_opts;
	struct mbedtls_x509_crl *next;
} mbedtls_x509_crl;

typedef struct {
	uint32_t allowed_mds;
	uint32_t allowed_pks;
	uint32_t allowed_curves;
	uint32_t rsa_min_bitlen;
} mbedtls_x509_crt_profile;

typedef int32_t mbedtls_mpi_sint;
typedef uint32_t mbedtls_mpi_uint;
typedef struct {
	int s;
	size_t n;
	mbedtls_mpi_uint *p;
	mbedtls_mpi_uint limbs[2];
} mbedtls_mpi;

typedef void * QueueHandle_t;
typedef QueueHandle_t SemaphoreHandle_t;
typedef struct {
	int fd;
} mbedtls_net_context;

typedef struct {
	SemaphoreHandle_t mutex;
	uint8_t is_valid;
} mbedtls_threading_mutex_t __attribute__((aligned(4)));

typedef struct {
	int ver;
	size_t len;
	mbedtls_mpi N;
	mbedtls_mpi E;
	mbedtls_mpi D;
	mbedtls_mpi P;
	mbedtls_mpi Q;
	mbedtls_mpi DP;
	mbedtls_mpi DQ;
	mbedtls_mpi QP;
	mbedtls_mpi RN;
	mbedtls_mpi RP;
	mbedtls_mpi RQ;
	mbedtls_mpi Vi;
	mbedtls_mpi Vf;
	int padding;
	int hash_id;
	mbedtls_threading_mutex_t mutex;
} mbedtls_rsa_context;

typedef struct {
	uint32_t total[2];
	uint32_t state[5];
	uint8_t buffer[64];
} mbedtls_sha1_context;

typedef struct {
	uint32_t total[2];
	uint32_t state[8];
	uint8_t buffer[64];
	int is224;
} mbedtls_sha256_context;

typedef struct {
	uint64_t total[2];
	uint64_t state[8];
	uint8_t buffer[128];
	int is384;
} mbedtls_sha512_context __attribute__((aligned(8)));

typedef struct {
	uint32_t total[2];
	uint32_t state[4];
	uint8_t buffer[64];
} mbedtls_md5_context;

typedef struct {
	int ciphersuite;
	int compression;
	size_t id_len;
	uint8_t id[32];
	uint8_t master[48];
	mbedtls_x509_crt *peer_cert;
	uint32_t verify_result;
} mbedtls_ssl_session;

typedef void (*mbedtls_ssl_set_timer_t)(void *, uint32_t, uint32_t);

typedef struct {
	mbedtls_md_type_t type;
	const uint8_t *name;
	int size;
	int block_size;
	void (*starts_func)(void *);
	void (*update_func)(void *, const uint8_t *, size_t);
	void (*finish_func)(void *, uint8_t *);
	void (*digest_func)(const uint8_t *, size_t, uint8_t *);
	void *(*ctx_alloc_func)(void);
	void (*ctx_free_func)(void *);
	void (*clone_func)(void *, const void *);
	void (*process_func)(void *, const uint8_t *);
} mbedtls_md_info_t;

typedef struct {
	const mbedtls_md_info_t *md_info;
	void *md_ctx;
	void *hmac_ctx;
} mbedtls_md_context_t;

typedef struct {
	mbedtls_cipher_id_t cipher;
	int (*ecb_func)(void *, mbedtls_operation_t, const uint8_t *, uint8_t *);
	int (*cbc_func)(void *, mbedtls_operation_t, size_t, uint8_t *, const uint8_t *, uint8_t *);
	int (*stream_func)(void *, size_t, const uint8_t *, uint8_t *);
	int (*setkey_enc_func)(void *, const uint8_t *, unsigned int);
	int (*setkey_dec_func)(void *, const uint8_t *, unsigned int);
	void *(*ctx_alloc_func)(void);
	void (*ctx_free_func)(void *);
} mbedtls_cipher_base_t;

typedef struct {
	mbedtls_cipher_type_t type;
	mbedtls_cipher_mode_t mode;
	unsigned int key_bitlen;
	const uint8_t *name;
	unsigned int iv_size;
	int flags;
	unsigned int block_size;
	const mbedtls_cipher_base_t *base;
} mbedtls_cipher_info_t;

typedef struct {
	const mbedtls_cipher_info_t *cipher_info;
	int key_bitlen;
	mbedtls_operation_t operation;
	void (*add_padding)(uint8_t *, size_t, size_t);
	int (*get_padding)(uint8_t *, size_t, size_t *);
	uint8_t unprocessed_data[16];
	size_t unprocessed_len;
	uint8_t iv[16];
	size_t iv_size;
	void *cipher_ctx;
} mbedtls_cipher_context_t;

typedef struct {
	int id;
	const uint8_t *name;
	mbedtls_cipher_type_t cipher;
	mbedtls_md_type_t mac;
	mbedtls_key_exchange_type_t key_exchange;
	int min_major_ver;
	int min_minor_ver;
	int max_major_ver;
	int max_minor_ver;
	uint8_t flags;
} mbedtls_ssl_ciphersuite_t __attribute__((aligned(4)));

typedef struct {
	const mbedtls_ssl_ciphersuite_t *ciphersuite_info;
	unsigned int keylen;
	size_t minlen;
	size_t ivlen;
	size_t fixed_ivlen;
	size_t maclen;
	uint8_t iv_enc[16];
	uint8_t iv_dec[16];
	uint8_t mac_enc[20];
	uint8_t mac_dec[20];
	mbedtls_md_context_t md_ctx_enc;
	mbedtls_md_context_t md_ctx_dec;
	mbedtls_cipher_context_t cipher_ctx_enc;
	mbedtls_cipher_context_t cipher_ctx_dec;
} mbedtls_ssl_transform;

typedef struct mbedtls_ssl_key_cert {
	mbedtls_x509_crt *cert;
	mbedtls_pk_context *key;
	struct mbedtls_ssl_key_cert *next;
} mbedtls_ssl_key_cert;

typedef void (*mbedtls_ssl_set_timer_t)(void *, uint32_t, uint32_t);
typedef int (*mbedtls_ssl_get_timer_t)(void *);

typedef struct mbedtls_ssl_handshake_params mbedtls_ssl_handshake_params;
typedef struct mbedtls_ssl_context mbedtls_ssl_context;
typedef struct mbedtls_ssl_config mbedtls_ssl_config;

struct mbedtls_ssl_config {
	const int *ciphersuite_list[4];
	void (*f_dbg)(void *, int, const uint8_t *, int, const uint8_t *);
	void *p_dbg;
	int (*f_rng)(void *, uint8_t *, size_t);
	void *p_rng;
	int (*f_get_cache)(void *, mbedtls_ssl_session *);
	int (*f_set_cache)(void *, const mbedtls_ssl_session *);
	void *p_cache;
	int (*f_sni)(void *, mbedtls_ssl_context *, const uint8_t *, size_t);
	void *p_sni;
	int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *);
	void *p_vrfy;
	int (*f_psk)(void *, mbedtls_ssl_context *, const uint8_t *, size_t);
	void *p_psk;
	const mbedtls_x509_crt_profile *cert_profile;
	mbedtls_ssl_key_cert *key_cert;
	mbedtls_x509_crt *ca_chain;
	mbedtls_x509_crl *ca_crl;
	const int *sig_hashes;
	uint8_t *psk;
	size_t psk_len;
	uint8_t *psk_identity;
	size_t psk_identity_len;
	const uint8_t **alpn_list;
	uint32_t read_timeout;
	uint8_t max_major_ver;
	uint8_t max_minor_ver;
	uint8_t min_major_ver;
	uint8_t min_minor_ver;
	uint32_t endpoint :1;
	uint32_t transport :1;
	uint32_t authmode :2;
	uint32_t allow_legacy_renegotiation :2;
	uint32_t arc4_disabled :1;
};

struct mbedtls_ssl_handshake_params {
	int sig_alg;
	int verify_sig_alg;
	uint8_t *psk;
	size_t psk_len;
	mbedtls_ssl_key_cert *key_cert;
	int sni_authmode;
	mbedtls_ssl_key_cert *sni_key_cert;
	mbedtls_x509_crt *sni_ca_chain;
	mbedtls_x509_crl *sni_ca_crl;
	mbedtls_md5_context fin_md5;
	mbedtls_sha1_context fin_sha1;
	mbedtls_sha256_context fin_sha256;
	mbedtls_sha512_context fin_sha512;
	void (*update_checksum)(mbedtls_ssl_context *, const uint8_t *, size_t);
	void (*calc_verify)(mbedtls_ssl_context *, uint8_t *);
	void (*calc_finished)(mbedtls_ssl_context *, uint8_t *, int);
	int (*tls_prf)(const uint8_t *, size_t, const uint8_t *, const uint8_t *, size_t, uint8_t *, size_t);
	size_t pmslen;
	uint8_t randbytes[64];
	uint8_t premaster[68];
	int resume;
	int max_major_ver;
	int max_minor_ver;
	int cli_exts;
};

struct mbedtls_ssl_context {
	const mbedtls_ssl_config *conf;
	int state;
	int major_ver;
	int minor_ver;
	mbedtls_ssl_send_t *f_send;
	mbedtls_ssl_recv_t *f_recv;
	mbedtls_ssl_recv_timeout_t *f_recv_timeout;
	void *p_bio;
	mbedtls_ssl_session *session_in;
	mbedtls_ssl_session *session_out;
	mbedtls_ssl_session *session;
	mbedtls_ssl_session *session_negotiate;
	mbedtls_ssl_handshake_params *handshake;
	mbedtls_ssl_transform *transform_in;
	mbedtls_ssl_transform *transform_out;
	mbedtls_ssl_transform *transform;
	mbedtls_ssl_transform *transform_negotiate;
	void *p_timer;
	mbedtls_ssl_set_timer_t *f_set_timer;
	mbedtls_ssl_get_timer_t *f_get_timer;
	uint8_t *in_buf;
	uint8_t *in_ctr;
	uint8_t *in_hdr;
	uint8_t *in_len;
	uint8_t *in_iv;
	uint8_t *in_msg;
	uint8_t *in_offt;
	int in_msgtype;
	size_t in_msglen;
	size_t in_left;
	size_t in_hslen;
	int nb_zero;
	int record_read;
	uint8_t *out_buf;
	uint8_t *out_ctr;
	uint8_t *out_hdr;
	uint8_t *out_len;
	uint8_t *out_iv;
	uint8_t *out_msg;
	int out_msgtype;
	size_t out_msglen;
	size_t out_left;
	int client_auth;
	uint8_t *hostname;
	const uint8_t *alpn_chosen;
	int secure_renegotiation;
};

typedef struct {
	int nr;
	uint32_t *rk;
	uint32_t buf[68];
} mbedtls_aes_context;

typedef struct {
	uint8_t counter[16];
	int reseed_counter;
	int prediction_resistance;
	size_t entropy_len;
	int reseed_interval;
	mbedtls_aes_context aes_ctx;
	int (*f_entropy)(void *, uint8_t *, size_t);
	void *p_entropy;
	mbedtls_threading_mutex_t mutex;
} mbedtls_ctr_drbg_context;

typedef int (*mbedtls_entropy_f_source_ptr)(void *, uint8_t *, size_t, size_t *);

typedef struct {
	mbedtls_entropy_f_source_ptr f_source;
	void *p_source;
	size_t size;
	size_t threshold;
	int strong;
} mbedtls_entropy_source_state;

typedef struct {
	mbedtls_sha512_context accumulator;
	int source_count;
	mbedtls_entropy_source_state source[20];
	mbedtls_threading_mutex_t mutex;
} mbedtls_entropy_context __attribute__((aligned(8)));


#endif /* EXT_API_SSL_H_ */
