# Copyright (c) Open Enclave SDK contributors.
# Licensed under the MIT License.

.PHONY: all build clean run simulate

OE_CRYPTO_LIB := mbedtls
export OE_CRYPTO_LIB
NAME = "guessing_game"

all: build

build:
	$(MAKE) -C enclave
	$(MAKE) -C host

clean:
	$(MAKE) -C enclave clean
	$(MAKE) -C host clean

run:
	host/$(NAME)_host ./enclave/$(NAME)_enc.signed

simulate:
	host/$(NAME)_host ./enclave/$(NAME)_enc.signed --simulate

