#!/bin/bash

echo -n 'Name eingeben: ' ; read name

test -e include/main.h.backup || cp include/main.h include/main.h.backup
sed -i "/#define TEXT / s/^.*$/#define TEXT \"$name\" /" include/main.h

echo "$name" >> list_of_names.txt 

pio run --target fuses || { echo FEHLER beim setzen der Fuses ; exit 1; }
pio run --target upload || { echo FEHLER beim compilieren oder flashen ; exit 1; }

mv include/main.h.backup include/main.h
