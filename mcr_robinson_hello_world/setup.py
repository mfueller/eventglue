#!/usr/bin/env python

from distutils.core import setup
from catkin_pkg.python_setup import generate_distutils_setup

d = generate_distutils_setup(
    packages=['mcr_robinson_hello_world'],
    package_dir={'': 'common/scripts'}
)

setup(**d)