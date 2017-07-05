##!/bin/bash

python scripts/prerequisites.py

echo "Generating Sheet1"
python scripts/sheet1Main.py

echo "for CADI PubComm queries, you only need Sheet1 and Sheet8"

echo "Generating Sheet8"
python scripts/sheet8Main.py

