/*
  Udp.cpp - UDP class for Raspberry Pi
  Copyright (c) 2016 Hristo Gochkov  All right reserved.

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
#include <DEV.h>
#include "nbUdp.h"
#include <lwip/sockets.h>
#include <lwip/netdb.h>
#include <errno.h>

#define DEBUG_UDP DBG

#undef write
#undef read

nbUDP::nbUDP()
    : udp_server(-1),
      server_port(0),
      remote_port(0),
      tx_buffer(0),
      tx_buffer_len(0),
      rx_buffer(0)
{
}

nbUDP::~nbUDP()
{
    stop();
}

uint8_t nbUDP::begin(IPAddress address, uint16_t port)
{
    stop();
    server_port = port;
    tx_buffer = new char[1460];
    if (!tx_buffer)
    {
        DEBUG_UDP("could not create tx buffer: %d", errno);
        return 0;
    }
    if ((udp_server = lwip_socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        DEBUG_UDP("could not create socket: %d", errno);
        return 0;
    }
    struct sockaddr_in addr;
    memset((char *)&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(server_port);
    addr.sin_addr.s_addr = (in_addr_t)address;
    if (lwip_bind(udp_server, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        DEBUG_UDP("could not bind socket: %d", errno);
        stop();
        return 0;
    }
    lwip_fcntl(udp_server, F_SETFL, O_NONBLOCK);
    return 1;
}

uint8_t nbUDP::begin(uint16_t p)
{
    return begin(IPAddress(INADDR_ANY), p);
}

void nbUDP::stop()
{
    if (tx_buffer)
    {
        delete[] tx_buffer;
        tx_buffer = NULL;
    }
    tx_buffer_len = 0;
    if (rx_buffer)
    {
        cbuf *b = rx_buffer;
        rx_buffer = NULL;
        delete b;
    }
    if (udp_server == -1)
        return;
    if (multicast_ip != 0)
    {
    }
    lwip_close(udp_server);
    udp_server = -1;
}

int nbUDP::beginPacket()
{
    if (!remote_port)
        return 0;
    // allocate tx_buffer if is necessary
    if (!tx_buffer)
    {
        tx_buffer = new char[1460];
        if (!tx_buffer)
        {
            DEBUG_UDP("could not create tx buffer: %d", errno);
            return 0;
        }
    }
    tx_buffer_len = 0;
    // check whereas socket is already open
    if (udp_server != -1)
        return 1;
    if ((udp_server = lwip_socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        DEBUG_UDP("could not create socket: %d", errno);
        return 0;
    }
    lwip_fcntl(udp_server, F_SETFL, O_NONBLOCK);
    return 1;
}

int nbUDP::beginPacket(IPAddress ip, uint16_t port)
{
    remote_ip = ip;
    remote_port = port;
    return beginPacket();
}

int nbUDP::beginPacket(const char *host, uint16_t port)
{
    IPAddress ip;
    if (0 == getHostByName(host, ip))
    {
        DEBUG_UDP("could not get host from dns: %d", errno);
        return 0;
    }
    return beginPacket(ip, port);
}

int nbUDP::endPacket()
{
    struct sockaddr_in recipient;
    recipient.sin_addr.s_addr = (uint32_t)remote_ip;
    recipient.sin_family = AF_INET;
    recipient.sin_port = htons(remote_port);
    int sent = lwip_sendto(udp_server, tx_buffer, tx_buffer_len, 0, (struct sockaddr *)&recipient, sizeof(recipient));
    if (sent < 0)
    {
        DEBUG_UDP("could not send data: %d", errno);
        return 0;
    }
    return 1;
}

size_t nbUDP::write(uint8_t data)
{
    if (tx_buffer_len == 1460)
    {
        endPacket();
        tx_buffer_len = 0;
    }
    tx_buffer[tx_buffer_len++] = data;
    return 1;
}

size_t nbUDP::write(const uint8_t *buffer, size_t size)
{
    size_t i;
    for (i = 0; i < size; i++)
        write(buffer[i]);
    return i;
}

int nbUDP::parsePacket()
{
    if (rx_buffer)
        return 0;
    struct sockaddr_in si_other;
    int slen = sizeof(si_other), len;
    char *buf = new char[1460];
    if (!buf)
        return 0;
    if ((len = lwip_recvfrom(udp_server, buf, 1460, MSG_DONTWAIT, (struct sockaddr *)&si_other, (socklen_t *)&slen)) == -1)
    {
        delete[] buf;
        if (errno == EWOULDBLOCK)
        {
            return 0;
        }
        DEBUG_UDP("could not receive data: %d", errno);
        return 0;
    }
    remote_ip = IPAddress(si_other.sin_addr.s_addr);
    remote_port = ntohs(si_other.sin_port);
    if (len > 0)
    {
        rx_buffer = new cbuf(len);
        rx_buffer->write(buf, len);
    }
    delete[] buf;
    return len;
}

int nbUDP::available()
{
    if (!rx_buffer)
        return 0;
    return rx_buffer->available();
}

int nbUDP::read()
{
    if (!rx_buffer)
        return -1;
    int out = rx_buffer->read();
    if (!rx_buffer->available())
    {
        cbuf *b = rx_buffer;
        rx_buffer = 0;
        delete b;
    }
    return out;
}

int nbUDP::read(unsigned char *buffer, size_t len)
{
    return read((char *)buffer, len);
}

int nbUDP::read(char *buffer, size_t len)
{
    if (!rx_buffer)
        return 0;
    int out = rx_buffer->read(buffer, len);
    if (!rx_buffer->available())
    {
        cbuf *b = rx_buffer;
        rx_buffer = 0;
        delete b;
    }
    return out;
}

int nbUDP::peek()
{
    if (!rx_buffer)
        return -1;
    return rx_buffer->peek();
}

void nbUDP::flush()
{
    if (!rx_buffer)
        return;
    cbuf *b = rx_buffer;
    rx_buffer = 0;
    delete b;
}

IPAddress nbUDP::remoteIP()
{
    return remote_ip;
}

uint16_t nbUDP::remotePort()
{
    return remote_port;
}