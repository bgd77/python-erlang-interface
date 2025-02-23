#!/usr/bin/env python

from distutils.core import setup, Extension
import os
import re

otp_dir = None

def getSearchDir():
    return os.environ.get('ERL_HOME', os.environ.get('ERLANG_HOME', '/usr'))

def findInSubdirectory(filename, subdirectory=''):
    if subdirectory:
        path = subdirectory
    else:
        path = os.getcwd()
    for root, dirs, names in os.walk(path):
        if filename in names:
            this_path = re.sub('include/erl_interface.h', '', os.path.join(root, filename))
            return this_path
    return None

otp_dir = findInSubdirectory('erl_interface.h', getSearchDir())

if otp_dir == None:
    print('Cannot find Erlang/OTP directory.')
    print('You need to install Erlang/OTP.')
    exit(1)

include_dirs = [otp_dir + 'include/']
library_dirs = [otp_dir + 'lib/']

setup(name = "PyErl",
      version = "0.6",
      description = "Erlang Interface for Python 3",
      long_description = '''
PyErl is Erlang Interface for Python 3, which help you integrate
programs written in Python 3 and Erlang.
''',
      author = "Tsukasa Hamano",
      author_email = "code@cuspy.org",
      update="Bogdan Sacarea",
      url="http://github.com/bgd77/python-erlang-interface",
      license="MPL",
      ext_modules = [
        Extension(
            "pyerl",
            ["pyerl.c", "eterm.c"],
            libraries=["erl_interface", "ei"],
            include_dirs = include_dirs,
            library_dirs = library_dirs,
            )
        ],
      classifiers = [
        'Programming Language :: Python :: 3',
        'Programming Language :: Erlang',
        'Topic :: Software Development :: Libraries :: Python Modules',
        ],
      )
