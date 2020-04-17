---
title: 'X.1: File systems'
pre: "<i class='fab fa-linux'></i> "
weight: 1
---

## Introduction in Unix filesystems

- file: unit of storage in unix system. filesystem: relaties files + attributes
    - name, size, timestamp
    - owner, protection system chmod
    - https://homepages.uc.edu/~thomam/Intro_Unix_Text/Images/file_attributes.png + link src
- dir = file. soft/hardlinks (contain refs)
- device files: char/block, map data naar physical device (link stuk Jo)
- structuur: / tree. verschil Linux/Unix/OSX 

### Common techniques

#### (De)fragmentation

#### Journaling

This technique records the metadata and its changes in the volume or partition.

#### Transactioning

This function enable files and folders to be recreated, renamed, deleted and many more without affecting others.

#### Compressing


## File system flavors

### EXT (Extended File System)

> Originally developed for UNIX and LINUX like Operating Systems. Its first variant came into market in 1992.Variant by variant this has overcome the limitations like size of single file, size of volume, number of files in a folder or directory. We have many software which could help in developing ext2 environment on Windows OS.

Features:

* Unlimited subdirs
* Fast file system checks
* ext4 support online defrag

### FAT (File Allocation Table)

> FAT stands for File Allocation Table and this is called so because it allocates different file and folders using tables. This was originally designed to handle small file systems and disks. This system majorly has three variant FAT12, FAT16 and FAT32 which were introduced in 1980, 1984 and 1996 respectively.
These variant have their own pros and cons, like FAT32 (mostly used in pen drive and micro SD). It could store or copy a file with max size of 4GB (size of a single file to be stored) if the size of file exceeds 4GB it won’t copy on storage media, but its partition size was up to 8TB(size of partition on which FAT could be applied).

### NTFS (New Tech. File System)

Win moved on

> Windows NT has come with a new file system called NTFS in 1993. This stands for New Technology File System. This was an enhanced and more advanced version of FAT systems. All Windows installation is done on NTFS, it first formats the storage in NFTS format and then install on it. Mostly NTFS is done on internal drives.
This has no file size limits and no partition or volume limits. Theoretically up to 16 EiB size of a single file.

Features:

* Journaling 
* Transactions
* File Compression
* Security

### NFS (Network File System)
