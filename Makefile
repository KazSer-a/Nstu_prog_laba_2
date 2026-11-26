.PHONY: all cpp go clean

all: cpp go

cpp:
	$(MAKE) -C cpp

go:
	cd go && go build -o laba2 .

clean:
	$(MAKE) -C cpp clean
	rm -f go/laba2 go/laba2.exe
