#include "ip_utils.h"

unsigned long ip2numero(char *ip) {
    /* Una IPv4 consiste en 4 bloques separados por puntos. */
    unsigned long numero = 0;

    /*
     * comprobamos si es ipv4
     */
    if (es_ipv4(ip)) {
        /* Primer rango. */
        char *bloque = strtok(ip, ".");
        if (bloque) {
            numero += atoi(bloque) * pow(256, 3);
        }

        /* Si todo va bien continuamos con los demás. */
        int exponente = 2;
        while (bloque && exponente >= 0) {
            bloque = strtok(NULL, ".\0");
            if (bloque) numero += atoi(bloque) * pow(256, exponente--);
        }
    } else {
        /* Determinamos si es la ip local */
        if (strcmp("::1", ip) == 0) {
            numero = 2130706433;
        }
    }
    return numero;
}

char* numero2ip(unsigned long numero) {
    char *ip = malloc(16 * sizeof (char));
    int exponente;
    for (exponente = 3; exponente >= 0; --exponente) {
        int r = numero / pow(256, exponente);
        char buf[4];
        sprintf(buf, "%d", r);
        strcat(ip, buf);
        strcat(ip, ".");
        numero -= r * pow(256, exponente);
    }
    /* Reemplazamos el último . por '\0' */
    ip[strlen(ip) - 1] = 0;
    return ip;
}

int es_ipv4(char *ip) {
    int ipv4 = 0;
    struct addrinfo hint, *res = NULL;
    int ret;

    /* Inicializo las funciones de red */
    memset(&hint, '\0', sizeof hint);
    hint.ai_family = PF_UNSPEC;
    hint.ai_flags = AI_NUMERICHOST;

    ret = getaddrinfo(ip, NULL, &hint, &res);
    if (ret > 0) {
        /*
         * Ocurrio un error
         */
        ipv4 = 0;
    } else {
        if (res->ai_family == AF_INET) {
            /* Soy una ipv4 */
            ipv4 = 1;
        } else if (res->ai_family == AF_INET6) {
            /* Soy una ipv6, ergo no soy una ipv4 */
            ipv4 = 0;
        } else {
            /* No sé lo que soy, pero no soy una ipv4 */
            ipv4 = 0;
        }
    }
    freeaddrinfo(res);
    return ipv4;
}

unsigned long cantidad_direcciones(int cidr) {
    unsigned long total = 0;
    /* Valido que el sufijo cidr sea válido */
    if (cidr >= 0 && cidr <= 32) {
        total = pow(2, 32 - cidr);
    }
    return total;
}
