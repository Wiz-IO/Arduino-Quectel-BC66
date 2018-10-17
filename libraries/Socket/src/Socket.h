/*
 * Socket.h
 *
 *  Created on: 10.10.2018
 *      Author: georgi.angelov
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include "Arduino.h"
#include "Client.h"
#include "IPAddress.h"

class Socket: public Client {
	private:
	//uint8_t rx[1024];
	//int rx_index;


	int32_t _sock_type;
	sockaddr_in _address;
	int32_t _timeout;
	uint8_t _connected;
	int _read(int flag);
	int _connect();
	void _socket_ctort(uint32_t type, uint32_t family);
public:
	int _socket;


	Socket() {
		_socket_ctort(SOCK_STREAM, AF_INET);
	}
	Socket(int type) {
		_socket_ctort(type, AF_INET);
	}
	Socket(int type, int family) {
		_socket_ctort(type, family);
	}
	~Socket() {
		close();
	}
	void close();
	void setTimeout(int32_t ms) { _timeout = ms; }
	int connect(sockaddr_in addr);

	virtual int connect(IPAddress ip, uint16_t port);
	virtual int connect(const char *host, uint16_t port);
	virtual size_t write(uint8_t b) { return write(&b, 1); }
	virtual size_t write(const uint8_t *buf, size_t size);
	virtual int available();
	virtual int read() { return _read(0); }
	virtual int read(uint8_t *buf, size_t size);
	virtual int peek();
	virtual void flush();
	virtual void stop();
	virtual uint8_t connected(){ return _connected; };
	virtual operator bool(){ return _socket != -1; };
};

#endif /* SOCKET_H_ */
