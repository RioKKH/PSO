#!/bin/bash

jis2utf() {
	local -r fin=$1
	local -r tempfile=$(mktemp)
	nkf -w "${fin}" > "${tempfile}" && mv "${tempfile}" "${fin}"
	# or nkf -w --overwrite "${fin}"
}

jis2utf "$@"
