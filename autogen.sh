#!/bin/sh

set -e

builddir="$(pwd)"
srcdir="$(dirname "$0")"

cd "$srcdir"
autoreconf -vfi

cd "$builddir"
[ -z "$NOCONFIGURE" ] && exec "$srcdir"/configure "$@"
