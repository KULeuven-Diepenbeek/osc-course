#!/bin/bash
# sys_createUser.sh

# VERIFY ARGUMENTS
if [ $# -ne 1 ]
then
  echo "  usage: create_user.sh USERNAME"
  exit 1
fi

USERNAME=$1

# VERIFY ROOT PRIVILEDGE
ROOT=$(whoami)
if [ "$ROOT" != "root" ]
then
  echo "  you forgot \"sudo\""
  exit 0
fi

# VERIFY USER DOESN'T EXIST
USEREXISTS=$(grep -w $USERNAME /etc/passwd | wc -l)

if [ "$USEREXISTS" -gt 0 ]
then
  echo "  username \"$USERNAME\" already exists ($USEREXISTS)"
  exit 1
fi

echo "creating user $USERNAME"

# ADD THE USER & SET INITIAL PASSWORD
adduser --disabled-password --gecos "" $USERNAME
echo -e "$USERNAME\n$USERNAME" | passwd $USERNAME

# ASSIGN THE USER TO A GROUP
addgroup $USERNAME students

# INIT GIT GLOBALS
TARGET="/home/$USERNAME/.gitconfig"
echo "[user]" > $TARGET
echo "  name = $USERNAME" >> $TARGET
echo "  email = $USERNAME@kuleuven.be" >> $TARGET
echo "[core]" >> $TARGET
echo "  editor = vi" >> $TARGET

# CREATE PERSONAL GIT REPO
bash /home/jvliegen/sysadmin/git_createRepo.sh ${USERNAME}_
chown -R $USERNAME.$USERNAME /repositories/${USERNAME}_

# CREATE RSA KEYS
su -c "ssh-keygen -t rsa -f ~/.ssh/id_rsa -N \"\"" $USERNAME
su -c "cp ~/.ssh/id_rsa.pub ~/.ssh/authorized_keys" $USERNAME

# UPDATE ENVIRONMENT SETTINGs
su -c "echo \"\" >> ~/.profile" $USERNAME
su -c "echo \"export EDITOR=vi\" >> ~/.profile" $USERNAME

# SET HOME DIR AS 700
chmod 700 /home/$USERNAME
