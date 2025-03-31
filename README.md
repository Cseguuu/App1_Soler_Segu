# 🍕 Pizzería Analytics - Tarea 1 en C

Este programa en **C** analiza ventas de pizzas desde un archivo CSV y calcula métricas específicas utilizando punteros a funciones.

## 🚀 Cómo Usar

### Ejecución

./app1 test/ventas.csv [métrica1] [métrica2] ...

#### Ejemplo:

./app1 test/ventas.csv pms pls dms apo

## 📊 Métricas Implementadas

| Código | Descripción                     |
| ------ | ------------------------------- |
| `pms`  | Pizza más vendida               |
| `pls`  | Pizza menos vendida             |
| `dms`  | Fecha con más ventas (dinero)   |
| `dls`  | Fecha con menos ventas (dinero) |
| `dmsp` | Fecha con más pizzas vendidas   |
| `dlsp` | Fecha con menos pizzas vendidas |
| `apo`  | Promedio de pizzas por orden    |
| `apd`  | Promedio de pizzas por día      |
| `ims`  | Ingrediente más vendido         |
| `hp`   | Pizzas vendidas por categoría   |

## 📝 Documentación Adicional

### Para consultar nuestra documentación:

Informe de Diseño: Explicación de la arquitectura y decisiones técnicas.

Para abrirlo debes correr en la terminal:
Mac: open entregables/informe.html
Windows: start entregables/informe.html

Reflexiones: Aprendizajes y desafíos del equipo.
