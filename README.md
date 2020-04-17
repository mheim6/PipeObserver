# PipeObserver

In the [pipeobserver.c] program, it starts by checking if the first argument it receives is a filename to open a corresponding file for write access. It then parses its own arguments, separating them into first and second executable’s names with corresponding arguments. It calls pipe to obtain a new process pipe. Then it continues by creating first and second child process of itself. The children then replaces itself by a process corresponding to the first and second executables to run and then passes on the appropriate arguments. To compile this program, use the following command: gcc -Wall -O3 -o pipeobserver pipeobserver.c. To run the program, use the following command (in Linux): ./pipeobserver <arg1> <arg2> <arg3>.