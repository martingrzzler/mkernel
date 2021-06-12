#include "disk.h"
#include "status.h"
#include "config.h"
#include "io/io.h"
#include "memory/memory.h"

struct disk disk;

int disk_read_sector(int lba, int total, void *buf)
{
  // remember LBA consists of 28 bits not 32!
  outb(0x1F6, (lba >> 24) | 0xE0); // tells disk we ant to use LBA mode and send bits 24 - 27
  outb(0x1F2, total);
  outb(0x1F3, (unsigned char)(lba & 0xff)); // sends bits 0 - 7
  outb(0x1F4, (unsigned char)(lba >> 8));   // send bits 8 - 15
  outb(0x1F5, (unsigned char)(lba >> 16));  // send bits 16 - 23
  outb(0x1F7, 0x20);                        // 0x20 for read | 0x30 for write

  unsigned short *ptr = (unsigned short *)buf;
  for (int b = 0; b < total; b++)
  {
    // Wait for the buffer to be ready (until bit 4 is set i belief)
    char c = insb(0x1F7);
    while (!(c & 0x08))
    {
      c = insb(0x1F7);
    }

    // reads one sector = 512 bytes
    for (int i = 0; i < 256; i++)
    {
      *ptr = insw(0x1F0); // read 2 bytes from disk
      ptr++;              // move pointer two bytes = 1 short
    }
  }

  return 0;
}

void disk_search_and_init()
{
  memset(&disk, 0, sizeof(disk));
  disk.type = DISK_TYPE_REAL;
  disk.sector_size = SECTOR_SIZE;
  disk.filesystem = fs_resolve(&disk);
}

struct disk *disk_get(int index)
{
  if (index != 0)
    return 0;

  return &disk;
}

int disk_read_block(struct disk *idisk, unsigned int lba, int total, void *buf)
{
  if (idisk != &disk)
  {
    return -EIO;
  }

  return disk_read_sector(lba, total, buf);
}
