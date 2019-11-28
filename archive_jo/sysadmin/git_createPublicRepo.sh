#!/bin/bash

if [ $# -ne 1 ]
then
  echo "  usage: git_createrepo.sh repository_name"
  exit 1
fi

USERNAME=$(whoami)
REPONAME="$USERNAME_$1"

REPOSITORIES_HOME=/repositories

cd $REPOSITORIES_HOME
if [ -d $REPONAME ]
then
  echo "  repository \"$REPONAME\" already exists"
  exit 1
fi

mkdir $REPONAME
chmod 777 $REPONAME
cd $REPONAME
git init --bare

cd /tmp
git clone $REPOSITORIES_HOME/$REPONAME
cd $REPONAME
echo $USERNAME > README.md
git add README.md
git commit -m "adding a readme"
git push origin master
cd ..
rm -Rf $REPONAME
