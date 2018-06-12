#!/bin/ksh

ID="2C"
PROJ_DIR="/home/users/hank/public_html/330/projects/2C"
DRIVER_PROG="${PROJ_DIR}/driver_2C.c"
PROTO_HEADER="${PROJ_DIR}/prototypes.h"
CORRECT_OUTPUT="${PROJ_DIR}/driver_output"
OUT_NAME="my_output"
EXEC_NAME="project_${ID}"


#Check if files were modified
diff $PROTO_HEADER ./prototypes.h
if [[ $? != 0 ]] ; then
   echo "prototypes.h should not be modified."
   exit 1
fi

diff $DRIVER_PROG ./driver_2C.c
if [[ $? != 0 ]] ; then
   echo "driver_2C.c should not be modified."
   exit 1
fi

#Check if the output file name is correct
if [[ ! -f ./$OUT_NAME ]] ; then
   echo "The output file name is not correct."
   exit 1
fi

#Check that a readme was provided
if [[ ! -f ./README ]] ; then
   echo "A README was not provided."
   exit 1
fi

#Check that code compiles with provided Makefile
make
if [[ $? != 0 ]] ; then
   echo "Compile failure!"
   exit 1
fi

#Remove your output file and generate a new one
#by running the executable
rm -f ./$OUT_NAME
./$EXEC_NAME > $OUT_NAME

#Check for correct output
diff $CORRECT_OUTPUT ./$OUT_NAME
if [[ $? != 0 ]] ; then
   echo "Your output is not correct."
   exit 1
fi

echo "Your program appears to be working correctly."
echo "It compiles, runs, and generates the correct output."
echo "Please upload your code to Canvas, following the instructions in the ${ID} prompt."
echo "Grading will consist of the steps performed by this script, complemented by inspection of your code."

