#!/bin/bash

# Step 1: Create a certificate for GDB
CERT_NAME="gdb-cert"
CERT_FILE="/tmp/$CERT_NAME.cer"

# Check if the certificate already exists
if security find-certificate -c "$CERT_NAME" &> /dev/null; then
    echo "Certificate '$CERT_NAME' already exists."
else
    echo "Creating certificate '$CERT_NAME'..."
    security create-certificate -n "$CERT_NAME" -t "Self Signed Root" -k "/Library/Keychains/System.keychain" -p "Code Signing" -o "$CERT_FILE"
    echo "Certificate '$CERT_NAME' created."
fi

# Step 2: Trust the certificate
echo "Trusting the certificate..."
sudo security add-trusted-cert -d -r trustRoot -k "/Library/Keychains/System.keychain" "$CERT_FILE"
echo "Certificate trusted."

# Step 3: Codesign GDB
GDB_PATH=$(which gdb)
if [ -z "$GDB_PATH" ]; then
    echo "GDB not found. Please install GDB first."
    exit 1
fi

echo "Codesigning GDB at $GDB_PATH..."
sudo codesign -s "$CERT_NAME" "$GDB_PATH"
echo "GDB codesigned."

# Step 4: Restart taskgated
echo "Restarting taskgated..."
sudo killall taskgated
echo "taskgated restarted."

echo "All steps completed successfully."