#!/bin/bash
#SBATCH -J final-hybrid   #Job name
#SBATCH -A acf-utk0011  #Write your project account associated to utia condo
#SBATCH -p short
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=8  #--ntasks-per-node is used when we want to define the number of processes per node
#SBATCH --cpus-per-task=4
#SBATCH --time=00:20:00
#SBATCH -o hybrid.o%j
#SBATCH --qos=short

TEST_DIR="raw_text_input"

args=()

for file in "$TEST_DIR"/*; do
    args+=("$file")
done

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

module load openmpi/4.1.5-gcc

srun -n 8 ./hybrid "${args[@]}" > hybrid_out.txt
