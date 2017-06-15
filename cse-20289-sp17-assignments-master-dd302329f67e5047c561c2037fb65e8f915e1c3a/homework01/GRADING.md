Homework 01 - Grading
=====================

**Score**: 13.75/15

Deductions
----------
Act1 1b) -0.25 Private does not allow nd_campus or system:authuser to read or list to read or list that directory, while Public does.
Act4 2) -0.25 Need to sort before uniq. Try: `who | cut -d ' ' -f 1 | sort | uniq | wc -l`
Act4 3) -0.5 Errors not suppressed and results differ from expected results. Try: `du -h /etc/* 2> /dev/null | sort -r -h | head -n 5`
Act4 4) -0.25 The `grep /pts` is actually not needed and filters out some results.

Comments
--------
