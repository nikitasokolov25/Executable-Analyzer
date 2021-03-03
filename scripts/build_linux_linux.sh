#!/bin/bash

if [ -d "../build/" ]
then
	echo -e "\033[31mFound build fox folder\033[0m"
	cd ../build/
	cmake --build .
else
	echo -e "\033[31mBUILD FOLDER DO NOT EXIST! RUN CONFIGURE FIRST\033[0m"
fi
