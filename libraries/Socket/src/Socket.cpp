#include "Socket.h"

void Socket::_socket_ctort(uint32_t type, uint32_t family) {
	_sock_type = type;
	_socket = -1;
	if (_sock_type != SOCK_STREAM || _sock_type != SOCK_DGRAM)
		_sock_type = SOCK_STREAM;
	memset(&_address, 0, sizeof(_address));
	_address.sin_family = family;
	_timeout = -1; //WAIT_FOREVER;
	_connected = 0;
}

void Socket::close() {
	if (_socket < 0)
		return;
	lwip_close(_socket);
	_socket = -1;
}

int Socket::_connect() { /* TODO non blocked */
	if (_socket > -1)
		return EISCONN;
	if (0 == _address.sin_addr.s_addr || 0 == _address.sin_port)
		return EINVAL;
	int err;
	if ((_socket = lwip_socket(AF_INET, _sock_type, 0)) < 0) {
		LOG("[ERROR] lwip_socket( %d )", _socket);
		return _socket;
	}
	if ((err = lwip_connect(_socket, (sockaddr*) &_address, sizeof(_address)))) {
		LOG("[ERROR] lwip_connect( %d )", err);
		goto END;
	}
	END: //
	if (err)
		close();
	_connected = err == 0;
	return err;
}

int Socket::connect(sockaddr_in addr) {
	_address.sin_port = addr.sin_port;
	_address.sin_addr.s_addr = addr.sin_addr.s_addr;
	return _connect();
}

int Socket::connect(const char * ip, uint16_t port) {
	_address.sin_port = lwip_htons(port);
	_address.sin_addr.s_addr = inet_addr(ip);
	return _connect();
}

int Socket::connect(IPAddress ip, uint16_t port) {
	_address.sin_port = lwip_htons(port);
	_address.sin_addr.s_addr = ip.ADDR;
	return _connect();
}

int Socket::read(uint8_t * buf, size_t size) {
	if (_socket < 0 || !buf || !size)
		return -1;
	uint32_t from = sizeof(_address);
	if (_sock_type == SOCK_DGRAM)
		return lwip_recvfrom(_socket, buf, size, 0, (sockaddr*) &_address, &from);
	else
		return lwip_recv(_socket, buf, size, 0);
}

int Socket::_read(int flag) {
	if (_socket < 0)
		return -1;
	uint8_t byte;
	int rc;
	uint32_t from = sizeof(_address);
	if (_sock_type == SOCK_DGRAM)
		rc = lwip_recvfrom(_socket, &byte, 1, flag, (sockaddr*) &_address, &from);
	else
		rc = lwip_recv(_socket, &byte, 1, flag);
	if (rc == 0)
		return -2;
	return (rc != 1) ? -1 : byte;
}

size_t Socket::write(const uint8_t * buf, size_t size) {
	if (_socket < 0 || !buf || !size)
		return 0;
	int rc;
	if (_sock_type == SOCK_DGRAM) {
		rc = lwip_sendto(_socket, buf, size, 0, (sockaddr*) &_address, sizeof(_address));
	} else {
		rc = lwip_send(_socket, buf, size, 0);
	}
	if (rc < 0) {
		close();
		return 0;
	} else
		return rc;
}

int Socket::available() {
	if (_socket < 0)
		return 0;
	return _read(MSG_PEEK | MSG_DONTWAIT) != -1 ? 1 : 0;

}

int Socket::peek() {
	return _read(MSG_PEEK | MSG_DONTWAIT);
}

void Socket::flush() {
	while (available())
		read();
}

void Socket::stop() {
	if (_socket < 0)
		return;
	lwip_close(_socket);
	_socket = -1;
	_connected = 0;
}
