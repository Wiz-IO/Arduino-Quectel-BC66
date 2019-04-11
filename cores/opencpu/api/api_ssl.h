#ifndef API_MBEDTLS_H
#define API_MBEDTLS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum
{
	MBEDTLS_MD_NONE = 0x0,
	MBEDTLS_MD_MD2 = 0x1,
	MBEDTLS_MD_MD4 = 0x2,
	MBEDTLS_MD_MD5 = 0x3,
	MBEDTLS_MD_SHA1 = 0x4,
	MBEDTLS_MD_SHA224 = 0x5,
	MBEDTLS_MD_SHA256 = 0x6,
	MBEDTLS_MD_SHA384 = 0x7,
	MBEDTLS_MD_SHA512 = 0x8,
	MBEDTLS_MD_RIPEMD160 = 0x9,
} mbedtls_md_type_t;

typedef enum
{
	MBEDTLS_PK_NONE = 0x0,
	MBEDTLS_PK_RSA = 0x1,
	MBEDTLS_PK_ECKEY = 0x2,
	MBEDTLS_PK_ECKEY_DH = 0x3,
	MBEDTLS_PK_ECDSA = 0x4,
	MBEDTLS_PK_RSA_ALT = 0x5,
	MBEDTLS_PK_RSASSA_PSS = 0x6,
} mbedtls_pk_type_t;

typedef enum
{
	MBEDTLS_PK_DEBUG_NONE = 0x0,
	MBEDTLS_PK_DEBUG_MPI = 0x1,
	MBEDTLS_PK_DEBUG_ECP = 0x2,
} mbedtls_pk_debug_type;

typedef enum
{
	MBEDTLS_OPERATION_NONE = 0xFF,
	MBEDTLS_DECRYPT = 0x0,
	MBEDTLS_ENCRYPT = 0x1,
} mbedtls_operation_t;

