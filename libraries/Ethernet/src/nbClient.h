/*
  nbClient.cpp - Library
  Copyright (c) 2011-2014 Arduino.  All right reserved.

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

#ifndef nbClient_h
#define nbClient_h

#include <stdio.h>
#include "Client.h"
#include "IPAddress.h"

class nbClient : public Client {

public:
    nbClient();

    // This constructor is designed for WiFiServer::available().
    // The nbClient object returned from WiFiServer::available() should
    // persist its connection even when the returned client object goes out of scope; 
    // The user should close it by calling client.stop().
    nbClient(int sock);
    ~nbClient();

    virtual int connect(IPAddress ip, uint16_t port);
    virtual int connect(const char *host, uint16_t port);
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buf, size_t size);
    virtual int available();
    virtual int read();
    virtual int read(uint8_t *buf, size_t size);
    virtual int peek();
    virtual void flush(){}
    virtual void stop();
    virtual uint8_t connected();
    virtual operator bool();

    friend class WiFiServer;
    using Print::write;

private:
    int m_socket;
    bool m_externalSocket;
    
protected:
    bool _connected;    
};

#endif