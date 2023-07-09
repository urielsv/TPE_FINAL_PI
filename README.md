# TPE_FINAL_PI
En este Trabajo Practico especial, `Final Julio 2023` se analizan los datos de estaciones de bicicletas, en especifico analizamos los datos de las estaciones y rentas de Montreal, y New York City (se puede extrapolar para cualquier ciudad). Se obtienen los datos mencionados y lugo se crean tres queries distintas.

## Compilacion y ejecucion del programa.
### Compilacion
Para compilar el proyecto ingrese a su directorio con los archivos fuente, correr:
```
make all
```

Si desea unicamente crear el proyecto para la informacion de tipo "Montreal", entonces correr:
```
make mon
```
Caso contrario, para la informacion de tipo "New York City", correr:
```
make nyc
```

### Ejecucion
Una vez compilado el programa, para ejecutarlo se debe correr de la siguiente manera.
```
./bikeSharingMON bikesMON.csv stationsMON.csv
```
Siendo, bikeSharingMON el nombre del ejecutable, bikesMON el .csv que contiene la informacion de rentas para Montreal, y stationsMON la informacion de estaciones que contiene la misma ciudad.

_De misma forma se puede ejecutar el programa de NYC, con el nombre de bikeSharingNYC y sus archivos csv correspondientes._

## Queries

### Query1
Guarda en un archivo .csv y .html la informacion de la consulta dada por la `cantidad total de rentas (viajes) por miembros de esa estacion`.

### Query2
Guarda en un archivo .csv y .html la informacion de la consulta dada por la cantidad total de viajes que se realizaron desde EstacionA hacia la EstacionB y viseversa (de EstacionB a EstacionA).

### Query3 
Guarda en un archivo .csv y .html la informacion de la consulta dada la cantidad total de viajes iniciados por cada mes del anio de cada estacion.

## Autoria
La autoria del Trabajo Practico Especial es de Luca Pugliese - 63188, Felipe Venturino - 63161, y Uriel Sosa Vazquez - 63250.


