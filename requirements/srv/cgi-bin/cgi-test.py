#!/usr/bin/python3

import os

cgi_fd = os.environ["CGI_FD"]

text = "Lorem Ipsum"

os.write(cgi_fd, text)