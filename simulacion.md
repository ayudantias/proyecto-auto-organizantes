# Simulación

- Simular una red ad hoc de mínimo 4 nodos
-	Generar tráfico aleatorio sobre la red ad hoc
- Para los enlaces analizar la tasa de pérdida de throughput entre nodos
-	Analizar: Si el ancho de banda de los enlaces se reduce. ¿Cuál es la probabilidad de pérdida de paquetes?

Se realizó la simulación en NS3 ([archivo adhocfus](adhocfus.cc)).
Para el análisis del escenario se generaron archivos pcap al finalizar la ejecución para cada uno de los cuatro nodos de la red. Se utilizarán distintos anchos de banda para observar el cambio en el comportamiento del sistema (1 Mbps y 10 Mbps).

A continuación se muestran los resultados de las simulaciones y el análisis respectivo.

**Escenario 1: Ancho de banda de 1 Mbps**

Nodes = 4 Avg throughput = 350.437 kbits/sec AllTx= 645 AllRx= 322 AllLx= 549 TotalDelay= 0.699607

**En el nodo 0 :**

En la figura 1 se muestra la gráfica de número de paquete vs longitud de paquete de las primeras 1000 muestras para una mejor visualización de los resultados.

<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68620614-de0c2000-049b-11ea-8442-99f99084e31b.png">
  <br><br>
  <b>Figura 1. Número de paquete vs longitud de paquete en el primer nodo.</b><br>
</p>

En la figura 2 se muestra la cantidad de paquetes según su longitud.

<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68622176-87084a00-049f-11ea-857c-20d9b1c871e1.png">
  <br><br>
  <b>Figura 2. Cantidad de paquetes según longitud (por intervalos) en el primer nodo.</b><br>
</p>
En la figura 3 se muestra el tiempo de llegada vs la longitud del paquete en los primeros 1000 paquetes del primer nodo.

<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68622469-3513f400-04a0-11ea-94b3-1da4fc6ffe07.png">
  <br><br>
  <b>Figura 3. Tiempo de llegada vs longitud del paquete de los primeros 1000 paquetes en el primer nodo.</b><br>
</p>
La figura 4 muestra la gráfica de tiempo vs paquetes por segundo del primer nodo.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68622680-bb303a80-04a0-11ea-83c6-c5ef2c7dffb0.png">
  <br><br>
  <b>Figura 4. Tiempo vs paquetes por segundo en el primer nodo</b><br>
</p>
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68622710-d1d69180-04a0-11ea-9c67-1b0bc9dd902f.png">
  <br><br>
  <b>Tabla 1. Resumen de conversación entre nodos BW=1Mbps Nodo =1</b><br>
</p>
<b>En el nodo 2 :</b>

En la figura 5 se muestra la gráfica de número de paquete vs longitud de paquete de las primeras 1000 muestras para una mejor visualización de los resultados.

<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68624880-d6517900-04a5-11ea-9853-e540a0807150.png">
  <br><br>
  <b>Figura 5. Número de paquete vs longitud de paquete en el segundo nodo.</b><br>
</p>
En la figura 6 se muestra la cantidad de paquetes según su longitud en el segundo nodo.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68625060-4b24b300-04a6-11ea-8555-985f42bfbda7.png">
  <br><br>
  <b>Figura 6. Cantidad de paquetes según longitud (por intervalos) en el segundo nodo.</b><br>
</p>
En la figura 7 se muestra el tiempo de llegada vs la longitud del paquete en los primeros 1000 paquetes del segundo nodo.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68625516-562c1300-04a7-11ea-960a-9b63d4463d3a.png">
  <br><br>
  <b>Figura 7. Tiempo de llegada vs longitud del paquete de los primeros 1000 paquetes en el segundo nodo.</b><br>
</p>
La figura 8 muestra la gráfica de tiempo vs paquetes por segundo del segundo nodo.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68626679-e703ee00-04a9-11ea-82f8-cc407f7d10fa.png">
  <br><br>
  <b>Figura 8. Tiempo vs paquetes por segundo en el segundo nodo.</b><br>
</p>
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68627957-27b13680-04ad-11ea-96a7-3cbee29b3597.png">
  <br><br>
  <b>Tabla 2. Resumen de conversación entre nodos BW=1Mbps Nodo=2</b><br>
</p>
<b>En el nodo 3 :</b>

En la figura 9 se muestra la gráfica de número de paquete vs longitud de paquete de las primeras 1000 muestras para una mejor visualización de los resultados.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68626718-f97e2780-04a9-11ea-978e-dd9b0c41549e.png">
  <br><br>
  <b>Figura 9. Número de paquete vs longitud de paquete en el tercer nodo.</b><br>
</p>
En la figura 10 se muestra la cantidad de paquetes según su longitud en el tercer nodo.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68626748-0ac73400-04aa-11ea-8527-711cdbc02bd3.png">
  <br><br>
  <b>Figura 10. Cantidad de paquetes según longitud (por intervalos) en el tercer nodo.</b><br>
