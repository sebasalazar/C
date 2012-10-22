#!/bin/bash

openssl genrsa -out privada.pem 4096
openssl rsa -in privada.pem -pubout -out publica.pem
