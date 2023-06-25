import json
from nltk.stem.snowball import SnowballStemmer
import os
import re
import sys
import math
from pathlib import Path
from typing import Optional, List, Union, Dict
import pickle

class SAR_Indexer:
    """
    Prototipo de la clase para realizar la indexacion y la recuperacion de artículos de Wikipedia
        
        Preparada para todas las ampliaciones:
          parentesis + multiples indices + posicionales + stemming + permuterm

    Se deben completar los metodos que se indica.
    Se pueden añadir nuevas variables y nuevos metodos
    Los metodos que se añadan se deberan documentar en el codigo y explicar en la memoria
    """

    # lista de campos, el booleano indica si se debe tokenizar el campo
    # NECESARIO PARA LA AMPLIACION MULTIFIELD
    fields = [
        ("all", True), ("title", True), ("summary", True), ("section-name", True), ('url', False),
    ]
    def_field = 'all'
    PAR_MARK = '%'
    # numero maximo de documento a mostrar cuando self.show_all es False
    SHOW_MAX = 10

    all_atribs = ['urls', 'index', 'sindex', 'ptindex', 'docs', 'weight', 'articles',
                  'tokenizer', 'stemmer', 'show_all', 'use_stemming']

    def __init__(self):
        """
        Constructor de la classe SAR_Indexer.
        NECESARIO PARA LA VERSION MINIMA

        Incluye todas las variables necesaria para todas las ampliaciones.
        Puedes añadir más variables si las necesitas 

        """
        #self.urls = set() # hash para las urls procesadas
        self.index = {} # hash para el indice invertido de terminos --> clave: termino, valor: posting list
        self.sindex = {} # hash para el indice invertido de stems --> clave: stem, valor: lista con los terminos que tienen ese stem
        self.ptindex = {} # hash para el indice permuterm.
        self.docs = {} # diccionario de terminos --> clave: entero(docid),  valor: ruta del fichero.
        self.weight = {} # hash de terminos para el pesado, ranking de resultados.
        self.articles = {} # hash de articulos --> clave entero (artid), valor: la info necesaria para diferencia los artículos  dentro de su fichero
        self.tokenizer = re.compile("\W+") # expresion regular para hacer la tokenizacion
        self.stemmer = SnowballStemmer('spanish') # stemmer en castellano
        self.show_all = False # valor por defecto, se cambia con self.set_showall()
        self.show_snippet = False # valor por defecto, se cambia con self.set_snippet()
        self.use_stemming = False # valor por defecto, se cambia con self.set_stemming()
        self.use_ranking = False  # valor por defecto, se cambia con self.set_ranking()

        self.urls = {} # diccionario donde cada key es un campo y cada valor son las urls procesadas para ese campo

        
    ###############################
    ###                         ###
    ###      CONFIGURACION      ###
    ###                         ###
    ###############################


    def set_showall(self, v:bool):
        """

        Cambia el modo de mostrar los resultados.
        
        input: "v" booleano.

        UTIL PARA TODAS LAS VERSIONES

        si self.show_all es True se mostraran todos los resultados el lugar de un maximo de self.SHOW_MAX, no aplicable a la opcion -C

        """
        self.show_all = v


    def set_snippet(self, v:bool):
        """

        Cambia el modo de mostrar snippet.
        
        input: "v" booleano.

        UTIL PARA TODAS LAS VERSIONES

        si self.show_snippet es True se mostrara un snippet de cada noticia, no aplicable a la opcion -C

        """
        self.show_snippet = v


    def set_stemming(self, v:bool):
        """

        Cambia el modo de stemming por defecto.
        
        input: "v" booleano.

        UTIL PARA LA VERSION CON STEMMING

        si self.use_stemming es True las consultas se resolveran aplicando stemming por defecto.

        """
        self.use_stemming = v



    #############################################
    ###                                       ###
    ###      CARGA Y GUARDADO DEL INDICE      ###
    ###                                       ###
    #############################################


    def save_info(self, filename:str):
        """
        Guarda la información del índice en un fichero en formato binario
        
        """
        info = [self.all_atribs] + [getattr(self, atr) for atr in self.all_atribs]
        with open(filename, 'wb') as fh:
            pickle.dump(info, fh)

    def load_info(self, filename:str):
        """
        Carga la información del índice desde un fichero en formato binario
        
        """
        #info = [self.all_atribs] + [getattr(self, atr) for atr in self.all_atribs]
        with open(filename, 'rb') as fh:
            info = pickle.load(fh)
        atrs = info[0]
        for name, val in zip(atrs, info[1:]):
            setattr(self, name, val)

    ###############################
    ###                         ###
    ###   PARTE 1: INDEXACION   ###
    ###                         ###
    ###############################

    def already_in_index(self, article:Dict) -> bool:
        """
        Args:
            article (Dict): diccionario con la información de un artículo

        Returns:
            bool: True si el artículo ya está indexado, False en caso contrario
        """
        return article['url'] in self.urls


    def index_dir(self, root:str, **args):
        """
        
        Recorre recursivamente el directorio o fichero "root" 
        NECESARIO PARA TODAS LAS VERSIONES
        
        Recorre recursivamente el directorio "root"  y indexa su contenido
        los argumentos adicionales "**args" solo son necesarios para las funcionalidades ampliadas

        """

        self.multifield = args['multifield']
        self.positional = args['positional']
        self.stemming = args['stem']
        self.permuterm = args['permuterm']

        # en caso de multifields, añadimos los campos, tanto para el indice de terminos, como para los de las ampliaciones para que funcionen conjuntamente
        if self.multifield:
            self.index = {
                'all': {},
                'title': {},
                'summary': {},
                'section-name': {},
                'url': {}
            }

            self.urls = {
                'all': set(),
                'title': set(),
                'summary': set(),
                'section-name': set(),
                'url': set()
            }

            # si llamamos con opción de stemming
            if self.stemming:            
                self.sindex = {
                    'all': {},
                    'title': {},
                    'summary': {},
                    'section-name': {},
                    'url': {}
                }

            # si llamamos con opción de permuterm
            if self.permuterm:            
                self.ptindex = {
                    'all': {},
                    'title': {},
                    'summary': {},
                    'section-name': {},
                    'url': {}
                }

        # en caso base, solo indexamos en el campo 'all'
        else:
            self.index = {
                'all': {}
            }

            self.urls = {
                'all': set()
            }

            # si llamamos con opción de stemming
            if self.stemming:            
                self.sindex = {
                    'all': {}
                }

            # si llamamos con opción de permuterm
            if self.permuterm:            
                self.ptindex = {
                    'all': {}
                }


        file_or_dir = Path(root)
        self.set_stemming(self.stemming)
        
        if file_or_dir.is_file():
            # is a file
            self.index_file(root)
            if self.use_stemming:
                self.make_stemming()
            if self.permuterm:
                self.make_permuterm()


        elif file_or_dir.is_dir():
            # is a directory
            for d, _, files in os.walk(root):
                for filename in files:
                    if filename.endswith('.json'):
                        fullname = os.path.join(d, filename)
                        self.index_file(fullname)
            if self.use_stemming:
                self.make_stemming()
            if self.permuterm:
                self.make_permuterm()

        else:
            print(f"ERROR:{root} is not a file nor directory!", file=sys.stderr)
            sys.exit(-1)

        ## COMPLETAR PARA FUNCIONALIDADES EXTRA ##
        
        
    def parse_article(self, raw_line:str) -> Dict[str, str]:
        """
        Crea un diccionario a partir de una linea que representa un artículo del crawler

        Args:
            raw_line: una linea del fichero generado por el crawler

        Returns:
            Dict[str, str]: claves: 'url', 'title', 'summary', 'all', 'section-name'
        """
        
        article = json.loads(raw_line)
        sec_names = []
        txt_secs = ''
        for sec in article['sections']:
            txt_secs += sec['name'] + '\n' + sec['text'] + '\n'
            txt_secs += '\n'.join(subsec['name'] + '\n' + subsec['text'] + '\n' for subsec in sec['subsections']) + '\n\n'
            sec_names.append(sec['name'])
            sec_names.extend(subsec['name'] for subsec in sec['subsections'])
        article.pop('sections') # no la necesitamos 
        article['all'] = article['title'] + '\n\n' + article['summary'] + '\n\n' + txt_secs
        article['section-name'] = '\n'.join(sec_names)

        return article
                
    
    def index_file(self, filename:str):
        """

        Indexa el contenido de un fichero.
        
        input: "filename" es el nombre de un fichero generado por el Crawler cada línea es un objeto json
            con la información de un artículo de la Wikipedia

        NECESARIO PARA TODAS LAS VERSIONES

        dependiendo del valor de self.multifield y self.positional se debe ampliar el indexado


        """
        
        #
        # 
        # En la version basica solo se debe indexar el contenido "article"
        #
        #

        docid = len(self.docs)    # identificador del documento
        self.docs[docid] = filename          # añadimos el fichero al diccionario de documentos: clave -> id del documento / valor -> ruta del fichero

        # recorremos y enumeramos cada articulo del documento filename
        for i, line in enumerate(open(filename)):
            # procesamos el articulo y devuelve un diccionario procesado
            art_dic = self.parse_article(line)
            artid = len(self.articles)           # identificador del articulo

            # recorremos todos los campos, por si hay mas de uno por llamada con multifield
            for field in self.index.keys():
                terminos = set() # conjunto en el que le iremos metiendo los terminos del articulo

                # en el caso de que haya que tokenizar los terminos del campo
                if field != 'url':
                    articulo = self.tokenize(art_dic[field])        # elimina los simbolos y separa por espacios cada articulo
                else:
                    articulo = [art_dic[field]]

                # en el caso de que la url del articulo no haya sido referenciada antes
                if art_dic['url'] not in self.urls[field]:

                    self.articles[artid] = {
                        'docid': docid,
                        'pos': i,
                        'title': art_dic['title'],
                        'url': art_dic['url']
                    }
                           
                    # añadimos cada articulo del documento al diccionario de articulos: clave -> id del articulo / valor -> tupla (id del documento y posicion dentro del documento)
                    # self.articles[artid] = self.articles.get(artid, []) + [(docid, i)]
                    self.urls[field].add(art_dic['url']) # añadimos al conjunto de urls la url del articulo para que no se repitan

                    # para cada termino del articulo lo introducimos en el diccionario de terminos
                    for t in articulo:
                        # en el caso de que se repitan terminos en un mismo articulo, que no se referencie el articulo varias veces en el diccionario
                        if t not in terminos:
                            # añadimos cada termino al diccionario de terminos: clave -> termino / valor -> id del articulo en el que se encuentra
                            self.index[field][t] = self.index[field].get(t, []) + [artid]
                            terminos.add(t)     # añadimos al conjunto de terminos el termino actual para que no se repitan
        
        

    def set_stemming(self, v:bool):
        """

        Cambia el modo de stemming por defecto.
        
        input: "v" booleano.

        UTIL PARA LA VERSION CON STEMMING

        si self.use_stemming es True las consultas se resolveran aplicando stemming por defecto.

        """
        self.use_stemming = v


    def tokenize(self, text:str):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Tokeniza la cadena "texto" eliminando simbolos no alfanumericos y dividientola por espacios.
        Puedes utilizar la expresion regular 'self.tokenizer'.

        params: 'text': texto a tokenizar

        return: lista de tokens

        """
        return self.tokenizer.sub(' ', text.lower()).split()


    def make_stemming(self):
        """

        Crea el indice de stemming (self.sindex) para los terminos de todos los indices.

        NECESARIO PARA LA AMPLIACION DE STEMMING.

        "self.stemmer.stem(token) devuelve el stem del token"


        """
        
        for key in self.index.keys():
            for token in self.index[key]:
                token_stem = self.stemmer.stem(token)   
                self.sindex[key][token_stem] = self.sindex[key].get(token_stem, []) + [token]

    
    def make_permuterm(self):
        """

        Crea el indice permuterm (self.ptindex) para los terminos de todos los indices.

        NECESARIO PARA LA AMPLIACION DE PERMUTERM


        """

        ## COMPLETAR PARA FUNCIONALIDAD EXTRA DE STEMMING ##

        for field in self.index.keys():
            for token in self.index[field].keys():
                per = [] #para almacenar permutaciones
                tokenn = token + '$'
                for i in range(len(tokenn)):
                    # el dolar se pone al principio
                    tokenn = tokenn[1:]+tokenn[0]
                    per+=[tokenn]
                for j in per:
                    if j not in self.ptindex:
                        self.ptindex[field][j]=[token]
                    else:
                        if token not in self.ptindex[field][j]:
                            self.ptindex[field][j]+=[token]


    def show_stats(self):
        """
        NECESARIO PARA TODAS LAS VERSIONES
        
        Muestra estadisticas de los indices
        
        """
        
        ## COMPLETAR PARA TODAS LAS VERSIONES ##

        print('========================================')
        print('Number of indexed files: {}'.format(len(self.docs)))
        print('----------------------------------------')
        print('Number of indexed articles: {}'.format(len(self.articles)))
        print('----------------------------------------')
        print('TOKENS:')
        for f in self.index.keys():
            print("\t# of tokens in '{}': {}".format(f,len(self.index[f])))
        print('----------------------------------------')
        if self.permuterm:
            print('PERMUTERM:')
            for f in self.index.keys():
                print("\t# of stems in '{}': {}".format(f, len(self.ptindex[f])))
            print('----------------------------------------')
        if self.use_stemming:
            print('STEMS:')
            for f in self.index.keys():
                print("\t# of stems in '{}': {}".format(f, len(self.sindex[f])))
            print('----------------------------------------')
        print('Positional queries are NOT allowed')
        print('========================================')





    #################################
    ###                           ###
    ###   PARTE 2: RECUPERACION   ###
    ###                           ###
    #################################

    ###################################
    ###                             ###
    ###   PARTE 2.1: RECUPERACION   ###
    ###                             ###
    ###################################


    def separador(self, query):
        aux = query.split(sep=':')
        if len(aux) == 1:
           aux.insert(0,'all') 

        return (aux[0], aux[1])
        

    def solve_query(self, query:str, prev:Dict={}):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Resuelve una query.
        Debe realizar el parsing de consulta que sera mas o menos complicado en funcion de la ampliacion que se implementen


        param:  "query": cadena con la query
                "prev": incluido por si se quiere hacer una version recursiva. No es necesario utilizarlo.


        return: posting list con el resultado de la query

        """

        if query is None or len(query) == 0:
            return []

        result = []
        query = query.split()
        
        f = 'all'
        
        if len(query) == 1:
            
            f, query[0] = self.separador(query[0])
            
            word = query[0]
            result = self.get_posting(word, f)
        elif len(query) == 2 and query[0] == 'NOT':
            f, query[1] = self.separador(query[1])
            word = query[1]
            word_posting = self.get_posting(word, f)
            result = self.reverse_posting(word_posting)
        else:
            aux_posting = []
            key_words = ['AND','OR']

            for i in range(1,len(query)):
                if query[i] not in key_words:
                    continue

                if len(result) == 0 and  i > 1 and query[i-2] == 'NOT':
                    f, query[i-1] = self.separador(query[i-1])
                    word = query[i-1]
                    word_posting = self.get_posting(word, f)
                    result = self.reverse_posting(word_posting)
                elif len(result) == 0:
                    f, query[i-1] = self.separador(query[i-1])
                    word = query[i-1]
                    result = self.get_posting(word, f)

                if i+2 < len(query) and query[i+1] == 'NOT':
                    f, query[i+2] = self.separador(query[i+2])
                    word = query[i+2]
                    word_posting = self.get_posting(word, f)
                    aux_posting = self.reverse_posting(word_posting)
                elif i+1 < len(query):
                    f, query[i+1] = self.separador(query[i+1])
                    word = query[i+1]
                    aux_posting = self.get_posting(word, f)
                
                if query[i] == 'AND':
                    result = self.and_posting(result, aux_posting)
                        
                if query[i] == 'OR':
                    result = self.or_posting(result,aux_posting)

        return result




    def get_posting(self, term:str, field:Optional[str]='all'):
        """

        Devuelve la posting list asociada a un termino. 
        Dependiendo de las ampliaciones implementadas "get_posting" puede llamar a:
            - self.get_positionals: para la ampliacion de posicionales
            - self.get_permuterm: para la ampliacion de permuterms
            - self.get_stemming: para la amplaicion de stemming


        param:  "term": termino del que se debe recuperar la posting list.
                "field": campo sobre el que se debe recuperar la posting list, solo necesario si se hace la ampliacion de multiples indices

        return: posting list
        
        NECESARIO PARA TODAS LAS VERSIONES
S
        """
        term = term.lower()
        
        if self.use_stemming:
            return self.get_stemming(term, field)
        elif '*' in term or '?' in term:
            return self.get_permuterm(term,field)
        # devuelve el valor al termino asociado
        return self.index[field].get(term,[])



    def get_positionals(self, terms:str, index):
        """

        Devuelve la posting list asociada a una secuencia de terminos consecutivos.
        NECESARIO PARA LA AMPLIACION DE POSICIONALES

        param:  "terms": lista con los terminos consecutivos para recuperar la posting list.
                "field": campo sobre el que se debe recuperar la posting list, solo necesario se se hace la ampliacion de multiples indices

        return: posting list

        """
        pass
        ########################################################
        ## COMPLETAR PARA FUNCIONALIDAD EXTRA DE POSICIONALES ##
        ########################################################


    def get_stemming(self, term:str, field: Optional[str]='all'):
        """

        Devuelve la posting list asociada al stem de un termino.
        NECESARIO PARA LA AMPLIACION DE STEMMING

        param:  "term": termino para recuperar la posting list de su stem.
                "field": campo sobre el que se debe recuperar la posting list, solo necesario se se hace la ampliacion de multiples indices

        return: posting list

        """
        
        stem = self.stemmer.stem(term)
        result = []

        tokens = self.sindex[field].get(stem, [])
        for token in tokens:
            token_posting = self.index[field].get(token, [])
            result = self.or_posting(result, token_posting)

        return result

    def get_permuterm(self, term:str, field:Optional[str]='all'):
        """

        Devuelve la posting list asociada a un termino utilizando el indice permuterm.
        NECESARIO PARA LA AMPLIACION DE PERMUTERM

        param:  "term": termino para recuperar la posting list, "term" incluye un comodin (* o ?).
                "field": campo sobre el que se debe recuperar la posting list, solo necesario se se hace la ampliacion de multiples indices

        return: posting list

        """

        ## COMPLETAR PARA FUNCIONALIDAD EXTRA PERMUTERM ##

        posList = []
        term+='$'
        while(term[-1]!='*' and term[-1]!='?'):
            term= term[1:0]+term[0]
        sign = term[-1]
        term = term[:-1]
        #buscar permutaciones
        for per in (x for x in list(self.ptindex[field].keys())if x.startswith(term) and (sign=='*' or len(x)==len(term)+1)):
           for token in self.ptindex[field][per]:
               posList = self.or_posting(posList, self.get_posting(token,field,wildcard=True))
        return posList



    def reverse_posting(self, p:list):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Devuelve una posting list con todas las noticias excepto las contenidas en p.
        Util para resolver las queries con NOT.


        param:  "p": posting list


        return: posting list con todos los artid exceptos los contenidos en p

        """

        # devuelve una posting list con todos los articulos que no se encuentran en p
        return [a for a in self.articles.keys() if a not in p]



    def and_posting(self, p1:list, p2:list):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Calcula el AND de dos posting list de forma EFICIENTE

        param:  "p1", "p2": posting lists sobre las que calcular


        return: posting list con los artid incluidos en p1 y p2

        """
        res = []
        i = 0
        j = 0

        while i < len(p1) and j < len(p2):
            if p1[i] == p2[j]:
                res.append(p1[i])
                i += 1
                j += 1
            elif p1[i] <= p2[j]:
                i += 1
            elif p1[i] >= p2[j]:
                j += 1

        return res



    def or_posting(self, p1:list, p2:list):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Calcula el OR de dos posting list de forma EFICIENTE

        param:  "p1", "p2": posting lists sobre las que calcular


        return: posting list con los artid incluidos de p1 o p2

        """

        res = []
        i = 0
        j = 0
        while i < len(p1) and j < len(p2):
            if p1[i] == p2[j]:
                res.append(p1[i])
                i += 1
                j += 1
            elif p1[i] <= p2[j]:
                res.append(p1[i])
                i += 1
            elif p1[i] >= p2[j]:
                res.append(p2[j])
                j += 1
        
        while i < len(p1): 
            res.append(p1[i])
            i += 1

        while j < len(p2): 
            res.append(p2[j])
            j += 1
        
        return res


    def minus_posting(self, p1, p2):
        """
        OPCIONAL PARA TODAS LAS VERSIONES

        Calcula el except de dos posting list de forma EFICIENTE.
        Esta funcion se incluye por si es util, no es necesario utilizarla.

        param:  "p1", "p2": posting lists sobre las que calcular


        return: posting list con los artid incluidos de p1 y no en p2

        """

        
        pass
        ########################################################
        ## COMPLETAR PARA TODAS LAS VERSIONES SI ES NECESARIO ##
        ########################################################





    #####################################
    ###                               ###
    ### PARTE 2.2: MOSTRAR RESULTADOS ###
    ###                               ###
    #####################################

    def solve_and_count(self, ql:List[str], verbose:bool=True) -> List:
        results = []
        for query in ql:
            if len(query) > 0 and query[0] != '#':
                r = self.solve_query(query)
                results.append(len(r))
                if verbose:
                    print(f'{query}\t{len(r)}')
            else:
                results.append(0)
                if verbose:
                    print(query)
        return results


    def solve_and_test(self, ql:List[str]) -> bool:
        errors = False
        for line in ql:
            if len(line) > 0 and line[0] != '#':
                query, ref = line.split('\t')
                reference = int(ref)
                result = len(self.solve_query(query))
                if reference == result:
                    print(f'{query}\t{result}')
                else:
                    print(f'>>>>{query}\t{reference} != {result}<<<<')
                    errors = True                    
            # else:
            #     print(query)
        return not errors


    def solve_and_show(self, query:str):
        """
        NECESARIO PARA TODAS LAS VERSIONES

        Resuelve una consulta y la muestra junto al numero de resultados 

        param:  "query": query que se debe resolver.

        return: el numero de artículo recuperadas, para la opcion -T

        """
        

        res = self.solve_query(query)
        max_to_show = len(res) if self.show_all else self.SHOW_MAX

        print('========================================')
        for i, art_id in enumerate(res):
            if i == max_to_show:
                break
            title = self.articles[art_id]['title']
            url = self.articles[art_id]['url']
            print(f'# {i+1:02} ({art_id:3}) {title}: {url}')
        print('========================================')
        print("Number of results: {}".format(len(res)))

        return len(res)
