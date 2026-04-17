# Simulación de Epidemias SIR (Secuencial vs Paralelo)

**Autor:** Roshell Esmeraly Fajardo de la Cruz
**Matrícula:** 20241777
**Asignatura:** Programación Paralela
**Instituto:** ITLA


## Introducción

La simulación de epidemias permite analizar cómo se propagan enfermedades dentro de una población. En este proyecto se implementa el modelo SIR (Susceptible, Infectado, Recuperado) utilizando programación en C++.

Se desarrollaron tres versiones del sistema:

 Versión secuencial
 Versión paralela básica (OpenMP)
 Versión paralela optimizada

El objetivo es comparar el rendimiento y demostrar el impacto del paralelismo en problemas de gran escala.

## Objetivos

### Objetivo general

Implementar y comparar una simulación del modelo SIR utilizando enfoques secuencial y paralelo.

### Objetivos específicos

 Modelar una epidemia usando una grilla 2D
 Implementar el modelo en C++
 Aplicar paralelismo con OpenMP
 Medir tiempos de ejecución
 Calcular el speedup
 Optimizar la versión paralela


## Modelo SIR

Cada celda representa una persona:

 0 → Susceptible
 1 → Infectado
 2 → Recuperado

### Parámetros del modelo

 Tamaño: 1000 x 1000 (1 millón de individuos)
 Duración: 365 días
 Probabilidad de contagio: 0.25
 Probabilidad de recuperación: 0.05

### Reglas

 Un infectado puede contagiar a sus vecinos
 Puede recuperarse con cierta probabilidad
 La simulación evoluciona día a día


## Metodología

### Versión Secuencial

 Ejecución tradicional
 Procesamiento celda por celda
 No utiliza múltiples núcleos


### Versión Paralela (OpenMP)

Se utiliza la directiva:

```id="a9j3l1"
#pragma omp parallel for reduction(+:infectados)
```

Esto permite dividir el trabajo entre varios hilos.


### Versión Paralela Optimizada

Se realizaron mejoras clave:

* Uso de generadores aleatorios por hilo (`mt19937`)
* Eliminación de `rand()` (no eficiente en paralelo)
* Uso de `schedule(static)`
* Reducción de operaciones de impresión
* Control manual del número de hilos


## Tecnologías utilizadas

* Lenguaje: C++
* Compilador: GCC (WinLibs)
* Librería: OpenMP
* Entorno: Visual Studio Code / CMD


## Estructura del Proyecto

```id="d3p7s9"
proyecto/
│
├── secuencial/
│   └── sir_secuencial.cpp
│
├── paralelo/
│   ├── sir_paralelo.cpp
│   └── sir_paralelo_optimizado.cpp
```


## Compilación y Ejecución

### Secuencial

```id="wq8n2e"
g++ sir_secuencial.cpp -o sir.exe
.\sir.exe
```


### Paralelo básico

```id="r2b4k1"
C:\winlibs\mingw64\bin\g++ -fopenmp sir_paralelo.cpp -o sir_paralelo.exe -mconsole
.\sir_paralelo.exe
```

### Paralelo optimizado

```id="p8x1n6"
C:\winlibs\mingw64\bin\g++ -fopenmp sir_paralelo_optimizado.cpp -o sir_opt.exe -mconsole
.\sir_opt.exe
```


## Resultados Experimentales

### Versión Secuencial

```id="z1v6t8"
Tiempo total secuencial: 0.25844 segundos
```


### Versión Paralela (OpenMP)

```id="q5m3c2"
Tiempo total paralelo: 0.404166 segundos
```


## Comparación de Resultados

| Métrica             | Secuencial | Paralelo          |
| ------------------- | ---------- | ----------------- |
| Tiempo de ejecución | 0.258 s    | 0.404 s           |
| Rendimiento         | Mejor      | Menor             |
| Uso de CPU          | 1 núcleo   | Múltiples núcleos |


## Cálculo de Speedup

```id="t4g2b7"
Speedup = Tiempo_secuencial / Tiempo_paralelo
Speedup = 0.25844 / 0.404166 ≈ 0.64
```


## Análisis

En esta implementación, la versión paralela resultó más lenta que la secuencial.

Esto se debe a:

* Overhead de creación de hilos
* Uso inicial de funciones no optimizadas (`rand()`)
* Características del hardware
* Costos de sincronización

Sin embargo, tras aplicar optimizaciones, se espera una mejora en el rendimiento.


## Optimización del Paralelismo

Se implementó una versión optimizada con mejoras en:

* Generación de números aleatorios
* Distribución de carga
* Reducción de operaciones innecesarias
* Control de hilos

Estas mejoras permiten un mejor aprovechamiento del paralelismo.


## Conclusión

El proyecto demuestra que el paralelismo no siempre garantiza mejoras inmediatas en el rendimiento. Sin embargo, con una correcta implementación y optimización, es posible obtener mejoras significativas.

El uso de OpenMP representa una herramienta poderosa para acelerar simulaciones complejas en grandes volúmenes de datos.


## Capturas

### Ejecución Secuencial

Captura desde PowerShell mostrando la evolución de infectados y tiempo total.

### Ejecución Paralela

Captura desde PowerShell ejecutando la versión con OpenMP.

### Resultados en Consola

Capturas donde se observa:

* Evolución diaria de infectados
* Final de la simulación (infectados = 0)
* Tiempo total de ejecución

Ejemplo:

Tiempo total secuencial: 0.25844 segundos
Tiempo total paralelo: 0.404166 segundos


## Estado del Proyecto

Finalizado


Capturas

Ejecución secuencial
![alt text](image.png)
![alt text](image-1.png)
Ejecución paralela
![alt text](image-2.png)
![alt text](image-3.png)
Resultados en consola
Tiempo total secuencial: 0.25844 segundos  
Tiempo total paralelo: 0.404166 segundos
