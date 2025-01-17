[Back](../README.md)
# PostgreSQL: The World's Most Advanced Open Source Relational Database
- [Link] https://www.postgresql.org/
- [Link] https://www.postgresql.org/docs/current/installation.html
- [Link] https://www.postgresql.org/download/linux/debian/
- [Link] https://harshityadav95.medium.com/postgresql-in-windows-subsystem-for-linux-wsl-6dc751ac1ff3


    $ sudo sh -c 'echo "deb https://apt.postgresql.org/pub/repos/apt $(lsb_release -cs)-pgdg main" > /etc/apt/sources.list.d/pgdg.list'
    $ wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
    $ sudo apt-get update
    $ sudo apt-get -y install postgresql-16
    
    postgresql-client-12        client libraries and client binaries
    postgresql-12               core database server
    libpq-dev                   libraries and headers for C language frontend development
    postgresql-server-dev-12    libraries and headers for C language backend development

## Build from source

    $ sudo apt install libreadline-dev
    $ git clone -b REL_16_STABLE git://git.postgresql.org/git/postgresql.git
    $ cd postgresql

    
[HOST]

    $ mkdir build 
    $ cd build  
    $ ../configure
    $ make -j$(nproc)
    $ sudo make install
    
[TARGET]

    $ mkdir build build/install_aarch64
    $ cd build  
    
    Note: add to PATH the aarch64-beagle-linux-gnu
    $ ../configure --host=aarch64-beagle-linux-gnu --prefix=$(pwd)/install 
    $ make -j$(nproc)
    $ sudo make install

https://www.postgresqltutorial.com/postgresql-getting-started/install-postgresql-linux/

    $ sudo su
    $ adduser postgres
    $ passwd postgres [1234]
    $ adduser imgui
    $ passwd imgui [1234]
    $ mkdir -p /usr/local/pgsql/data
    $ chown postgres /usr/local/pgsql/data
    $ su - postgres
    $ /usr/lib/postgresql/16/bin/initdb -D /usr/local/pgsql/data
    $ /usr/lib/postgresql/16/bin/pg_ctl -D /usr/local/pgsql/data -l logfile start
    $ /usr/lib/postgresql/16/bin/createdb test
    $ /usr/lib/postgresql/16/bin/psql test

    $ sudo systemctl status postgresql
    $ sudo systemctl enable postgresql
    $ sudo systemctl disable postgresql
    $ sudo systemctl start postgresq
    $ sudo systemctl stop postgresq

    $ sudo iptables -A INPUT -p tcp --dport 5432 -j ACCEPT

Access psql

    $ sudo -u postgres psql
    
Creating user

    $ sudo -u postgres createuser <username>

Giving the user a password

    $ sudo -u postgres psql
    $ psql=# alter user <username> with encrypted password '<password>';
             alter user imgui with encrypted password '1234';
    $ postgres=# alter user imgui with password '1234';
    
Create a database

    $ createdb -h localhost -p 5432 -U <username> <new_database>
    
    $ CREATE DATABASE project;
    
Change Database Owner:

    $ ALTER DATABASE project OWNER TO imgui;
    
Granting privileges on database

    $ psql=# grant all privileges on database <dbname> to <username> ; 
    
List all Databases:
    $ \l
    
CREATE ROLE imgui LOGIN PASSWORD 'your_password';
ALTER ROLE imgui CREATEDB
GRANT ALL PRIVILEGES ON DATABASE project to imgui;

Create users tables

CREATE TABLE public.tb_users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50) UNIQUE NOT NULL,
    security_level INT CHECK (security_level IN (0, 1, 2)) NOT NULL,
    password VARCHAR(100) NOT NULL
);


## PgAdmin

[Link] https://www.pgadmin.org/download/pgadmin-4-apt/

### Setup the repository

* Install the public key for the repository (if not done previously):
    

    $ curl -fsS https://www.pgadmin.org/static/packages_pgadmin_org.pub | sudo gpg --dearmor -o /usr/share/keyrings/packages-pgadmin-org.gpg

* Create the repository configuration file:
    

    $ sudo sh -c 'echo "deb [signed-by=/usr/share/keyrings/packages-pgadmin-org.gpg] https://ftp.postgresql.org/pub/pgadmin/pgadmin4/apt/$(lsb_release -cs) pgadmin4 main" > /etc/apt/sources.list.d/pgadmin4.list && apt update'

* Install for both desktop and web modes:


    $ sudo apt install pgadmin4

* Install for desktop mode only:


    $ sudo apt install pgadmin4-desktop

* Install for web mode only: 
    

    $ sudo apt install pgadmin4-web 

* Configure the webserver, if you installed pgadmin4-web:


    $ sudo /usr/pgadmin4/bin/setup-web.sh
    
