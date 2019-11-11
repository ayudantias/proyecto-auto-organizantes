# Simulación

- Simular una red ad hoc de mínimo 4 nodos
-	Generar tráfico aleatorio sobre la red ad hoc
- Para los enlaces analizar la tasa de pérdida de throughput entre nodos
-	Analizar: Si el ancho de banda de los enlaces se reduce. ¿Cuál es la probabilidad de pérdida de paquetes?

Se realizó la simulación en NS3 ([archivo adhocfus](adhocfus.cc)).
Para el análisis del escenario se generaron archivos pcap al finalizar la ejecución para cada uno de los cuatro nodos de la red. Se utilizarán distintos anchos de banda para observar el cambio en el comportamiento del sistema (1 Mbps y 10 Mbps).

A continuación se muestran los resultados de las simulaciones y el análisis respectivo.
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
La figura 4 muestra la gráfica de tiempo vs paquetes por segundo del primer nodo
