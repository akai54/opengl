#  Makefile 
#  Auteur : Besher AL ADDAM
#  Email  : beshoux@outlook.fr
#  Date   : 07/05/2022

SHELL = /bin/sh

# définition des commandes utilisées
CC = g++
RM = rm -f
MKDIR = mkdir

# déclaration des options du compilateur
LDFLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

# définition des fichiers et dossiers
PROGNAME = main
VERSION = 1.0
SOURCES = main.cpp glad.c

all: $(PROGNAME)

$(PROGNAME): $(SOURCES)
	$(CC) $(SOURCES) $(LDFLAGS) -o $(PROGNAME)

clean:
	@$(RM) -r $(PROGNAME)
