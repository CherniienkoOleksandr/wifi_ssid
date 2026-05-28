#!/usr/bin/env python3
"""Convert wpa_supplicant config to/from JSON."""

import json
import sys
from typing import TextIO


def strip_inline_comment(line: str) -> str:
    in_quote = False
    for i, ch in enumerate(line):
        if ch == '"':
            in_quote = not in_quote
        elif ch == '#' and not in_quote:
            return line[:i].rstrip()
    return line.rstrip()


def parse_key_value(line: str) -> tuple[str, str] | None:
    line = strip_inline_comment(line)
    if '=' not in line:
        return None
    key, _, value = line.partition('=')
    key = key.strip()
    value = value.strip().strip('"')
    if not key:
        return None
    return key, value


def needs_quoting(value: str) -> bool:
    return bool(value) and (' ' in value or '\t' in value or '#' in value)


def wpa_to_json(f: TextIO) -> dict:
    settings = {}
    networks = []
    current_network = None

    for raw_line in f:
        line = raw_line.rstrip()
        stripped = line.strip()

        if not stripped:
            continue

        if stripped.startswith('#'):
            continue

        if stripped.startswith('network={') or stripped == 'network={':
            current_network = {}
            continue

        if current_network is not None:
            if stripped == '}':
                if current_network.get('ssid'):
                    networks.append(current_network)
                current_network = None
                continue
            if stripped.startswith('#'):
                continue
            kv = parse_key_value(line)
            if kv:
                current_network[kv[0]] = kv[1]
            continue

        kv = parse_key_value(line)
        if kv:
            settings[kv[0]] = kv[1]

    return {'settings': settings, 'networks': networks}


def json_to_wpa(f: TextIO) -> str:
    data = json.load(f)
    lines = []

    for key, value in data.get('settings', {}).items():
        lines.append(f'{key}={value}')

    if lines:
        lines.append('')

    for net in data.get('networks', []):
        lines.append('network={')
        for key, value in net.items():
            val = value.strip('"')
            if key in ('ssid', 'psk') or needs_quoting(val):
                lines.append(f'\t{key}="{val}"')
            else:
                lines.append(f'\t{key}={val}')
        lines.append('}')
        lines.append('')

    return '\n'.join(lines).rstrip('\n') + '\n'


def main():
    if len(sys.argv) != 2:
        print('Usage: wifi_conf_tool.py (wpa-to-json|json-to-wpa) < input > output',
              file=sys.stderr)
        sys.exit(1)

    command = sys.argv[1]

    if command == 'wpa-to-json':
        data = wpa_to_json(sys.stdin)
        json.dump(data, sys.stdout, indent=2, ensure_ascii=False)
        sys.stdout.write('\n')
    elif command == 'json-to-wpa':
        output = json_to_wpa(sys.stdin)
        sys.stdout.write(output)
    else:
        print(f'Unknown command: {command}', file=sys.stderr)
        sys.exit(1)


if __name__ == '__main__':
    main()
