# **CI4835 - Redes de Computadoras I - Proyecto 1**

## **Autores**
 * *Alejandro Salazar, 1611080*
 * *Cristian Inojosa, 1710285*

## **Descripción**

El objetivo principal del proyectoes ofrecer la oportunidad de crear una aplicación basada en la red. Desarrollaremos un programa de calculadora que acepte conexiones de clientes a través de Internet.


* Tendrá un protocolo de comunicación entre los clientes y el servidor
* Permitirá la comunicación a través de una red (concretamente, aceptando conexiones TCP de los clientes)
* Permitirá el acceso a los datos almacenados en el servidor (en forma de valores de variables que persisten entre sesiones de comunicación)
* Utilizar hilos para manejar las conexiones concurrentes de los clientes
* Utilizar la sincronización para permitir que varios hilos accedan a datos compartidos

Los siguientes tipos de expresiones son soportados:

* operando
* operando op operando
* var = operando
* var = operando op operando

## **Compilación**

Para construir y ejecutar el proyecto utilice el comando:

```bash
make
```


## **Tests**


### **Pruebas unitarias**
El programa calcTest contiene un conjunto bastante completo de pruebas unitarias para las funciones calc_. Puedes construirlo y ejecutarlo usando los comandos

```bash
make calcTest
./calcTest
```

Si las pruebas tienen éxito, deberías ver la siguiente salida:

testEvalLiteral...passed!<br>
testAssignment...passed <br>
testComputation...passed!<br>
testComputationAndAssignment...passed! <br>
testUpdate...passed!<br>
testInvalidExpr...passed! <br>
All tests passed!<br>

### **Calculadora Interactiva**

El programa calcInteractive permite al usuario introducir interactivamente expresiones (una por línea). Cada expresión se evalúa y el resultado se imprime. Las expresiones que no son válidas dan lugar al mensaje de error Error. Si se introduce el comando quit, la calculadora sale.

Compile y ejecute calcInteractive utilizando los siguientes comandos:

```bash
make calcInteractive
./calcInteractive
```

Ejemplo de transcripción (la entrada del usuario está en negrita):
```bash
a = 5
5
a + 3
8
4 / 0
Error
+ 4
Error
quit
```


### **Servidor de calculadora** 

Aquí hay algunas pruebas automatizadas que puedes probar.

Ejecute los siguientes comandos para descargar los archivos necesarios para las pruebas:

```bash
curl -O https://jhucsf.github.io/fall2019/hw/hw7/test_server_concurrent1.sh
curl -O https://jhucsf.github.io/fall2019/hw/hw7/test_server_concurrent2.sh
curl -O https://jhucsf.github.io/fall2019/hw/hw7/test_server_concurrent_stress.sh
curl -O https://jhucsf.github.io/fall2019/hw/hw7/test_input.txt
curl -O https://jhucsf.github.io/fall2019/hw/hw7/conc_test_input1.txt
curl -O https://jhucsf.github.io/fall2019/hw/hw7/conc_test_input2.txt
chmod a+x test_server_concurrent1.sh
chmod a+x test_server_concurrent2.sh
chmod a+x test_server_concurrent_stress.sh
```

Primera prueba: ejecute los siguientes comandos:

```bash
./test_server_concurrent1.sh 30000 test_input.txt actual1.txt
cat actual1.txt
```

La salida del comando cat debería ser

```bash
2
3
5
```

Esta prueba comprueba que un cliente de larga duración no impide al servidor gestionar una conexión de cliente adicional.

```bash
./test_server_concurrent2.sh 30000 conc_test_input1.txt actual1.txt conc_test_input2.txt actual2.txt
cat actual1.txt
cat actual2.txt
```

Segunda prueba: ejecute los siguientes comandos:

La salida del primer comando `cat` debería ser:

```bash
1
42
```

La salida del segundo comando `cat` debería ser:

```bash
40
54
```

Esta prueba prueba que dos sesiones de cliente pueden interactuar entre sí a través de 
comandos que acceden a una variable compartida.

 
