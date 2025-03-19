[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/QWH6Ld8w)
# Laboratorio 1 - El lenguaje de programacion C
El objetivo de este laboratorio es familiarizarse con el lenguaje C y las herramientas de desarrollo.

### Programa de referencia
El programa `demo.c` demuestra las funcionalidades básicas del lenguaje C: declaración de variables, estructuras, ciclos, control, punteros e imprimir mensajes por la salida estándar haciendo uso de funciones de la biblioteca.

## Ejercicio 1
Completar el programa `sum.c` para que retorne la suma de los números enteros indicados desde la línea de comandos o bien desde la entrada estándar (uno o más números por línea).

Por ejemplo, para sumar números indicadolos como argumentos al invocar el programa el comando sería así:
```
$ bin/sum 1 2 3
6
```

Para sumar números ingresados desde la entrada estándar, la ejecución sería así (`↵` representa un Enter y `^D` significa `Ctrl + D`, que ingresa un `EOF`):
```
$ bin/sum
1↵
2↵
3↵
^D
6
$ bin/sum
1 2 3 4↵
^D
10
$
```
Utilizar la funcion [`atoi()`](https://www.man7.org/linux/man-pages/man3/atoi.3.html) para convertir las cadenas de texto a números enteros.

## Ejercicio 2
Completar el programa `palabras.c` para que imprima las palabras que recibe desde la _entrada estándar_. Por ejemplo:
```
$ bin/palabras
Esto es un texto ↵
Esto
es
un
texto
Hola mundo ↵
Hola
mundo
^C
$
```
En el ejemplo, luego de ingresar una frase y presionar Enter (`↵`), el programa imprime cada palabra, una por línea. El programa finaliza al presionar `^C` (Ctrl+C).

Utilizar la función [`getchar()`](https://www.man7.org/linux/man-pages/man3/getchar.3.html) para obtener un carácter desde la _entrada estándar_.

## Ejercicio 3
Completar los programas `encrypt.c` y `decrypt.c` para que encripten y desencripten un mensaje respectivamente. La encriptación es muy sencilla: cada byte del mensaje debe ser precedido por 7 bytes aleatorios en el resultado encriptado.

### Llamadas al sistema a utilizar

Utilizar las siguientes llamadas al sistema:

- [`open()`](http://man7.org/linux/man-pages/man2/open.2.html): abre el archivo indicado y devuelve un descriptor de archivo. 
- [`write()`](http://man7.org/linux/man-pages/man2/write.2.html): escribe *n* bytes en el archivo indicado.
- [`read()`](http://man7.org/linux/man-pages/man2/read.2.html): lee _n_ bytes del archivo indicado.
- [`fstat()`](http://man7.org/linux/man-pages/man2/fstat.2.html): retorna información del archivo indicado.
- [`close()`](http://man7.org/linux/man-pages/man2/close.2.html): cierra un archivo.

También usar la siguiente función de biblioteca:

- [`rand()`](https://www.man7.org/linux/man-pages/man3/rand.3.html): retorna un número pseudo-aleatorio.
- [`srand()`](https://www.man7.org/linux/man-pages/man3/rand.3.html): inicializa semilla para generación de números pseudo-aleatorios.

### Encriptador
El programa `encrypt.c` debe leer el mensaje a encriptar como un argumento desde la línea de comando o desde la _entrada estándar_ y generar el contenido encriptado en la _salida estándar_ o bien guardarlo en el archivo indicado antes del mensaje:

- Encripta "hola" y lo imprime por la salida estándar: `bin/encrypt "hola"`
- Encripta "hello" y lo guarda en el archivo `mensaje.msg`: `bin/encrypt mensaje.msg "hello"`

Utilizar `argv` y `argc` para determinar donde debe enviarse el resultado.

A continuación un ejemplo de que tendría que devolver el programa al encriptar "hola" y enviarlo a la salida estándar. El programa `xxd` muestra una reprsentación hexadecimal de su entrada y lo usamos para que la salida sea más fácil de leer:
```
$ bin/encrypt "hola" | xxd
00000000: 2b07 7d09 250e 5e68 5c17 2b2c 0c17 5b6f  +.}.%.^h\.+,..[o
00000010: 1829 0100 5f26 186c 247d 1f15 087b 4061  .).._&.l$}...{@a
```

### Desencriptador
El programa `decrypt.c` debe leer los datos encriptados desde la entrada estándar o desde el archivo indicado como argumento. El mensaje oculto es presentado en la _salida estándar_. El tamaño del archivo encriptado (o el número de bytes leído de la entrada estándar) indica la longitud del mensaje oculto.

### Ejecución

Dado que ambos programan pueden leer y escribir de la entrada estándar, tendrían que poder ejecutar un comando como el siguiente:
```
$ bin/encrypt "hola" | bin/decrypt
hola
$
```

O incluso así, pasando el mensaje desde la entrada estándar:
```
$ echo -n "hola" | bin/encrypt | bin/decrypt
hola
$
```

---

¡Fín del Laboratorio 1!
