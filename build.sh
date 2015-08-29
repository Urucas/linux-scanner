#!/bin/bash
echo_fail()
{
  echo -e "\033[31m✗ \033[0m${1}";
  exit 1
}
echo_ok()
{
  echo -e "\033[32m✓ \033[0m${1}";
}

# clean
if [ -f linux-scanner ]; 
then
  rm linux-scanner
fi

ARCH=$(uname -m)
if [ $ARCH = "x86_64" ];
then
  FLAGS="-L/usr/lib/x86_64-linux-gnu/ " 
  OUTPUT="linux-scanner"
else
  FLAGS="-L/usr/lib/i386-linux-gnu/ "
  OUTPUT="linux-scanner32"
fi
FLAGS+="-I/usr/include "
FLAGS+="-Wall "
FLAGS+="-Wno-write-strings "

INPUT="main.cpp"

BUILD=$(gcc $FLAGS -o $OUTPUT $INPUT -lsane -lm -lpng)

if [ -f linux-scanner ];
then
  chmod 755 linux-scanner
  echo_ok "linux-scanner cli successfully created"
else
  echo_fail "Error building linux-scanner cli"
fi
