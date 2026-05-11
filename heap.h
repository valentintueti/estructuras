//
// Created by valma on 5/5/2026.
//

#ifndef HEAP_H
#define HEAP_H


#include <vector>
#include <stdexcept>
#include <algorithm>


enum class HeapType {
    Max,
    Min
};


template <typename T>
class Heap {
public:

    explicit Heap(HeapType tipo = HeapType::Max)
        : tipo_(tipo) {}


    Heap(const std::vector<T>& datos, HeapType tipo = HeapType::Max)
        : datos_(datos), tipo_(tipo)
    {
        construir();
    }



    void insertar(const T& valor) {
        datos_.push_back(valor);
        subir(datos_.size() - 1);
    }


    T extraer() {
        if (vacio())
            throw std::underflow_error("Heap vacío");

        T raiz = datos_[0];
        datos_[0] = datos_.back();
        datos_.pop_back();

        if (!vacio())
            bajar(0);

        return raiz;
    }


    const T& cima() const {
        if (vacio())
            throw std::underflow_error("Heap vacío");
        return datos_[0];
    }



    bool   vacio()    const { return datos_.empty(); }
    size_t tamano()   const { return datos_.size();  }
    HeapType tipo()   const { return tipo_;           }


    const std::vector<T>& datos() const { return datos_; }

private:
    std::vector<T> datos_;
    HeapType       tipo_;


    bool tieneProioridad(const T& hijo, const T& padre) const {
        return (tipo_ == HeapType::Max) ? (hijo > padre) : (hijo < padre);
    }


    static size_t padre(size_t i) { return (i - 1) / 2; }
    static size_t hijoIzq(size_t i) { return 2 * i + 1; }
    static size_t hijoDer(size_t i) { return 2 * i + 2; }


    void subir(size_t i) {
        while (i > 0 && tieneProioridad(datos_[i], datos_[padre(i)])) {
            std::swap(datos_[i], datos_[padre(i)]);
            i = padre(i);
        }
    }


    void bajar(size_t i) {
        size_t n = datos_.size();

        while (true) {
            size_t objetivo = i;
            size_t izq = hijoIzq(i);
            size_t der = hijoDer(i);

            if (izq < n && tieneProioridad(datos_[izq], datos_[objetivo]))
                objetivo = izq;

            if (der < n && tieneProioridad(datos_[der], datos_[objetivo]))
                objetivo = der;

            if (objetivo == i) break;

            std::swap(datos_[i], datos_[objetivo]);
            i = objetivo;
        }
    }


    void construir() {
        if (datos_.size() <= 1) return;


        for (int i = static_cast<int>(datos_.size() / 2) - 1; i >= 0; --i)
            bajar(static_cast<size_t>(i));
    }
};

#endif //HEAP_H
