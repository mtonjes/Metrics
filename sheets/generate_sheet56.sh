##!/bin/bash

python3 scripts/prerequisites.py

echo "Generating Sheet5"
python3 scripts/sheet5Main.py

echo "Generating Sheet6"
python3 scripts/sheet6Main.py
