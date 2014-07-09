#!/bin/bash

#Add the compilation commands to this script. Note that currently this is not a complete code and probably just works for my Ubuntu machine...

g++ penetrability.cpp -o penetrability `root-config --cflags --libs` -lgsl -lgslcblas
