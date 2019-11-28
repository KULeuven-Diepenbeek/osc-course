#!/bin/bash
# delete_user.sh

if [ $# -ne 1 ]
then
  echo "  usage: sysDelete_user.sh USERNAME"
  exit 1
fi

USERNAME=$1

ROOT=$(whoami)
if [ "$ROOT" != "root" ]
then
  echo "  you forgot \"sudo\""
  exit 0
fi

USEREXISTS=$(grep -w $USERNAME /etc/passwd | wc -l)

if [ "$USEREXISTS" -ne 1 ]
then
  echo "  username \"$USERNAME\" doesn't exist ($USEREXISTS)"
  exit 1
fi

echo "deleting user $USERNAME"

# REMOEV THE USER & BACKUP HOME FOLDER
deluser --remove-home --backup-to /backup/deleted_homes $USERNAME

cd /repositories
tar jcf /backup/deleted_personal_repos/${USERNAME}.tar.bz2  ${USERNAME}_
rm -Rf /repositories/${USERNAME}_

