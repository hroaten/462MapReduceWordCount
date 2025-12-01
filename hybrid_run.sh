#!/bin/bash
#SBATCH -J final-hybrid   #Job name
#SBATCH -A acf-utk0011  #Write your project account associated to utia condo
#SBATCH -p short
#SBATCH --nodes=4
#SBATCH --ntasks-per-node=1 #--ntasks-per-node is used when we want to define the number of processes per node
#SBATCH --cpus-per-task=16
#SBATCH --time=00:20:00
#SBATCH -o hybrid4.o%j
#SBATCH --qos=short

TEST_DIR="raw_text_input"

args=()

for file in "$TEST_DIR"/*; do
    args+=("$file")
done

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

module load openmpi/4.1.5-gcc

srun ./hybrid "${args[@]}" > hybrid_out.txt
