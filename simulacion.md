# Simulación

- Simular una red ad hoc de mínimo 4 nodos
-	Generar tráfico aleatorio sobre la red ad hoc
- Para los enlaces analizar la tasa de pérdida de throughput entre nodos
-	Analizar: Si el ancho de banda de los enlaces se reduce. ¿Cuál es la probabilidad de pérdida de paquetes?

Se realizó la simulación en NS3 ([archivo adhocfus](adhocfus.cc)).
Para el análisis del escenario se generaron archivos pcap al finalizar la ejecución para cada uno de los cuatro nodos de la red. Se utilizarán distintos anchos de banda para observar el cambio en el comportamiento del sistema (1 Mbps y 10 Mbps).

A continuación se muestran los resultados de las simulaciones y el análisis respectivo.

![f1 jpg](https://user-images.githubusercontent.com/57605830/68620614-de0c2000-049b-11ea-8442-99f99084e31b.png)
Figura 1. Número de paquete vs longitud de paquete en el primer nodo.

En la figura 2 se muestra la cantidad de paquetes según su longitud.

