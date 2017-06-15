#!/usr/bin/env python2.7

import os
import re
import sys

import requests

# Global variables

FIELD        = "title"
LIMIT        = 10
SUBREDDIT    = "linux" 

# Functions

def usage(status=0):
    print(''''Usage: reddit.py [ -f FIELD -s SUBREDDIT ] regex
        -f FIELD        Which field to search (default: title)
        -n LIMIT        Limit number of articles to report (default: 10)
        -s SUBREDDIT    Which subreddit to search (default: linux)''')
    sys.exit(status)

# Pulls desired field from JSON structure
def getAttribute(string, field):
    match = re.match(field + ' "(.*)", "', string)
    if match:
        return match.group(1)
    else:
        return "Error reading attribute"



# Parse command line options

args = sys.argv[1:]

while len(args) and args[0].startswith('-') and len(args[0]) > 1:
    arg = args.pop(0)
    
    if arg == "-f":
        FIELD = args.pop(0)
    elif arg == "-n":
        LIMIT = int(args.pop(0)) 
    elif arg == "-s":
        SUBREDDIT = args.pop(0) 
    elif arg == '-h':
        usage(0)
    else:
        usage(1)

if len(args) != 1:
    REGEX = '.*'
else:
    REGEX = args.pop(0)

headers  = {'user-agent': 'reddit-{}'.format(os.environ['USER'])}
response = requests.get("https://www.reddit.com/r/" + SUBREDDIT + "/.json", headers=headers)
text = response.text

# insert newlines before each post, so each line is one post, and split into list
text = text.replace('{"kind"','\n{"kind"')
posts = text.split('\n')

# remove all empty lines
posts = [post for post in posts if post != '']

# removes first listing
posts = posts[1:]

index = 1

# Make sure the user provided a valid field
if len(re.findall('^.*"' + FIELD + '":.*$', posts[0])) == 0:
    print("Error: invalid field '" + FIELD + "'")
    sys.exit(1)  


# iterates through all posts
for post in posts:

    # check FIELD for REGEX, skips if not present
    field = str(re.match('^.*"' + FIELD + '": "([^"]*)".*$', post).group(1))
    if(re.search(REGEX,field) == None):
        continue 

    # scrapes data from post
    author = re.match('^.*"author": "(.*)", "saved".*$', post).group(1)
    title = re.match('^.*"title": "(.*)", "created_utc.*$', post).group(1)
    link = "http://www.reddit.com" + re.match('^.*"permalink": "(.*)", "num_reports.*$', post).group(1)

    # Generates shortened url
    short = requests.get('http://is.gd/create.php',{'format' : 'json','url' : link})
    if "errorcode" in short.json():
        print "Error shortening link"
        shorturl = "Error: Too many is.gd shortening requests."
    else:
        shorturl = short.json()["shorturl"]

    # print post information
    print("%02d." % index + " Title:   " + title)
    print("    Author:  " + author)
    print("    Link:    " + link)
    print("    Short:   " + shorturl)
    print ''

    # stop if printed max number
    if index == LIMIT:
        break
    index+= 1
