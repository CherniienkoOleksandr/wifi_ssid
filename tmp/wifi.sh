#!/bin/bash
# v1.3 
# Author: al and he
# Fri May 15 11:12:35 PM EEST 2026
#
set -euo pipefail

convert_to_json() {
	$py_tool wpa-to-json < $config_file > $wpa_json
}
convert_to_config() {
	$py_tool json-to-wpa < $wpa_json > $config_file
}
wpa_json=/tmp/wpa.json
wpa_tmp_json=/tmp/tmp_wpa.json
config_file=/etc/wpa_supplicant/wpa_supplicant-wlp5s0.conf
py_tool=/home/al/Git/wifi_ssid/wifi_conf_tool.py
wifi_man=/home/al/Git/wifi_ssid/ls.1

PARSED=$(getopt --options nclh: --long new-ssid,current,list,help: -name "$0" -- "$@")
eval set -- "$PARSED"
while true; do
	case $1 in
		-h|--help)
            echo "Use: $(basename "$0") [-h|--help]"
			echo "man other options"
			exit 0
            ;;
		-n|--new-ssid)
			convert_to_json
			read -p "Enter a ssid: " ssid
			echo "$1"
			echo "$2"
			read -p "Enter a password: " psk
			jq '(.networks[0]) |=(.ssid="'$ssid'" | .psk="'$psk'")' $wpa_json > $wpa_tmp_json && mv $wpa_tmp_json $wpa_json
			convert_to_config
			;;
		-c|--current)
			echo current ssid,psk:
            convert_to_json
			jq -r '.networks[] | "\(.ssid) \(.psk)"' < $wpa_json
			;;
		-l|--list)
			echo "list, not available yet"
			;;
		*)
			echo "Use: $(basename "$0") [-h|--help]"
			exit 0;
			;;
	esac

done
