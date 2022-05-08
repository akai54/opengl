#  Makefile 
#  Auteur : Besher AL ADDAM
#  Email  : beshoux@outlook.fr
#  Date   : 07/05/2022

SHELL = /bin/sh

# définition des commandes utilisées
CC = g++
ECHO = echo
RM = rm -f
MKDIR = mkdir

# déclaration des options du compilateur
LDFLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

# définition des fichiers et dossiers
PROGNAME = main
VERSION = 1.0
distdir = $(PROGNAME)-$(VERSION)
HEADERS = 
SOURCES = main.cpp glad.c

# EXTRAFILES = COPYING $(wildcard shaders/*.?s images/*.png)
DISTFILES = $(SOURCES) Makefile $(HEADERS)

all: $(PROGNAME)

$(PROGNAME):
	$(CC) $(SOURCES) $(LDFLAGS) -o $(PROGNAME)


dist: distdir
	$(CHMOD) -R a+r $(distdir)
	$(TAR) zcvf $(distdir).tgz $(distdir)
	$(RM) -r $(distdir)

distdir: $(DISTFILES)
	$(RM) -r $(distdir)
	$(MKDIR) $(distdir)
	$(CHMOD) 777 $(distdir)
	$(CP) $(DISTFILES) $(distdir)

clean:
	@$(RM) -r $(PROGNAME) $(OBJ) *~ $(distdir).tgz gmon.out core.*
