#!/usr/bin/env bash

if [ -z "$(whereis fdfind)" ]; then
  echo "fdfind not found, please install it"
  read -r -p "The script can install it? [y/N] " response
  if [[ "$response" =~ ^([yY][eE][sS]|[yY])+$ ]]; then
    sudo apt install fd-find
  else
    exit 1
  fi
fi

echo "Running clang-format..."

if [ "$(fdfind -E "cmake-*/" -i -e cpp -e hpp | xargs clang-format-16 -style=file --verbose --dry-run --Werror)" ]; then
  echo "No files to format"
  exit 0
else
  echo "Some files need to be formatted"
  read -r -p "Do you want to format it? [y/N] " response
  if [[ "$response" =~ ^([yY][eE][sS]|[yY])+$ ]]; then
    fdfind -E "cmake-*/" -i -e cpp -e hpp | xargs clang-format-16 -style=file -i
    exit 0
  else
    exit 1
  fi
fi
