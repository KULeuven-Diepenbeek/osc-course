---
title: '1.2: File systems'
pre: "<i class='fab fa-linux'></i> "
weight: 2
---

## Introduction in Unix filesystems

### Everything is a file

On Linux, almost everything is a file. A file is a file. A directory is a file. An entire harddrive is a file. A UART port is a file. Even a network connection is a file! Every file is owned by one user. All other users' privileges for that file (read, write, execute) are based on the **access permissions** (see below).

Working daily with files in Unix operating systems will no doubt increase your awareness of the specific ins and outs of the Unix filesystem. A very important aspect is that **everything is a _file_ in Unix** (even things that aren't really files, like devices, network sockets and even processes!). We will for example use this to our advantage to inspect the inner workings of a process in the `/proc` directory later. 

A real **file** is the smallest possible unit of storage in a unix system. However, a **filesystem** is more than mere data (the file itself): it also contains relations to other files, and attributes or _metadata_ of the file itself, such as:

- name
- size
- timestamp
- owner, protection parameters

A **directory** is a special kind of file, in which other files can be stored. It simply references to other files it contains and does not duplicate the data itself. 

{{<figure src="/img/filesystem.gif" title="src: http://www.rhyshaden.com/unix.htm">}}

The image above gives an overview of common Unix directory structures, starting from the root `/` (forward slash). Depending on the Unix flavor, there will be slight variations. For example, Linux usually has `/home` as user root, while OSX has `/Users` (capital). 

There are also special **device files**, mapped at `/dev`, that form the bridge between the virtual OS system and the physical machine system. These device files are char or block systems that enable the OS to read data from an external device. For instance, your USB devices, listed through `lsusb`, can be read directly using `cat /dev/ttyXX`. 

Hard drives are mapped using the same technique, in `/dev/sdx`, listed through `cat /etc/fstab` (`mount`). `lsblk` (list block devices) allows you to see which block devices are currently linked through files to the OS. On OSX, my `mount` command outputs:

<pre>
Wouters-MacBook-Air:~ wgroeneveld$ mount
/dev/disk1 on / (hfs, local, journaled)
devfs on /dev (devfs, local, nobrowse)
map -hosts on /net (autofs, nosuid, automounted, nobrowse)
map auto_home on /home (autofs, automounted, nobrowse)
</pre>

Depending on the Unix flavor, the location of the device files will be different. 

### File attributes

When you list all files using `ls -la` (list all), you see something like this:

{{<figure src="/img/file_attributes.png" title="src: https://homepages.uc.edu/~thomam/">}}

You can see that each file has a large number of associated attributes. Some of which you'll know (size, date, name), others are somewhat more linux-specific (users, groups and permissions).

{{% notice note %}}
You will notice two special/strange entries at the top of the `ls -al` output, named "." and "..". These are not real files on the disk, but rather virtual files that help navigation in the filesystem and the execution of commands. Firstly, the ".." always means "the parent of this directory". So if you are at the path "/home/user/test" and you do `cd ..`, you will automatically go to "/home/user". Doing `cd ../..` will go to "/home". Secondly, the single dot "." means "the current directory". This comes in handy if you want to search for something in files in the current directory or copy something to where you are at that moment without having to type the entire path. 
{{% /notice %}}

An important attribute is listed at the start: the `permission modes` of a given file or directory. As we've discussed with `sudo` before, not all users or user groups have equal capabilities in a UNIX system. Each file is "owned" by a single user (typically the user that created it) and single user group (the group of the user that created it). The permission modes allow us to very finegrainedly control what each a user can do with each (group of) files (and, because everything is a file, also with each device etc.).

There are five different permission mode characters displayed: 

1. `r` (readable), 
2. `w` (writable), 
3. `x` (executable). 
4. `-` means this specific permission is disabled or this flag is not set, and
5. `d` means it's a directory. If this is -, it means it's a normal file.

The first character is always the directory indicator, but after that we see 3 collections of 3 characters. These are a repetition of `rwx` with potentially also `-`. Each group of 3 indicates permissions for a (group of) user(s) (so 9 in total).

1. The first collection indicates the permissions for the **owning user**.
2. The second collection indicates the permissions for the **owning user group**.
3. The thid collection indicates the permissions for **all users**. 

For example, -rwxrw---- can be divided into - rwx rw- --- and would mean that:

1. The owner can read, write and execute the file.
2. All users in the owner user group can read and write but NOT execute the file.
3. No other users can do anything with the file.

For example, if a file was not created by you, and you're not in the same user group as the creator, you'd get the permissions of the third collection. 

The _default file permission modes_ of new files can be set using `umask`, while the the permission mode of existing files can be changed using the `chmod` (change mode) command. For example:

- `chmod +x [filepath]` adds the execute permission for **all three collections**.
- `chmod -x [filepath]` removes the execute permission for all three collections.
- `chmod 640 [filepath]` uses "bitflags" to change all the 9 different permissions at once. 

Especially the last one deserves some further explanation. Each collection of `rwx` can be seen as 3 bits, where a value of 0 means the permission is OFF, and 1 means the permission is ON. So `101` would mean `r-x` for example. Now, we don't always want to write `chmod 101111010` for example, so we use a shorter version by representing each collection of 3 bits as a number from 0-7 (the octal number system). This is what you get when you interpret the 3 binary digits as decimal numbers (for example, 110 is 6, 101 is 5, while 011 is 3). Some examples:

- `chmod 640 [filepath]` maps to `chmod 110 010 000` which means permissions `rw- -w- ---` for that particular file. Thus, the current user can read and write, the user group can only write and no one can execute. 
- `chmod 777 [filepath]` maps to `chmod 111 111 111` which means permissions `rwx rwx rwx`. Put differently: everyone can do everything. This is often the "lazy option" because it's sure to work, but also very insecure!

Of course the `root` user (for example, when using `sudo`) can always write to files, even if they just have permission `400`, as it has full permission on the entire system. 

{{% notice note %}}
For this course, you will primarily use `chmod +x` to make a script or compiled file executable so it can be run as a program (since that doesn't always happen automatically).
{{% /notice %}}

Changing the owners of the file can be done using `chown user:group [filepath]`.

A complete overview of the permission system, neatly summarized by Julia Evans:

{{% figure src="https://1.bp.blogspot.com/-4YYentw6dEM/W2WjhM1l1DI/AAAAAAAAL6M/2pJn_KbDXmUPEImvikiCFcnWJ0pLvzVVACLcBGAs/s640/UNIX%2Bfile%2Bpermissions%2Bby%2BJulia%2BEvans.jpg" title="source: drawings.jvns.ca"%}}


## File system (FS) flavors

### EXT (Extended File System)

The EXT filesystem is originally developed for Unix-like Operating Systems. Its first variant came into market in 1992. Variant by variant this has overcome the limitations like size of single file, size of volume, number of files in a folder or directory. Journaling was introduced in ext3, and extended features in ext4, such as persistent pre-allocation, delayed allocation, an unlimited number of subdirectories, checksums, transparent encryption, online defrag.

Ext4 is backwards compatible with Ext2, meaning you can safely `mount` an older disk formatted with the older file system using ext4 drivers. Using Ext filesystems in Windows usually requires some driver that enables mounting of these file systems ([Ext2Fsd for example](https://www.ext2fsd.com)).


### FAT (File Allocation Table)

FAT stands for File Allocation Table and this is called so because it allocates different file and folders using lookup _tables_. This was originally designed to handle small file systems and disks. This system majorly has three variant FAT12, FAT16 and FAT32 which were introduced in 1980, 1984 and 1996 respectively.

{{<figure src="/img/floppy.jpg" title="Remember this? src: http://www.youtube.com/watch?v=EHRc-QMoUE4">}}

(Magnetic) [Floppy disks](https://en.wikipedia.org/wiki/Floppy_disk) that could store up to 1.2 MB and later on 1.44 MB, were ideally for this FS. FAT32 is still mostly used in pen drive and micro SDs. It can store or copy a file with a max size of 4GB (size of a single file to be stored). If the size of file exceeds 4GB it won’t copy on storage media, but its partition size was up to 8TB (size of partition on which FAT could be applied).

### NTFS (New Tech. File System)

Microsoft too has moved on from FAT to NTFS with the introduction of [Windows NT (nice intro video for the curious student)](https://www.youtube.com/watch?v=12mx5GbQh2Q) (_New Technology_ - what an original name!) in 1993. This was an enhanced and more advanced version of FAT systems. All modenr Windows installations are done on NTFS. NTFS has no file size limit and no partition or volume limit. 

Modern features of this brand New Technology:

* Journaling 
* Transactions
* File Compression
* Security

Since NTFS is a proprietary technology, is has long been difficult to mount NTFS partitions using Unix systems. Read-only is no problem, but writing is another matter. Even on OSX, it still requires the use of third-party software such as [Mounty](https://mounty.app).

### NFS (Network File System)

File systems usually enable the storage of files on local disks. The NFS FS, Network File System, does enable us to manage files in a **distributed manner**, where _multiple client machines_ can connect to one or _a few servers_.  To be able to do that, there are two different File Systems:

- A _client-side_ one, connected to a network layer
- A _server-side_ one, connected to a network layer - with underlying effective FS

{{<figure src="/img/nfs.jpg" title="src: http://bigdata-guide.blogspot.com/2014/02/network-file-system-nfs.html">}}

Client system calls such as `read()`, `write()` and others pass through these. That means the Virtual FS is completely **transparent**: no special API is required. A network protocol (TCP/UDP) through a network layer enables communication between both client and server. The server is also called the '_file server_'. NFS was originally developed by Sun Microsystems, and it contains much needed server crash recovery modules.

NFS version 2 migrated from a _stateful_ to a _stateless_ network protocol. Statelessness means the server is unaware of what the client is doing (what blocks are being cached, for instance) - it simply delivers al information that is required to service a client request. If a server crash happens, the client would simply have to retry the request. 

## Common File System techniques

### Fragmentation

A hard disk drive has a number of sectors on it, each of which can contain a small piece of data. Files, particularly large ones, must be stored across a number of different sectors (in **file fragments**). As files grow in size (for example, by altering them), these chunks drift apart, depending on the file system. in the old FAT FS, file parts are simply saved as close to the physical start of the disk as possible, and so on, becoming _fragmented_ over time.

{{<figure src="/img/fragment.jpg" title="src: https://7datarecovery.com/best-registry-cleaners/">}}

NTFS is a bit smarter, allocating free _buffer_ space around the files on the drive. However, after a set amount of time, NTFS systems still become fragmented. The **Defragmentation** process then is the process of rearranging file fragments from different sectors closer to each other, to minimize disk IO, especially without solid state. 

The EXT file system handles sectors differently. The FS scatters different files all over the disk, leaving a large amount of free space between them. When a file is edited and needs to grow, there’s usually plenty of free space for the file to grow into. This means fragmentation will only occur if the disk space is used up from `80%` and onwards. 

### Transactions

When programs need to make multiple changes at FS level, if one or two changes fail for some reason, no change at all should occur. That is the main premise of a transactional system, in which **rollback** behavior will occur when something goes wrong. 

It's the same principle applied to most database transactions: a transaction should be an _atomic_ operation, meaning no change or influence can occur in-between different changes. This usually involves some kind of locking mechanism. 

Windows Vista introduced Transactions in NTFS, but the use is now discouraged. The transaction system has largely been superseded by the Journaling system.

### Journaling

A definition from Wikipedia:

> A journaling file system is a file system that **keeps track of changes not yet committed to the file system's main part** by recording the intentions of such changes in a data structure known as a "journal", which is usually a circular log. In the event of a system crash or power failure, such file systems can be brought back online more quickly with a lower likelihood of becoming corrupted.

Journaling minimizes the loss of data when hard disks crash by recording additional metadata in a circular log. EXT4 and NTFS both implement this technique.

### Compressing

Some file systems, such as the open-source Btrfs, introduce transparent file compression. In NTFS, it is not completely transparent: you can enable NTFS compression by changing advanced attributes of directories in Windows Explorer. It does come at a cost: CPU power. Therefore, it should never be applied to OS-specific and frequently-modified files. 

Ext4 does not have transparent file compression, but it can be enabled in conjunction with ZFS. The APFS (Apple File System), a proprietary system by Apple for High Sierra (10.13) and later, does come with auto-compression systems based on Zlib and LZVN. HFS+, Apple's older FS, comes without it. 


## More Resources

- https://kerneltalks.com/disk-management/difference-between-ext2-ext3-and-ext4/
- https://www.freebsd.org/doc/handbook/network-nfs.html
- https://en.wikipedia.org/wiki/Ext4
- https://en.wikipedia.org/wiki/Comparison_of_file_systems
- https://www.linux-magazine.com/Online/Features/Filesystems-Benchmarked
- https://selvamvasu.wordpress.com/2014/08/01/inode-vs-ext4/