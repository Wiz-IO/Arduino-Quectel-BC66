/*
 *
 * MIT License:
 * Copyright (c) 2011 Adrian McEwen
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * adrianm@mcqn.com 1/1/2011
 * bryan.odonoghue@intel.com 18/09/2013
 */

#ifndef IPAddress_h
#define IPAddress_h

#include <WString.h>

/* Arduino headers */
#include <Printable.h>

// A class to make it easier to handle and pass around IP addresses

class IPAddress : public Printable {
private:
    // Access the raw byte array containing the address.  Because this returns a pointer
    // to the internal structure rather than a copy of the address this function should only
    // be used when you know that the usage of the returned uint8_t* will be transient and not stored.
    uint8_t * raw_address() { return (uint8_t*)&ADDR; };
public:
    uint32_t ADDR = 0;

    // Constructors
    IPAddress(){ ADDR = 0; };
    IPAddress(uint32_t address){ ADDR = address; };
    IPAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet);
    IPAddress(const uint8_t * address);

    // Overloaded cast operator to allow IPAddress objects to be used where a pointer to a four-byte uint8_t array is expected
    operator uint32_t() { return ADDR; };
    bool operator==(const IPAddress& addr) { return addr.ADDR == ADDR; };
    bool operator==(const uint32_t addr) { return addr == ADDR; };
    bool operator==(const uint8_t * addr);

    // Overloaded index operator to allow getting and setting individual octets of the address
    uint8_t operator[](int idx) const { return ((uint8_t*)&ADDR)[idx]; };

    // Overloaded copy operators to allow initialisation of IPAddress objects from other types
    IPAddress& operator=(const uint8_t * address);
    IPAddress& operator=(uint32_t address);
    IPAddress& operator=(struct sockaddr_in * p_sin);

    virtual size_t printTo(Print& p) const;
    String toString() const;

    friend class WiFiClass;
    friend class EthernetClass;
    friend class UDP;
    friend class Client;
    friend class Server;

    friend class DdsClient;
    friend class DnsClient;
    friend class ClientSocket;
};

#endif
