#!/bin/bash
original_dir=$(pwd)
file_name="../build/myapp.exe"
destination_dir="./public/myapp.exe"

if ! [ -f "$file_name" ]; then
    echo "File $file_name does not exist. Compiling..."
    make -C ../
fi

# Check if the file exists
if [ -f "$file_name" ]; then
    echo "Copying $file_name to $destination_dir..."
    cp "$file_name" "$destination_dir"
    chmod +x $destination_dir
else
    echo "$file_name does not exist."
fi

export PORT=8443
export MYAPP_FLAGS="--test"

# cd "$original_dir"
