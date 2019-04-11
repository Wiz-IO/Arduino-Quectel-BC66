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

#define DEBUG_TCP /*DBG*/

#include "interface.h"
extern "C"
{
#include "lwip/lwipopts.h"
#include "lwip/sockets.h"
}
#include "nbClient.h"

nbClient::nbClient() : m_socket(-1),
                       m_externalSocket(false),
                       _connected(false)
{
}

nbClient::nbClient(int sock) : m_socket(sock),
                               m_externalSocket(true),
                               _connected(false)
{
    // accepting an externally allocated socket
}

nbClient::~nbClient()
{
    if (!m_externalSocket)
        stop();
}

int nbClient::connect(const char *host, uint16_t port)
{
    sockaddr_in a;
    IPAddress remote_addr;
    if (resolveAddress(host, &a))
    {
        remote_addr = a.sin_addr.s_addr;
        return connect(remote_addr, port);
    }
    return 0;
}

int nbClient::connect(IPAddress ip, uint16_t port)
{
    if (m_socket)
        stop();
    m_socket = lwip_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    m_externalSocket = true;
    if (-1 == m_socket)
    {
        DEBUG_TCP("[TCP] socket allocation failed!");
        return 0;
    }
    struct sockaddr_in server;
    server.sin_addr.s_addr = (uint32_t)ip;
    server.sin_family = AF_INET;
    server.sin_port = lwip_htons(port);
    if (0 > lwip_connect(m_socket, (struct sockaddr *)&server, sizeof(server)))
    {
        lwip_close(m_socket);
        m_socket = -1;
        DEBUG_TCP("[TCP] connect() failed\n");
        return 0;
    }
    DEBUG_TCP("[TCP] connected! with socket = %d\n", m_socket);
    _connected = true;
    return 1;
}

size_t nbClient::write(uint8_t b)
{
    if (m_socket == -1)
        return 0;
    int ret = lwip_send(m_socket, &b, 1, 0);
    DEBUG_TCP("[TCP] send() returns %d\n", ret);
    return ret;
}

size_t nbClient::write(const uint8_t *buf, size_t size)
{
    if (m_socket == -1)
        return 0;
    int ret = lwip_send(m_socket, buf, size, 0);
    if (ret < 0)
    {
        DEBUG_TCP("[TCP] buffered send fails with ret= %d\n", ret);
    }
    return ret;
}

int nbClient::available()
{
    if (m_socket == -1)
        return 0;
#if 0
	// Note: to enable FIONREAD, we need to enable lwIP option `LWIP_SO_RCVBUF	1`.
	// Currently, it is not enabled.
	int count = 0;
	int ret = lwip_ioctl(m_socket, FIONREAD, &count);
	DEBUG_TCP("[TCP] ioctl FIONREAD returns %d with count = %d", ret, count);
	return count;
#endif
    if (-1 == peek())
        return 0;
    return 1;
}

int nbClient::read()
{
    if (m_socket == -1)
        return -1;
    uint8_t b;
    if (1 == lwip_recv(m_socket, &b, 1, MSG_DONTWAIT))
        return b;
    else
        return -1;
}

int nbClient::read(uint8_t *buf, size_t size)
{
    if (m_socket == -1)
        return 0;
    int ret = lwip_recv(m_socket, buf, size, MSG_DONTWAIT);
    DEBUG_TCP("[TCP] recv() returns %d\n", ret);
    return ret;
}

int nbClient::peek()
{
    if (m_socket == -1)
        return -1;
    uint8_t b;
    int ret = lwip_recv(m_socket, &b, 1, MSG_PEEK | MSG_DONTWAIT);
    if (ret == 1)
        return b;
    return -1;
}

void nbClient::stop()
{
    if (m_socket == -1)
        return;
    DEBUG_TCP("[TCP] close() on socket %d\n", m_socket);
    lwip_close(m_socket);
    m_socket = -1;
    _connected = false;
}

uint8_t nbClient::connected()
{
    if (-1 == m_socket)
        return 0;
    int error_code = 0;
    socklen_t error_code_size = sizeof(error_code);
    lwip_getsockopt(m_socket, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
    if ((error_code == ENOTCONN) ||
        (error_code == ENOTSOCK) ||
        (error_code == ECONNRESET) ||
        (error_code == ETIMEDOUT))
        return 0;
    else
        return 1;
}

nbClient::operator bool()
{
    return connected();
}