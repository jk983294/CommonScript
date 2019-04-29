### path
multiple successive ‘/’ characters are equivalent to a single ‘/’ character

### thread safe
by default the stream operations are atomic.

To do this each stream has an internal lock object which has to be (implicitly) acquired before any work can be done.

flockfile acquires the internal locking object associated with the stream stream

funlockfile releases the internal locking object associated with the stream stream

### avoid file lock
use suffix "_unlocked" like putc_unlocked / getc_unlocked

### mmap IO
Memory mapping only works on entire pages of memory. So addresses for mapping must be page-aligned, and length values will be rounded up.

MAP_PRIVATE: writes to the region should never be written back to the attached file.

MAP_SHARED:  writes to the region will be written back to the file. Changes made will be shared immediately with other processes mmaping the same file.

MAP_ANONYMOUS: create an anonymous mapping, not connected to a file, the region is initialized with zeros.

### I/O Operating Modes
flags are set by open and can be fetched and changed with fcntl.

O_APPEND: enables append mode for the file

O_NONBLOCK: read requests on the file can return immediately with a failure status if there is no input immediately available, instead of blocking. Likewise, write requests can also return immediately with a failure status if the output can’t be written immediately.

O_NOATIME: read will not update the access time of the file. This is used by programs that do backups.

### Pipe I/O
Reading or writing pipe data is atomic if the size of data written is not greater than PIPE_BUF.
