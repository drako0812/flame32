@rem Builds the BIOS/OS for Flame32

tools\customasm\customasm.exe -f binary -o flame32-os.bin flame32-os.asm
tools\customasm\customasm.exe -f hexdump -o flame32-os.hexd flame32-os.asm
