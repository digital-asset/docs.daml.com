#!/usr/bin/env python3

from docutils import nodes
from docutils.parsers.rst import Directive

class EnterpriseOnlyDirective(Directive):
    def run(self):
        para_node = nodes.paragraph(text="This feature is only available in ")
        ref_node = nodes.reference('Canton Enterprise', 'Canton Enterprise', internal=True, refuri="/canton/usermanual/downloading.html")
        para_node += ref_node
        important_node = nodes.important()
        important_node += para_node
        return [important_node]

def setup(app):
    app.add_directive('enterprise-only', EnterpriseOnlyDirective)
