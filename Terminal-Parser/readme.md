# CMD line parser
## main.c

Este archivo sirve para probar el funcionamiento del modulo "parser". Incluye un template de la funcion
de callBack requerida por el mismo con las validaciones minimas y un banco de pruebas para verificar su
correcto funcionamiento.

El programa permite el ingreso de argumentos por linea de comando por parte del usuario, en cuyo caso
los mismos seran guardados en un arreglo y luego impresos en consola para verificar los resultados.
Ante la falta de argumentos al darse la ejecucion, el programa entrara en modo "testing", en el cual
usara un banco de pruebas para mostrar los casos limite contemplados.

Para el acople del modulo en cualquier codigo, basta con utilizar los archivos parse.c y parse.h y crear una
funcion de callBack que se ajuste a las necesidades del programador. La misma puede mantener la funcion de guardado
de argumentos en un arreglo o implementar un manejo distinto de los datos deseados segun la ocasion.

## parser.c

La funcion valida la forma de lo ingresado por linea de comandos y utiliza una funcion recibida para validar su coherencia

- Clave: Argumento que comienza con '-' y requiere un valor como siguiente argumento. No puede ser vacia
- Valor: Argumento precededido por una clave. No puede ser vacio
- Parámetro: Argumento que no comienza con '-' y no es precedido por una clave