
include ../config.mk

CFLAGS=$(shell pkg-config oehost-$(COMPILER) --cflags)
LDFLAGS=$(shell pkg-config oehost-$(COMPILER) --libs)
INCDIR=$(shell pkg-config oehost-$(COMPILER) --variable=includedir)
NAME=guessing_game
build:
	@ echo "Compilers used: $(CC), $(CXX)"
	oeedger8r ../$(NAME).edl --untrusted \
		--search-path $(INCDIR) \
		--search-path $(INCDIR)/openenclave/edl/sgx
	$(CC) -g -c $(CFLAGS) host.c
	$(CC) -g -c $(CFLAGS) $(NAME)_u.c
	$(CC) -o $(NAME)_host $(NAME)_u.o host.o $(LDFLAGS)

clean:
	rm -f $(NAME)_host host.o $(NAME)_u.o $(NAME)_u.c $(NAME)_u.h $(NAME)_args.h
