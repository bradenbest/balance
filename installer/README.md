# balance tool installer

This directory is for holding the installer (for releases)

Build instructions
-

Go to the trunk and run `make`

    $ make

Move the generated binary file `balance` to /installer/build

    $ mv balance installer/build/

Package up `/installer` directory as a tar.gz

    $ tar zcf installer.tar.gz installer/

Upload the resulting .tar.gz using the release feature. Format of release should be as follows:

    Tag version: [version]
    
    Release title: balance [version]
    
    Describe this release: [description of release]
    
    Attach Binaries: [.tar.gz file]
