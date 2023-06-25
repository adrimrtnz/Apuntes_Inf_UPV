#!/usr/bin/env python
#! -*- encoding: utf8 -*-

# Autor: Adrián Martínez

# 1.- Pig Latin

import re
import sys
from typing import Optional, Text
from os.path import isfile

class Translator():

    def __init__(self, punt:Optional[Text]=None):
        """
        Constructor de la clase Translator

        :param punt(opcional): una cadena con los signos de puntuación
                                que se deben respetar
        :return: el objeto de tipo Translator
        """
        if punt is None:
            punt = ".,;?!"
        self.re = re.compile(r"(\w+)([" + punt + r"]*)")

    def translate_word(self, word:Text) -> Text:
        """
        Recibe una palabra en inglés y la traduce a Pig Latin

        :param word: la palabra que se debe pasar a Pig Latin
        :return: la palabra traducida
        """
        # patrón para encontrar las vocales (aquí se considera 'y' como vocal)
        re_vowels = r'[aeiouAEIOUyY]'
        #patrón para encontrar los signos de puntuación
        re_punct = r'[.,;?!]'

        # Si el primer caracter de la palabra no es alfanumérico, se deja como está
        if not word[0].isalpha():
            new_word = word
        else:
            # Si empieza por vocal, se añade 'yay' al final y se mantien mayúsculas de la palabra original
            if re.search(re_vowels, word).span()[0] == 0:
                new_word = (word + 'yay').upper() if word.isupper() else (word + 'yay')
            else:
                v_index = re.search(re_vowels, word).span()[0]                              # índice de la primera vocal
                p_index = re.search(re_punct, word)                                         # índice del signo de puntuación si lo hay
                p_index = p_index.span()[0] if p_index else len(word)
                aux_word = word[v_index:p_index] + word[:v_index] + 'ay' + word[p_index:]   # se forma la palabra traducida

                # mantenemos las mayúsculas de la palabra original
                new_word = aux_word.upper() if word.isupper() else (aux_word.capitalize() if word[0].isupper() else aux_word.lower()) 

        return new_word

    def translate_sentence(self, sentence:Text) -> Text:
        """
        Recibe una frase en inglés y la traduce a Pig Latin

        :param sentence: la frase que se debe pasar a Pig Latin
        :return: la frase traducida
        """
        # separamos cada linea del fichero en sus diferentes palabras y las traducimos una a una
        words = sentence.split()
        words = [self.translate_word(word) for word in words]

        # juntamos las palabras traducidas de nuevo
        new_sentence = ' '.join(words)

        # devolvemos la traducción de la linea de entrada
        return new_sentence

    def translate_file(self, filename:Text):
        """
        Recibe un fichero y crea otro con su tradución a Pig Latin

        :param filename: el nombre del fichero que se debe traducir
        :return: None
        """
        
        if not isfile(filename):
            print(f'{filename} no existe o no es un nombre de fichero', file=sys.stderr)

        # se genera un archivo de salida con el mismo nombre que el archivo original, añadiendo '_latin' al nombre
        first_dot = filename.find('.')  
        in_file = open(filename)
        out_file = open(filename[:first_dot] + '_latin' + filename[first_dot:], 'w')

        # traduce cada fila del fichero y escribe la traducción en el archivo de salida
        for sentence in in_file:
            out_file.write(self.translate_sentence(sentence) + '\n')

        # cerramos los ficheros
        in_file.close()
        out_file.close()


if __name__ == "__main__":
    if len(sys.argv) > 2:
        print(f'Syntax: python {sys.argv[0]} [filename]')
        exit()
    t = Translator()
    if len(sys.argv) == 2:
        t.translate_file(sys.argv[1])
    else:
        sentence = input("ENGLISH: ")
        while len(sentence) > 1:
            print("PIG LATIN:", t.translate_sentence(sentence))
            sentence = input("ENGLISH: ")
