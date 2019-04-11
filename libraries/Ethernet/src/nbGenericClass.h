

#include "IPAddress.h"
#include "api.h"

class nbGenericClass
{
  public:
    nbGenericClass();
    static int hostByName(const char *aHostname, IPAddress &aResult)
    {
        struct sockaddr_in addr;
        int res = resolveAddress(aHostname, &addr);
        aResult = addr.sin_addr.s_addr;
        return res;
    }
};