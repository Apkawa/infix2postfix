Build
=====

Requirements:

* cmake >= 3.0
* gcc


::
    mkdir build
    cd build
    cmake ..


Usage
=====

Generate infix file by 1024 symbols count +- close brackets::

    ./generate_infix 1024 > infix.txt

Convert infix to postfix::

    ./infix2postfix infix.txt > postfix.txt

Can use pipe::

    ./generate_infix 1024 | ./infix2postfix > postfix.txt

