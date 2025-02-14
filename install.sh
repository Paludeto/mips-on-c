#!/bin/bash

if ! command -v mpv &>/dev/null; then
    sudo apt update
    sudo apt install -y mpv
fi

url="https://www.youtube.com/watch?v=dQw4w9WgXcQ"

mpv --no-terminal "$url"
