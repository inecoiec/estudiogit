//ACCESO A LA FAT POR FTP

#class auto
#memmap xmem

#define TCPCONFIG 1



#define FAT_BLOCK
#define FAT_USE_FORWARDSLASH
#use sflash_fat.lib
#use fat.lib

#define SSPEC_NO_STATIC
#define SSPEC_FLASHRULES
#define SSPEC_MAXNAME  35
#define FTP_EXTENSIONS
#use "dcrtcp.lib"
#use "ftp_server.lib"

FATfile file;

#define ANON_GROUP 0x0001
#define ADMIN_GROUP 0x0002

SSPEC_RULETABLE_START
         SSPEC_RULE("/A/","soloparami",2,2,SERVER_FTP),
         SSPEC_RULE("/A/iec/","soloparami2",2,2,SERVER_FTP)
SSPEC_RULETABLE_END

main ()
{
int rc;
int uid;
fat_part *particion;

   uid = sauth_adduser("admin", "istrador", SERVER_FTP);
      sauth_setusermask(uid, ADMIN_GROUP, NULL);
      sauth_setwriteaccess(uid,SERVER_FTP|1);
   uid = sauth_adduser("anonymous", "", SERVER_FTP);
      sauth_setusermask(uid, ANON_GROUP, NULL);
   ftp_set_anonymous(uid);



   if ((rc=sspec_automount(SSPEC_MOUNT_FAT,NULL,NULL,NULL))==0){ // inicializa estructuras de FAT
      particion=fat_part_mounted[0];   // Se refiere a la primera partición de
                                    // la serial/NAND flash en el módulo

	   sock_init();
   	ftp_init(NULL);

      if (particion==NULL)
         exit(-1);
      while(1) {
            ftp_tick();
      }
   }
}

