#!/bin/sh
set -eux
cd "$(dirname "$0")"
qemu-system-i386 \
	-monitor stdio \
	-vnc 0.0.0.0:0,to=99,id=default \
	-boot order=c -drive file=os.iso,format=raw
