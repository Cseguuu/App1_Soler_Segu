# 🍕 Pizzería Analytics - Tarea 1 en C

Este programa en **C** analiza ventas de pizzas desde un archivo CSV y calcula métricas específicas utilizando punteros a funciones.

---

## 👥 Integrantes

- Cristobal Segú
- Diego Soler

---

## 🚀 Cómo Usar

### Ejecución

make
./app1 test/ventas.csv [métrica1] [métrica2] ...

#### Ejemplo:

make
./app1 test/ventas.csv pms pls dms apo

#### En caso de que no funcione:

make clean
make
./app1 test/ventas.csv pms pls dms apo

---

## 📊 Métricas Implementadas

| Código | Descripción                     |
| ------ | ------------------------------- |
| pms    | Pizza más vendida               |
| pls    | Pizza menos vendida             |
| dms    | Fecha con más ventas (dinero)   |
| dls    | Fecha con menos ventas (dinero) |
| dmsp   | Fecha con más pizzas vendidas   |
| dlsp   | Fecha con menos pizzas vendidas |
| apo    | Promedio de pizzas por orden    |
| apd    | Promedio de pizzas por día      |
| ims    | Ingrediente más vendido         |
| hp     | Pizzas vendidas por categoría   |

---

## 📝 Documentación Adicional

### Para consultar nuestra documentación:

Informe de Diseño: Explicación de la arquitectura y decisiones técnicas.

Para visitar el informe [haz click aquí](https://cseguuu.github.io/App1_Soler_Segu/informe.html#recursos)

Reflexiones: Aprendizajes y desafíos del equipo.
