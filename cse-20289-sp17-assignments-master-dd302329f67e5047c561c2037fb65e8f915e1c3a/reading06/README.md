Reading 06
===========

1. MapReduce is trying to solve the problem of performing operations on very large data sets. It is a programming model and implementation that has one "master" machine that partitions the two tasks("mapping" and "reducing"), sending each partitioned task out to a worker machine. It is typically run on networks with large numbers of connected machines (as many as several thousand, or more).
2. There are three phases to a typical MapReduc workflow: 
    i) The master splits the input into many different data files for different workers to use, and assigns workers tasks. The master handles the macro flow of the program - assigning workers to map and reduce, handling task failures, etc.
    ii) Workers recieve map tasks from the master and process the input data. They parse in the input key/value pairs and output intermediate key/value pairs that are buffered into memory.
    iii) The master assigns workers to Reduce tasks that operate on the intermediate key/value pairs in the buffer. It groups together all the different data with the same intermediate key to pass to the Reduce function. The outputs of the Reduce function are saved as the final outputs of the MapReduce procedure.
