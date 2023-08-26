# replyto
Small utility to create email replies

This utility reads from a file and pads every line with '>'.
Useful for email replies. Needed to do that once manually and decided to write an utility.

# usage
$ replyto [file] [-1]
Both parameters are optional.
If no file is speciffied, it reads from stdin.
If -1 is speciffied, it writes to stdout.
Configuration is done by editing replyto.h
