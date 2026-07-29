1. interface
	iw inverface is universal on linux
	wpa_cli only if wpa

cat net/wireless | awk 'NR>2{print $1}' | tr -d ':'
