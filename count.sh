awk '$0 ~ /won/ {lines++} $0 ~ /emamenko.filler won/ {wlines++} END { printf("\x1b[1;92memamenko\x1b[0m won \x1b[1m%d\x1b[0m fights from \x1b[1m%d\x1b[0m\n", wlines, lines) }' test.txt
