# HOST

## SYSROOT

Target

```bash
#
USER=daniel
IP=192.168.15.7
#
mkdir -p sysroot/
cd sysroot/
# 
rsync -avzS --rsync-path="rsync" --delete $USER@$IP:/usr/local ./usr
rsync -avzS --rsync-path="rsync" --delete $USER@$IP:/usr/include ./usr
rsync -avzS --rsync-path="rsync" --delete $USER@$IP:/usr/lib ./usr
rsync -avzS --rsync-path="rsync" --delete $USER@$IP:/lib .
rsync -avzS --rsync-path="rsync" --delete $USER@$IP:/opt .

# Fix symbolic links
sudo apt install symlinks
cd ..
symlinks -rc sysroot/

```