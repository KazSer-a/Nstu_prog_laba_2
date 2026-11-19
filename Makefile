.PHONY: all cpp go test clean

all: cpp go

cpp:
	$(MAKE) -C cpp

go:
	cd go && go build -o laba2 .

test:
	python3 tests/smoke_test.py

clean:
	$(MAKE) -C cpp clean
	rm -f go/laba2 go/laba2.exe
