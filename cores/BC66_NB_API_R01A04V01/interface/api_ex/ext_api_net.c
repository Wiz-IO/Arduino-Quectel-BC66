/*
 * ext_api_net.c
 *
 *  Created on: 17.10.2018
 *      Author: Georgi Angelov
 */

#include "ext_api.h"

int resolveAddress(const char *server, struct sockaddr_in *addr) {
	if (!server || !addr)
		return -1;
	struct addrinfo *ai;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = 1;
	hints.ai_protocol = 6;
	int rc;
	uint32_t * p;
	if (lwip_getaddrinfo(server, 0, &hints, &ai)) {
		return -1;
	} else {
		rc = -1;
		while (ai && rc < 0) {
			if (ai->ai_family == 2) {
				rc = ai->ai_addrlen;
				addr->sin_family = 2;
				p = (uint32_t *) &ai->ai_addr->sa_data[2];
				addr->sin_addr.s_addr = *p;
			}
			ai = ai->ai_next;
		}
		lwip_freeaddrinfo(ai);
	}
	return rc;
}
