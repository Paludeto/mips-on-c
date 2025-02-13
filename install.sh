#!/bin/bash

if ! command -v mpv &>/dev/null; then
    echo "Instalando dependências..."
    sudo apt update && sudo apt install -y mpv
    if ! command -v mpv &>/dev/null; then
        echo "Falha na instalação."
        exit 1
    fi
fi

url="https://www.youtube.com/watch?v=dQw4w9WgXcQ"
mpv "$url"
