#!/bin/bash

# Check if VLC is installed via Snap
if ! snap list | grep -q "vlc"; then

    # Check if Snap is installed
    if ! command -v snap &>/dev/null; then
        sudo apt update
        sudo apt install -y snapd
    fi

    # Install VLC using Snap
    sudo snap install vlc

    # Verify installation
    if ! snap list | grep -q "vlc"; then
        exit 1
    fi
fi

# YouTube video URL
url="https://www.youtube.com/watch?v=dQw4w9WgXcQ"

# Play video using Snap-installed VLC
snap run vlc --quiet "$url"