</p>
En la figura 11 se muestra el tiempo de llegada vs la longitud del paquete en los primeros 1000 paquetes del tercer nodo.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68626776-1a467d00-04aa-11ea-80b6-38cebfed4950.png">
  <br><br>
  <b>Figura 11. Tiempo de llegada vs longitud del paquete de los primeros 1000 paquetes en el tercer nodo.</b><br>
</p>
La figura 12 muestra la gráfica de tiempo vs paquetes por segundo del tercer nodo.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68626794-292d2f80-04aa-11ea-9c13-0ce3256af08c.png">
  <br><br>
  <b>Figura 12. Tiempo vs paquetes por segundo en el tercer nodo.</b><br>
</p>
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68627986-3d266080-04ad-11ea-8d07-a1e8167546b3.png">
  <br><br>
  <b>Tabla 3. Resumen de conversación entre nodos BW=1Mbps Nodo=3</b><br>
</p>
<b>En el nodo 4 :</b>

En la figura 13 se muestra la gráfica de número de paquete vs longitud de paquete de las primeras 1000 muestras para una mejor visualización de los resultados.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68626831-3fd38680-04aa-11ea-86b3-b5e91582f03e.png">
  <br><br>
  <b>Figura 13. Número de paquete vs longitud de paquete en el cuarto nodo</b><br>
</p>
En la figura 14 se muestra la cantidad de paquetes según su longitud en el cuarto nodo.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68626860-4f52cf80-04aa-11ea-9511-1036c046fe3f.png">
  <br><br>
  <b>Figura 14. Cantidad de paquetes según longitud (por intervalos) en el cuarto nodo.</b><br>
</p>
En la figura 15 se muestra el tiempo de llegada vs la longitud del paquete en los primeros 1000 paquetes del cuarto nodo
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68626904-698cad80-04aa-11ea-8221-d85c2dd1de4c.png">
  <br><br>
  <b>Figura 15. Tiempo de llegada vs longitud del paquete de los primeros 1000 paquetes en el cuarto nodo.</b><br>
</p>
La figura 16 muestra la gráfica de tiempo vs paquetes por segundo del cuarto nodo.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68626929-7b6e5080-04aa-11ea-9b5a-506575229676.png">
  <br><br>
  <b>Figura 16. Tiempo vs paquetes por segundo en el cuarto nodo.</b><br>
</p>
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68628016-53342100-04ad-11ea-8331-d1f8caeeeed8.png">
  <br><br>
  <b>Tabla 4. Resumen de conversación entre nodos BW=1Mbps Nodo=4.</b><br>
</p>

**Escenario 2: Ancho de banda de 10 Mbps**

Nodes = 4 Avg throughput = 104.577 kbits/sec AllTx= 3936 AllRx= 108 AllLx= 6462 TotalDelay= 4.42331

**En el nodo 1 :**

En la figura 17 se muestra la gráfica de número de paquete vs longitud de paquete de las primeras 1000 muestras para una mejor visualización de los resultados.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68626954-8aed9980-04aa-11ea-9cc9-a4098a6ca5b9.png">
  <br><br>
  <b>Figura 17. Número de paquete vs longitud de paquete en el primer nodo.</b><br>
</p>
En la figura 18 se muestra la cantidad de paquetes según su longitud en el primer nodo.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68626979-9a6ce280-04aa-11ea-86ab-c1d05ef4e03a.png">
  <br><br>
  <b>Figura 18. Cantidad de paquetes según longitud (por intervalos) en el primer nodo.</b><br>
</p>
En la figura 19 se muestra el tiempo de llegada vs la longitud del paquete en los primeros 1000 paquetes del primer nodo.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68627005-a9539500-04aa-11ea-81fb-2e5677c2070b.png">
  <br><br>
  <b>Figura 19. Tiempo de llegada vs longitud del paquete de los primeros 1000 paquetes en el primer nodo.</b><br>
</p>
La figura 20 muestra la gráfica de tiempo vs paquetes por segundo del primer nodo.
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68627032-b8d2de00-04aa-11ea-9183-e0b577f8b48b.png">
  <br><br>
  <b>Figura 20. Tiempo vs paquetes por segundo en el primer nodo.</b><br>
</p>
<p align="center">
  <img src="https://user-images.githubusercontent.com/57605830/68628035-63e49700-04ad-11ea-978e-924bf1d501e2.png">
  <br><br>
  <b>Tabla 5. Resumen de conversación entre nodos BW=10 Mbps Nodo =1.</b><br>
</p>
<b>En el nodo 2 :</b>

En la figura 21 se muestra la gráfica de número de paquete vs longitud de paquete de las primeras 1000 muestras para una mejor visualización de los resultados.






















