# Segunda Parte Proyecto de Sistemas Operativos

## Estudiante: Emmanuel Solis.

## Simulación de un Sistem Fyle

El lenguaje de programación utilizado fue Python y solo hay un archivo principal llamado
_File\_System.py_ por lo que con solo el comando `python3 File_System.py` se podrá
probar una ejecución de este en sistemas Unix. Este programa cuenta con un menu por lo que es sencillo usarlo, todas las opciones necesarias segun el enunciado se despliegan segun sea necesario. Además que es importante menciona que el **tamaño de los bloques de memoria y el tamaño del disco son editables**, esto se puede hacer editando las lineas 48, 49 y 52 del código.

El código se basa en 3 partes, el main para casos de prueba, la clase _Disk_ y la clase
_Header_. La clase Disk contiene una matriz a modo de representación del disco, mitad corresponde a los i-nodos y la otra mitad a los datos almacenados en si; cada uno de estos i-nodos está conformado por una instancia de la clase _Header_ que contiene atributos importantes respecto a los datos de los archivos a almacenar en el disco,
tales como:

- Tamaño de los bloques de memoria.
- Cantidad de bloques actualmente utilizados.
- Nombre del archivo guardado.
- Dirección del archivo en disco, representada por los puntos de la matriz [x, y].

Siguiendo las instrucciones del enunciados todos estos atributos pueden ser modificados, es decir que el código es funcional y modificable.

Además de lo anterior, según el enunciado este _File System_ debía tener tres capacidades fundamentales:

- Consultar los elementos almacenados: es la función `open_file(file_name)` que
  recibe como parámetro el nombre del archivo que se desea buscar, esta función retorna
  los datos de dicho archivo como una string o un mensaje de _"File does not exist"_ en
  caso que el archivo no existe puesto que nunca ha sido guardado.
- Agregar un nuevo documento: es la función `add_new_file(file_name, data)` que
  recibe cómo parámetro el nombre que llevará el archivo, así como los datos a almacenar. Esta
  función es **capaz de identificar si ya existe un archivo con este nombre** y en caso de ser hace
  solicitará al usuario un nuevo nombre.
- Agregar datos a un documento ya existente: es la función `add_data_to_file(file, data)` que recibe
  como parámetro el nombre del archivo en el que desea almacenar los nuevos datos y los datos en si.
  Esta función puede tener tres desenlaces:
  - Añade los datos al archivo solicitado satisfactoriamente.
  - El bloque del archivo al que se desea añadir estos datos ya se encuentra lleno en cuyo caso
  **no sobreescribe** sino que deja los datos que ya estaban y descarta los que se trataron de
  ingresar y muestra un mensaje que informa al usuario de este error de forma amigable.
  - Y como último caso es que el archivo al que se indica se agreguen los datos **no existe**, en
  este caso al igual que el anterior se descartan los datos y se muestra un mensaje que informa al
  usuario de este error de forma amigable.

Todas estas funcionalidad **están** presentes en el código, sus nombres de las funciones
ya se indicaron en la sección superior. Con todo esto el proyecto cumple con lo solicitado en el
enunciado del proyecto, de igual forma estoy atento a responder cualquier duda que pueda presentarse.

Muchas gracias.
