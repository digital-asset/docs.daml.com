#!/usr/bin/env python3

from docutils import nodes
from docutils.parsers.rst import Directive

class IgnoreSnippets(Directive):
    has_content = True
    def run(self):
        p = nodes.important()
        p += nodes.paragraph(text="Snippet removed for live-preview.")
        return [p]

def setup(app):
    app.add_directive('snippet', IgnoreSnippets)
