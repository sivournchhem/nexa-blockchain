#!/bin/bash
# Define the local source code directory and cloud storage bucket
SOURCE_DIR="/home/sivournchhemusa/nexa-blockchain"  # Path to your source code
BUCKET="gs://nexa-backup/"  # Your Google Cloud Storage bucket name

# Use gsutil to copy the source code to the cloud bucket
gsutil -m cp -r $SOURCE_DIR/* $BUCKET
