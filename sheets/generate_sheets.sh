##!/bin/bash

python3 scripts/prerequisites.py

echo "Generating Sheet1"
python3 scripts/sheet1Main.py

echo "Generating Sheet2"
python3 scripts/sheet2Main.py

echo "Generating Sheet3"
python3 scripts/sheet3Main.py

echo "Generating Sheet4"
python3 scripts/sheet4Main.py

echo "Generating Sheet5"
python3 scripts/sheet5Main.py

echo "Generating Sheet6"
python3 scripts/sheet6Main.py
