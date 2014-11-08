#! /bin/bash
# Ausgelagertes split 

split_textfiles()
{
  echo $0
  echo "Teile $filename auf"
# der Splitbefehl, zum Splitten von Dateien
# -l steht fuer die Lines, das -d fuer die digits (die zahlenfolge, die nach der DateiEndung kommt)
# -a4 bedeutet, dass es 4 Ziffern sein duerfen
# die beiden $filename sind für inFilename und outFilename
  split -l $size -d -a4 $filename $filename.
  
}
split_textfiles

exit 0

