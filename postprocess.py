import sys


begin_skipped = False

with open("input.txt", 'r') as f:
    with open("output.txt", 'w') as of:
        of.writelines('``` diff \n')
        for line in f:
            if begin_skipped == False:
                if line.find("Global test environment set-up") == -1:
                    continue
                begin_skipped = True
                continue

            if line.find("Global test environment tear-down") != -1:
                break

            line = line.replace('[==========]', '+[==========]')
            line = line.replace('[----------]', '+[----------]')
            line = line.replace('[ RUN      ]', '+[ RUN      ]')
            line = line.replace('[       OK ]', '+[       OK ]')
            line = line.replace('[  FAILED  ]', '-[  FAILED  ]')
            if line.find(": error:") != -1:
                line = "-"+line
            of.writelines(line)
        of.writelines('```')
        of.writelines('![UML](./UML.png)')