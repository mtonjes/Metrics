##!/bin/bash

python scripts/prerequisites.py

echo "Generating Sheet5"
python scripts/sheet5Main.py

echo "Generating Sheet6"
python scripts/sheet6Main.py
