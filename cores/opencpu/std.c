/*
  BC66 - std
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

#include <stdint.h>
#include <stddef.h>

int isdigit(int c) { return (c >= '0' && c <= '9'); }
int isalpha(int c) { return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')); }
int isalnum(int c) { return (isalpha(c) || isdigit(c)); }
int iscntrl(int c) { return (c == 127 || (c >= 0 && c <= 31)); }
int islower(int c) { return (c >= 'a' && c <= 'z'); }
int isprint(int c) { return (c >= 0x20 && c <= 0x7E); }
int isgraph(int c) { return (isprint(c) && c != ' '); }
int isspace(int c) { return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v'); }
int ispunct(int c) { return (isprint(c) && !isspace(c) && !isalnum(c)); }
int isupper(int c) { return (c >= 'A' && c <= 'Z'); }
int isxdigit(int c) { return (isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')); }

int isascii(int c) { return c >= 0 && c < 128; }
int toascii(int c) { return c & 0177; }

#if 0
int tolower(int c)
{
    if (isupper(c))
        return 'a' - 'A' + c;
    return c;
}

int toupper(int c)
{
    if (islower(c))
        return 'A' - 'a' + c;
    return c;
}
#endif

int *__errno() { return 0; }

int abs(int j)
{
    return (j < 0 ? -j : j);
}

void reverse(char *begin, char *end)
{
    char *is = begin;
    char *ie = end - 1;
    while (is < ie)
    {
        char tmp = *ie;
        *ie = *is;
        *is = tmp;
        ++is;
        --ie;
    }
}

extern long atol(const char *s)
{
    long val = 0;
    if (s)
    {
        extern int Ql_sscanf(const char *s, const char *format, ...);
        Ql_sscanf(s, "%l", &val);
    }
    return val;
}

static const char *str_digits = "0123456789abcdef";
extern char *itoa(int value, char *result, int base)
{
    if (result)
    {
        if (base < 2 || base > 16)
        {
            *result = 0;
            return result;
        }
        char *out = result;
        int quotient = abs(value);
        do
        {
            const int tmp = quotient / base;
            *out = str_digits[quotient - (tmp * base)];
            ++out;
            quotient = tmp;
        } while (quotient);
        if (value < 0)
            *out++ = '-';
        reverse(result, out);
        *out = 0;
    }
    return result;
}

extern char *ltoa(long value, char *result, int base)
{
    if (result)
    {
        if (base < 2 || base > 16)
        {
            *result = 0;
            return result;
        }
        char *out = result;
        long quotient = abs(value);
        do
        {
            const long tmp = quotient / base;
            *out = str_digits[quotient - (tmp * base)];
            ++out;
            quotient = tmp;
        } while (quotient);
        if (value < 0)
            *out++ = '-';
        reverse(result, out);
        *out = 0;
    }
    return result;
}

extern char *utoa(unsigned value, char *result, int base)
{
    if (result)
    {
        if (base < 2 || base > 16)
        {
            *result = 0;
            return result;
        }
        char *out = result;
        unsigned quotient = value;
        do
        {
            const unsigned tmp = quotient / base;
            *out = str_digits[quotient - (tmp * base)];
            ++out;
            quotient = tmp;
        } while (quotient);
        reverse(result, out);
        *out = 0;
    }
    return result;
}

extern char *ultoa(unsigned long value, char *result, int base)
{
    if (result)
    {
        if (base < 2 || base > 16)
        {
            *result = 0;
            return result;
        }
        char *out = result;
        unsigned long quotient = value;
        do
        {
            const unsigned long tmp = quotient / base;
            *out = str_digits[quotient - (tmp * base)];
            ++out;
            quotient = tmp;
        } while (quotient);
        reverse(result, out);
        *out = 0;
    }
    return result;
}

//https://github.com/Wiz-IO/platform-quectel