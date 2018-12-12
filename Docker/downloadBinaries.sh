#!/bin/bash

# Get CDT release by tag
if [ "$1" = "latest" ]; then
	cdt_url=$(curl -s https://api.github.com/repos/EOSIO/eosio.cdt/releases/latest | grep "browser_download_url.*deb" | cut -d '"' -f 4)
	cdt_filename=$(echo "$cdt_url" | awk -F "/" '{print $NF}')
else
    cdt_url=$(curl -s https://api.github.com/repos/EOSIO/eosio.cdt/releases/tags/$1 | grep "browser_download_url.*deb" | cut -d '"' -f 4)
	cdt_filename=$(echo "$cdt_url" | awk -F "/" '{print $NF}')
fi

# Make sure we could get it
if [ -z "$cdt_filename" ]; then
    echo "Either $1 is not a valid release for eosio.cdt, or there is not a published .deb package for the release."
    exit 1
fi

# Download
wget $cdt_url
