#!/bin/sh

[ ! -d "executables" ] && mkdir executables

# LINKED LIST
LL_LIB=$(ls ../DataStructures/LinkedList/*.c)
filename="linked_list.c"

echo "building linked list test..."
(set -x ; gcc -o "executables/${filename%.c}" "${LL_LIB}" "${filename}")

# QUEUE
QU_LIB=$(ls ../DataStructures/Queue/*.c)
filename="queue.c"

echo "building queue test..."
(set -x ; gcc -o "executables/${filename%.c}" "${LL_LIB}" "${QU_LIB}" "${filename}")

# THREAD POOL
TP_LIB=$(ls ../SysArchitecture/ThreadPool/*.c)
filename="thread_pool.c"

echo "building thread pool tests..."
(set -x ; gcc -o "executables/${filename%.c}" "${LL_LIB}" "${QU_LIB}" "${TP_LIB}" "${filename}" -lpthread)