typedef enum
{
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

typedef enum
{
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

typedef enum
{
	MBEDTLS_MODE_NONE = 0x0,
	MBEDTLS_MODE_ECB = 0x1,
	MBEDTLS_MODE_CBC = 0x2,
	MBEDTLS_MODE_CFB = 0x3,
	MBEDTLS_MODE_OFB = 0x4,
	MBEDTLS_MODE_CTR = 0x5,
	MBEDTLS_MODE_GCM = 0x6,
	MBEDTLS_MODE_STREAM = 0x7,
	MBEDTLS_MODE_CCM = 0x8,
} mbedtls_cipher_mode_t;

typedef enum
{
	MBEDTLS_CIPHER_ID_NONE = 0x0,
	MBEDTLS_CIPHER_ID_NULL = 0x1,
	MBEDTLS_CIPHER_ID_AES = 0x2,
	MBEDTLS_CIPHER_ID_DES = 0x3,
	MBEDTLS_CIPHER_ID_3DES = 0x4,
	MBEDTLS_CIPHER_ID_CAMELLIA = 0x5,
	MBEDTLS_CIPHER_ID_BLOWFISH = 0x6,
	MBEDTLS_CIPHER_ID_ARC4 = 0x7,
} mbedtls_cipher_id_t;

typedef enum
{
	MBEDTLS_PADDING_PKCS7 = 0x0,
	MBEDTLS_PADDING_ONE_AND_ZEROS = 0x1,
	MBEDTLS_PADDING_ZEROS_AND_LEN = 0x2,
	MBEDTLS_PADDING_ZEROS = 0x3,
	MBEDTLS_PADDING_NONE = 0x4,
} mbedtls_cipher_padding_t;

typedef enum
{
	MBEDTLS_KEY_LENGTH_NONE = 0x0,
	MBEDTLS_KEY_LENGTH_DES = 0x40,
	MBEDTLS_KEY_LENGTH_DES_EDE = 0x80,
	MBEDTLS_KEY_LENGTH_DES_EDE3 = 0xC0,
} mbedtls_key_length;

typedef enum
{
	MBEDTLS_SSL_HELLO_REQUEST = 0x0,
	MBEDTLS_SSL_CLIENT_HELLO = 0x1,
	MBEDTLS_SSL_SERVER_HELLO = 0x2,
	MBEDTLS_SSL_SERVER_CERTIFICATE = 0x3,
	MBEDTLS_SSL_SERVER_KEY_EXCHANGE = 0x4,
	MBEDTLS_SSL_CERTIFICATE_REQUEST = 0x5,
	MBEDTLS_SSL_SERVER_HELLO_DONE = 0x6,
	MBEDTLS_SSL_CLIENT_CERTIFICATE = 0x7,
	MBEDTLS_SSL_CLIENT_KEY_EXCHANGE = 0x8,
	MBEDTLS_SSL_CERTIFICATE_VERIFY = 0x9,
	MBEDTLS_SSL_CLIENT_CHANGE_CIPHER_SPEC = 0xA,
	MBEDTLS_SSL_CLIENT_FINISHED = 0xB,
	MBEDTLS_SSL_SERVER_CHANGE_CIPHER_SPEC = 0xC,
	MBEDTLS_SSL_SERVER_FINISHED = 0xD,
	MBEDTLS_SSL_FLUSH_BUFFERS = 0xE,
	MBEDTLS_SSL_HANDSHAKE_WRAPUP = 0xF,
	MBEDTLS_SSL_HANDSHAKE_OVER = 0x10,
	MBEDTLS_SSL_SERVER_NEW_SESSION_TICKET = 0x11,
	MBEDTLS_SSL_SERVER_HELLO_VERIFY_REQUEST_SENT = 0x12,
} mbedtls_ssl_states;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct mbedtls_ssl_session mbedtls_ssl_session;
typedef struct mbedtls_ssl_context mbedtls_ssl_context;
typedef struct mbedtls_ssl_config mbedtls_ssl_config;
typedef struct mbedtls_ssl_handshake_params mbedtls_ssl_handshake_params;
typedef struct mbedtls_ssl_transform mbedtls_ssl_transform;
typedef struct mbedtls_ssl_key_cert mbedtls_ssl_key_cert;
typedef struct mbedtls_ssl_ciphersuite_t mbedtls_ssl_ciphersuite_t;
typedef struct mbedtls_md_info_t mbedtls_md_info_t;
typedef struct mbedtls_cipher_context_t mbedtls_cipher_context_t;
typedef struct mbedtls_cipher_info_t mbedtls_cipher_info_t;

typedef struct
{
	/*SemaphoreHandle_t*/ void *mutex;
	unsigned char is_valid;
} mbedtls_threading_mutex_t __attribute__((aligned(4)));

typedef struct
{
	mbedtls_pk_debug_type type;
	const unsigned char *name;
	void *value;
} mbedtls_pk_debug_item;

typedef struct
{
	mbedtls_pk_type_t type;
	const unsigned char *name;
	size_t (*get_bitlen)(const void *);
	int (*can_do)(mbedtls_pk_type_t);
	int (*verify_func)(void *, mbedtls_md_type_t, const unsigned char *, size_t, const unsigned char *, size_t);
	int (*sign_func)(void *, mbedtls_md_type_t, const unsigned char *, size_t, unsigned char *, size_t *, int (*)(void *, unsigned char *, size_t), void *);
	int (*decrypt_func)(void *, const unsigned char *, size_t, unsigned char *, size_t *, size_t, int (*)(void *, unsigned char *, size_t), void *);
	int (*encrypt_func)(void *, const unsigned char *, size_t, unsigned char *, size_t *, size_t, int (*)(void *, unsigned char *, size_t), void *);
	int (*check_pair_func)(const void *, const void *);
	void *(*ctx_alloc_func)(void);
	void (*ctx_free_func)(void *);
	void (*debug_func)(const void *, mbedtls_pk_debug_item *);
} mbedtls_pk_info_t;

typedef struct
{
	const mbedtls_pk_info_t *pk_info;
	void *pk_ctx;
} mbedtls_pk_context;

typedef struct
{
	int tag;
	size_t len;
	unsigned char *p;
} mbedtls_asn1_buf;

typedef struct mbedtls_asn1_sequence
{
	mbedtls_asn1_buf buf;
	struct mbedtls_asn1_sequence *next;
} mbedtls_asn1_sequence;

typedef struct mbedtls_asn1_named_data
{
	mbedtls_asn1_buf oid;
	mbedtls_asn1_buf val;
	struct mbedtls_asn1_named_data *next;
	unsigned char next_merged;
} mbedtls_asn1_named_data __attribute__((aligned(4)));

typedef mbedtls_asn1_buf mbedtls_x509_buf;
typedef mbedtls_asn1_named_data mbedtls_x509_name;
typedef mbedtls_asn1_sequence mbedtls_x509_sequence;

typedef struct mbedtls_x509_time
{
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
} mbedtls_x509_time;

typedef struct mbedtls_x509_crl_entry
{
	mbedtls_x509_buf raw;
	mbedtls_x509_buf serial;
	mbedtls_x509_time revocation_date;
	mbedtls_x509_buf entry_ext;
	struct mbedtls_x509_crl_entry *next;
} mbedtls_x509_crl_entry;

typedef struct mbedtls_x509_crl
{
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

typedef struct mbedtls_x509_crt
{
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
	unsigned char ns_cert_type;
	mbedtls_x509_buf sig;
	mbedtls_md_type_t sig_md;
	mbedtls_pk_type_t sig_pk;
	void *sig_opts;
	struct mbedtls_x509_crt *next;
} mbedtls_x509_crt;

typedef struct
{
	uint32_t allowed_mds;
	uint32_t allowed_pks;
	uint32_t allowed_curves;
	uint32_t rsa_min_bitlen;
} mbedtls_x509_crt_profile;

typedef int mbedtls_ssl_send_t(void *, const unsigned char *, size_t);
typedef int mbedtls_ssl_recv_t(void *, unsigned char *, size_t);
typedef int mbedtls_ssl_recv_timeout_t(void *, unsigned char *, size_t, uint32_t);
typedef void mbedtls_ssl_set_timer_t(void *, uint32_t, uint32_t);
typedef int mbedtls_ssl_get_timer_t(void *);

struct mbedtls_ssl_session //typedef
{
	int ciphersuite;
	int compression;
	size_t id_len;
	unsigned char id[32];
	unsigned char master[48];
	mbedtls_x509_crt *peer_cert;
	uint32_t verify_result;
};

struct mbedtls_ssl_context //typedef
{
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
	unsigned char *in_buf;
	unsigned char *in_ctr;
	unsigned char *in_hdr;
	unsigned char *in_len;
	unsigned char *in_iv;
	unsigned char *in_msg;
	unsigned char *in_offt;
	int in_msgtype;
	size_t in_msglen;
	size_t in_left;
	size_t in_hslen;
	int nb_zero;
	int record_read;
	unsigned char *out_buf;
	unsigned char *out_ctr;
	unsigned char *out_hdr;
	unsigned char *out_len;
	unsigned char *out_iv;
	unsigned char *out_msg;
	int out_msgtype;
	size_t out_msglen;
	size_t out_left;
	int client_auth;
	unsigned char *hostname;
	const unsigned char *alpn_chosen;
	int secure_renegotiation;
};

struct mbedtls_ssl_config
{
	const int *ciphersuite_list[4];
	void (*f_dbg)(void *, int, const unsigned char *, int, const unsigned char *);
	void *p_dbg;
	int (*f_rng)(void *, unsigned char *, size_t);
	void *p_rng;
	int (*f_get_cache)(void *, mbedtls_ssl_session *);
	int (*f_set_cache)(void *, const mbedtls_ssl_session *);
	void *p_cache;
	int (*f_sni)(void *, mbedtls_ssl_context *, const unsigned char *, size_t);
	void *p_sni;
	int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *);
	void *p_vrfy;
	int (*f_psk)(void *, mbedtls_ssl_context *, const unsigned char *, size_t);
	void *p_psk;
	const mbedtls_x509_crt_profile *cert_profile;
	mbedtls_ssl_key_cert *key_cert;
	mbedtls_x509_crt *ca_chain;
	mbedtls_x509_crl *ca_crl;
	const int *sig_hashes;
	unsigned char *psk;
	size_t psk_len;
	unsigned char *psk_identity;
	size_t psk_identity_len;
	const unsigned char **alpn_list;
	uint32_t read_timeout;
	unsigned char max_major_ver;
	unsigned char max_minor_ver;
	unsigned char min_major_ver;
	unsigned char min_minor_ver;
	unsigned int endpoint : 1;
	unsigned int transport : 1;
	unsigned int authmode : 2;
	unsigned int allow_legacy_renegotiation : 2;
	unsigned int arc4_disabled : 1;
};

typedef struct
{
	uint32_t total[2];
	uint32_t state[4];
	unsigned char buffer[64];
} mbedtls_md5_context;

typedef struct
{
	uint32_t total[2];
	uint32_t state[5];
	unsigned char buffer[64];
} mbedtls_sha1_context;

typedef struct
{
	uint32_t total[2];
	uint32_t state[8];
	unsigned char buffer[64];
	int is224;
} mbedtls_sha256_context;

typedef struct
{
	uint64_t total[2];
	uint64_t state[8];
	unsigned char buffer[128];
	int is384;
} mbedtls_sha512_context __attribute__((aligned(8)));

struct mbedtls_ssl_handshake_params //typedef
{
	int sig_alg;
	int verify_sig_alg;
	unsigned char *psk;
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
	void (*update_checksum)(mbedtls_ssl_context *, const unsigned char *, size_t);
	void (*calc_verify)(mbedtls_ssl_context *, unsigned char *);
	void (*calc_finished)(mbedtls_ssl_context *, unsigned char *, int);
	int (*tls_prf)(const unsigned char *, size_t, const unsigned char *, const unsigned char *, size_t, unsigned char *, size_t);
	size_t pmslen;
	unsigned char randbytes[64];
	unsigned char premaster[68];
	int resume;
	int max_major_ver;
	int max_minor_ver;
	int cli_exts;
};

typedef struct
{
	const mbedtls_md_info_t *md_info;
	void *md_ctx;
	void *hmac_ctx;
} mbedtls_md_context_t;

struct mbedtls_cipher_context_t //typedef
{
	const mbedtls_cipher_info_t *cipher_info;
	int key_bitlen;
	mbedtls_operation_t operation;
	void (*add_padding)(unsigned char *, size_t, size_t);
	int (*get_padding)(unsigned char *, size_t, size_t *);
	unsigned char unprocessed_data[16];
	size_t unprocessed_len;
	unsigned char iv[16];
	size_t iv_size;
	void *cipher_ctx;
};

struct mbedtls_ssl_transform //typedef
{
	const mbedtls_ssl_ciphersuite_t *ciphersuite_info;
	unsigned int keylen;
	size_t minlen;
	size_t ivlen;
	size_t fixed_ivlen;
	size_t maclen;
	unsigned char iv_enc[16];
	unsigned char iv_dec[16];
	unsigned char mac_enc[20];
	unsigned char mac_dec[20];
	mbedtls_md_context_t md_ctx_enc;
	mbedtls_md_context_t md_ctx_dec;
	mbedtls_cipher_context_t cipher_ctx_enc;
	mbedtls_cipher_context_t cipher_ctx_dec;
};

struct mbedtls_ssl_key_cert //typedef
{
	mbedtls_x509_crt *cert;
	mbedtls_pk_context *key;
	mbedtls_ssl_key_cert *next;
};

struct __attribute__((aligned(4))) mbedtls_ssl_ciphersuite_t //typedef
{
	int id;
	const unsigned char *name;
	mbedtls_cipher_type_t cipher;
	mbedtls_md_type_t mac;
	mbedtls_key_exchange_type_t key_exchange;
	int min_major_ver;
	int min_minor_ver;
	int max_major_ver;
	int max_minor_ver;
	unsigned char flags;
};

struct mbedtls_md_info_t //typedef
{
	mbedtls_md_type_t type;
	const unsigned char *name;
	int size;
	int block_size;
	void (*starts_func)(void *);
	void (*update_func)(void *, const unsigned char *, size_t);
	void (*finish_func)(void *, unsigned char *);
	void (*digest_func)(const unsigned char *, size_t, unsigned char *);
	void *(*ctx_alloc_func)(void);
	void (*ctx_free_func)(void *);
	void (*clone_func)(void *, const void *);
	void (*process_func)(void *, const unsigned char *);
};

typedef struct
{
	mbedtls_cipher_id_t cipher;
	int (*ecb_func)(void *, mbedtls_operation_t, const unsigned char *, unsigned char *);
	int (*cbc_func)(void *, mbedtls_operation_t, size_t, unsigned char *, const unsigned char *, unsigned char *);
	int (*stream_func)(void *, size_t, const unsigned char *, unsigned char *);
	int (*setkey_enc_func)(void *, const unsigned char *, unsigned int);
	int (*setkey_dec_func)(void *, const unsigned char *, unsigned int);
	void *(*ctx_alloc_func)(void);
	void (*ctx_free_func)(void *);
} mbedtls_cipher_base_t;

struct mbedtls_cipher_info_t //def
{
	mbedtls_cipher_type_t type;
	mbedtls_cipher_mode_t mode;
	unsigned int key_bitlen;
	const unsigned char *name;
	unsigned int iv_size;
	int flags;
	unsigned int block_size;
	const mbedtls_cipher_base_t *base;
};

typedef struct
{
	int fd;
} mbedtls_net_context;

typedef int (*mbedtls_entropy_f_source_ptr)(void *, unsigned char *, size_t, size_t *);

typedef struct
{
	mbedtls_entropy_f_source_ptr f_source;
	void *p_source;
	size_t size;
	size_t threshold;
	int strong;
} mbedtls_entropy_source_state;

typedef struct
{
	mbedtls_sha512_context accumulator;
	int source_count;
	mbedtls_entropy_source_state source[20];
	mbedtls_threading_mutex_t mutex;
} mbedtls_entropy_context __attribute__((aligned(8)));

typedef struct
{
	int nr;
	uint32_t *rk;
	uint32_t buf[68];
} mbedtls_aes_context;

typedef struct
{
	unsigned char counter[16];
	int reseed_counter;
	int prediction_resistance;
	size_t entropy_len;
	int reseed_interval;
	mbedtls_aes_context aes_ctx;
	int (*f_entropy)(void *, unsigned char *, size_t);
	void *p_entropy;
	mbedtls_threading_mutex_t mutex;
} mbedtls_ctr_drbg_context;

typedef struct
{
	int x;
	int y;
	unsigned char m[256];
} mbedtls_arc4_context;

typedef uint32_t mbedtls_mpi_uint;

typedef struct
{
	int s;
	size_t n;
	mbedtls_mpi_uint *p;
	mbedtls_mpi_uint limbs[2];
} mbedtls_mpi;

typedef struct
{
	size_t len;
	unsigned char unused_bits;
	unsigned char *p;
} mbedtls_asn1_bitstring;

typedef int32_t mbedtls_mpi_sint;

typedef struct
{
	mbedtls_cipher_type_t type;
	const mbedtls_cipher_info_t *info;
} mbedtls_cipher_definition_t;

typedef struct
{
	uint32_t sk[32];
} mbedtls_des_context;

typedef struct
{
	uint32_t sk[96];
} mbedtls_des3_context;

typedef struct
{
	const unsigned char *asn1;
	size_t asn1_len;
	const unsigned char *name;
	const unsigned char *description;
} mbedtls_oid_descriptor_t;

typedef struct
{
	mbedtls_oid_descriptor_t descriptor;
	const unsigned char *short_name;
} oid_x520_attr_t;

typedef struct
{
	mbedtls_oid_descriptor_t descriptor;
	int ext_type;
} oid_x509_ext_t;

typedef struct
{
	mbedtls_oid_descriptor_t descriptor;
	mbedtls_md_type_t md_alg;
	mbedtls_pk_type_t pk_alg;
} oid_sig_alg_t __attribute__((aligned(4)));

typedef struct
{
	mbedtls_oid_descriptor_t descriptor;
	mbedtls_pk_type_t pk_alg;
} oid_pk_alg_t __attribute__((aligned(4)));

typedef struct
{
	mbedtls_oid_descriptor_t descriptor;
	mbedtls_cipher_type_t cipher_alg;
} oid_cipher_alg_t __attribute__((aligned(4)));

typedef struct
{
	mbedtls_oid_descriptor_t descriptor;
	mbedtls_md_type_t md_alg;
} oid_md_alg_t __attribute__((aligned(4)));

typedef struct
{
	unsigned char *buf;
	size_t buflen;
	unsigned char *info;
} mbedtls_pem_context;

typedef struct
{
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

typedef struct
{
	mbedtls_md_type_t mgf1_hash_id;
	int expected_salt_len;
} mbedtls_pk_rsassa_pss_options;

typedef mbedtls_asn1_bitstring mbedtls_x509_bitstring;

typedef struct
{
	int code;
	const unsigned char *string;
} x509_crt_verify_string;

/************************************************************************************************/

void mbedtls_aes_init(mbedtls_aes_context *ctx);
void mbedtls_aes_free(mbedtls_aes_context *ctx);
int mbedtls_aes_setkey_enc(mbedtls_aes_context *ctx, const unsigned char *key, unsigned int keybits);
int mbedtls_aes_setkey_dec(mbedtls_aes_context *ctx, const unsigned char *key, unsigned int keybits);
void mbedtls_aes_encrypt(mbedtls_aes_context *ctx, const unsigned char *input, unsigned char *output);
void mbedtls_aes_decrypt(mbedtls_aes_context *ctx, const unsigned char *input, unsigned char *output);
int mbedtls_aes_crypt_ecb(mbedtls_aes_context *ctx, int mode, const unsigned char *input, unsigned char *output);
int mbedtls_aes_crypt_cbc(mbedtls_aes_context *ctx, int mode, size_t length, unsigned char *iv, const unsigned char *input, unsigned char *output);
void mbedtls_arc4_init(mbedtls_arc4_context *ctx);
void mbedtls_arc4_free(mbedtls_arc4_context *ctx);
void mbedtls_arc4_setup(mbedtls_arc4_context *ctx, const unsigned char *key, unsigned int keylen);
int mbedtls_arc4_crypt(mbedtls_arc4_context *ctx, size_t length, const unsigned char *input, unsigned char *output);
int mbedtls_asn1_get_len(unsigned char **p, const unsigned char *end, size_t *len);
int mbedtls_asn1_get_tag(unsigned char **p, const unsigned char *end, size_t *len, int tag);
int mbedtls_asn1_get_bool(unsigned char **p, const unsigned char *end, int *val);
int mbedtls_asn1_get_int(unsigned char **p, const unsigned char *end, int *val);
int mbedtls_asn1_get_mpi(unsigned char **p, const unsigned char *end, mbedtls_mpi *X);
int mbedtls_asn1_get_bitstring(unsigned char **p, const unsigned char *end, mbedtls_asn1_bitstring *bs);
int mbedtls_asn1_get_bitstring_null(unsigned char **p, const unsigned char *end, size_t *len);
int mbedtls_asn1_get_sequence_of(unsigned char **p, const unsigned char *end, mbedtls_asn1_sequence *cur, int tag);
int mbedtls_asn1_get_alg(unsigned char **p, const unsigned char *end, mbedtls_asn1_buf *alg, mbedtls_asn1_buf *params);
int mbedtls_base64_encode(unsigned char *dst, size_t dlen, size_t *olen, const unsigned char *src, size_t slen);
int mbedtls_base64_decode(unsigned char *dst, size_t dlen, size_t *olen, const unsigned char *src, size_t slen);
void mpi_sub_hlp(size_t n, mbedtls_mpi_uint *s, mbedtls_mpi_uint *d);
void mpi_mul_hlp(size_t i, mbedtls_mpi_uint *s, mbedtls_mpi_uint *d, mbedtls_mpi_uint b);
int mbedtls_mpi_grow(mbedtls_mpi *X, size_t nblimbs);
void mbedtls_mpi_init(mbedtls_mpi *X);
void mbedtls_mpi_free(mbedtls_mpi *X);
int mbedtls_mpi_grow(mbedtls_mpi *X, size_t nblimbs);
int mbedtls_mpi_copy(mbedtls_mpi *X, const mbedtls_mpi *Y);
int mbedtls_mpi_lset(mbedtls_mpi *X, mbedtls_mpi_sint z);
size_t mbedtls_mpi_lsb(const mbedtls_mpi *X);
size_t mbedtls_mpi_bitlen(const mbedtls_mpi *X);
size_t mbedtls_mpi_size(const mbedtls_mpi *X);
int mbedtls_mpi_read_binary(mbedtls_mpi *X, const unsigned char *buf, size_t buflen);
int mbedtls_mpi_write_binary(const mbedtls_mpi *X, unsigned char *buf, size_t buflen);
int mbedtls_mpi_shift_l(mbedtls_mpi *X, size_t count);
int mbedtls_mpi_shift_r(mbedtls_mpi *X, size_t count);
int mbedtls_mpi_cmp_abs(const mbedtls_mpi *X, const mbedtls_mpi *Y);
int mpi_montmul(mbedtls_mpi *A, const mbedtls_mpi *B, const mbedtls_mpi *N, mbedtls_mpi_uint mm, const mbedtls_mpi *T);
int mbedtls_mpi_cmp_mpi(const mbedtls_mpi *X, const mbedtls_mpi *Y);
int mbedtls_mpi_cmp_int(const mbedtls_mpi *X, mbedtls_mpi_sint z);
int mbedtls_mpi_add_abs(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B);
int mbedtls_mpi_sub_abs(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B);
int mbedtls_mpi_add_mpi(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B);
int mbedtls_mpi_sub_mpi(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B);
int mbedtls_mpi_sub_int(mbedtls_mpi *X, const mbedtls_mpi *A, mbedtls_mpi_sint b);
int mbedtls_mpi_mul_mpi(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B);
int mbedtls_mpi_mul_int(mbedtls_mpi *X, const mbedtls_mpi *A, mbedtls_mpi_uint b);
int mbedtls_mpi_div_mpi(mbedtls_mpi *Q, mbedtls_mpi *R, const mbedtls_mpi *A, const mbedtls_mpi *B);
int mbedtls_mpi_mod_mpi(mbedtls_mpi *R, const mbedtls_mpi *A, const mbedtls_mpi *B);
int mbedtls_mpi_exp_mod(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *E, const mbedtls_mpi *N, mbedtls_mpi *_RR);
int mbedtls_mpi_gcd(mbedtls_mpi *G, const mbedtls_mpi *A, const mbedtls_mpi *B);
int mbedtls_mpi_fill_random(mbedtls_mpi *X, size_t size, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng);
int mbedtls_mpi_inv_mod(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *N);
unsigned int mbedtls_cipher_get_block_size(const mbedtls_cipher_context_t *ctx);
int get_no_padding(unsigned char *input, size_t input_len, size_t *data_len);
const mbedtls_cipher_info_t *mbedtls_cipher_info_from_type(const mbedtls_cipher_type_t cipher_type);
void mbedtls_cipher_init(mbedtls_cipher_context_t *ctx);
void mbedtls_cipher_free(mbedtls_cipher_context_t *ctx);
int mbedtls_cipher_setkey(mbedtls_cipher_context_t *ctx, const unsigned char *key, int key_bitlen, const mbedtls_operation_t operation);
int mbedtls_cipher_set_iv(mbedtls_cipher_context_t *ctx, const unsigned char *iv, size_t iv_len);
int mbedtls_cipher_reset(mbedtls_cipher_context_t *ctx);
int mbedtls_cipher_update(mbedtls_cipher_context_t *ctx, const unsigned char *input, size_t ilen, unsigned char *output, size_t *olen);
int mbedtls_cipher_finish(mbedtls_cipher_context_t *ctx, unsigned char *output, size_t *olen);
int mbedtls_cipher_set_padding_mode(mbedtls_cipher_context_t *ctx, mbedtls_cipher_padding_t mode);
int mbedtls_cipher_setup(mbedtls_cipher_context_t *ctx, const mbedtls_cipher_info_t *cipher_info);
int mbedtls_cipher_crypt(mbedtls_cipher_context_t *ctx, const unsigned char *iv, size_t iv_len, const unsigned char *input, size_t ilen, unsigned char *output, size_t *olen);
void des3_ctx_free(void *ctx);
int des3_set3key_dec_wrap(void *ctx, const unsigned char *key, unsigned int key_bitlen);
int des3_set3key_enc_wrap(void *ctx, const unsigned char *key, unsigned int key_bitlen);
int des3_crypt_cbc_wrap(void *ctx, mbedtls_operation_t operation, size_t length, unsigned char *iv, const unsigned char *input, unsigned char *output);
int des3_crypt_ecb_wrap(void *ctx, mbedtls_operation_t operation, const unsigned char *input, unsigned char *output);
int des3_set2key_dec_wrap(void *ctx, const unsigned char *key, unsigned int key_bitlen);
int des3_set2key_enc_wrap(void *ctx, const unsigned char *key, unsigned int key_bitlen);
void des_ctx_free(void *ctx);
int des_setkey_dec_wrap(void *ctx, const unsigned char *key, unsigned int key_bitlen);
int des_setkey_enc_wrap(void *ctx, const unsigned char *key, unsigned int key_bitlen);
int des_crypt_cbc_wrap(void *ctx, mbedtls_operation_t operation, size_t length, unsigned char *iv, const unsigned char *input, unsigned char *output);
int des_crypt_ecb_wrap(void *ctx, mbedtls_operation_t operation, const unsigned char *input, unsigned char *output);
void arc4_ctx_free(void *ctx);
int arc4_setkey_wrap(void *ctx, const unsigned char *key, unsigned int key_bitlen);
int arc4_crypt_stream_wrap(void *ctx, size_t length, const unsigned char *input, unsigned char *output);
void aes_ctx_free(void *ctx);
int aes_setkey_dec_wrap(void *ctx, const unsigned char *key, unsigned int key_bitlen);
int aes_setkey_enc_wrap(void *ctx, const unsigned char *key, unsigned int key_bitlen);
int aes_crypt_cbc_wrap(void *ctx, mbedtls_operation_t operation, size_t length, unsigned char *iv, const unsigned char *input, unsigned char *output);
int aes_crypt_ecb_wrap(void *ctx, mbedtls_operation_t operation, const unsigned char *input, unsigned char *output);
int block_cipher_df(unsigned char *output, const unsigned char *data, size_t data_len);
int ctr_drbg_update_internal(mbedtls_ctr_drbg_context *ctx, const unsigned char *data);
void mbedtls_ctr_drbg_init(mbedtls_ctr_drbg_context *ctx);
void mbedtls_ctr_drbg_free(mbedtls_ctr_drbg_context *ctx);
int mbedtls_ctr_drbg_reseed(mbedtls_ctr_drbg_context *ctx, const unsigned char *additional, size_t len);
int mbedtls_ctr_drbg_seed_entropy_len(mbedtls_ctr_drbg_context *ctx, int (*f_entropy)(void *, unsigned char *, size_t), void *p_entropy, const unsigned char *custom, size_t len, size_t entropy_len);
int mbedtls_ctr_drbg_seed(mbedtls_ctr_drbg_context *ctx, int (*f_entropy)(void *, unsigned char *, size_t), void *p_entropy, const unsigned char *custom, size_t len);
int mbedtls_ctr_drbg_random_with_add(void *p_rng, unsigned char *output, size_t output_len, const unsigned char *additional, size_t add_len);
int mbedtls_ctr_drbg_random(void *p_rng, unsigned char *output, size_t output_len);
void debug_send_line(const mbedtls_ssl_context *ssl, int level, const unsigned char *file, int line, const unsigned char *str);
void mbedtls_debug_set_threshold(int threshold);
void mbedtls_debug_print_ret(const mbedtls_ssl_context *ssl, int level, const unsigned char *file, int line, const unsigned char *text, int ret);
void mbedtls_debug_print_buf(const mbedtls_ssl_context *ssl, int level, const unsigned char *file, int line, const unsigned char *text, const unsigned char *buf, size_t len);
void mbedtls_debug_print_mpi(const mbedtls_ssl_context *ssl, int level, const unsigned char *file, int line, const unsigned char *text, const mbedtls_mpi *X);
void mbedtls_debug_print_crt(const mbedtls_ssl_context *ssl, int level, const unsigned char *file, int line, const unsigned char *text, const mbedtls_x509_crt *crt);
void mbedtls_zeroize(void *v, size_t n);
void mbedtls_des_init(mbedtls_des_context *ctx);
void mbedtls_des_free(mbedtls_des_context *ctx);
void mbedtls_des3_init(mbedtls_des3_context *ctx);
void mbedtls_des3_free(mbedtls_des3_context *ctx);
void mbedtls_des_setkey(uint32_t *SK, const unsigned char *key);
void des3_set2key(uint32_t *esk, uint32_t *dsk, const unsigned char *key);
void des3_set3key(uint32_t *esk, uint32_t *dsk, const unsigned char *key);
int mbedtls_des_setkey_enc(mbedtls_des_context *ctx, const unsigned char *key);
int mbedtls_des_setkey_dec(mbedtls_des_context *ctx, const unsigned char *key);
int mbedtls_des3_set2key_enc(mbedtls_des3_context *ctx, const unsigned char *key);
int mbedtls_des3_set2key_dec(mbedtls_des3_context *ctx, const unsigned char *key);
int mbedtls_des3_set3key_enc(mbedtls_des3_context *ctx, const unsigned char *key);
int mbedtls_des3_set3key_dec(mbedtls_des3_context *ctx, const unsigned char *key);
int mbedtls_des_crypt_ecb(mbedtls_des_context *ctx, const unsigned char *input, unsigned char *output);
int mbedtls_des_crypt_cbc(mbedtls_des_context *ctx, int mode, size_t length, unsigned char *iv, const unsigned char *input, unsigned char *output);
int mbedtls_des3_crypt_ecb(mbedtls_des3_context *ctx, const unsigned char *input, unsigned char *output);
int mbedtls_des3_crypt_cbc(mbedtls_des3_context *ctx, int mode, size_t length, unsigned char *iv, const unsigned char *input, unsigned char *output);
int entropy_update(mbedtls_entropy_context *ctx, unsigned char source_id, const unsigned char *data, size_t len);
int entropy_gather_internal(mbedtls_entropy_context *ctx);
void mbedtls_entropy_free(mbedtls_entropy_context *ctx);
int mbedtls_entropy_add_source(mbedtls_entropy_context *ctx, mbedtls_entropy_f_source_ptr f_source, void *p_source, size_t threshold, int strong);
void mbedtls_entropy_init(mbedtls_entropy_context *ctx);
int mbedtls_entropy_func(void *data, unsigned char *output, size_t len);
int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen);
void mbedtls_md5_init(mbedtls_md5_context *ctx);
void mbedtls_md5_free(mbedtls_md5_context *ctx);
void mbedtls_md5_clone(mbedtls_md5_context *dst, const mbedtls_md5_context *src);
void mbedtls_md5_starts(mbedtls_md5_context *ctx);
void mbedtls_md5_process(mbedtls_md5_context *ctx, const unsigned char *data);
void mbedtls_md5_update(mbedtls_md5_context *ctx, const unsigned char *input, size_t ilen);
void mbedtls_md5_update(mbedtls_md5_context *ctx, const unsigned char *input, size_t ilen);
void mbedtls_md5_finish(mbedtls_md5_context *ctx, unsigned char *output);
void mbedtls_md5(const unsigned char *input, size_t ilen, unsigned char *output);
const mbedtls_md_info_t *mbedtls_md_info_from_type(mbedtls_md_type_t md_type);
void mbedtls_md_init(mbedtls_md_context_t *ctx);
void mbedtls_md_free(mbedtls_md_context_t *ctx);
int mbedtls_md_setup(mbedtls_md_context_t *ctx, const mbedtls_md_info_t *md_info, int hmac);
int mbedtls_md_starts(mbedtls_md_context_t *ctx);
int mbedtls_md_update(mbedtls_md_context_t *ctx, const unsigned char *input, size_t ilen);
int mbedtls_md_finish(mbedtls_md_context_t *ctx, unsigned char *output);
int mbedtls_md(const mbedtls_md_info_t *md_info, const unsigned char *input, size_t ilen, unsigned char *output);
int mbedtls_md_hmac_starts(mbedtls_md_context_t *ctx, const unsigned char *key, size_t keylen);
int mbedtls_md_hmac_update(mbedtls_md_context_t *ctx, const unsigned char *input, size_t ilen);
int mbedtls_md_hmac_finish(mbedtls_md_context_t *ctx, unsigned char *output);
int mbedtls_md_hmac_reset(mbedtls_md_context_t *ctx);
int mbedtls_md_process(mbedtls_md_context_t *ctx, const unsigned char *data);
unsigned char mbedtls_md_get_size(const mbedtls_md_info_t *md_info);
mbedtls_md_type_t mbedtls_md_get_type(const mbedtls_md_info_t *md_info);
void md5_process_wrap(void *ctx, const unsigned char *data);
void md5_clone_wrap(void *dst, const void *src);
void md5_ctx_free(void *ctx);
void md5_finish_wrap(void *ctx, unsigned char *output);
void md5_update_wrap(void *ctx, const unsigned char *input, size_t ilen);
void md5_starts_wrap(void *ctx);
void sha1_process_wrap(void *ctx, const unsigned char *data);
void sha1_clone_wrap(void *dst, const void *src);
void sha1_ctx_free(void *ctx);
void sha1_finish_wrap(void *ctx, unsigned char *output);
void sha1_update_wrap(void *ctx, const unsigned char *input, size_t ilen);
void sha1_starts_wrap(void *ctx);
void sha224_process_wrap(void *ctx, const unsigned char *data);
void sha224_clone_wrap(void *dst, const void *src);
void sha224_ctx_free(void *ctx);
void sha224_wrap(const unsigned char *input, size_t ilen, unsigned char *output);
void sha256_wrap(const unsigned char *input, size_t ilen, unsigned char *output);
void sha224_finish_wrap(void *ctx, unsigned char *output);
void sha224_update_wrap(void *ctx, const unsigned char *input, size_t ilen);
void sha224_starts_wrap(void *ctx);
void sha256_starts_wrap(void *ctx);
void sha384_process_wrap(void *ctx, const unsigned char *data);
void sha384_clone_wrap(void *dst, const void *src);
void sha384_ctx_free(void *ctx);
void sha384_wrap(const unsigned char *input, size_t ilen, unsigned char *output);
void sha512_wrap(const unsigned char *input, size_t ilen, unsigned char *output);
void sha384_finish_wrap(void *ctx, unsigned char *output);
void sha384_update_wrap(void *ctx, const unsigned char *input, size_t ilen);
void sha384_starts_wrap(void *ctx);
void sha512_starts_wrap(void *ctx);
const oid_sig_alg_t *oid_sig_alg_from_asn1(const mbedtls_asn1_buf *oid);
int mbedtls_oid_get_attr_short_name(const mbedtls_asn1_buf *oid, const unsigned char **short_name);
int mbedtls_oid_get_x509_ext_type(const mbedtls_asn1_buf *oid, int *ext_type);
int mbedtls_oid_get_extended_key_usage(const mbedtls_asn1_buf *oid, const unsigned char **description);
int mbedtls_oid_get_sig_alg_desc(const mbedtls_asn1_buf *oid, const unsigned char **description);
int mbedtls_oid_get_sig_alg(const mbedtls_asn1_buf *oid, mbedtls_md_type_t *md_alg, mbedtls_pk_type_t *pk_alg);
int mbedtls_oid_get_pk_alg(const mbedtls_asn1_buf *oid, mbedtls_pk_type_t *pk_alg);
int mbedtls_oid_get_md_alg(const mbedtls_asn1_buf *oid, mbedtls_md_type_t *md_alg);
int mbedtls_oid_get_oid_by_md(mbedtls_md_type_t md_alg, const unsigned char **oid, size_t *olen);
void mbedtls_zeroize(void *v, size_t n);
int pem_get_iv(const unsigned char *s, unsigned char *iv, size_t iv_len);
void pem_pbkdf1(unsigned char *key, size_t keylen, unsigned char *iv, const unsigned char *pwd, size_t pwdlen);
void pem_des3_decrypt(unsigned char *des3_iv, unsigned char *buf, size_t buflen, const unsigned char *pwd, size_t pwdlen);
void pem_aes_decrypt(unsigned char *aes_iv, unsigned int keylen, unsigned char *buf, size_t buflen, const unsigned char *pwd, size_t pwdlen);
void mbedtls_pem_init(mbedtls_pem_context *ctx);
int mbedtls_pem_read_buffer(mbedtls_pem_context *ctx, const unsigned char *header, const unsigned char *footer, const unsigned char *data, const unsigned char *pwd, size_t pwdlen, size_t *use_len);
void mbedtls_pem_free(mbedtls_pem_context *ctx);
void mbedtls_pk_init(mbedtls_pk_context *ctx);
void mbedtls_pk_free(mbedtls_pk_context *ctx);
const mbedtls_pk_info_t *mbedtls_pk_info_from_type(mbedtls_pk_type_t pk_type);
int mbedtls_pk_setup(mbedtls_pk_context *ctx, const mbedtls_pk_info_t *info);
int mbedtls_pk_can_do(const mbedtls_pk_context *ctx, mbedtls_pk_type_t type);
int mbedtls_pk_verify(mbedtls_pk_context *ctx, mbedtls_md_type_t md_alg, const unsigned char *hash, size_t hash_len, const unsigned char *sig, size_t sig_len);
int mbedtls_pk_sign(mbedtls_pk_context *ctx, mbedtls_md_type_t md_alg, const unsigned char *hash, size_t hash_len, unsigned char *sig, size_t *sig_len, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng);
int mbedtls_pk_encrypt(mbedtls_pk_context *ctx, const unsigned char *input, size_t ilen, unsigned char *output, size_t *olen, size_t osize, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng);
size_t mbedtls_pk_get_bitlen(const mbedtls_pk_context *ctx);
int mbedtls_pk_verify_ext(mbedtls_pk_type_t type, const void *options, mbedtls_pk_context *ctx, mbedtls_md_type_t md_alg, const unsigned char *hash, size_t hash_len, const unsigned char *sig, size_t sig_len);
int mbedtls_pk_debug(const mbedtls_pk_context *ctx, mbedtls_pk_debug_item *items);
const unsigned char *mbedtls_pk_get_name(const mbedtls_pk_context *ctx);
mbedtls_pk_type_t mbedtls_pk_get_type(const mbedtls_pk_context *ctx);
int pk_parse_key_pkcs1_der(mbedtls_rsa_context *rsa, const unsigned char *key, size_t keylen);
int pk_get_pk_alg(unsigned char **p, const unsigned char *end, mbedtls_pk_type_t *pk_alg, mbedtls_asn1_buf *params);
int pk_parse_key_pkcs8_unencrypted_der(mbedtls_pk_context *pk, const unsigned char *key, size_t keylen);
int mbedtls_pk_parse_subpubkey(unsigned char **p, const unsigned char *end, mbedtls_pk_context *pk);
int mbedtls_pk_parse_key(mbedtls_pk_context *pk, const unsigned char *key, size_t keylen, const unsigned char *pwd, size_t pwdlen);
int rsa_can_do(mbedtls_pk_type_t type);
size_t rsa_get_bitlen(const void *ctx);
void rsa_debug(const void *ctx, mbedtls_pk_debug_item *items);
void rsa_free_wrap(void *ctx);
int rsa_check_pair_wrap(const void *pub, const void *prv);
int rsa_encrypt_wrap(void *ctx, const unsigned char *input, size_t ilen, unsigned char *output, size_t *olen, size_t osize, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng);
int rsa_decrypt_wrap(void *ctx, const unsigned char *input, size_t ilen, unsigned char *output, size_t *olen, size_t osize, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng);
int rsa_sign_wrap(void *ctx, mbedtls_md_type_t md_alg, const unsigned char *hash, size_t hash_len, unsigned char *sig, size_t *sig_len, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng);
int rsa_verify_wrap(void *ctx, mbedtls_md_type_t md_alg, const unsigned char *hash, size_t hash_len, const unsigned char *sig, size_t sig_len);
void mgf_mask(unsigned char *dst, size_t dlen, unsigned char *src, size_t slen, mbedtls_md_context_t *md_ctx);
int mbedtls_rsa_check_privkey(const mbedtls_rsa_context *ctx);
void mbedtls_rsa_init(mbedtls_rsa_context *ctx, int padding, int hash_id);
int mbedtls_rsa_check_pubkey(const mbedtls_rsa_context *ctx);
int mbedtls_rsa_check_privkey(const mbedtls_rsa_context *ctx);
int mbedtls_rsa_check_pub_priv(const mbedtls_rsa_context *pub, const mbedtls_rsa_context *prv);
int mbedtls_rsa_public(mbedtls_rsa_context *ctx, const unsigned char *input, unsigned char *output);
int mbedtls_rsa_private(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, const unsigned char *input, unsigned char *output);
int mbedtls_rsa_rsaes_oaep_encrypt(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, const unsigned char *label, size_t label_len, size_t ilen, const unsigned char *input, unsigned char *output);
int mbedtls_rsa_rsaes_pkcs1_v15_encrypt(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, size_t ilen, const unsigned char *input, unsigned char *output);
int mbedtls_rsa_pkcs1_encrypt(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, size_t ilen, const unsigned char *input, unsigned char *output);
int mbedtls_rsa_rsaes_oaep_decrypt(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, const unsigned char *label, size_t label_len, size_t *olen, const unsigned char *input, unsigned char *output, size_t output_max_len);
int mbedtls_rsa_rsaes_pkcs1_v15_decrypt(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, size_t *olen, const unsigned char *input, unsigned char *output, size_t output_max_len);
int mbedtls_rsa_pkcs1_decrypt(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, size_t *olen, const unsigned char *input, unsigned char *output, size_t output_max_len);
int mbedtls_rsa_rsassa_pss_sign(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, mbedtls_md_type_t md_alg, unsigned int hashlen, const unsigned char *hash, unsigned char *sig);
int mbedtls_rsa_rsassa_pkcs1_v15_sign(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, mbedtls_md_type_t md_alg, unsigned int hashlen, const unsigned char *hash, unsigned char *sig);
int mbedtls_rsa_pkcs1_sign(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, mbedtls_md_type_t md_alg, unsigned int hashlen, const unsigned char *hash, unsigned char *sig);
int mbedtls_rsa_rsassa_pss_verify_ext(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, mbedtls_md_type_t md_alg, unsigned int hashlen, const unsigned char *hash, mbedtls_md_type_t mgf1_hash_id, int expected_salt_len, const unsigned char *sig);
int mbedtls_rsa_rsassa_pss_verify(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, mbedtls_md_type_t md_alg, unsigned int hashlen, const unsigned char *hash, const unsigned char *sig);
int mbedtls_rsa_rsassa_pkcs1_v15_verify(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, mbedtls_md_type_t md_alg, unsigned int hashlen, const unsigned char *hash, const unsigned char *sig);
int mbedtls_rsa_pkcs1_verify(mbedtls_rsa_context *ctx, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng, int mode, mbedtls_md_type_t md_alg, unsigned int hashlen, const unsigned char *hash, const unsigned char *sig);
void mbedtls_rsa_free(mbedtls_rsa_context *ctx);
void mbedtls_sha1_init(mbedtls_sha1_context *ctx);
void mbedtls_sha1_free(mbedtls_sha1_context *ctx);
void mbedtls_sha1_clone(mbedtls_sha1_context *dst, const mbedtls_sha1_context *src);
void mbedtls_sha1_starts(mbedtls_sha1_context *ctx);
void mbedtls_sha1_process(mbedtls_sha1_context *ctx, const unsigned char *data);
void mbedtls_sha1_update(mbedtls_sha1_context *ctx, const unsigned char *input, size_t ilen);
void mbedtls_sha1_update(mbedtls_sha1_context *ctx, const unsigned char *input, size_t ilen);
void mbedtls_sha1_finish(mbedtls_sha1_context *ctx, unsigned char *output);
void mbedtls_sha1(const unsigned char *input, size_t ilen, unsigned char *output);
void mbedtls_sha256_init(mbedtls_sha256_context *ctx);
void mbedtls_sha256_free(mbedtls_sha256_context *ctx);
void mbedtls_sha256_clone(mbedtls_sha256_context *dst, const mbedtls_sha256_context *src);
void mbedtls_sha256_starts(mbedtls_sha256_context *ctx, int is224);
void mbedtls_sha256_process(mbedtls_sha256_context *ctx, const unsigned char *data);
void mbedtls_sha256_update(mbedtls_sha256_context *ctx, const unsigned char *input, size_t ilen);
void mbedtls_sha256_update(mbedtls_sha256_context *ctx, const unsigned char *input, size_t ilen);
void mbedtls_sha256_finish(mbedtls_sha256_context *ctx, unsigned char *output);
void mbedtls_sha256(const unsigned char *input, size_t ilen, unsigned char *output, int is224);
void mbedtls_sha512_init(mbedtls_sha512_context *ctx);
void mbedtls_sha512_free(mbedtls_sha512_context *ctx);
void mbedtls_sha512_clone(mbedtls_sha512_context *dst, const mbedtls_sha512_context *src);
void mbedtls_sha512_starts(mbedtls_sha512_context *ctx, int is384);
void mbedtls_sha512_process(mbedtls_sha512_context *ctx, const unsigned char *data);
void mbedtls_sha512_update(mbedtls_sha512_context *ctx, const unsigned char *input, size_t ilen);
void mbedtls_sha512_update(mbedtls_sha512_context *ctx, const unsigned char *input, size_t ilen);
void mbedtls_sha512_finish(mbedtls_sha512_context *ctx, unsigned char *output);
void mbedtls_sha512(const unsigned char *input, size_t ilen, unsigned char *output, int is384);
const mbedtls_ssl_ciphersuite_t *mbedtls_ssl_ciphersuite_from_id(int ciphersuite);
const unsigned char *mbedtls_ssl_get_ciphersuite_name(const int ciphersuite_id);
mbedtls_pk_context *mbedtls_ssl_own_key(mbedtls_ssl_context *ssl);
int mbedtls_ssl_handshake_client_step(mbedtls_ssl_context *ssl);
mbedtls_x509_crt *mbedtls_ssl_own_cert(mbedtls_ssl_context *ssl);
void mbedtls_zeroize_1(void *v, size_t n);
void ssl_set_timer(mbedtls_ssl_context *ssl, uint32_t millisecs);
void ssl_calc_finished_tls_sha256(mbedtls_ssl_context *ssl, unsigned char *buf, int from);
void ssl_calc_verify_tls_sha256(mbedtls_ssl_context *ssl, unsigned char *hash);
int tls_prf_generic(mbedtls_md_type_t md_type, const unsigned char *secret, size_t slen, const unsigned char *label, const unsigned char *random, size_t rlen, unsigned char *dstbuf, size_t dlen);
int tls_prf_sha256(const unsigned char *secret, size_t slen, const unsigned char *label, const unsigned char *random, size_t rlen, unsigned char *dstbuf, size_t dlen);
int tls_prf_sha384(const unsigned char *secret, size_t slen, const unsigned char *label, const unsigned char *random, size_t rlen, unsigned char *dstbuf, size_t dlen);
int tls1_prf(const unsigned char *secret, size_t slen, const unsigned char *label, const unsigned char *random, size_t rlen, unsigned char *dstbuf, size_t dlen);
void ssl_calc_finished_tls_sha384(mbedtls_ssl_context *ssl, unsigned char *buf, int from);
void ssl_calc_verify_tls_sha384(mbedtls_ssl_context *ssl, unsigned char *hash);
void ssl_calc_finished_tls(mbedtls_ssl_context *ssl, unsigned char *buf, int from);
void ssl_calc_verify_tls(mbedtls_ssl_context *ssl, unsigned char *hash);
void ssl_update_checksum_md5sha1(mbedtls_ssl_context *ssl, const unsigned char *buf, size_t len);
void ssl_calc_finished_ssl(mbedtls_ssl_context *ssl, unsigned char *buf, int from);
void ssl_calc_verify_ssl(mbedtls_ssl_context *ssl, unsigned char *hash);
int ssl3_prf(const unsigned char *secret, size_t slen, const unsigned char *label, const unsigned char *random, size_t rlen, unsigned char *dstbuf, size_t dlen);
void ssl_mac(mbedtls_md_context_t *md_ctx, unsigned char *secret, unsigned char *buf, size_t len, unsigned char *ctr, int type);
int ssl_append_key_cert(mbedtls_ssl_key_cert **head, mbedtls_x509_crt *cert, mbedtls_pk_context *key);
void ssl_update_checksum_sha256(mbedtls_ssl_context *ssl, const unsigned char *buf, size_t len);
void ssl_update_checksum_sha384(mbedtls_ssl_context *ssl, const unsigned char *buf, size_t len);
void ssl_update_checksum_start(mbedtls_ssl_context *ssl, const unsigned char *buf, size_t len);
int mbedtls_ssl_derive_keys(mbedtls_ssl_context *ssl);
int mbedtls_ssl_psk_derive_premaster(mbedtls_ssl_context *ssl, mbedtls_key_exchange_type_t key_ex);
int mbedtls_ssl_fetch_input(mbedtls_ssl_context *ssl, size_t nb_want);
int mbedtls_ssl_flush_output(mbedtls_ssl_context *ssl);
int mbedtls_ssl_write_record(mbedtls_ssl_context *ssl);
int mbedtls_ssl_prepare_handshake_record(mbedtls_ssl_context *ssl);
void mbedtls_ssl_update_handshake_status(mbedtls_ssl_context *ssl);
int mbedtls_ssl_handle_message_type(mbedtls_ssl_context *ssl);
int mbedtls_ssl_send_alert_message(mbedtls_ssl_context *ssl, unsigned char level, unsigned char message);
int mbedtls_ssl_send_fatal_handshake_failure(mbedtls_ssl_context *ssl);
int mbedtls_ssl_read_record_layer(mbedtls_ssl_context *ssl);
int mbedtls_ssl_read_record(mbedtls_ssl_context *ssl);
int mbedtls_ssl_write_certificate(mbedtls_ssl_context *ssl);
int mbedtls_ssl_parse_certificate(mbedtls_ssl_context *ssl);
int mbedtls_ssl_write_change_cipher_spec(mbedtls_ssl_context *ssl);
int mbedtls_ssl_parse_change_cipher_spec(mbedtls_ssl_context *ssl);
void mbedtls_ssl_optimize_checksum(mbedtls_ssl_context *ssl, const mbedtls_ssl_ciphersuite_t *ciphersuite_info);
int mbedtls_ssl_write_finished(mbedtls_ssl_context *ssl);
int mbedtls_ssl_parse_finished(mbedtls_ssl_context *ssl);
void mbedtls_ssl_session_init(mbedtls_ssl_session *session);
void mbedtls_ssl_init(mbedtls_ssl_context *ssl);
void mbedtls_ssl_conf_authmode(mbedtls_ssl_config *conf, int authmode);
void mbedtls_ssl_conf_rng(mbedtls_ssl_config *conf, int (*f_rng)(void *, unsigned char *, size_t), void *p_rng);
void mbedtls_ssl_conf_dbg(mbedtls_ssl_config *conf, void (*f_dbg)(void *, int, const unsigned char *, int, const unsigned char *), void *p_dbg);
void mbedtls_ssl_set_bio(mbedtls_ssl_context *ssl, void *p_bio, mbedtls_ssl_send_t *f_send, mbedtls_ssl_recv_t *f_recv, mbedtls_ssl_recv_timeout_t *f_recv_timeout);
void mbedtls_ssl_conf_read_timeout(mbedtls_ssl_config *conf, uint32_t timeout);
void mbedtls_ssl_conf_cert_profile(mbedtls_ssl_config *conf, const mbedtls_x509_crt_profile *profile);
int mbedtls_ssl_conf_own_cert(mbedtls_ssl_config *conf, mbedtls_x509_crt *own_cert, mbedtls_pk_context *pk_key);
void mbedtls_ssl_conf_ca_chain(mbedtls_ssl_config *conf, mbedtls_x509_crt *ca_chain, mbedtls_x509_crl *ca_crl);
uint32_t mbedtls_ssl_get_verify_result(const mbedtls_ssl_context *ssl);
int mbedtls_ssl_handshake_step(mbedtls_ssl_context *ssl);
int mbedtls_ssl_handshake(mbedtls_ssl_context *ssl);
int mbedtls_ssl_read(mbedtls_ssl_context *ssl, unsigned char *buf, size_t len);
int mbedtls_ssl_write(mbedtls_ssl_context *ssl, const unsigned char *buf, size_t len);
int mbedtls_ssl_close_notify(mbedtls_ssl_context *ssl);
void mbedtls_ssl_transform_free(mbedtls_ssl_transform *transform);
void mbedtls_ssl_handshake_free(mbedtls_ssl_handshake_params *handshake);
void mbedtls_ssl_session_free(mbedtls_ssl_session *session);
void mbedtls_ssl_handshake_wrapup(mbedtls_ssl_context *ssl);
int ssl_handshake_init(mbedtls_ssl_context *ssl);
int mbedtls_ssl_setup(mbedtls_ssl_context *ssl, const mbedtls_ssl_config *conf);
void mbedtls_ssl_free(mbedtls_ssl_context *ssl);
void mbedtls_ssl_config_init(mbedtls_ssl_config *conf);
int mbedtls_ssl_config_defaults(mbedtls_ssl_config *conf, int endpoint, int transport, int preset);
void mbedtls_ssl_config_free(mbedtls_ssl_config *conf);
unsigned char mbedtls_ssl_sig_from_pk(mbedtls_pk_context *pk);
unsigned char mbedtls_ssl_hash_from_md_alg(int md);
void mbedtls_ssl_write_version(int major, int minor, int transport, unsigned char *ver);
void mbedtls_ssl_read_version(int *major, int *minor, int transport, const unsigned char *ver);
void threading_mutex_init_freertos(mbedtls_threading_mutex_t *mutex);
void threading_mutex_free_freertos(mbedtls_threading_mutex_t *mutex);
int threading_mutex_lock_freertos(mbedtls_threading_mutex_t *mutex);
int threading_mutex_unlock_freertos(mbedtls_threading_mutex_t *mutex);
int x509_parse_int(unsigned char **p, size_t n, int *res);
int mbedtls_x509_get_serial(unsigned char **p, const unsigned char *end, mbedtls_x509_buf *serial);
int mbedtls_x509_get_alg(unsigned char **p, const unsigned char *end, mbedtls_x509_buf *alg, mbedtls_x509_buf *params);
int mbedtls_x509_get_name(unsigned char **p, const unsigned char *end, mbedtls_x509_name *cur);
int mbedtls_x509_get_time(unsigned char **p, const unsigned char *end, mbedtls_x509_time *time);
int mbedtls_x509_get_sig(unsigned char **p, const unsigned char *end, mbedtls_x509_buf *sig);
int mbedtls_x509_get_sig_alg(const mbedtls_x509_buf *sig_oid, const mbedtls_x509_buf *sig_params, mbedtls_md_type_t *md_alg, mbedtls_pk_type_t *pk_alg, void **sig_opts);
int mbedtls_x509_get_ext(unsigned char **p, const unsigned char *end, mbedtls_x509_buf *ext, int tag);
int mbedtls_x509_dn_gets(unsigned char *buf, size_t size, const mbedtls_x509_name *dn);
int mbedtls_x509_serial_gets(unsigned char *buf, size_t size, const mbedtls_x509_buf *serial);
int mbedtls_x509_sig_alg_gets(unsigned char *buf, size_t size, const mbedtls_x509_buf *sig_oid, mbedtls_pk_type_t pk_alg, mbedtls_md_type_t md_alg, const void *sig_opts);
int mbedtls_x509_key_size_helper(unsigned char *buf, size_t buf_size, const unsigned char *name);
int mbedtls_x509_time_is_past(const mbedtls_x509_time *to);
int mbedtls_x509_time_is_future(const mbedtls_x509_time *from);
void mbedtls_zeroize_2(void *v, size_t n);
int x509_memcasecmp(const void *s1, const void *s2, size_t len);
int x509_name_cmp(const mbedtls_x509_name *a, const mbedtls_x509_name *b);
int x509_crt_check_parent(const mbedtls_x509_crt *child, const mbedtls_x509_crt *parent, int top, int bottom);
int x509_check_wildcard(const unsigned char *cn, mbedtls_x509_buf *name);
int x509_get_uid(unsigned char **p, const unsigned char *end, mbedtls_x509_buf *uid, int n);
int x509_crt_verify_child(mbedtls_x509_crt *child, mbedtls_x509_crt *parent, mbedtls_x509_crt *trust_ca, mbedtls_x509_crl *ca_crl, const mbedtls_x509_crt_profile *profile, int path_cnt, int self_cnt, uint32_t *flags, int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *), void *p_vrfy);
int mbedtls_x509_crt_info(unsigned char *buf, size_t size, const unsigned char *prefix, const mbedtls_x509_crt *crt);
int mbedtls_x509_crt_verify_info(char *buf, size_t size, const char *prefix, uint32_t flags);
int mbedtls_x509_crt_verify_with_profile(mbedtls_x509_crt *crt, mbedtls_x509_crt *trust_ca, mbedtls_x509_crl *ca_crl, const mbedtls_x509_crt_profile *profile, const unsigned char *cn, uint32_t *flags, int (*f_vrfy)(void *, mbedtls_x509_crt *, int, uint32_t *), void *p_vrfy);
void mbedtls_x509_crt_init(mbedtls_x509_crt *crt);
void mbedtls_x509_crt_free(mbedtls_x509_crt *crt);
int mbedtls_x509_crt_parse_der(mbedtls_x509_crt *chain, const unsigned char *buf, size_t buflen);
int mbedtls_x509_crt_parse(mbedtls_x509_crt *chain, const unsigned char *buf, size_t buflen);
int net_would_block(const mbedtls_net_context *ctx);
void mbedtls_net_init(mbedtls_net_context *ctx);
int mbedtls_net_connect(mbedtls_net_context *ctx, const char *host, const char *port, int proto);
int mbedtls_net_set_nonblock(mbedtls_net_context *ctx);
int mbedtls_net_recv(void *ctx, unsigned char *buf, size_t len);
int mbedtls_net_recv_timeout(void *ctx, unsigned char *buf, size_t len, uint32_t timeout);
int mbedtls_net_send(void *ctx, const unsigned char *buf, size_t len);
void mbedtls_net_free(mbedtls_net_context *ctx);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define mbedtls_calloc calloc
#define mbedtls_free free

const char *mbedtls_ssl_get_version(const mbedtls_ssl_context *ssl);
void mbedtls_strerror(int ret, char *buf, size_t buflen);
int mbedtls_ssl_set_hostname(mbedtls_ssl_context *ssl, const char *hostname);
int mbedtls_ssl_conf_psk(mbedtls_ssl_config *conf, const unsigned char *psk, size_t psk_len, const unsigned char *psk_identity, size_t psk_identity_len);
int mbedtls_ssl_get_record_expansion(const mbedtls_ssl_context *ssl);
size_t mbedtls_ssl_get_bytes_avail(const mbedtls_ssl_context *ssl);
const char *mbedtls_ssl_get_ciphersuite(const mbedtls_ssl_context *ssl);
const mbedtls_x509_crt *mbedtls_ssl_get_peer_cert(const mbedtls_ssl_context *ssl);

struct _hr_time
{
	struct timeval start;
};

struct mbedtls_timing_hr_time
{
	unsigned char opaque[32];
};

typedef struct
{
	struct mbedtls_timing_hr_time timer;
	uint32_t int_ms;
	uint32_t fin_ms;
} mbedtls_timing_delay_context;

void mbedtls_timing_set_delay(void *data, uint32_t int_ms, uint32_t fin_ms);
int mbedtls_timing_get_delay(void *data);
void mbedtls_ssl_set_timer_cb(mbedtls_ssl_context *ssl, void *p_timer, mbedtls_ssl_set_timer_t *f_set_timer, mbedtls_ssl_get_timer_t *f_get_timer);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MBEDTLS_OID_SIZE(x) (sizeof(x) - 1)
#define MBEDTLS_OID_CMP(oid_str, oid_buf)             \
	((MBEDTLS_OID_SIZE(oid_str) != (oid_buf)->len) || \
	 memcmp((oid_str), (oid_buf)->p, (oid_buf)->len) != 0)

#define MBEDTLS_OID_ISO_MEMBER_BODIES "\x2a"  /* {iso(1) member-body(2)} */
#define MBEDTLS_OID_ISO_IDENTIFIED_ORG "\x2b" /* {iso(1) identified-organization(3)} */
#define MBEDTLS_OID_ISO_CCITT_DS "\x55"		  /* {joint-iso-ccitt(2) ds(5)} */
#define MBEDTLS_OID_ISO_ITU_COUNTRY "\x60"	/* {joint-iso-itu-t(2) country(16)} */

#define MBEDTLS_OID_AT MBEDTLS_OID_ISO_CCITT_DS "\x04" /**< id-at OBJECT IDENTIFIER ::= {joint-iso-ccitt(2) ds(5) 4} */
#define MBEDTLS_OID_AT_CN MBEDTLS_OID_AT "\x03"		   /**< id-at-commonName AttributeType:= {id-at 3} */

/*
 * SSL Error codes
 */
#define MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE -0x7080			  /**< The requested feature is not available. */
#define MBEDTLS_ERR_SSL_BAD_INPUT_DATA -0x7100				  /**< Bad input parameters to function. */
#define MBEDTLS_ERR_SSL_INVALID_MAC -0x7180					  /**< Verification of the message MAC failed. */
#define MBEDTLS_ERR_SSL_INVALID_RECORD -0x7200				  /**< An invalid SSL record was received. */
#define MBEDTLS_ERR_SSL_CONN_EOF -0x7280					  /**< The connection indicated an EOF. */
#define MBEDTLS_ERR_SSL_UNKNOWN_CIPHER -0x7300				  /**< An unknown cipher was received. */
#define MBEDTLS_ERR_SSL_NO_CIPHER_CHOSEN -0x7380			  /**< The server has no ciphersuites in common with the client. */
#define MBEDTLS_ERR_SSL_NO_RNG -0x7400						  /**< No RNG was provided to the SSL module. */
#define MBEDTLS_ERR_SSL_NO_CLIENT_CERTIFICATE -0x7480		  /**< No client certification received from the client, but required by the authentication mode. */
#define MBEDTLS_ERR_SSL_CERTIFICATE_TOO_LARGE -0x7500		  /**< Our own certificate(s) is/are too large to send in an SSL message. */
#define MBEDTLS_ERR_SSL_CERTIFICATE_REQUIRED -0x7580		  /**< The own certificate is not set, but needed by the server. */
#define MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED -0x7600		  /**< The own private key or pre-shared key is not set, but needed. */
#define MBEDTLS_ERR_SSL_CA_CHAIN_REQUIRED -0x7680			  /**< No CA Chain is set, but required to operate. */
#define MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE -0x7700			  /**< An unexpected message was received from our peer. */
#define MBEDTLS_ERR_SSL_FATAL_ALERT_MESSAGE -0x7780			  /**< A fatal alert message was received from our peer. */
#define MBEDTLS_ERR_SSL_PEER_VERIFY_FAILED -0x7800			  /**< Verification of our peer failed. */
#define MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY -0x7880			  /**< The peer notified us that the connection is going to be closed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO -0x7900			  /**< Processing of the ClientHello handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO -0x7980			  /**< Processing of the ServerHello handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE -0x7A00			  /**< Processing of the Certificate handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_REQUEST -0x7A80	/**< Processing of the CertificateRequest handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE -0x7B00	/**< Processing of the ServerKeyExchange handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO_DONE -0x7B80	  /**< Processing of the ServerHelloDone handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE -0x7C00	/**< Processing of the ClientKeyExchange handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP -0x7C80 /**< Processing of the ClientKeyExchange handshake message failed in DHM / ECDH Read Public. */
#define MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_CS -0x7D00 /**< Processing of the ClientKeyExchange handshake message failed in DHM / ECDH Calculate Secret. */
#define MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY -0x7D80	 /**< Processing of the CertificateVerify handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_CHANGE_CIPHER_SPEC -0x7E00	 /**< Processing of the ChangeCipherSpec handshake message failed. */
#define MBEDTLS_ERR_SSL_BAD_HS_FINISHED -0x7E80				  /**< Processing of the Finished handshake message failed. */
#define MBEDTLS_ERR_SSL_ALLOC_FAILED -0x7F00				  /**< Memory allocation failed */
#define MBEDTLS_ERR_SSL_HW_ACCEL_FAILED -0x7F80				  /**< Hardware acceleration function returned with error */
#define MBEDTLS_ERR_SSL_HW_ACCEL_FALLTHROUGH -0x6F80		  /**< Hardware acceleration function skipped / left alone data */
#define MBEDTLS_ERR_SSL_COMPRESSION_FAILED -0x6F00			  /**< Processing of the compression / decompression failed */
#define MBEDTLS_ERR_SSL_BAD_HS_PROTOCOL_VERSION -0x6E80		  /**< Handshake protocol not within min/max boundaries */
#define MBEDTLS_ERR_SSL_BAD_HS_NEW_SESSION_TICKET -0x6E00	 /**< Processing of the NewSessionTicket handshake message failed. */
#define MBEDTLS_ERR_SSL_SESSION_TICKET_EXPIRED -0x6D80		  /**< Session ticket has expired. */
#define MBEDTLS_ERR_SSL_PK_TYPE_MISMATCH -0x6D00			  /**< Public key type mismatch (eg, asked for RSA key exchange and presented EC key) */
#define MBEDTLS_ERR_SSL_UNKNOWN_IDENTITY -0x6C80			  /**< Unknown identity received (eg, PSK identity) */
#define MBEDTLS_ERR_SSL_INTERNAL_ERROR -0x6C00				  /**< Internal error (eg, unexpected failure in lower-level module) */
#define MBEDTLS_ERR_SSL_COUNTER_WRAPPING -0x6B80			  /**< A counter would wrap (eg, too many messages exchanged). */
#define MBEDTLS_ERR_SSL_WAITING_SERVER_HELLO_RENEGO -0x6B00   /**< Unexpected message at ServerHello in renegotiation. */
#define MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED -0x6A80		  /**< DTLS client must retry for hello verification */
#define MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL -0x6A00			  /**< A buffer is too small to receive or write a message */
#define MBEDTLS_ERR_SSL_NO_USABLE_CIPHERSUITE -0x6980		  /**< None of the common ciphersuites is usable (eg, no suitable certificate, see debug messages). */
#define MBEDTLS_ERR_SSL_WANT_READ -0x6900					  /**< Connection requires a read call. */
#define MBEDTLS_ERR_SSL_WANT_WRITE -0x6880					  /**< Connection requires a write call. */
#define MBEDTLS_ERR_SSL_TIMEOUT -0x6800						  /**< The operation timed out. */
#define MBEDTLS_ERR_SSL_CLIENT_RECONNECT -0x6780			  /**< The client initiated a reconnect from the same port. */
#define MBEDTLS_ERR_SSL_UNEXPECTED_RECORD -0x6700			  /**< Record header looks valid but is not expected. */
#define MBEDTLS_ERR_SSL_NON_FATAL -0x6680					  /**< The alert message received indicates a non-fatal error. */
#define MBEDTLS_ERR_SSL_INVALID_VERIFY_HASH -0x6600			  /**< Couldn't set the hash for verifying CertificateVerify */

/*
 * Various constants
 */
#define MBEDTLS_SSL_MAJOR_VERSION_3 3
#define MBEDTLS_SSL_MINOR_VERSION_0 0 /*!< SSL v3.0 */
#define MBEDTLS_SSL_MINOR_VERSION_1 1 /*!< TLS v1.0 */
#define MBEDTLS_SSL_MINOR_VERSION_2 2 /*!< TLS v1.1 */
#define MBEDTLS_SSL_MINOR_VERSION_3 3 /*!< TLS v1.2 */

#define MBEDTLS_SSL_TRANSPORT_STREAM 0   /*!< TLS      */
#define MBEDTLS_SSL_TRANSPORT_DATAGRAM 1 /*!< DTLS     */

#define MBEDTLS_SSL_MAX_HOST_NAME_LEN 255 /*!< Maximum host name defined in RFC 1035 */

/* RFC 6066 section 4, see also mfl_code_to_length in ssl_tls.c
 * NONE must be zero so that memset()ing structure to zero works */
#define MBEDTLS_SSL_MAX_FRAG_LEN_NONE 0	/*!< don't use this extension   */
#define MBEDTLS_SSL_MAX_FRAG_LEN_512 1	 /*!< MaxFragmentLength 2^9      */
#define MBEDTLS_SSL_MAX_FRAG_LEN_1024 2	/*!< MaxFragmentLength 2^10     */
#define MBEDTLS_SSL_MAX_FRAG_LEN_2048 3	/*!< MaxFragmentLength 2^11     */
#define MBEDTLS_SSL_MAX_FRAG_LEN_4096 4	/*!< MaxFragmentLength 2^12     */
#define MBEDTLS_SSL_MAX_FRAG_LEN_INVALID 5 /*!< first invalid value        */

#define MBEDTLS_SSL_IS_CLIENT 0
#define MBEDTLS_SSL_IS_SERVER 1

#define MBEDTLS_SSL_IS_NOT_FALLBACK 0
#define MBEDTLS_SSL_IS_FALLBACK 1

#define MBEDTLS_SSL_EXTENDED_MS_DISABLED 0
#define MBEDTLS_SSL_EXTENDED_MS_ENABLED 1

#define MBEDTLS_SSL_ETM_DISABLED 0
#define MBEDTLS_SSL_ETM_ENABLED 1

#define MBEDTLS_SSL_COMPRESS_NULL 0
#define MBEDTLS_SSL_COMPRESS_DEFLATE 1

#define MBEDTLS_SSL_VERIFY_NONE 0
#define MBEDTLS_SSL_VERIFY_OPTIONAL 1
#define MBEDTLS_SSL_VERIFY_REQUIRED 2
#define MBEDTLS_SSL_VERIFY_UNSET 3 /* Used only for sni_authmode */

#define MBEDTLS_SSL_LEGACY_RENEGOTIATION 0
#define MBEDTLS_SSL_SECURE_RENEGOTIATION 1

#define MBEDTLS_SSL_RENEGOTIATION_DISABLED 0
#define MBEDTLS_SSL_RENEGOTIATION_ENABLED 1

#define MBEDTLS_SSL_ANTI_REPLAY_DISABLED 0
#define MBEDTLS_SSL_ANTI_REPLAY_ENABLED 1

#define MBEDTLS_SSL_RENEGOTIATION_NOT_ENFORCED -1
#define MBEDTLS_SSL_RENEGO_MAX_RECORDS_DEFAULT 16

#define MBEDTLS_SSL_LEGACY_NO_RENEGOTIATION 0
#define MBEDTLS_SSL_LEGACY_ALLOW_RENEGOTIATION 1
#define MBEDTLS_SSL_LEGACY_BREAK_HANDSHAKE 2

#define MBEDTLS_SSL_TRUNC_HMAC_DISABLED 0
#define MBEDTLS_SSL_TRUNC_HMAC_ENABLED 1
#define MBEDTLS_SSL_TRUNCATED_HMAC_LEN 10 /* 80 bits, rfc 6066 section 7 */

#define MBEDTLS_SSL_SESSION_TICKETS_DISABLED 0
#define MBEDTLS_SSL_SESSION_TICKETS_ENABLED 1

#define MBEDTLS_SSL_CBC_RECORD_SPLITTING_DISABLED 0
#define MBEDTLS_SSL_CBC_RECORD_SPLITTING_ENABLED 1

#define MBEDTLS_SSL_ARC4_ENABLED 0
#define MBEDTLS_SSL_ARC4_DISABLED 1

#define MBEDTLS_SSL_PRESET_DEFAULT 0
#define MBEDTLS_SSL_PRESET_SUITEB 2

/////////////////////////////////////////////////////////////////////////////////////////

#define MBEDTLS_SSL_MAX_CONTENT_LEN (16 * 1024)
#define MBEDTLS_PSK_MAX_LEN 32

#endif
