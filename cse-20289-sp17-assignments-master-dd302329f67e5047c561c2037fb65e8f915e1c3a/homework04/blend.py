#!/usr/bin/env python2.7

import atexit
import os
import re
import shutil
import sys
import tempfile
import urllib

import requests
os.environ['PATH'] = '~ccl/software/external/imagemagick/bin:' + os.environ['PATH']

# Global variables

REVERSE     = False
DELAY       = 20
STEPSIZE    = 5

# Functions

def usage(status=0):
    print '''Usage: {} [ -r -d DELAY -s STEPSIZE ] netid1 netid2 target
    -r          Blend forward and backward
    -d DELAY    GIF delay between frames (default: {})
    -s STEPSIZE Blending percentage increment (default: {})'''.format(
    os.path.basename(sys.argv[0]), DELAY, STEPSIZE
    )
    sys.exit(status)

def cleanup():
    shutil.rmtree(workspace)
    print("Cleaning up workspace: " + workspace)

# Parse command line options

args = sys.argv[1:]

while len(args) and args[0].startswith('-') and len(args[0]) > 1:
    arg = args.pop(0)
    
    if arg == "-r":
        REVERSE = True
    elif arg == "-d":
        DELAY = int(args.pop(0)) 
    elif arg == "-s":
        STEPSIZE = int(args.pop(0)) 
    else:
        usage(1)

if len(args) != 3:
    usage(1)

netid1 = args[0]
netid2 = args[1]
target = args[2]

# Main execution

# Create workspace, store initial directory, then change to it
workspace = tempfile.mkdtemp()
startdir = os.getcwd()
os.chdir(workspace)
print("Using workspace: " + workspace + " ... ")

# Register cleanup
atexit.register(cleanup)

# Extract portrait URLs
try:
    url1 = "https://engineering.nd.edu/profiles/" + netid1
    url2 = "https://engineering.nd.edu/profiles/" + netid2
    print("Fetching user profiles...")
    profile1 = requests.get(url1)
    profile2 = requests.get(url2)
    print("Searching for portrait of " + netid1 + " ...")
    imgurl1 = re.findall("https://.*jpeg",profile1.text)[0]
    print("Searching for portrait of " + netid2 + " ...")
    imgurl2 = re.findall("https://.*jpeg",profile2.text)[0]

    # Download portraits and save to files
    img1 = netid1 + ".jpg"
    img2 = netid2 + ".jpg"
    print("Downloading " + imgurl1 + "...")
    urllib.urlretrieve(imgurl1,img1)
    print("Downloading " + imgurl2 + "...")
    urllib.urlretrieve(imgurl2,img2)

except:
    print("Error - not found!")
    sys.exit(1)

# Generate blended composite images

# Generate list of steps from 0 to 100
steps = range(STEPSIZE,99,STEPSIZE)
steps.insert(0,0)
steps.insert(len(steps),100)

blendFiles = []
# Create blended files and add filenames to list
for step in steps:
    os.system("composite -blend "+str(step)+" "+img1+" "+img2+" "+str(step)+"-"+netid1+"_"+ netid2+".gif")
    blendFiles.insert(len(blendFiles),str(step)+"-"+netid1+"_"+ netid2+".gif")
    print("Generated " + blendFiles[-1] + " ...")

# Generate final animation
COMMAND = "convert -loop 0 -delay " + str(DELAY) + " "
# Add all blend files to command
for file in blendFiles:
    COMMAND += file + " "

# If reverse, add files in reverse too
if REVERSE == True:
    for index in range(len(blendFiles)-2,0,-1):
        COMMAND += blendFiles[index] + " "
COMMAND += startdir + "/" + target

print("Blending images...")
os.system(COMMAND)
