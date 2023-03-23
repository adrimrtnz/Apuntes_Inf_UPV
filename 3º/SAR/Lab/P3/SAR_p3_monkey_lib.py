#!/usr/bin/env python
#! -*- encoding: utf8 -*-
# 3.- Mono Library

import pickle
import random
import re
import sys
from typing import List, Optional, TextIO

## Nombres: Adrián Martínez Martinez

########################################################################
########################################################################
###                                                                  ###
###  Todos los métodos y funciones que se añadan deben documentarse  ###
###                                                                  ###
########################################################################
########################################################################


def convert_to_lm_dict(d: dict):
    for k in d:
        l = sorted(((y, x) for x, y in d[k].items()), reverse=True)
        d[k] = (sum(x for x, _ in l), l)


class Monkey():

    def __init__(self):
        self.r1 = re.compile('[.;?!]')
        self.r2 = re.compile('\W+')
        self.info = {}


    def get_n(self):
        return self.info.get('n', 0)
    

    def index_sentence(self, sentence:str):
        """
        Este método procesa una frase del texto. La frase es transformada a minúsculas
        y se procesa desde n=2 al n pasado como argumento, creando los 2-gramas, ..., n-gramas
        necesarios.

        Si no se pasa un n como argumento, n=2 es el por defecto, por tanto, ante la ausencia de
        un n>=2, solo se crearían lo 2-gramas.
            
        :param 
            sentence: frase del texto a procesar
        """

        n = self.info['n']
        sentence = self.r2.sub(' ', sentence)   # elimina los caracteres no alfanuméricos
        sentence = sentence.lower()             # pasa contenido a minúsculas
        sentence = sentence.split()             # convierte el string a lista
        
        for i in range(2,n+1):
            self.compute_sentence(sentence, i)
        
        
    def compute_sentence(self, sentence:list, n:int):
        """
        Este método procesa una frase del texto. A dicha frase se le añaden 
        al principio n-1 símbolos '$' y uno al final.
            
        :param 
            sentence: frase del texto a procesar
            n: tamaño del n-grama
        """
        sentence[0:0] = ['$' for _ in range(n-1)]  # inserta n-1 '$' al principio de la frase
        sentence.append('$')                       # inserta '$' al final 

        self.parse_n_gram(sentence, n)
        
        for _ in range(n):                          # elimina los símbolos insertados una vez procesada la frase
            sentence.remove('$')


    def parse_n_gram(self, words:list, n:int):
        """
        Este método crea los n-gramas correspondientes pasada una lista de palabras.
            
        :param 
            words: lista de palabras a parsear
            n: tamaño del n-grama
        """
        for i in range(len(words)-n+1):
            key = tuple(words[i:i+n-1])
            value = words[i+n-1]
            self.info['lm'][n][key] = self.info['lm'][n].get(key, {})
            self.info['lm'][n][key][value] = self.info['lm'][n][key].get(value, 0) + 1   


    def compute_lm(self, filenames:List[str], lm_name:str, n:int):
        self.info = {'name': lm_name, 'filenames': filenames, 'n': n, 'lm': {}}
        for i in range(2, n+1):
            self.info['lm'][i] = {}
        for filename in filenames:
            for line in open(filename, encoding='utf-8'):
                self.index_sentence(line)
                
        for i in range(2, n+1):
            convert_to_lm_dict(self.info['lm'][i])


    def load_lm(self, filename:str):
        with open(filename, "rb") as fh:
            self.info = pickle.load(fh)


    def save_lm(self, filename:str):
        with open(filename, "wb") as fh:
            pickle.dump(self.info, fh)


    def save_info(self, filename:str):
        with open(filename, "w", encoding='utf-8', newline='\n') as fh:
            self.print_info(fh=fh)


    def show_info(self):
        self.print_info(fh=sys.stdout)


    def print_info(self, fh:TextIO):
        print("#" * 20, file=fh)
        print("#" + "INFO".center(18) + "#", file=fh)
        print("#" * 20, file=fh)
        print(f"language model name: {self.info['name']}", file=fh)
        print(f'filenames used to learn the language model: {self.info["filenames"]}', file=fh)
        print("#" * 20, file=fh)
        print(file=fh)
        for i in range(2, self.info['n']+1):
            print("#" * 20, file=fh)
            print("#" + f'{i}-GRAMS'.center(18) + "#", file=fh)
            print("#" * 20, file=fh)
            for prev in sorted(self.info['lm'][i].keys()):
                wl = self.info['lm'][i][prev]
                print(f"'{' '.join(prev)}'\t=>\t{wl[0]}\t=>\t{', '.join(['%s:%s' % (x[1], x[0]) for x in wl[1]])}" , file=fh)


    def generate_sentences(self, n:Optional[int], nsentences:int=10, prefix:Optional[str]=None):
        """
        Este método genera frases aleatorias a partir de un modelo de lenguaje.
        Se coge el n-grama que corresponda con el prefijo dado si se da alguno o con
        palabra vacía en caso contrario.

        Una vez seleccionado el n-grama inicial se elige aleatoriamente la siguiente palabra
        teniendo en cuenta la probabilidad con la que aparecen en el modelo dado ese n-grama.
        Es decir, se hace una elección aleatoria ponderada.
            
        :param 
            n: (opccional) tamaño de los n-gramas a tener en cuenta del modelo de lenguaje
            nsentences: número de frases a generar.
            prefix: (opcional) prefijo por el que deberían empezar todas las frases generadas
        """

        prefix = prefix if prefix else ''
        prefix = self.r2.sub(' ', prefix)                       # limpia el prefijo
        prefix = prefix.split()
        prefix[0:0] = ['$' for _ in range(n-1-len(prefix))]     # inserta n-1 '$' al principio de la frase
        first_words = ' '.join(prefix)                          # si hay prefijo, las frases deben empezar por él
        first_words = self.r2.sub(' ', first_words)

        max_words = 50;
        for s in range(nsentences):
            ini = list(prefix[-n+1:])                           # prefijo inicial, dependiente de la longitud del n-grama
            ini = ini if ini else ['$'] * (n-1)                 # si no existe el prefijo el n-grama inicial es el n-grama formado por palabra vacia
            ini = tuple(ini)                                    # convierte el prefijo en tupla
            print(first_words, end=' ')                         # imprime las primera palabras
            for _ in range(max_words):
                key = self.info['lm'][n][ini]
                value_list = key[1]
                weights = [v[0] for v in value_list]            # guarda los pesos de las diferentes opciones
                words = [v[1] for v in value_list]              # guarda las palabras asociadas a esos pedod

                choice = random.choices(words, weights, k=1)    # elección aleatoria ponderada
                if choice == ['$']:                             # si la elección es palabra vacia, fin de frase actual
                    break
                ini = list(ini[1:]) + choice                    # actualiza el n-grama
                ini = tuple(ini)                                # transforma el n-grama en tupla
                print(' '.join(choice) + ' ', end='')           # imprime la palabra seleccionada
            print()     # imprime el salto de linea        
        pass


if __name__ == "__main__":
    print("Este fichero es una librería, no se puede ejecutar directamente")


