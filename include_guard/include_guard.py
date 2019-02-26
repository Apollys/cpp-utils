#! /usr/bin/python2

from __future__ import print_function, division
import os
import re
import sys

def ParseArgs():
  if (len(sys.argv) < 2) or (len(sys.argv) > 3):
    print('Usage:', sys.argv[0], '<filename>', '<{optional} identifier>')
    sys.exit()
  filename = os.path.abspath(sys.argv[1])
  identifier = ''
  if len(sys.argv) >= 3:
    identifier = sys.argv[2]
  else:
    upper_basename = os.path.basename(filename).upper();
    non_alphanumeric_pattern = '[^0-9a-zA-Z]'
    identifier = re.sub(non_alphanumeric_pattern, '_', upper_basename)
  return filename, identifier
  
def main():
  filename, identifier = ParseArgs()
  lines = []
  # Prepend beginning macros
  lines.append('#ifndef ' + identifier + '\n')
  lines.append('#define ' + identifier + '\n')
  lines.append('\n')
  # Read file
  with open(filename, 'r') as f:
    lines.extend(f.readlines())
  if (lines[-1] != '\n'):
    lines.append('\n')
  # Append ending macro
  lines.append('#endif  // ' + identifier + '\n')
  lines.append('\n')
  # Write output
  with open(filename, 'w') as f:
    for line in lines:
      f.write(line)

if __name__ == '__main__':
  main()
  
