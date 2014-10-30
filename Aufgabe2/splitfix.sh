#!/bin/bash
# Splitfix shell script
# Jan Bartels
# 30.10.2014
version="1.0 by JanBartels"
usage()
{
cat<<EOF
  $0 [OPTIONS] FILE [FILE..] Split FILE into
    fixed-size pieces.
    The pieces are 10 lines long,
      if FILE is a text file.
    The pieces are 10 kiB long,
      if FILE is *not* a text file.
    The last piece may be smaller, it contains the rest
      of the original file.
    The output files bear the name of the input file
      with a 4-digit numerical suffix.
    The original file can be reconstructed with
      the command	''cat FILE.*''
      
  EXAMPLE:
    splitfix.sh foo.pdf
      splits foo.pdf into the files foo.pdf.0000 foo.pdf.0001 etc.
      
  splitfix.sh [-h | --help] This help text
  splitfix.sh --version     Print version number
  
  OPTIONS:
  -h
    --help	this help text
  
  -s SIZE	size of the pieces
		  in lines (for text files)
		  or in kiBytes (for other files)
  
  -v
    --verbose print debugging messages
EOF
}
# ---------------------------------------------------------------------
# Text Dateien
split_textfiles()
{
  echo "Teile $filename auf"
  split -l $size -d -a4 $filename $filename.
}
#
#Andere Dateien
split_other()
{
  echo "Teile $filename auf"
  split -b $size+k -d -a4 $filename $filename.
}
# ---------------------------------------------------------------------
#
#
if [ $# -eq 1 ]; then
    case $1 in
      "-h" | "--help")
      usage
      ;;
      "--version")
      echo $version
      ;;
      "-s" | "-v" | "--verbose")
      echo "Ungültiger Parameter"
      ;;
      *)
      filename=$1
      size=10
      if [ ${filename: -4} == ".txt" ]; then
	split_textfiles
      else
	split_other
      fi
    esac
elif [ $# -eq 3 ]; then
  case $2 in
    "-s")
      case $3 in
	[0-9]*)
	  size=$3 # Größe wird gesetzt
	  filename=$1
	  if [ ${filename: -4} == ".txt" ]; then
	    split_textfiles
	  else
	    split_other
	  fi
	;;
	*)
	echo "Error: Size ist kein int wert!"
      esac
    ;;
    *)
    echo "Ungültiger Parameter"
  esac
else 
  echo "Fehler"
fi
exit 0