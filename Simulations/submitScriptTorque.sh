#!/bin/bash -l
#
#$ -N permanent
#$ -q low.q
#$ -pe threaded 1
#$ -w e
#$ -l h_vmem=20G
#$ -l h_rt=36:00:00
#$ -l s_rt=35:59:50
#$ -v SCENARIO_INDEX
#$ -v UPPER_LIMIT
#$ -v LOWER_LIMIT
#$ -S /bin/bash
#$ -cwd
#$ -j y
#$ -R y
trap "echo recieved SIGUSR1;" SIGUSR1;
R CMD BATCH --no-save --no-restore -- jobScript.R jobScript.Rout.$JOB_ID
