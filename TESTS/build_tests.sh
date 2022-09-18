#!/bin/sh

# LINKED LIST
LL_LIB=$(ls ../DataStructures/LinkedList/*.c)

echo "building linked list tests..."
ls LinkedList/*.c | while read -r filename; do
	(set -x ; gcc -o "${filename%.c}" "${LL_LIB}" "${filename}")
done

# QUEUE
QU_LIB=$(ls ../DataStructures/Queue/*.c)

echo "building queue tests..."
ls Queue/*.c | while read -r filename; do
	(set -x ; gcc -o "${filename%.c}" "${LL_LIB}" "${QU_LIB}" "${filename}")
done
