#! /bin/bash

#Andere Dateien
# Hier wird ebenfalls der echo Code ausgegeben, wenn der split Befehl ausgeführt wird.
# 
split_other()
{
  echo "Teile $filename auf"
# Das -b steht fuer die groesse der bytes in die ausgabedatei zu geben
# das K ist                                               der multiplier 1024
# -d steht fuer die digits hinter dem dateinamen
# -a4 zeigt, dass es 4 Ziffern am ende sind
# $filename inFilename
# $filename outFilename
  split -b ${size}K -d -a4 $filename $filename.
}
split_other

exit 0
