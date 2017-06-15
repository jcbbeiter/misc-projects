Reading 03
==========

1. echo "All your base are belong to us" | tr [:lower:] [:upper:]
2. echo "monkeys love bananas" | sed 's/monkeys/gorillaz'
3. echo "        monkeys love bananas" | sed 's/\s*\(.*\)/\1/'
4. cat /etc/passwd | grep '^root' | cut -d ':' -f 7
5.  cat /etc/passwd | sed 's/\/bin\/bash\|\/bin\/csh\|\/bin\/tcsh/\/usr\/bin\/python/' | grep python
6. cat /etc/passwd | grep '[^0-9]4[0-9]*7[^0-9]'
7. comm -12 --nocheck-order foo.txt bar.txt
8. diff file1.txt file2.txt
