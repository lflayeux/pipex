#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'

outfile_pipex="outfile_pipex.txt"
outfile_bash="outfile_bash.txt"

# TEST 1
echo "TEST 1: ./pipex Makefile cat cat outfile_pipex.txt"
./pipex "Makefile" "cat" "cat" "$outfile_pipex"

< Makefile cat | cat > "$outfile_bash"

if diff -q "$outfile_pipex" "$outfile_bash" > /dev/null; then
	echo -e "${GREEN}[OK]${RESET}"
else
	echo -e "${RED}[KO]${RESET}"
fi

# TEST 2
echo "TEST 2: ./pipex Makefile cat "" outfile_pipex.txt"
./pipex "Makefile" "cat" "" "$outfile_pipex"

< Makefile cat |  > "$outfile_bash"

if diff -q "$outfile_pipex" "$outfile_bash" > /dev/null; then
	echo -e "${GREEN}[OK]${RESET}"
else
	echo -e "${RED}[KO]${RESET}"
fi

# TEST 3
echo "TEST 3: ./pipex Makefile "" cat outfile_pipex.txt"
./pipex "Makefile" "" "cat" "$outfile_pipex"

< Makefile  | cat > "$outfile_bash"

if diff -q "$outfile_pipex" "$outfile_bash" > /dev/null; then
	echo -e "${GREEN}[OK]${RESET}"
else
	echo -e "${RED}[KO]${RESET}"
fi

# TEST 4
echo "TEST 4: ./pipex Makefile cat -e cat outfile_pipex.txt"
./pipex "Makefile" "cat -e" "cat" "$outfile_pipex"

< Makefile cat -e | cat > "$outfile_bash"

if diff -q "$outfile_pipex" "$outfile_bash" > /dev/null; then
	echo -e "${GREEN}[OK]${RESET}"
else
	echo -e "${RED}[KO]${RESET}"
fi
