ORG 0x7c00
BITS 16

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

jmp short start
nop

;FAT16 Header
OEMIdentifier db 'MKERNEL '
BytesPerSector dw 0x200
SectorsPerCluster db 0x80
ReservedSectors dw 200
FATCopies db 0x02
RootDirEntries dw 0x40
NumSectors dw 0x00 ; ignored
MediaType db 0xF8
SectorsPerFat dw 0x100
SectorsPerTrack dw 0x20
NumberOfHeads dw 0x40
HiddenSectors dd 0x00
SectorsBig dd 0x773594

; Extended BPB (Dos 4.0)
DriveNumber db 0x80
WinNTBit db 0x00
Signature db 0x29
VolumeID dd 0xD105
VolumeIDString db 'MKERNEL BOO'
SystemIDString db 'FAT16   '


start:
  jmp 0:step2


step2:
  cli ; Clear Interrupts
  mov ax, 0x00
  mov ds, ax
  mov es, ax
  mov ss, ax
  mov sp, 0x7c00
  sti ; Enable Interrupts

.load_protected:
  cli
  lgdt[gdt_descriptor]
  mov eax, cr0
  or eax, 0x1
  mov cr0, eax
  jmp CODE_SEG:load32

; GDT
gdt_start:

gdt_null:
  dd 0x0
  dd 0x0

gdt_code:
  dw 0xffff
  dw 0
  db 0
  db 0x9a
  db 11001111b
  db 0 

gdt_data:
  dw 0xffff
  dw 0
  db 0
  db 0x92
  db 11001111b
  db 0 

gdt_end:

gdt_descriptor:
  dw gdt_end - gdt_start-1
  dd gdt_start

[BITS 32]
load32:
  mov eax, 1
  mov ecx, 100
  mov edi, 0x0100000
  call ata_lba_read
  jmp CODE_SEG:0x0100000

ata_lba_read:
  mov ebx, eax ;Backup LBA
  ; send highest 8 bits of the lba to hard disk
  shr eax, 24 
  or eax, 0xe0 ;select master hard disk
  mov dx, 0x1f6
  out dx, al
  ; finished sending the highest 8 bits

  ;send all sectors to read
  mov eax, ecx
  mov dx, 0x1f2
  out dx, al

  ;send more bits of lba
  mov eax, ebx
  mov dx, 0x1f3
  out dx, al

  mov dx, 0x1f4
  mov eax, ebx
  shr eax, 8
  out dx, al

  mov dx, 0x1f5
  mov eax, ebx
  shr eax, 16
  out dx, al

  mov dx, 0x1f7
  mov al, 0x20
  out dx, al

  ;read all sectors into memory
.next_sector
  push ecx
.try_again
  mov dx, 0x1f7
  in al, dx
  test al, 8
  jz .try_again
; read 256 words at a time
  mov ecx, 256
  mov dx, 0x1f0
  rep insw
  pop ecx
  loop .next_sector
  ret

times 510-($ - $$) db 0
dw 0xAA55
