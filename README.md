# Simulateur d'interaction électrostatiques
**Deadline : 20/06 à 0h00**  
**À envoyer par mail à olivier.cros@yncrea.fr et yannick.lambert@yncrea.fr**

Lien de la librairie GTK (3.20) : [ici](https://download.gnome.org/sources/gtk+/3.20/gtk+-3.20.0.tar.xz "GTK 3.20") 
## How to install GTK

### Mac OS
  ```shell
  brew install gtk+3
  ```

### Ubuntu
  ```shell
  sudo apt install libgtk-3-dev
  ```

__To ensure you've correctly installed GTK, try the following command inside the project's root directory:__ 
```
make
```
Protocole à suivre -> ANSSI C (C89)  
Librairie graphique -> GTK  

## Good practices

### Architecture
* There is 2 main directories: __logic__, which refers to the physic part of the project, and __graphic__, which contains all the graphical part of the project.
* Both of these directories contains 2 directories: __includes__, which contains every headers file, ans __sources__, which contains the source files.

### Makefile
* When creating a new file, be sure to add its path to the __SOURCE_FILES__ variable and the __O_FILES__ variable, otherwise they won't be compiled.

### Miscellaneous

* You __never__ should include a .c file. The only files which should be included are the headers (.h) files.

* Every "class-like" functions (constructors, getter/setter, toString, etc...) should start with the name of the struct to prevent struct mismatches.

Example:
```
my_struct_to_string(my_truct a);
```

