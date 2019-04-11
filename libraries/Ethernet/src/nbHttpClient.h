#ifndef HTTPCLIENT_H_
#define HTTPCLIENT_H_

#include <Arduino.h>

class nbHttpClient
{
  public:
    nbHttpClient() { clean(); }
    ~nbHttpClient() { end(); }
    void clean();
    void end();
    int begin(const char *url);
    int begin(const char *url, size_t response_size);
    int begin(const char *url, size_t response_size, size_t header_size);    

    uint32_t get();
    uint32_t post(const char *post);
    uint32_t post(const char *post, size_t size);

    char *getResponse();
    char *getHeader();
    void setClientHeader(char *header);
    void setPostContent(char *content);
    void setTimeout(uint32_t seconds);

  private:
    char *m_url;
    httpclient_t client;
    httpclient_data_t data;
    size_t create_buffer(char **buf, size_t size);
    uint32_t execute(HTTPCLIENT_REQUEST_TYPE method);
};

#endif /* HTTPCLIENT_H_ */
