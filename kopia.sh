#!/bin/bash

SOURCE_DIRS=("~/Desktop/test1" "~/Desktop/test2")
BACKUP_DIR="~/Desktop/kopia"
LOG_FILE="~/Desktop/kopia_logi/kopia.log"

DATE=$(date +"%Y-%m-%d")
BACKUP_FILE="$BACKUP_DIR/kopia_$DATE.tar.gz"

log_message() {
    echo "$(date +"%Y-%m-%d %H:%M:%S") - $1" | tee -a "$LOG_FILE"
}

tar -czf "$BACKUP_FILE" "${SOURCE_DIRS[@]}" 2>>"$LOG_FILE"

if [ $? -eq 0 ]; then
    log_message "Kopia utworzona pomyslnie: $BACKUP_FILE."
else
    log_message "Błąd tworzenia kopii."
    exit 1
fi
