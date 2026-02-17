#!/bin/bash

echo "=== Hedgewars Asset Analysis ==="

if [ ! -d "hedgewars/share/hedgewars/Data" ]; then
    echo "Error: Data/ directory not found"
    echo "Make sure hedgewars is cloned"
    exit 1
fi

cd hedgewars/share/hedgewars/Data

echo ""
echo "Total size:"
du -sh .

echo ""
echo "Breakdown by directory:"
du -sh */ | sort -h

echo ""
echo "Largest files:"
find . -type f -exec du -h {} + | sort -rh | head -20

echo ""
echo "File type distribution:"
find . -type f | sed 's/.*\.//' | sort | uniq -c | sort -rn | head -10
