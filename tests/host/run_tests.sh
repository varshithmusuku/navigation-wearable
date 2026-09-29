#!/bin/sh
# Usage: sh tests/host/run_tests.sh   (from repo root; needs g++)
cd "$(dirname "$0")/../.." || exit 1
for fw in original_tested navigation_wearable; do
  echo "=== firmware/$fw ==="
  g++ -std=c++17 -o /tmp/host_$fw -DFIRMWARE_FILE="\"../../firmware/$fw/$fw.ino\"" tests/host/host_test.cpp || exit 1
  for s in 1 2 3 4 5 6; do /tmp/host_$fw $s | grep RESULT; done
done
