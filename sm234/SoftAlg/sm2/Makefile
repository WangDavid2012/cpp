#
# OpenSSL/crypto/sm2/Makefile
#

DIR=	sm2
TOP=	../..
CC=	cc
INCLUDES= -I.. -I$(TOP) -I../../include
CFLAG=-g
MAKEFILE=	Makefile
AR=		ar r

CFLAGS= $(INCLUDES) $(CFLAG)

GENERAL=Makefile
TEST=sm2test.c
APPS=

LIB=$(TOP)/libcrypto.a
LIBSRC= sm2_enc.c sm2_sign.c sm2_util.c sm2_derive.c
LIBOBJ= sm2_enc.o sm2_sign.o sm2_util.o sm2_derive.o

SRC= $(LIBSRC)

EXHEADER= sm2.h
HEADER=	$(EXHEADER) sm2_util.h

ALL=    $(GENERAL) $(SRC) $(HEADER)

top:
	(cd ../..; $(MAKE) DIRS=crypto SDIRS=$(DIR) sub_all)

all:	lib

lib:	$(LIBOBJ)
	$(AR) $(LIB) $(LIBOBJ)
	$(RANLIB) $(LIB) || echo Never mind.
	@touch lib

files:
	$(PERL) $(TOP)/util/files.pl Makefile >> $(TOP)/MINFO

links:
	@$(PERL) $(TOP)/util/mklink.pl ../../include/openssl $(EXHEADER)
	@$(PERL) $(TOP)/util/mklink.pl ../../test $(TEST)
	@$(PERL) $(TOP)/util/mklink.pl ../../apps $(APPS)

install:
	@[ -n "$(INSTALLTOP)" ] # should be set by top Makefile...
	@headerlist="$(EXHEADER)"; for i in $$headerlist ; \
	do  \
	(cp $$i $(INSTALL_PREFIX)$(INSTALLTOP)/include/openssl/$$i; \
	chmod 644 $(INSTALL_PREFIX)$(INSTALLTOP)/include/openssl/$$i ); \
	done;

tags:
	ctags $(SRC)

tests:

lint:
	lint -DLINT $(INCLUDES) $(SRC)>fluff

depend:
	@[ -n "$(MAKEDEPEND)" ] # should be set by upper Makefile...
	$(MAKEDEPEND) -- $(CFLAG) $(INCLUDES) $(DEPFLAG) -- $(PROGS) $(LIBSRC)

dclean:
	$(PERL) -pe 'if (/^# DO NOT DELETE THIS LINE/) {print; exit(0);}' $(MAKEFILE) >Makefile.new
	mv -f Makefile.new $(MAKEFILE)

clean:
	rm -f *.o */*.o *.obj lib tags core .pure .nfs* *.old *.bak fluff

# DO NOT DELETE THIS LINE -- make depend depends on it.
sm2_util.o: sm2_util.c sm2_util.h ../../include/openssl/ec.h
sm2_util.o: ../../include/openssl/opensslconf.h ../../include/openssl/ossl_typ.h
sm2_util.o: ../../include/openssl/symhacks.h ../../include/openssl/bio.h ../../include/openssl/objects.h
sm2_util.o: ../../include/openssl/e_os2.h ../../include/openssl/crypto.h ../../include/openssl/obj_mac.h ../ec/ec_lcl.h
sm2_derive.o: sm2_derive.c ../../include/openssl/sm2.h ../../include/openssl/ec.h
sm2_derive.o: ../../include/openssl/opensslconf.h ../../include/openssl/ossl_typ.h
sm2_derive.o: ../../include/openssl/symhacks.h ../../include/openssl/bio.h ../../include/openssl/objects.h
sm2_derive.o: ../../include/openssl/e_os2.h ../../include/openssl/crypto.h ../../include/openssl/obj_mac.h ../ec/ec_lcl.h
sm2_enc.o: sm2_enc.c ../../include/openssl/sm2.h ../../include/openssl/ec.h
sm2_enc.o: ../../include/openssl/opensslconf.h ../../include/openssl/ossl_typ.h
sm2_enc.o: ../../include/openssl/symhacks.h ../../include/openssl/bio.h ../../include/openssl/objects.h
sm2_enc.o: ../../include/openssl/e_os2.h ../../include/openssl/crypto.h ../../include/openssl/obj_mac.h ../ec/ec_lcl.h
sm2_sign.o: sm2_sign.c ../../include/openssl/sm2.h ../../include/openssl/ec.h
sm2_sign.o: ../../include/openssl/opensslconf.h ../../include/openssl/ossl_typ.h
sm2_sign.o: ../../include/openssl/symhacks.h ../../include/openssl/bio.h ../../include/openssl/objects.h
sm2_sign.o: ../../include/openssl/e_os2.h ../../include/openssl/crypto.h ../../include/openssl/obj_mac.h ../ec/ec_lcl.h