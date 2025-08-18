/// CÓMO USAR
Para ejecutar el programa es necesario utilizar el IDE Zinjai.

Abrir el archivo IdiomasParaSorprender.zrp desde el IDE.

Compilar y ejecutar directamente desde Zinjai.

/// RESPECTO AL PROCESADOR DE TEXTO

Las palabras se obtienen verificando si el carácter en tratamiento
es alfabético. En caso afirmativo, se va concatenando a un string temporal (palabra).

Sin embargo, este método implica que cadenas como II, III, IV, V, etc.
se reconozcan erróneamente como palabras, cuando en realidad se trata de números romanos.
Ese es solo un ejemplo, pero existen otros casos similares.

Como solución, se puede implementar un sistema de exclusión (o “lista de palabras vetadas”),
el cual evalúe cada palabra una vez formada, y determine si pertenece a un vector
de términos no válidos. Si así fuera, dicha cadena no se considerará en el resto del programa.

/// RESPECTO A LOS ARCHIVOS INCLUIDOS

//ARCHIVO usuarios.bin

El archivo binario usuarios.bin fue creado utilizando código auxiliar,
ubicado en la carpeta extras.

A continuación se detallan algunos usuarios de referencia:

Legajo: 12348 | Contraseña: 84329 | (Daniel Ambort)

Legajo: 12350 | Contraseña: 05321 | (Diana Margarita)

Legajo: 12345 | Contraseña: 54326 | (Scarabino Román)

Legajo: 12352 | Contraseña: 25323 | (Sophia Davis)

Legajo: 12361 | Contraseña: 16322 | (Henry Taylor)

//ARCHIVO frecuencia.txt

El enunciado solicitaba mantener el mismo formato que un archivo de ejemplo incluido.
Sin embargo, dicho archivo no fue adjuntado en el correo.

Se solicitó la referencia correspondiente, pero no hubo respuesta.
En caso de ser necesario, este archivo puede modificarse fácilmente para ajustarse a las pautas.