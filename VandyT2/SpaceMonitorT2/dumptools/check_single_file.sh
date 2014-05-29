#!/bin/sh
# See: https://twiki.cern.ch/twiki/bin/view/LCG/ConsistencyChecksSEsDumps#Format_of_SE_dumps
# Check a single file and output PFN,Size,Time stamp and check sum (optional)
FILE=$1
CKSUMFILE=`echo $FILE | sed 's/store/store\/cksums/'`
if [ -f $CKSUMFILE ] ; then
ADLER32=`grep ADLER32 $CKSUMFILE | awk -F\: '{print $2}'`
elif [ -z $ADLER32 ] ; then
ADLER32="N/A"
else
ADLER32="N/A"
fi
ls -lc --time-style=+%s $FILE | \
awk -v val=$ADLER32 '{print $7"|"$5"|"$6"|" val}' | sed 's/ //g'
exit
