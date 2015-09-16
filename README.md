# BTFon

BTFon is small application developed in C that can be used to log into a BT Fon access point.

## Usage

    ./btfon user@btopenzone.com secret_password

## Compile

Compilation requires libcurl.

    gcc -o btfon btfon.c -lcurl
