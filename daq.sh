#!/bin/bash
##source /home/shenqiuping/env/dp.env
#rm -fr build`date +%y%m%d` run`date +%y%m%d`
cd Run
mkdir MAKE
cd MAKE
mkdir build #`date +%y%m%d` ##/home/shenqiuping/RPC_Anal/DAQ/build12
cd build #`date +%y%m%d` ##/home/shenqiuping/RPC_Anal/DAQ/build12
cmake -DANALYSER=ON ../../../
make -j100
mkdir ../run #`date +%y%m%d`
cd ../run #`date +%y%m%d`
../build/Analysis 64

