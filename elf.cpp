#include <stdio.h>

#include "main.h"

class Elf32 : public Elf {
public:
	Elf32(const char *data, size_t size);
};

class Elf64 : public Elf {
public:
	Elf64(const char *data, size_t size);
};

Elf* Elf::open(const char *data, size_t size)
{
	unsigned char *elf_ident = (unsigned char*)data;
	if (elf_ident[EI_MAG0] != ELFMAG0 ||
	    elf_ident[EI_MAG1] != ELFMAG1 ||
	    elf_ident[EI_MAG2] != ELFMAG2 ||
	    elf_ident[EI_MAG3] != ELFMAG3)
	{
		log(Debug, "not an ELF file\n");
		return 0;
	}

	unsigned char ei_class      = elf_ident[EI_CLASS];
	unsigned char ei_version    = elf_ident[EI_VERSION];

	if (ei_version != EV_CURRENT) {
		log(Error, "invalid ELF version: %u\n", (unsigned)ei_version);
		return 0;
	}

	printf("version: %u\n", (unsigned int)elf_ident[EI_VERSION]);
	printf("osabi:   %u\n", (unsigned int)elf_ident[EI_OSABI]);
	for (size_t i = 0; i < EI_NIDENT; ++i) {
		printf("%i: %u\n", (int)i, (unsigned)elf_ident[i]);
	}

	if (ei_class == ELFCLASS32)
		return new Elf32(data, size);
	else if (ei_class == ELFCLASS64)
		return new Elf64(data, size);
	else {
		log(Error, "unrecognized ELF class: %u\n", (unsigned)ei_class);
		return 0;
	}
}

Elf::Elf(const char *data_, size_t size_)
: error(false), data(data_), size(size_)
{
	elf_ident = (unsigned char*)data;
	if (elf_ident[EI_MAG0] != ELFMAG0 ||
	    elf_ident[EI_MAG1] != ELFMAG1 ||
	    elf_ident[EI_MAG2] != ELFMAG2 ||
	    elf_ident[EI_MAG3] != ELFMAG3)
	{
		error = true;
		return;
	}

	ei_class      = elf_ident[EI_CLASS];
	ei_data       = elf_ident[EI_DATA];
	ei_version    = elf_ident[EI_VERSION];
	ei_osabi      = elf_ident[EI_OSABI];
	ei_abiversion = elf_ident[EI_ABIVERSION];
}

Elf32::Elf32(const char *data, size_t size)
: Elf(data, size)
{
}

Elf64::Elf64(const char *data, size_t size)
: Elf(data, size)
{
}
