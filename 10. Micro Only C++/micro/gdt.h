#ifndef __GDT_H__
#define __GDT_H__

struct GDT_Pointer {
	unsigned short size __attribute ((packed));
	unsigned long offset __attribute ((packed));
};


struct GDT_Entry {

    unsigned short limit_15_0;
    unsigned short base_addr_15_0;
    unsigned char base_addr_23_16;
    unsigned char type;
    unsigned char limit_19_16:4;
    unsigned char u:1;
    unsigned char x:1;
    unsigned char d:1;
    unsigned char g:1;
    unsigned char base_addr_31_24;
} __attribute__((__packed__));

#define GDT_CS_TYPE  0x9a
#define GDT_DS_TYPE  0x92

#define BUILD_GDT_ENTRY(base_addr, limit, segtype)      \
    {                               \
        (limit) & 0xffff,           \
        (base_addr) & 0xffff,       \
        ((base_addr) >> 16) & 0xff, \
        segtype,                    \
        ((limit) >> 16) & 0xf,      \
        0, 0, 1, 0,                 \
        ((base_addr) >> 24) & 0xff, \
    }

#endif
