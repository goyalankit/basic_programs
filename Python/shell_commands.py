#!/usr/bin/env python

import optparse
from sh import grep

def main():
    p = optparse.OptionParser()
    p.add_option('--person', '-p', default="world")
    options, arguments = p.parse_args()
    print 'Hello %s' % options.person


if __name__ == '__main__':
    main()
