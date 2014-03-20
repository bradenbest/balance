# balance tool installer

This directory is for holding the installer (for releases)

Build instructions
-

1. go to the trunk and run `make`

    $ make

2. move the generated binary file `balance` to /installer/build

    $ mv balance installer/build/

3. package up `/installer` directory as a tar.gz and a .zip

    $ tar zcf installer.tar.gz installer/
    $ zip installer.zip installer/* installer/build/*

4. Upload the resulting .zip and .tar.gz using the release feature. Format of release should be as follows:

    Tag version: [version]
    
    Release title: balance [version]
    
    Describe this release: [description of release]
    
    Attach Binaries: [.tar.gz and .zip files]
