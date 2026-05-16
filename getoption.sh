#!/bin/bash
# Get the option value from the command line arguments script version 1.0
# Author: al
# Fri May 15 11:12:35 PM EEST 2026
#
EXIT_CODE=0
passwd () {
	echo password one 
	EXIT_CODE=6
	
}
new() {
	echo entered ssdi, if passwd return not 5, ssid will be change
	passwd
	if [ $EXIT_CODE == 5 ]; then
		echo one
	else 
		echo "netu ddone"
		exit 1
	fi
		
}

if [ $# == 0 ]; then
	new;
	passwd; 
	exit 
fi

if [ "$1" == "-h" ] || [ "$1" == "--help" ]; then
	echo "use help"
else
	case $1 in
		-n|--new-ssid)
			SSID=$2
			echo "SSID: $SSID"
			# проверяем $2 и $3 на ввод сразу
			# read sid, and password
			# -> save
			# условие, если $2 не пустой, то вводим пароль
			#
			;;
		-c|--current)
			echo "current ssid"
			;;
		-l|--list)
			echo "list"
			;;
		-s|--ssid)
			echo "enter ssid"
			;;
		*)
			echo "something else"
			exit 1;
			;;
	esac
fi

