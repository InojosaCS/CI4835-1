#! /bin/bash

if [ $# -ne 3 ]; then
	echo "Usage: test_server.sh <port> <input file> <output file>"
	exit 1
fi

port="$1"
input_file="$2"
output_file="$3"

# Start server process
./calcServer $port &
CALC_PID=$!

# Send input to server, capture its output
timeout 10 nc localhost $port < $input_file > $output_file

# Could do additional sessions here if desired...

# Kill server process
sleep 1
kill -9 $CALC_PID
