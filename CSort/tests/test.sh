#!/bin/bash


echo "quick sort"
{ /usr/bin/time -v ./test_quick.sh >/dev/null; } |& grep -E \
    "Max|User time|System time"
echo

echo "insert sort"
{ /usr/bin/time -v ./test_insert.sh >/dev/null; } |& grep -E \
    "Max|User time|System time"
echo

echo "bubble sort"
{ /usr/bin/time -v ./test_bubble.sh >/dev/null; } |& grep -E \
    "Max|User time|System time"
