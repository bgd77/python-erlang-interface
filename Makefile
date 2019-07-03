.PHONY: build

all: build

build:
	python3 setup.py build
	cp build/lib.*/*.so ./

clean:
	rm -rf build/ MANIFEST pyerl.html *.beam

test:
	./tests/test_pyerl.py
	./tests/test_rpc.py

sdist:
	python setup.py sdist

upload:
	python setup.py sdist upload

doc:
	pydoc -w pyerl
