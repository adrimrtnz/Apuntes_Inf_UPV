#!/bin/sh
#SBATCH --nodes=1
#SBATCH --time=10:00
#SBATCH --partition=cpa

echo " "
echo "----- REALIGN1.C -----"
echo " "
echo "static"
OMP_NUM_THREADS=2       OMP_SCHEDULE=static ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=4       OMP_SCHEDULE=static ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=8       OMP_SCHEDULE=static ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=16      OMP_SCHEDULE=static ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=32      OMP_SCHEDULE=static ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=64      OMP_SCHEDULE=static ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=128     OMP_SCHEDULE=static ./realign1 /scratch/cpa/large.ppm outlarge.ppm

echo " "
echo "static,1"
OMP_NUM_THREADS=2       OMP_SCHEDULE=static,1 ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=4       OMP_SCHEDULE=static,1 ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=8       OMP_SCHEDULE=static,1 ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=16      OMP_SCHEDULE=static,1 ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=32      OMP_SCHEDULE=static,1 ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=64      OMP_SCHEDULE=static,1 ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=128     OMP_SCHEDULE=static,1 ./realign1 /scratch/cpa/large.ppm outlarge.ppm

echo " "
echo "dynamic"
OMP_NUM_THREADS=2       OMP_SCHEDULE=dynamic ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=4       OMP_SCHEDULE=dynamic ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=8       OMP_SCHEDULE=dynamic ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=16      OMP_SCHEDULE=dynamic ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=32      OMP_SCHEDULE=dynamic ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=64      OMP_SCHEDULE=dynamic ./realign1 /scratch/cpa/large.ppm outlarge.ppm
OMP_NUM_THREADS=128     OMP_SCHEDULE=dynamic ./realign1 /scratch/cpa/large.ppm outlarge.ppm