/*
  BC66 - API
    Created on: 01.01.2019
    Author: Georgi Angelov

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

#include "api.h"

int resolveAddress(const char *server, struct sockaddr_in *addr)
{
	if (!server || !addr)
		return -1;
	struct addrinfo *ai;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = 1;
	hints.ai_protocol = 6;
	int rc;
	uint32_t *p;
	if (lwip_getaddrinfo(server, 0, &hints, &ai))
	{
		return -1;
	}
	else
	{
		rc = -1;
		while (ai && rc < 0)
		{
			if (ai->ai_family == 2)
			{
				rc = ai->ai_addrlen;
				addr->sin_family = 2;
				p = (uint32_t *)&ai->ai_addr->sa_data[2];
				addr->sin_addr.s_addr = *p;
			}
			ai = ai->ai_next;
		}
		lwip_freeaddrinfo(ai);
	}
	return rc;
}
