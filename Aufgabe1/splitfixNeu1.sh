#! /bin/bash
version="1.0 by JanBartels"

# Exporte fuer die Variablen
export filename=""
export size=0

# usage() gibt den Text aus, der aus der aufgabenstellung uebernommen wurde
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

if [ $# -eq 1 ]; then
# Wenn der erste Parameter ein -h oder --help ist  wird die Funktion Usage aufgerufen
    case $1 in
      "-h" | "--help")
      usage
      ;;
# Wenn der erste Parameter ein --version ist, wird die Version der Datei ausgegeben      
      "--version")
      echo $version
      ;;
# Fehlerhafte Parameter an der ersten Stelle sind -s -v --verbose      
      "-s" | "-v" | "--verbose")
      echo "Ungültiger Parameter"
      ;;
      *)
# Hier ist die eigentliche Syntax fuer das ausfuehren:
# Parameter 1 -> Dateiname dann soll es aufgeteilt werden

      filename=$1
      size=10
      if [ ${filename: -4} == ".txt" ]; then
# aufteilen von Textdateien   ausgelagerte Funktion  
	./splitfixTextfiles.sh
      else
# aufteilen von anderen Dateien  ausgelagerte funktion    
	./splitfixOtherFiles.sh
      fi
    esac
elif [ $# -eq 3 ]; then
# Der zweite Parameter soll ein -s sein
  case $2 in
    "-s")
# Der dritte Parameter darf eine beliebig Große Zahl sein mit den Ziffern 0-9    
      case $3 in
	[0-9]*)
	  size=$3 # Größe wird gesetzt
	  filename=$1
	  if [ ${filename: -4} == ".txt" ]; then
	    ./splitfixTextfiles.sh 
	  else
	    ./splitfixOtherFiles.sh
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
  echo "Es wurde keine gültige Eingabe getätigt!"
fi
exit 0
 
