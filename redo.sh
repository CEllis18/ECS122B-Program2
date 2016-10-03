#!/bin/bash
g++ subset.cpp -o subset
g++ datagenerator.cpp -std=c++11 -o datagenerator
g++ ntuple.cpp -std=c++11 -o ntuple
echo "running subset"
./subset >> subset.txt
./subset
echo "running ntuple"
./ntuple >> ntuple.txt
./ntuple
