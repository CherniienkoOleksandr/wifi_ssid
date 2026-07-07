#!/usr/bin/env bash
#### todo
#	Пробелы u другие страшные вещи в sid и psk
#	Дупликация одинаковых
error_code=8
file=./known
if [[ $# -ne 1 ]]; then
	echo must have one arg.
	exit $error_code
else
	sid=$1
fi

function finder() {
	if grep -q "^$sid" $file; then
		psk=$(grep "^$sid" ./known | awk '{print $2}')
		echo "$sid"
		echo "$psk"
	else
		echo "SID not found in known file."
		exit $error_code
	fi

}
finder

function keep_saved() {
	n_lives=10
	total_lines=$(wc -l <$file)
	calc=$((total_lines - n_lives))
	sed -i "1,${calc}d" $file
	echo "keep_saved. Done"
	sort -u $file -o $file
}
keep_saved
