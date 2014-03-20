# balance tool installer

This directory is for holding the installer (for releases)

Build instructions
-

Go to the trunk and run `make`

```bash
    $ make
```

Move the generated binary file `balance` to /installer/build

```bash
    $ mv balance installer/build/
```

Package up `/installer` directory as a tar.gz and a .zip

```bash
    $ tar zcf installer.tar.gz installer/
    $ zip -r installer.zip installer/
```

Upload the resulting .tar.gz and .zip using the release feature. Format of release should be as follows:

    Tag version: [version]
    
    Release title: balance [version]
    
    Describe this release: [description of release]
    
    Attach Binaries: [.tar.gz file, .zip file]
