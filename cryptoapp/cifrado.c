#include "cifrado.h"

char* cifrar(char* pub_cert, char* llave_privada, byte* mensaje) {
    int outlen = 0;
    int key_len = 0;
    int iv_len = 16;
    int largo_en = 0;
    int i = 0, j = 0, k = 0;
    int tamano_firma = 0;
    int largo_encodeado = 0;

    char* cifrado_final;

    RSA* rsa = obtenerRSA(pub_cert, 1);
    RSA* firma = obtenerRSA(llave_privada, 0);

    byte* salida;
    byte* cifrado;
    byte* llave_rsa;
    byte* firmado;
    byte* msj_enviado;
    byte* encodeado;

    // Vector de inicialización aleatoreo.
    byte iv[iv_len];
    RAND_bytes(iv, sizeof (iv));

    // Basado en una llave de texto
    // byte* llave_final;
    // llave_final = generar_llave(llave);

    // llave de cifrado aleatorea
    byte llave_final[32];
    RAND_bytes(llave_final, sizeof (llave_final));

    // Firmo el mensaje
    firmado = firma_mensaje(firma, mensaje, &tamano_firma);

    // uno la firma y el mensaje
    largo_en = (tamano_firma + strlen((char*) mensaje));
    msj_enviado = (byte *) malloc(largo_en * sizeof (byte *));
    // Firma
    j = 0;
    for (i = 0; i < tamano_firma; i++) {
        msj_enviado[i] = firmado[j];
        j++;
    }
    // Mensaje
    j = 0;
    for (i = tamano_firma; i < largo_en; i++) {
        msj_enviado[i] = mensaje[j];
        j++;
    }


    // Cifro la llave RSA.
    llave_rsa = cifrar_llave_rsa(rsa, llave_final, &key_len);
    if (llave_rsa == NULL || key_len <= 0) {
#ifdef DEBUG
        fprintf(stderr, "\n[cifrado.c : cifrar] Problemas al cifrar la llave RSA");
#endif
        return NULL;
    }

    // Cifro el mensaje firmado con AES 256 CBC
    cifrado = (byte *) cifrar_aes(llave_final, iv, msj_enviado, &largo_en);
    if (cifrado == NULL || largo_en <= 0) {
#ifdef DEBUG
        fprintf(stderr, "\n[cifrado.c : cifrar] Problemas al cifrar el mensaje %s con AES", msj_enviado);
#endif
        return NULL;
    }

    int tamano_total = (iv_len + key_len + largo_en);
    salida = (byte *) malloc(tamano_total * sizeof (byte *));

    for (i = 0; i < iv_len; i++) {
        salida[k] = iv[i];
        k++;
    }

    for (i = 0; i < key_len; i++) {
        salida[k] = llave_rsa[i];
        k++;
    }

    for (i = 0; i < largo_en; i++) {
        salida[k] = cifrado[i];
        k++;
    }


    // Encodeo en Base 64
    cifrado_final = (char *) base64_encode(salida, tamano_total, &outlen);
    if (cifrado_final == NULL || outlen <= 0) {
#ifdef DEBUG
        fprintf(stderr, "\n[cifrado.c : cifrar] Problemas al encodear con BASE64");
#endif
        return NULL;
    }

    // Encodeo con url encoding
    encodeado = url_encode((byte*) cifrado_final, outlen, &largo_encodeado);
    if (encodeado == NULL || largo_encodeado <= 0) {
#ifdef DEBUG
        fprintf(stderr, "\n[cifrado.c : cifrar] Problemas al encodear con URL ENCODE");
#endif
        return NULL;
    }

#ifdef DEBUG

    fprintf(stderr, "\n[cifrado.c : cifrar] Largo salida: %d\tLargo Llave: %d\tLargo Cifrado: %d\tLargo Firma: %d\tLargo Mensaje: %d\n", outlen, key_len, largo_en, tamano_firma, strlen((char *) mensaje));

    char* ivstr = hex2str(iv, iv_len);
    fprintf(stderr, "\n[cifrado.c : cifrar] IV en cifrar: %s\n", ivstr);

    char* firmastr = hex2str(firmado, tamano_firma);
    fprintf(stderr, "\n[cifrado.c : cifrar] Firma en cifrar: %s-%d-%d\n", firmastr, strlen(firmastr), tamano_firma);

    char* completo = hex2str(msj_enviado, strlen((char *) mensaje) + tamano_firma);
    fprintf(stderr, "\n[cifrado.c : cifrar] Mensaje Firmado y Cifrado en cifrar: %s-%d\n", completo, strlen(completo));

    char* cifradostr = hex2str(cifrado, largo_en);
    fprintf(stderr, "\n[cifrado.c : cifrar] Cifrado en cifrar: %s\n", cifradostr);

    fprintf(stderr, "\n[cifrado.c : cifrar] BASE 64 en cifrar: %s\n", cifrado_final);
    
    fprintf(stderr, "\n[cifrado.c : cifrar] URL_ENCODE en cifrar: %s\n", encodeado);
#endif

    // Libero memoria
    free(msj_enviado);
    free(cifrado);
    free(salida);

    return (char *) encodeado;
}

