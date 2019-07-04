PyErl
=====

PyErl is Erlang Interface for Python. which help you integrate
programs written in Python and Erlang.

This is a fork of https://github.com/hamano/python-erlang-interface that adds Python 3 support. More precisely Python 3.6.8 was used.

Please note that the **print_term** methods were removed because of changes to the C API in Python 3.

While the tests pass and for me the module works ok, I cannot guarantee that all is fine, so use it at your own risk.

DEPENDENCIES
------------

This module requires these other modules and libraries:

Erlang/OTP R12 or later

In debian:
~~~
apt-get install erlang-dev
~~~

INSTALL
-------

~~~
python setup.py build
python setup.py install
~~~

EXAMPLE
-------

* make erlang terms

~~~
import pyerl
atom = pyerl.mk_atom("hello")
string = pyerl.mk_string("world")
int = pyerl.mk_int(-1)
list = pyerl.mk_list([atom, string, int])
print list
~~~

* call rpc

~~~
# just call pingpong:ping() in node2@localhost
import pyerl
host = "localhost"
name = "node1"
node = name + "@" + host
cookie = "TESTCOOKIE"
pyerl.connect_xinit(host, name, node, "127.0.0.1", cookie, 1)
pyerl.xconnect("127.0.0.1", "node2")
atom = pyerl.mk_atom("ping")
args = pyerl.mk_list([atom]);
eterm = pyerl.rpc(sock, "pingpong", "ping", args);
pyerl.close_connection(sock);
print eterm
~~~

AUTHOR
------
Original author: Tsukasa Hamano <code@cuspy.org>

Python 3 update: https://github.com/bgd77
