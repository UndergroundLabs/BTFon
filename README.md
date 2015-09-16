# BTFon

BTFon is small application developed in C that can be used to log into a BT Fon access point from the command line.

## Usage

    ./btfon user@btopenzone.com secret_password

## Compile

Compilation requires libcurl. Tested on Linux and OSX. Not tested on Windows.

    gcc -o btfon btfon.c -lcurl

## Executable

I've included a pre built executable compiled on Debian Jessie i686.
