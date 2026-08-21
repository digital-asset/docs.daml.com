#!/usr/bin/env python3
#
# Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
# Proprietary code. All rights reserved.
#

"""\
This script replaces the snippet directives in-place with the pre-recorded snippet output data.

Usage: snippet_directive.py SNIPPET_DATA_DIRECTORY PROCESSING_DIRECTORY
"""
import re
import os
import json
import sys
from operator import itemgetter
from itertools import groupby
from pathlib import Path

# matches our custom snippet directive until there is an empty line
SNIPPET_REGEX = re.compile(r'^\.{2} snippet.*(?:\n.+)*[^\n]', re.MULTILINE)


def process_snippet_directive(rst_file: Path, snippet_data_file: Path) -> None:
    # load snippet data
    with snippet_data_file.open(encoding='utf-8') as f:
        try:
            snippet_data_sets = json.load(f)
        except Exception as e:
            print(f'FAILED TO READ {snippet_data_file} because of {repr(e)}')
            raise e

        # snippet line numbers; a single snippet (data set) may cover multiple lines in its rst file
        unordered_line_numbers = [int(key) for key in snippet_data_sets.keys()]

        # group consecutive line numbers;
        # so that all lines belonging to a single snippet (data set) are grouped together consecutively
        grouped_line_numbers = _group_consecutive_line_numbers(unordered_line_numbers)

        # convert snippets (data sets) into rst code blocks, and collect them as they appear in the rst file
        code_blocks = _convert_and_collect_snippets(grouped_line_numbers, snippet_data_sets)

        original = rst_file.read_text(encoding='utf-8')

        _assert_snippet_and_code_block_count(rst_file, original, snippet_data_file, code_blocks)

        updated = _replace_snippets_with_code_blocks(original, code_blocks)

        rst_file.write_text(updated, encoding='utf-8', newline='\n')


def _group_consecutive_line_numbers(line_numbers: list[int]) -> list[list[int]]:
    ranges = []
    for key, groupIterator in groupby(enumerate(sorted(line_numbers)), lambda pair: pair[0] - pair[1]):
        group = list(map(itemgetter(1), groupIterator))
        ranges.append(group)
    return ranges


def _convert_and_collect_snippets(
        grouped_line_numbers: list[list[int]],
        a_json: dict[str, dict[str, str]]) -> list[str]:
    code_blocks = []
    for group in grouped_line_numbers:
        code_blocks.append(_convert_json_snippet_data_to_rst_code_block(group, a_json))
    return code_blocks


def _convert_json_snippet_data_to_rst_code_block(line_numbers: list[int], a_json: dict[str, dict[str, str]]) -> str:
    code_block = ''
    for lno in line_numbers:
        code_block += _convert_line_number_to_rst(f'{lno}', a_json)
    return code_block


def _convert_line_number_to_rst(line_number: str, a_json: dict[str, dict[str, str]]) -> str:
    out = ''
    cmd = a_json[line_number]['command']
    if len(cmd) > 0:
        out += '.. code-block:: none\n\n    @ ' + cmd + '\n'
    res = a_json[line_number]['output'].split('\n')
    # print("replacing line %s with %s and %d lines of output" % (line_number, cmd, len(res)))
    if len(res) > 0:
        for oo in res:
            out += '    ' + oo + '\n'
    return out


def _assert_snippet_and_code_block_count(rst_file: Path,
                                         rst_content: str,
                                         snippet_data_file: Path,
                                         code_blocks: list[str]) -> None:
    snippet_count = len(SNIPPET_REGEX.findall(rst_content))
    code_block_count = len(code_blocks)
    assert snippet_count == code_block_count, \
        f'Expect same number of snippet directives (found {snippet_count}) in {rst_file} ' \
        f'as there are code blocks (found {code_block_count}) resulting from {snippet_data_file}.\n\n' \
        f'Possible Resolutions:\n' \
        f'-> Check that there is at least one empty line between snippets and following text.\n' \
        f'-> Included snippet output data may need to be updated.\n'


def _replace_snippets_with_code_blocks(original_rst: str, code_blocks: list[str]) -> str:
    code_blocks_iterator = iter(code_blocks)
    return SNIPPET_REGEX.sub(lambda _: next(code_blocks_iterator), original_rst)


if __name__ == '__main__':

    assert len(sys.argv) == 3, \
        'Expect 2 directories as arguments; the snippet (input) data directory, and the (output) processing directory'
    snippet_data_dir, output_dir = sys.argv[1:]

    for root, dirs, files in os.walk(output_dir):
        rst_files = [file for file in files if file.endswith('.rst')]
        for rst in rst_files:
            base = root[len(output_dir):]
            data = Path(snippet_data_dir + base + '/' + rst[:-4] + '.json')
            # check if we have a corresponding file with snippets
            if data.exists():
                print(('found', data, 'for', rst))
                process_snippet_directive(Path(root, rst), data)
