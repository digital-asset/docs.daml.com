#!/usr/bin/env bash

# Script: update_tags.sh (Daml Finance)
#
# Description:
# Upgrades versioned references in the documentation from one version to another.
#
# Example:
#   Updates `type-daml-finance-lifecycle-v4-event-replacement-event-23525` to
#   `type-daml-finance-lifecycle-v5-event-replacement-event-53425` when upgrading to v5.
#
# Functionality:
# 1. **Extract References**: Scans all files in the reference directory (`REF_DIR`) for lines
#    starting with `.. _module`, `.. _type`, `.. _function`, or `.. _constr`.
# 2. **Update References**:
#    - Locates corresponding references in the target directory (`TRGT_DIR`).
#    - Updates the version segment from the old version (e.g., `v4`) to the new version (e.g., `v5`).
#    - Changes the numerical identifier to ensure uniqueness.
#
# Prerequisites:
# - **Build Workdir**: Ensure the working directory (`workdir`) is fully built to have up-to-date
#   reference files.
#
# Usage:
# 1. **Set Directories**:
#    - Define `REF_DIR` with the path to current reference files.
#    - Define `TRGT_DIR` with the path where references should be updated.
# 2. **Execute Script**:
#    - Run the script in the terminal to automatically scan and update all relevant references based
#      on the new version.

# Get the directory where the script is located, to ensure paths are correct no matter where it's called from
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Set the reference directory (contains canonical _module, _type, _function, _constr lines)
REF_DIR="${SCRIPT_DIR}/../../workdir/build/source/source/daml-finance/reference/code-documentation/daml-finance-rst"

# Set the target directory (where we need to replace occurrences)
TRGT_DIR="${SCRIPT_DIR}/../../docs/daml-finance"

echo "Reference directory: $REF_DIR"
echo "Target directory: $TRGT_DIR"

tmpfile=$(mktemp)
echo "Temporary file: $tmpfile"

# Regex explanation:
# .. _module-daml-finance-account-v4-account-[0-9]+$ : Match lines with the format 'module-<any number>'
grep -hEr '..[[:space:]]+_(module|type|function|constr).*-[0-9]+:$' "$REF_DIR" > "$tmpfile" || true

line_count=$(wc -l < "$tmpfile")
echo "Found $line_count canonical lines."

while IFS= read -r line; do
    [ -z "$line" ] && continue
    echo "Processing line: $line"

    # Remove everything before '.. _' and trailing ':'
    line_no_prefix="${line##*.. _}"
    base="${line_no_prefix%:}"

    # Extract the last number
    number="${base##*-}"

    # Extract everything before the number as the pattern
    pattern="${base%-*}"

    echo "  Pattern: $pattern"
    echo "  Number: $number"

    # Check if the pattern contains a version segment like -vX- (e.g. -v4-)
    # Example pattern: type-daml-finance-lifecycle-v4-event-replacement-event
    if [[ $pattern =~ ^(.*)(-v[0-9]+)(-.*)$ ]]; then
        pattern_before="${BASH_REMATCH[1]}"  # up to and including 'v'
        pattern_version="${BASH_REMATCH[2]}" # the version digits
        pattern_after="${BASH_REMATCH[3]}"   # the rest after the version

        echo "  Detected version segment: $pattern_version"
        echo "  Pattern before version: $pattern_before"
        echo "  Pattern after version: $pattern_after"

        # In target files,
        # 1. Override any version number (say "-v3" or ""), with the current one (say "-v4").
        # 2. Override the reference number with the current one.
        # Using '#' as sed delimiter to avoid conflicts with '-'.
        find "$TRGT_DIR" -type f -exec sed -i "s#${pattern_before}\(-v[0-9]\\{1,\\}\)\?${pattern_after}-[0-9]\\{1,\\}#${pattern_before}${pattern_version}${pattern_after}-${number}#g" {} +

    else
        # No version found, do the standard replacement
        find "$TRGT_DIR" -type f -exec sed -i "s#${pattern}-[0-9]\\{1,\\}#${pattern}-${number}#g" {} +
    fi

    echo "  Done processing this pattern."
    echo
done < "$tmpfile"

rm "$tmpfile"
echo "All done."
