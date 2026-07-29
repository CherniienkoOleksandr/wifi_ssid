#!/bin/bash
# v0.3 — detect WiFi interface name
# fallback chain: iw dev → /proc/net/wireless → sysfs
#
# Usage:
#   source ./check_if_wpa.sh   → sets WIFI_IFACE (first), WIFI_IFACES (all)
#   ./check_if_wpa.sh          → prints names, one per line
#
# Exit: 0 if any found, 1 if none

(return 0 2>/dev/null) && _sourced=1 || _sourced=0

WIFI_IFACE=""
WIFI_IFACES=""

if command -v iw &>/dev/null; then
  WIFI_IFACES=$(iw dev 2>/dev/null | awk '/Interface/{print $2}')
fi

if [[ -z "$WIFI_IFACES" && -r /proc/net/wireless ]]; then
  WIFI_IFACES=$(awk 'NR>2{print $1}' /proc/net/wireless | tr -d ':')
fi

if [[ -z "$WIFI_IFACES" ]]; then
  for _d in /sys/class/net/*/wireless; do
    [[ -d "$_d" ]] || continue
    _if=$(basename "$(dirname "$_d")")
    WIFI_IFACES+="${WIFI_IFACES:+ }$_if"
  done
fi

WIFI_IFACE="${WIFI_IFACES%% *}"

if [[ $_sourced -eq 0 ]]; then
  if [[ -n "$WIFI_IFACE" ]]; then
    printf '%s\n' $WIFI_IFACES
    exit 0
  fi
  echo "no wifi interface found" >&2
  exit 1
fi
