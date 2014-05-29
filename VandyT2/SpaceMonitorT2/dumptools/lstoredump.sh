#!/bin/sh
begintime=`date +%s`
OUTFILE="storage_dump_vandyT2.$begintime.txt"
touch $OUTFILE
echo "BEGIN TIME $begintime `date`" > $OUTFILE.log
find /store/hidata/HIRun2013/PAMuon/RECO/ZMuMuPA-PromptSkim-v1/00000 \
 /store/mc/Summer12/MinBias_TuneZ2star_8TeV-pythia6/GEN-SIM/START50_V13-v3/0000 \
 -type f -exec ./check_single_file.sh {} \; >> $OUTFILE
echo "END TIME `date +%s` `date`" >> $OUTFILE.log 
