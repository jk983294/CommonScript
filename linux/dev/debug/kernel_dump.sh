# kexec is a tool to boot to another kernel from the currently running one
kexec -l KERNEL_IMAGE           # Load the kernel to the address space of a production kernel for a regular reboot
kexec -p KERNEL_IMAGE           # Load the kernel to a reserved area of memory, kernel will be booted automatically when the system crashes
