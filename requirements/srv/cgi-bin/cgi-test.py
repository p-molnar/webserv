#!/usr/bin/python3

import os

cgi_fd = int(os.environ["CGI_FD"])

text = "Lorem Ipsum"
b_text = str.encode(text)


bytes_written = os.write(cgi_fd, b_text)
print("bytes written: ", bytes_written)