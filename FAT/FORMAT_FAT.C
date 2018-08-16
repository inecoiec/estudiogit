/***********************************************************************
	FMT_DEVICE.C

   COPYRIGHT - Z-World (c) 2004

   Formats the configured device(s) for use with the FAT file system.

   Demonstrates "conditional" and "unconditional" format modes for both
   device(s) and partition(s).  The conditional format mode will format
   a device or partition that is unformatted, but will not format a
   device or partition that is already formatted.  Use the unconditional
   format mode to erase a device or partition regardless of whether or
   not it is already formatted.

   Formatting a device unconditionally will erase the device and re-format
   it with a single large partition.  This device erasure does not check
   for non-FAT partitions and will destroy ALL existing partitions on the
   device.  Please use with caution.

************************************************************************/

// Map program to xmem if not compiling to separate I&D space.
#if !__SEPARATE_INST_DATA__
#memmap xmem
#endif

// Uncomment to turn on Debug options
//#define FAT_DEBUG
//#define NFLASH_DEBUG
//#define NFLASH_FAT_DEBUG
//#define SFLASH_DEBUG
//#define FATWTC_DEBUG
//#define PART_DEBUG

//#define FAT_VERBOSE		// Make FAT library print some messages
//#define FATWTC_VERBOSE		// Make WTC library print some messages

// Set FAT library to blocking mode
#define FAT_BLOCK
#define FAT_USE_FORWARDSLASH
// Makes the device drivers and FAT filesystem libraries available
#use "fat.lib"


int main()
{
   int i, rc;
   char s[80];
   int uncond;
   int norec;
   int dev;
   char cmd;
   word fmt_flags;
   fat_part *particion;


   uncond = 0;
   norec = 0;

	fat_print_config();
	rc = fat_AutoMount(FDDF_MOUNT_DEV_ALL | FDDF_MOUNT_PART_ALL);
	if (rc) {
		printf("\nfat_AutoMount() returned result code %d.\n", rc);
	}

   printf("\nNOTE:  Formatting destroys all data.\n");
   printf("       Quit now or forever hold your peace!\n\n");

   for (;;) {
   	for (i = 0; i < num_fat_devices * FAT_MAX_PARTITIONS; ++i) {
   		if (fat_part_mounted[i]) {
   			printf("Partition %c is mounted.\n", 'A' + i);
   		}
   	}
   	printf("\nEnter a command (single char only, then press Enter):\n");
      printf("  u      Toggle 'unconditional' mode (currently %s)\n",
             uncond ? "ON" : "OFF");
      printf("  n      Toggle 'norecovery' mode (currently %s)\n",
             norec ? "ON" : "OFF");
      printf("  p      Purge cache - try this if getting -310 error codes\n");
      printf("  a-d    Format partition 0,1,2 or 3 on device 0\n");
      printf("  i      Crear directorio luego del Format partition 0\n");
      if (num_fat_devices > 1)
	      printf("  e-h    Format partition 0,1,2 or 3 on device 1\n");
      printf("  0      Format entire device 0, create one partition\n");
      if (num_fat_devices > 1)
         printf("  1      Format entire device 1, create one partition\n");
      printf("  q      Quit (after unmounting all partitions)\n");
      printf("\nYour choice?  ");
      gets(s);
      printf("\n\n");
      cmd = toupper(s[0]);
      rc = 0;
      switch (cmd) {
      case 'U':
      	uncond = !uncond;
         break;
      case 'N':
      	norec = !norec;
         break;
      case 'P':
      	rc = fatwtc_flushall(WTC_PURGE | WTC_WAIT);
     		printf("Cache purge was %s\n", rc ? "unsuccessful!" : "successful.\n");
      	if (!rc) {
      		printf("Restart fmt_device.c to format devices (exiting now).\n");
      		exit(0);
      	}
         break;
      case 'A': case 'B': case 'C': case 'D':
         fmt_flags = FDDF_COND_PART_FORMAT | FDDF_MOUNT_DEV_0 |
                     (FDDF_MOUNT_PART_0 << (cmd - 'A'));
         fmt_flags |= uncond ? FDDF_UNCOND_PART_FORMAT : 0;
         fmt_flags |= norec ? FDDF_NO_RECOVERY : 0;
         rc = fat_AutoMount(fmt_flags);
         break;
      case 'E': case 'F': case 'G': case 'H':
         fmt_flags = FDDF_COND_PART_FORMAT | FDDF_MOUNT_DEV_1 |
                     (FDDF_MOUNT_PART_0 << (cmd - 'E'));
         fmt_flags |= uncond ? FDDF_UNCOND_PART_FORMAT : 0;
         fmt_flags |= norec ? FDDF_NO_RECOVERY : 0;
         rc = fat_AutoMount(fmt_flags);
         break;
      case '0':
      	fmt_flags = FDDF_COND_DEV_FORMAT | FDDF_COND_PART_FORMAT |
      	            FDDF_MOUNT_DEV_0 | FDDF_MOUNT_PART_0;
         fmt_flags |= uncond ? FDDF_UNCOND_PART_FORMAT | FDDF_UNCOND_DEV_FORMAT
                               : 0;
         fmt_flags |= norec ? FDDF_NO_RECOVERY : 0;
         rc = fat_AutoMount(fmt_flags);
         break;
      case '1':
      	fmt_flags = FDDF_COND_DEV_FORMAT | FDDF_COND_PART_FORMAT |
      	            FDDF_MOUNT_DEV_1 | FDDF_MOUNT_PART_0;
         fmt_flags |= uncond ? FDDF_UNCOND_PART_FORMAT | FDDF_UNCOND_DEV_FORMAT
                               : 0;
         fmt_flags |= norec ? FDDF_NO_RECOVERY : 0;
         rc = fat_AutoMount(fmt_flags);
         break;
      case 'Q':
      	// Unmount all of the mounted FAT partitions & devices before exiting
      	for (i = 0; i < num_fat_devices * FAT_MAX_PARTITIONS;
         											 i += FAT_MAX_PARTITIONS) {
	      	if (fat_part_mounted[i]) {
	      		fat_UnmountDevice(fat_part_mounted[i]->dev);
	      	}
	      }
      	exit(0);
      case 'I':
			 rc = fat_AutoMount(FDDF_USE_DEFAULT); // inicializa estructuras de FAT
      			particion=fat_part_mounted[0];   // Se refiere a la primera partición de
                                   // la serial/NAND flash en el módulo

         fat_CreateDir( particion,"sitio");
			fat_CreateDir( particion,"log");
			fat_CreateDir( particion,"ircodes");
         break;





      default:
      	printf("Unrecognized command.\n");
         continue;
      }

      if (rc)
      	printf("\nOperation return code %d\n\n", rc);
      else
      	printf("\nOperation successful.\n\n");
   }
}

