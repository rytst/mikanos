TARGET := hello.efi

CC := clang


.PHONY: all clean distclean

all: $(TARGET)

$(TARGET): hello.o
	lld-link /subsystem:efi_application \
		/entry:EfiMain /out:hello.efi hello.o

hello.o: hello.c
	$(CC) -target x86_64-pc-win32-coff -mno-red-zone \
		-fno-stack-protector -fshort-wchar -Wall -c hello.c

clean:
	$(RM) hello.o

distclean:
	$(RM) hello.efi
