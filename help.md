
# Helpbox Simulator

  

## Compile the project

***

## 1- Install GTK

  

#### Mac OS

  

```shell

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


Inside the terminal, type `./projetc.bin`. If you've followed carefully every steps the program should starts fine.

<div style="page-break-after: always;"></div>

## Use the program

### Create a specific charge

Click on the `create charge(s)` button.
A new window will appears and you will be able to select the different characteristics of the charge :

- `Coordinate x` is the abscissa of the charge,
- `Coordinate y` is the ordinate of the charge,
- `Force` is the force of the charge (N)
- `Weight` is the weight of the charge (g)
- `Fixed charge` is a switch which allow you to choose if the charge will be static or dynamic

**/!\ This is orthonormal Cartesian coordinate system**

![](pictures/create_charge.png)

**Once all your parameters are sets, click `Create charge`, your charge is on the grid !**

### Modify or delete a charge

To modify the attributs of a charge or delete it, click on the charge you have placed on the grid.
A window will pop out and you will be able to modify the charge's parameters. 
Once it is done, click on the `Modify charge` button.
  
If you want to delete the charge, click on the `Delete charge` button.

![](pictures/create_charge.png)


### Reset the grid

Click on the `Reset` button.
The grid has been completed wiped from every charges.