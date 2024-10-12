// Format of an ELF executable file

#define ELF_MAGIC 0x464C457FU  // "\x7FELF" in little endian

// File header
struct elfhdr {
  uint magic; // must equal ELF_MAGIC, 用于识别文件是否是ELF格式
  uchar elf[12]; // 这里省略了很多, 参考：https://en.wikipedia.org/wiki/Executable_and_Linkable_Format
  ushort type; // Identifies object file type: 0x00:ET_NONE; 0x01:ET_REL; 0x02:ET_EXEC
  ushort machine;
  uint version;
  uint64 entry; // This is the memory address of the entry point from where the process starts executing.

  /* Points to the start of the program header table.
   * It usually follows the file header immediately following this one,
   * making the offset 0x34 or 0x40 for 32- and 64-bit ELF executables, respectively.
   */
  uint64 phoff;
  uint64 shoff; // Points to the start of the section header table.
  uint flags;
  ushort ehsize;
  ushort phentsize;
  ushort phnum; // Contains the number of entries in the program header table.
  ushort shentsize;
  ushort shnum;
  ushort shstrndx;
};

// Program section header
struct proghdr {
  uint32 type; // Identifies the type of the segment. 0x00000001:PT_LOAD(Loadable segment).
  uint32 flags;
  uint64 off; // Offset of the segment in the file image.
  uint64 vaddr; // Virtual address of the segment in memory.
  uint64 paddr; // On systems where physical address is relevant, reserved for segment's physical address.
  uint64 filesz; // Size in bytes of the segment in the file image. May be 0.
  uint64 memsz; // Size in bytes of the segment in memory. May be 0.
  uint64 align;
};

// Values for Proghdr type
#define ELF_PROG_LOAD           1 // PT_LOAD(Loadable segment)

// Flag bits for Proghdr flags
#define ELF_PROG_FLAG_EXEC      1
#define ELF_PROG_FLAG_WRITE     2
#define ELF_PROG_FLAG_READ      4
