The zipped file contains following CPP files.

README.txt

Sequential Versions
--------------------
fifo_queue_seq.cpp
pqueue_seq.cpp

Compilation:
icpc -o fifo_queue_seq fifo_queue_seq.cpp

Give second parameter if you want to print the output.

To Run Without output: ./fifo_queue_seq graph_file

To Get output in A FILE ./fifo_queue_seq graph_file true > output_file

Parallel Versions
-----------------
chunked_fifo_galois.cpp
dchunked_fifo_galois.cpp
dchunked_fifo_obim_galois.cpp
fifo_galois.cpp
local_queue_dchunked_galois.cpp
local_queue_galois.cpp

Parallel versions need to be compiled using CMAKE in galois environment.

To Run Without output: ./fifo_galois graph_file

To Get output in A FILE ./fifo_galois graph_file true > output_file


Report
-------------------------
software_multicore_hw3.pdf
