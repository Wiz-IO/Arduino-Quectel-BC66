#include "nbHttpClient.h"

#define HTTP_DEBUG DBG

#define CONTENT_DEFAULT_SIZE 64
#define CONTENT_MAX_SIZE 1024

char *nbHttpClient::getResponse()
{
    return data.response_buf;
}

char *nbHttpClient::getHeader()
{
    return data.header_buf;
}

void nbHttpClient::setTimeout(uint32_t seconds)
{
    client.timeout_in_sec = 10;
}

void nbHttpClient::setClientHeader(char *header)
{
    client.header = header;
}

void nbHttpClient::setPostContent(char *content)
{
    data.post_content_type = content;
}

void nbHttpClient::clean()
{
    memset(&client, 0, sizeof(httpclient_t));
    memset(&data, 0, sizeof(httpclient_data_t));
    HTTP_DEBUG("[HTTP] clean()\n");
}

void nbHttpClient::end()
{
    free(data.header_buf);
    free(data.response_buf);
    HTTP_DEBUG("[HTTP] free()\n");
}

size_t nbHttpClient::create_buffer(char **buf, size_t size)
{

    if (size > CONTENT_MAX_SIZE) // limit
        size = CONTENT_MAX_SIZE;
    *buf = (char *)malloc(size);
    if (NULL == *buf)
    {
        HTTP_DEBUG("[ERROR][HTTP] allocate buffer\n");
        return 0; // error
    }
    memset(*buf, 0, size);
    HTTP_DEBUG("[HTTP] create_buffer[%d] %p\n", size, *buf);
    return size - 1;
}

int nbHttpClient::begin(const char *url, size_t response_size = 0)
{
    if (data.header_buf)
    {
        HTTP_DEBUG("[HTTP] free header_buf\n");
        free(data.header_buf);
        data.header_buf = NULL;
    }
    if (data.response_buf)
    {
        HTTP_DEBUG("[HTTP] free header_buf\n");
        free(data.response_buf);
        data.response_buf = NULL;
    }
    clean();
    data.response_content_len = -1;
    m_url = (char *)url;
    HTTP_DEBUG("[HTTP] begin() %s\n", url);
    if (0 == response_size)
        response_size = CONTENT_DEFAULT_SIZE;
    data.response_buf_len = create_buffer(&data.response_buf, response_size);
    HTTP_DEBUG("[HTTP] response_buf_len = %d, %d\n", response_size, data.response_buf_len);
    if ((response_size - 1) != data.response_buf_len)
    {
        HTTP_DEBUG("[ERROR][HTTP] default size\n");
        return false;
    }
    return url != NULL; // done
}

int nbHttpClient::begin(const char *url, size_t response_size, size_t header_size)
{
    if (begin(url, response_size))
    {
        data.header_buf_len = create_buffer(&data.header_buf, header_size);
        HTTP_DEBUG("[HTTP] header_buf_len = %d, %d\n", header_size, data.header_buf_len);
        return (header_size - 1) == data.header_buf_len;
    }
    return 0;
}

uint32_t nbHttpClient::execute(HTTPCLIENT_REQUEST_TYPE method)
{
    uint32_t code = 0;
    int res;
    if (m_url)
    {
        res = httpclient_common(&client, (char *)m_url, method, &data);
        HTTP_DEBUG("[HTTP] Execute: %d\n", res);
        if (0 == res)
        {
            code = client.response_code;
            HTTP_DEBUG("[HTTP] Post     [ %03d ] %p\n", data.post_buf_len, data.post_buf);
            HTTP_DEBUG("[HTTP] Header   [ %03d ] %p\n", data.header_buf_len, data.header_buf);
            HTTP_DEBUG("[HTTP] Response [ %03d ] %p\n", data.response_buf_len, data.response_buf);
            HTTP_DEBUG("[HTTP] Content  [ %03d ]\n", data.response_content_len);
        }
    }
    return code;
}

/// Return http response code or error = 0
uint32_t nbHttpClient::get()
{
    if (m_url)
        return execute(HTTPCLIENT_GET);
    return 0;
}

uint32_t nbHttpClient::post(const char *post_data)
{
    if (m_url && post_data)
    {
        data.post_buf = (char *)post_data;
        data.post_buf_len = strlen(post_data);
        return execute(HTTPCLIENT_POST);
    }
    return 0;
}

uint32_t nbHttpClient::post(const char *post_data, size_t post_size)
{
    if (m_url && post_data && post_size)
    {
        data.post_buf = (char *)post_data;
        data.post_buf_len = post_size;
        return execute(HTTPCLIENT_POST);
    }
    return 0;
}
