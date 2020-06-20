# Electrostatic interaction simulator

Like of the library (3.20) : [ici](https://download.gnome.org/sources/gtk+/3.20/gtk+-3.20.0.tar.xz "GTK 3.20")


## Compile the project
***
## 1- Install GTK

#### Mac OS
Dowload [this](https://gitlab.gnome.org/GNOME/gtk-osx/raw/master/gtk-osx-setup.sh "GTK-OSX") and pull it in project's repository  
Once it is done, execute theses commands in project's repository

```shell
sh gtk-osx-setup.sh
brew install gtk+3
brew install gnome-icon-theme
```

#### Ubuntu
```shell
sudo apt install libgtk-3-dev
```
## 2- Compile the source files

Inside the project's root folder, simply type `make` in the terminal

## Run the project
***
Inside the terminal, type `./projetc.bin`. If you've followed carefully every steps the program should starts fine.

## Documentation
To get more informations on every features, please take a look on `help.md`