byte* descifrar(char* priv_cert, char* llave_publica, char* encodeado) {
    int outlen = 0;
    int key_len = 0;
    int largo_cif = 0;
    int largo_llave = 0;
    int largo_firma = 0;
    int largo_mensaje = 0;
    int largo_desencodeado = 0;
    int i = 0, j = 0, k = 0;

    RSA* rsa = obtenerRSA(priv_cert, 0);
    RSA* firma = obtenerRSA(llave_publica, 1);

    byte iv[16];
    byte* llave;
    byte* cifrado;
    byte* descifrado;
    byte* key;
    byte* msj_firma;
    byte* mensaje;
    byte* desencodeado;

    desencodeado = url_decode((byte*) encodeado, strlen(encodeado), &largo_desencodeado);
    byte* salida = base64_decode(desencodeado, largo_desencodeado, &outlen);

    largo_llave = RSA_size(rsa);
    largo_cif = outlen - largo_llave - 16;

    llave = (byte *) malloc(sizeof (byte *) * largo_llave);
    cifrado = (byte *) malloc(sizeof (byte *) * largo_cif);

    // iv
    for (i = 0; i < 16; i++) {
        iv[i] = salida[k];
        k++;
    }

    // llave
    for (i = 0; i < largo_llave; i++) {
        llave[i] = salida[k];
        k++;
    }

    // cifrado
    for (i = 0; i < largo_cif; i++) {
        cifrado[i] = salida[k];
        k++;
    }

    // Descifro la llave con RSA
    key = descifrar_llave_rsa(rsa, llave, &key_len);
    if (key_len <= 0) {
#ifdef DEBUG
        fprintf(stderr, "\n[cifrado.c : descifrar] El largo de la llave es inválido\n");
#endif
        return NULL;
    }

    // Descifro el mensaje
    descifrado = descifrar_aes(key, iv, cifrado, &largo_cif);
    if (descifrado == NULL || largo_cif <= 0) {
#ifdef DEBUG
        fprintf(stderr, "\n[cifrado.c : descifrar] Problemas al descifrar con AES\n");
#endif
    }

    // Separo la firma del mensaje
    largo_firma = RSA_size(firma);
    largo_mensaje = largo_cif - largo_firma;

    msj_firma = (byte *) malloc(largo_firma * sizeof (byte *));
    mensaje = (byte *) malloc((largo_mensaje + 1) * sizeof (byte *));

    j = 0;
    // Firma
    for (i = 0; i < largo_firma; i++) {
        msj_firma[i] = descifrado[j];
        j++;
    }

    // Mensaje
    for (i = 0; i < largo_mensaje; i++) {
        mensaje[i] = descifrado[j];
        j++;
    }
    mensaje[largo_mensaje] = '\0';


#ifdef DEBUG

    fprintf(stderr, "\n[cifrado.c : descifrar] Largo entrada: %d\tLargo Llave: %d\tLargo Cifrado: %d\tLargo Firma: %d\tLargo Mensaje: %d\n", outlen, largo_llave, largo_cif, largo_firma, largo_mensaje);

    char* keystr = hex2str(key, key_len);
    fprintf(stderr, "\n[cifrado.c : descifrar] Llave %s-%d\n", keystr, key_len);

    char* ivstr = hex2str(iv, 16);
    fprintf(stderr, "\n[cifrado.c : descifrar] IV en decifrar: %s\n", ivstr);

    char* cifradostr = hex2str(cifrado, largo_cif);
    fprintf(stderr, "\n[cifrado.c : descifrar] Cifrado en decifrar: %s\n", cifradostr);

    fprintf(stderr, "\n[cifrado.c : descifrar] Largo Cifrado en decifrar: %d\n", largo_cif);

    fprintf(stderr, "\n[cifrado.c : descifrar] Mensaje descifrado: \n%s-%d\n", (char *) mensaje, strlen((char *) mensaje));

    char* firmastr = hex2str(msj_firma, largo_firma);
    fprintf(stderr, "\n[cifrado.c : descifrar] Firma Mensaje: %s\n", firmastr);

#endif



    if (!verificar_mensaje(firma, mensaje, largo_mensaje, msj_firma)) {
#ifdef DEBUG
        fprintf(stderr, "\n[cifrado.c : descifrar] El mensaje no es válido\n");
#endif
        return NULL;
    }

    // Libero espacio en memoria
    free(msj_firma);
    free(descifrado);
    free(llave);
    free(cifrado);

    return mensaje;
}
