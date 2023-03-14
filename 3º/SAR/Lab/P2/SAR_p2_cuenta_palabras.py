#! -*- encoding: utf8 -*-

## Nombres: Adrián Martínez Martínez

########################################################################
########################################################################
###                                                                  ###
###  Todos los métodos y funciones que se añadan deben documentarse  ###
###                                                                  ###
########################################################################
########################################################################

import argparse
import os
import re
from typing import Optional

def sort_dic_by_values(d:dict) -> list:
    return sorted(d.items(), key=lambda a: (-a[1], a[0]))

class WordCounter:

    def __init__(self):
        """
           Constructor de la clase WordCounter
        """
        self.clean_re = re.compile('\W+')

    def write_stats(self, filename:str, stats:dict, use_stopwords:bool, full:bool):
        """
        Este método escribe en fichero las estadísticas de un texto
            
        :param 
            filename: el nombre del fichero destino.
            stats: las estadísticas del texto.
            use_stopwords: booleano, si se han utilizado stopwords
            full: boolean, si se deben mostrar las stats completas
        """

        with open(filename, 'w', encoding='utf-8', newline='\n') as fh:
            ## completar
            fh.write(f"Lines: {stats['nlines']}\n")
            fh.write(f"Number words (including stopwords): {stats['nwords']}\n")

            if use_stopwords:
                fh.write(f"Number words (without stopwords): {stats['nwords'] - stats['excluded_words']}\n")

            fh.write(f"Vocabulary size: {len(stats['word'])}\n")
            fh.write(f"Number of symbols: {stats['nsymbol']}\n")
            fh.write(f"Number of different symbols: {len(stats['symbol'])}\n")
           
            fh.write('Words (alphabetical order):\n')
            max = len(stats['word']) if full else 20
            for w in sorted(stats['word']):
                fh.write(f"\t{w}: {stats['word'][w]}\n")
                max -= 1
                if max == 0:
                    break

            fh.write('Words (by frequency):\n')
            max = len(stats['word']) if full else 20
            for key,value in sort_dic_by_values(stats['word']):
                fh.write(f"\t{key}: {value}\n")
                max -= 1
                if max == 0:
                    break
            
            fh.write('Symbols (alphabetical order):\n')
            max = len(stats['symbol']) if full else 20
            for s in sorted(stats['symbol']):
                fh.write(f"\t{s}: {stats['symbol'][s]}\n")
                max -= 1
                if max == 0:
                    break
            
            fh.write('Symbols (by frequency):\n')
            max = len(stats['symbol']) if full else 20
            for key,value in sort_dic_by_values(stats['symbol']):
                fh.write(f"\t{key}: {value}\n")
                max -= 1
                if max == 0:
                    break

            if (stats.setdefault('biword')):
                fh.write('Word pairs (alphabetical order):\n')
                max = len(stats['biword']) if full else 20
                for s in sorted(stats['biword']):
                    fh.write(f"\t{s}: {stats['biword'][s]}\n")
                    max -= 1
                    if max == 0:
                        break

                fh.write('Word pairs (by frequency):\n')
                max = len(stats['biword']) if full else 20
                for key,value in sort_dic_by_values(stats['biword']):
                    fh.write(f"\t{key}: {value}\n")
                    max -= 1
                    if max == 0:
                        break

                fh.write('Symbol pairs (alphabetical order):\n')
                max = len(stats['bisymbol']) if full else 20
                for s in sorted(stats['bisymbol']):
                    fh.write(f"\t{s}: {stats['bisymbol'][s]}\n")
                    max -= 1
                    if max == 0:
                        break

                fh.write('Symbol pairs (by frequency):\n')
                max = len(stats['bisymbol']) if full else 20
                for key,value in sort_dic_by_values(stats['bisymbol']):
                    fh.write(f"\t{key}: {value}\n")
                    max -= 1
                    if max == 0:
                        break    

            fh.write('Prefixes (by frequency):\n')
            max = len(stats['prefix']) if full else 20
            for key, value in sort_dic_by_values(stats['prefix']):
                fh.write(f"\t{key}: {value}\n")
                max -= 1
                if max == 0:
                    break

            fh.write('Suffixes (by frequency):\n')
            max = len(stats['suffix']) if full else 20
            for key, value in sort_dic_by_values(stats['suffix']):
                fh.write(f"\t{key}: {value}\n")
                max -= 1
                if max == 0:
                    break


    def file_stats(self, fullfilename:str, lower:bool, stopwordsfile:Optional[str], bigrams:bool, full:bool):
        """
        Este método calcula las estadísticas de un fichero de texto

        :param 
            fullfilename: el nombre del fichero, puede incluir ruta.
            lower: booleano, se debe pasar todo a minúsculas?
            stopwordsfile: nombre del fichero con las stopwords o None si no se aplican
            bigram: booleano, se deben calcular bigramas?
            full: booleano, se deben montrar la estadísticas completas?
        """

        stopwords = [] if stopwordsfile is None else open(stopwordsfile, encoding='utf-8').read().split()

        # variables for results
        sts = {
                'nwords': 0,
                'nlines': 0,
                'word': {},
                'symbol': {},
                'nsymbol': 0,
                'prefix': {},
                'suffix': {}
                }

        if bigrams:
            sts['biword'] = {}
            sts['bisymbol'] = {}

        if stopwordsfile:
            sts['swords'] = {}
            sts['excluded_words'] = 0

        with open(fullfilename, 'r', encoding='utf-8', newline='\n') as file:
            for line in file:
                line = self.clean_re.sub(' ', line)
                words = line.split()
                self.compute_words(words, sts, lower, stopwords, bigrams)
                sts['nlines'] += 1
                sts['nwords'] += len(words)

        filename, ext0 = os.path.splitext(fullfilename)

        # Extensiones en el archivo de salida según parámetros de entrada
        l = 'l' if lower else ''
        b = 'b' if bigrams else ''
        f = 'f' if full else ''
        s = 's' if stopwordsfile else ''
        
        new_filename = filename + '_' + l + s + b + f + '_stats' + ext0
        self.write_stats(new_filename, sts, stopwordsfile is not None, full)
        

    def compute_words(self, words:list, stats:dict, lower:bool, stopwords:list, bigrams:bool):
        """
        Este método registra las diferentes palabras en el diccionario
        de estadísticas

        :param 
            words: lista con las palabras del texto.
            stats: diccionario de estadísticas del fichero.
            lower: booleano, se deben pasar las palabras a minúsculas?
            stopwords: palabras a eliminar

        :return: None
        """

        # si se pasa el parámetro -l convierte las palabras a minúsculas
        if (lower):
            words = [word.lower() for word in words]

        # generamos los bigramas si se especefíca el parámetro -b
        if (bigrams):
            self.compute_biwords(words, stats, lower, stopwords)

        # eliminamos las stopwords si tenemos un fichero pasado con el parámetro -s
        if (stopwords):
            original_length = len(words)
            words = [word for word in words if word not in stopwords]
            stats['excluded_words'] += original_length - len(words)

        # procesa cada una de las palabras
        for word in words:
            stats['word'][word] = stats['word'].get(word, 0) + 1
            self.compute_symbols(word, stats)
            self.compute_prefixes(word, stats)
            self.compute_suffixes(word, stats)
            if (bigrams):
                self.compute_bisymbols(word, stats)



    def compute_bisymbols(self, word:str, stats:dict):
        for i in range(len(word)-1):
            stats['bisymbol'][word[i] + word[i+1]] = stats['bisymbol'].get(word[i] + word[i+1], 0) + 1

        
    def compute_biwords(self, words:list, stats:dict, lower:bool, stopwords = []):
        """
        Este método genera las diferentes parejas de palabras

        :param 
            words: list de palabras a analizar.
            stats: diccionario de estadísticas del fichero.
            lower: booleano que expresa si se han de de procesar las palabras en minúscula o no
            stopwords: lista de stopwords

        :return None
        """

        words.insert(0,'$')
        words.append('$')

        for i in range(len(words) - 1):
            word_1 = words[i].lower() if lower else words[i]
            word_2 = words[i+1].lower() if lower else words[i+1]
            if word_1 == word_2 == '$' or word_1 in stopwords or word_2 in stopwords:
                continue
            stats['biword'][word_1 + ' ' + word_2] = stats['biword'].get(word_1 + ' ' + word_2, 0) + 1
        
        words.pop(0)
        words.pop(len(words) - 1)

    def compute_symbols(self, word:str, stats:dict):
        """
        Este método registra las diferentes letras en las palabras

        :param 
            word: palabra a analizar.
            stats: diccionario de estadísticas del fichero.

        :return: None
        """

        for char in word:
                stats['symbol'][char] = stats['symbol'].get(char, 0) + 1
                stats['nsymbol'] += 1


    def compute_prefixes(self, word:str, stats:dict):
        """
        Este método genera los diferentes prefijos de la palabra

        :param 
            word: palabra a analizar.
            stats: diccionario de estadísticas del fichero.

        :return None
        """
        for i in range(2,5):
            if len(word) > i:
                stats['prefix'][word[:i] + '-'] = stats['prefix'].get(word[:i] + '-', 0) + 1


    def compute_suffixes(self, word:str, stats:dict):
        """
        Este método genera los diferentes sufijos de la palabra

        :param 
            word: palabra a analizar.
            stats: diccionario de estadísticas del fichero.

        :return None
        """
        for i in range(2,5):
            if len(word) > i :
                stats['suffix']['-' + word[-i:]] = stats['suffix'].get('-' + word[-i:], 0) + 1


    def compute_files(self, filenames:str, **args):
        """
        Este método calcula las estadísticas de una lista de ficheros de texto

        :param 
            filenames: lista con los nombre de los ficheros.
            args: argumentos que se pasan a "file_stats".

        :return: None
        """

        for filename in filenames:
            self.file_stats(filename, **args)


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='Compute some statistics from text files.')
    parser.add_argument('file', metavar='file', type=str, nargs='+',
                        help='text file.')

    parser.add_argument('-l', '--lower', dest='lower',
                        action='store_true', default=False, 
                        help='lowercase all words before computing stats.')

    parser.add_argument('-s', '--stop', dest='stopwords', action='store',
                        help='filename with the stopwords.')

    parser.add_argument('-b', '--bigram', dest='bigram',
                        action='store_true', default=False, 
                        help='compute bigram stats.')

    parser.add_argument('-f', '--full', dest='full',
                        action='store_true', default=False, 
                        help='show full stats.')

    args = parser.parse_args()
    wc = WordCounter()
    wc.compute_files(args.file,
                     lower=args.lower,
                     stopwordsfile=args.stopwords,
                     bigrams=args.bigram,
                     full=args.full)
