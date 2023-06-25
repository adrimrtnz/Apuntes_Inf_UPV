#! -*- encoding: utf8 -*-
import heapq as hq

from typing import Tuple, List, Optional, Dict, Union

import requests
import bs4
import re
from urllib.parse import urljoin
import json
import math
import os






class SAR_Wiki_Crawler:

    def __init__(self):
        # Expresión regular para detectar si es un enlace de la Wikipedia
        self.wiki_re = re.compile(r"(http(s)?:\/\/(es)\.wikipedia\.org)?\/wiki\/[\w\/_\(\)\%]+")
        # Expresión regular para limpiar anclas de editar
        self.edit_re = re.compile(r"\[(editar)\]")
        # Formato para cada nivel de sección
        self.section_format = {
            "h1": "##{}##",
            "h2": "=={}==",
            "h3": "--{}--",
        }

        # Expresiones regulares útiles para el parseo del documento
        self.title_sum_re = re.compile(r"##(?P<title>.+)##\n(?P<summary>((?!==.+==).+|\n)+)(?P<rest>(.+|\n)*)")
        self.sections_re = re.compile(r"==.+==\n")
        self.section_re = re.compile(r"==(?P<name>.+)==\n(?P<text>((?!--.+--).+|\n)*)(?P<rest>(.+|\n)*)")
        self.subsections_re = re.compile(r"--.+--\n")
        self.subsection_re = re.compile(r"--(?P<name>.+)--\n(?P<text>(.+|\n)*)")


    def is_valid_url(self, url: str) -> bool:
        """Verifica si es una dirección válida para indexar

        Args:
            url (str): Dirección a verificar

        Returns:
            bool: True si es valida, en caso contrario False
        """
        return self.wiki_re.fullmatch(url) is not None


    def get_wikipedia_entry_content(self, url: str) -> Optional[Tuple[str, List[str]]]:
        """Devuelve el texto en crudo y los enlaces de un artículo de la wikipedia

        Args:
            url (str): Enlace a un artículo de la Wikipedia

        Returns:
            Optional[Tuple[str, List[str]]]: Si es un enlace correcto a un artículo
                de la Wikipedia en inglés o castellano, devolverá el texto y los
                enlaces que contiene la página.

        Raises:
            ValueError: En caso de que no sea un enlace a un artículo de la Wikipedia
                en inglés o español
        """
        if not self.is_valid_url(url):
            raise ValueError((
                f"El enlace '{url}' no es un artículo de la Wikipedia en español"
            ))

        req = requests.get(url)

        # Solo devolvemos el resultado si la petición ha sido correcta
        if req.status_code == 200:
            soup = bs4.BeautifulSoup(req.text, "lxml")
            urls = set()

            for ele in soup.select((
                'div#catlinks, div.printfooter, div.mw-authority-control'
            )):
                ele.decompose()

            # Recogemos todos los enlaces del contenido del artículo
            for a in soup.select("div#bodyContent a", href=True):
                href = a.get("href")
                if href is not None:
                    urls.add(href)

            # Contenido del artículo
            content = soup.select((
                "h1.firstHeading,"
                "div#mw-content-text h2,"
                "div#mw-content-text h3,"
                "div#mw-content-text h4,"
                "div#mw-content-text p,"
                "div#mw-content-text ul,"
                "div#mw-content-text li"
            ))
            text = "\n".join(
                self.section_format.get(element.name, "{}").format(element.text)
                for element in content
            )

            # Eliminamos el texto de las anclas de editar
            text = self.edit_re.sub('', text)

            return text, sorted(list(urls))

        return None


    def parse_wikipedia_textual_content(self, text: str, url: str) -> Optional[Dict[str, Union[str,List]]]:
        """Devuelve una estructura tipo noticia a partir del text en crudo

        Args:
            text (str): Texto en crudo del artículo de la Wikipedia
            url (str): url de la notica, para añadirlo como un campo

        Returns:

            Optional[Dict[str, Union[str,List[Dict[str,Union[str,List[str,str]]]]]]]:

            devuelve un diccionario con las claves 'url', 'title', 'summary', 'sections':
                Los valores asociados a 'url', 'title' y 'summary' son cadenas,
                el valor asociado a 'sections' es una lista de posibles secciones.
                    Cada sección es un diccionario con 'name', 'text' y 'subsections',
                        los valores asociados a 'name' y 'text' son cadenas y,
                        el valor asociado a 'subsections' es una lista de posibles subsecciones
                        en forma de diccionario con 'name' y 'text'.

            en caso de no encontrar título o resúmen del artículo, devolverá None

        """
        def clean_text(txt):
            return '\n'.join(l for l in txt.split('\n') if len(l) > 0).strip()

        document = None

        # COMPLETAR
        match = self.title_sum_re.match(text)
        
        if match is None:
            return
        else:
            document = {}
        
        # Diccionario con las keys ['title', 'summary', 'rest']
        groups = match.groupdict()
        
        document['url'] = url
        document['title'] = groups['title']
        document['summary'] = groups['summary']
        document['sections'] = []

        sections = self.sections_re.findall(groups['rest'])

        # Creación de tuplas (ini_section, ini_next_section)
        section_tuples_list = []
        for i in range(len(sections) - 1):
            section_tuples_list.append(tuple(sections[i:i+2]))


        for s in section_tuples_list:
            ini = text.find(s[0])
            fin = text.find(s[1])
            
            section_text = text[ini:fin]
            self.extract_section_data(document, section_text, s[1])

        # En el bucle de tuplas se queda fuera la tupla (last_section, fin)
        if len(section_tuples_list) > 1:
            s = section_tuples_list[-1][1]
            ini = text.find(s)
            
            section_text = text[ini:]
            self.extract_section_data(document, section_text, None)    
            
        return document


    def extract_section_data(self, document: dict, text: str, next_section_ini: str):
        """
        Extrae la información de la sección y la añade al documento

        Args:
            document (dict): diccionario del documento al que pertenece la sección
            text (str): texto de la sección
            next_section_ini (str): texto para delimitar el fin de esta sección
        """

        # Extraemos las partes de la sección
        match = self.section_re.match(text)
        # Diccionario con las keys ['name', 'text', 'rest']
        section_dic = match.groupdict()   
        
        section = {}
        section['name'] = section_dic['name']
        section['text'] = section_dic['text']
        section['subsections'] = []
        document['sections'].append(section)

        # Subsecciones
        subsections = self.subsections_re.findall(section_dic['rest'])

        # Creación de tuplas (ini_subsection, ini_next_subsection)
        subsections_tuples_list = []
        for j in range(len(subsections) - 1):
            subsections_tuples_list.append(tuple(subsections[j:j+2]))
        
        # Si hay subsecciones, en el bucle anterior se deja fuera la última subsección
        # la añadimos aquí delimitándola con el next_section_ini
        if len(subsections_tuples_list) > 1:
            t = (subsections_tuples_list[-1][1],next_section_ini)
            subsections_tuples_list.append(t)

        # Si solo hay una subsección no se crea ninguna tupla en los bucles anteriores
        if len(subsections) > 0 and len(subsections_tuples_list) == 0:
            subsections_tuples_list.append((subsections[0], next_section_ini))

        for sub in subsections_tuples_list:
            ini = text.find(sub[0])

            if sub[1] is not None:
                fin = text.find(sub[1])
            
            if fin is not None:
                subsection_text = text[ini:fin]
            else:
                subsection_text = text[ini:]
            self.extract_subsection_data(section, subsection_text)


    def extract_subsection_data(self, section: dict, text: str):
        """
        Extrae la información de la subsección y la añade a la sección

        Args:
            section (dict): diccionario de la sección a la que pertenece la subsección
            text (str): texto de la subsección

        en caso de no encontrar subsecciones de la sección, devolverá None
        """
        
        # Extraemos las partes de cada subsección si las tiene
        match = self.subsection_re.match(text)
        if match is None:
            return None
        
        # Diccionario con las keys ['name', 'text']
        subsection_dic = match.groupdict()

        subsection = {}
        subsection['name'] = subsection_dic['name']
        subsection['text'] = subsection_dic['text']
        section['subsections'].append(subsection)


    def save_documents(self,
        documents: List[dict], base_filename: str,
        num_file: Optional[int] = None, total_files: Optional[int] = None
    ):
        """Guarda una lista de documentos (text, url) en un fichero tipo json lines
        (.json). El nombre del fichero se autogenera en base al base_filename,
        el num_file y total_files. Si num_file o total_files es None, entonces el
        fichero de salida es el base_filename.

        Args:
            documents (List[dict]): Lista de documentos.
            base_filename (str): Nombre base del fichero de guardado.
            num_file (Optional[int], optional):
                Posición numérica del fichero a escribir. (None por defecto)
            total_files (Optional[int], optional):
                Cantidad de ficheros que se espera escribir. (None por defecto)
        """
        assert base_filename.endswith(".json")

        if num_file is not None and total_files is not None:
            # Separamos el nombre del fichero y la extensión
            base, ext = os.path.splitext(base_filename)
            # Padding que vamos a tener en los números
            padding = len(str(total_files))

            out_filename = f"{base}_{num_file:0{padding}d}_{total_files}{ext}"

        else:
            out_filename = base_filename

        with open(out_filename, "w", encoding="utf-8", newline="\n") as ofile:
            for doc in documents:
                print(json.dumps(doc, ensure_ascii=True), file=ofile)


    def start_crawling(self, 
                    initial_urls: List[str], document_limit: int,
                    base_filename: str, batch_size: Optional[int], max_depth_level: int,
                    ):        
         

        """Comienza la captura de entradas de la Wikipedia a partir de una lista de urls válidas, 
            termina cuando no hay urls en la cola o llega al máximo de documentos a capturar.
        
        Args:
            initial_urls: Direcciones a artículos de la Wikipedia
            document_limit (int): Máximo número de documentos a capturar
            base_filename (str): Nombre base del fichero de guardado.
            batch_size (Optional[int]): Cada cuantos documentos se guardan en
                fichero. Si se asigna None, se guardará al finalizar la captura.
            max_depth_level (int): Profundidad máxima de captura.
        """

        # URLs válidas, ya visitadas (se hayan procesado, o no, correctamente)
        visited = set()
        # URLs en cola
        to_process = set(initial_urls)
        # Direcciones a visitar
        queue = [(0, "", url) for url in to_process]
        hq.heapify(queue)
        # Buffer de documentos capturados
        documents: List[dict] = []
        # Contador del número de documentos capturados
        total_documents_captured = 0
        # Contador del número de ficheros escritos
        files_count = 0

        # En caso de que no utilicemos bach_size, asignamos None a total_files
        # así el guardado no modificará el nombre del fichero base
        if batch_size is None:
            total_files = None
        else:
            # Suponemos que vamos a poder alcanzar el límite para la nomenclatura
            # de guardado
            total_files = math.ceil(document_limit / batch_size)
            print(f'Tengo batch_size de {batch_size}, con un total_files={total_files}, y document_limit={document_limit}')

        while len(queue) > 0 and (total_documents_captured < document_limit):

            # 1. Seleccionar una página no procesada de la cola de prioridad
            depth, parent_url, url = hq.heappop(queue)
            # print(f'Voy a mirar url: {url}, y url padre: {parent_url}')

            # 2. Descarga el contenido textual de la página y los enlaces que aparecen en ella
            test_url = self.get_wikipedia_entry_content(url)
            visited.add(url)

            if test_url is not None:
                content, urls = test_url
                
                # Comentar o descomentar para comprobar lo que se coge realmente
                # with open(f'content-{total_documents_captured}.txt', 'w', encoding='utf-8') as content_f:
                #     print(content, file=content_f)
                # with open(f'urls-{total_documents_captured}.txt', 'w', encoding='utf-8') as urls_f:
                #     print(urls, file=urls_f)

                document = self.parse_wikipedia_textual_content(content, url)
                if document is None:
                    continue

                total_documents_captured += 1
                documents.append(document)

                if depth < max_depth_level:
                    for child_url in urls:
                        if self.is_valid_url(child_url):
                            if not 'http' in child_url:
                                child_url = urljoin(url, child_url)
                            if child_url not in visited:
                                queue.append((depth+1, url, child_url))

            
                
                if (batch_size is not None and len(documents) == batch_size):
                    self.save_documents(documents, base_filename, files_count+1, total_files);
                    files_count += 1
                    documents = []
                    # print(f'He guardado la parte ({files_count}/{total_files})')

        # hay que pasarle los cuatro parámetros, comprobar si hay documentos que guardar por si batch_size
        # no dejar documentos sin guardar, si no batch_size, la siguiente instrucción guarda todo
        if (len(documents) > 0):    
            files_count += 1
            self.save_documents(documents, base_filename, files_count, total_files)



    def wikipedia_crawling_from_url(self,
        initial_url: str, document_limit: int, base_filename: str,
        batch_size: Optional[int], max_depth_level: int
    ):
        """Captura un conjunto de entradas de la Wikipedia, hasta terminar
        o llegar al máximo de documentos a capturar.
        
        Args:
            initial_url (str): Dirección a un artículo de la Wikipedia
            document_limit (int): Máximo número de documentos a capturar
            base_filename (str): Nombre base del fichero de guardado.
            batch_size (Optional[int]): Cada cuantos documentos se guardan en
                fichero. Si se asigna None, se guardará al finalizar la captura.
            max_depth_level (int): Profundidad máxima de captura.
        """
        if not self.is_valid_url(initial_url) and not initial_url.startswith("/wiki/"):
            raise ValueError(
                "Es necesario partir de un artículo de la Wikipedia en español"
            )

        self.start_crawling(initial_urls=[initial_url], document_limit=document_limit, base_filename=base_filename,
                            batch_size=batch_size, max_depth_level=max_depth_level)



    def wikipedia_crawling_from_url_list(self,
        urls_filename: str, document_limit: int, base_filename: str,
        batch_size: Optional[int]
    ):
        """A partir de un fichero de direcciones, captura todas aquellas que sean
        artículos de la Wikipedia válidos

        Args:
            urls_filename (str): Lista de direcciones
            document_limit (int): Límite máximo de documentos a capturar
            base_filename (str): Nombre base del fichero de guardado.
            batch_size (Optional[int]): Cada cuantos documentos se guardan en
                fichero. Si se asigna None, se guardará al finalizar la captura.

        """

        urls = []
        with open(urls_filename, "r", encoding="utf-8") as ifile:
            for url in ifile:
                url = url.strip()

                # Comprobamos si es una dirección a un artículo de la Wikipedia
                if self.is_valid_url(url):
                    if not url.startswith("http"):
                        raise ValueError(
                            "El fichero debe contener URLs absolutas"
                        )

                    urls.append(url)

        urls = list(set(urls)) # eliminamos posibles duplicados

        self.start_crawling(initial_urls=urls, document_limit=document_limit, base_filename=base_filename,
                            batch_size=batch_size, max_depth_level=0)





if __name__ == "__main__":
    raise Exception(
        "Esto es una librería y no se puede usar como fichero ejecutable"
    )
