#
# Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates.
# Proprietary code. All rights reserved.
#

import unittest
import textwrap
from io import StringIO
from json import JSONDecodeError
from pathlib import Path
from unittest.mock import patch, mock_open

from snippet_directive import SNIPPET_REGEX, _group_consecutive_line_numbers, _convert_and_collect_snippets, \
    _replace_snippets_with_code_blocks, _assert_snippet_and_code_block_count, process_snippet_directive


class SnippetDirectiveProcessing(unittest.TestCase):

    @patch('sys.stdout', new_callable=StringIO)
    @patch('pathlib.Path.open', new_callable=mock_open, read_data='{ "invalid": "JSON"!!!}')
    def test_failing_to_read_snippet_data(self, mock_file, fake_output):
        self.assertRaises(JSONDecodeError, process_snippet_directive, Path('test.rst'), Path('test.json'))

        mock_file.assert_called_once()
        expected_stdout = 'FAILED TO READ test.json because of ' \
                          'JSONDecodeError("Expecting \',\' delimiter: line 1 column 20 (char 19)")'
        self.assertEqual(expected_stdout, fake_output.getvalue().strip())


class SnippetRegex(unittest.TestCase):

    def test_regex(self):
        valid_snippet = textwrap.dedent('''\
        .. snippet:: getting_started
            .. success:: Seq(1,2,3).map(_ * 2)
            .. assert:: RES.length == 3
        ''')

        self.assertTrue(SNIPPET_REGEX.match(valid_snippet))


class SnippetLineNumberGrouping(unittest.TestCase):

    def test_no_line_numbers(self):
        self.assertEqual([], _group_consecutive_line_numbers([]), 'should group into an empty list')

    def test_group_consecutive_line_numbers(self):
        line_numbers = [2, 3, 4, 5, 7, 9, 10, 13, 20]
        expected_grouping = [[2, 3, 4, 5], [7], [9, 10], [13], [20]]

        self.assertEqual(expected_grouping, _group_consecutive_line_numbers(line_numbers),
                         'should be a list of list containing consecutive line numbers')

    def test_group_unordered_line_numbers(self):
        line_numbers = [9, 7, 8, 2, 5, 3, 6]
        expected_grouping = [[2, 3], [5, 6, 7, 8, 9]]

        self.assertEqual(expected_grouping, _group_consecutive_line_numbers(line_numbers),
                         'should be a list of list containing consecutive line numbers')

    def test_string_line_numbers(self):
        self.assertRaises(TypeError, _group_consecutive_line_numbers, ['1', '2'],
                          'should throw for non-integer line numbers')


class SnippetDataToCodeBlockConversion(unittest.TestCase):
    def test_convert_and_collect_snippets(self):
        sample_snippet_data = {
            "68": {
                "command": "Seq(1,2,3).map(_ * 2)",
                "output": "res1: Seq[Int] = List(2, 4, 6)"
            },
            "69": {
                "command": "",
                "output": ""
            },
        }

        expected_snippet = ''.join([
            '.. code-block:: none\n',
            '\n',
            '    @ Seq(1,2,3).map(_ * 2)\n',
            '    res1: Seq[Int] = List(2, 4, 6)\n',
            '    \n'
        ])

        self.assertEqual(_convert_and_collect_snippets([[68, 69]], sample_snippet_data), [expected_snippet])


class ReplaceSnippetsWithCodeBlocks(unittest.TestCase):

    def test_replace_snippets_with_code_blocks(self):
        original = textwrap.dedent('''\
        Some awesome text.

        .. snippet:: first_snippet

        Some more awesome text.

        .. snippet:: second_snippet

        Even more awesome text.

        ''')

        expectation = textwrap.dedent('''\
        Some awesome text.

        10
        20

        Some more awesome text.

        30
        40
        50

        Even more awesome text.

        ''')

        self.assertEqual(expectation,
                         _replace_snippets_with_code_blocks(original, ['10\n20', '30\n40\n50']))

    def test_unequal_number_of_snippet_matches_and_code_blocks(self):
        original = textwrap.dedent('''\
        Some awesome text.

        .. snippet:: first_snippet
        Some more awesome text.
        .. snippet:: second_snippet

        Even more awesome text.

        ''')

        with self.assertRaises(AssertionError) as cm:
            _assert_snippet_and_code_block_count(Path('test.rst'), original, Path('test.json'), ['10\n20', '30\n40\n50'])
        self.assertEqual('Expect same number of snippet directives (found 1) in test.rst '
                         'as there are code blocks (found 2) resulting from test.json.\n\n'
                         'Possible Resolutions:\n'
                         '-> Check that there is at least one empty line between snippets and following text.\n'
                         '-> Included snippet output data may need to be updated.\n',
                         str(cm.exception))


if __name__ == '__main__':
    unittest.main()
