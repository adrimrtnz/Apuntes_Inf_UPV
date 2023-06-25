#!/usr/bin/env python
#! -*- encoding: utf8 -*-

from SAR_Crawler_lib import SAR_Wiki_Crawler
import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Capturador de entradas de la Wikipedia"
    )

    parser.add_argument(
        "--out-base-filename",
        help="Ruta donde se guardarán los documentos capturados (.json)",
        required=True
    )
    parser.add_argument(
        "--batch-size", type=int,
        help=(
            "Si se define un tamaño, se guardará en un fichero cada vez "
            "que hayamos capturado este número de documentos"
        )
    )
    parser.add_argument(
        "--initial-url", help="Ruta de un artículo de la Wikipedia"
    )
    parser.add_argument(
        "--urls-filename", help=(
            "Listado de URLs que se desea capturar. "
            "Se omitirán todas aquellas que no sean entradas de "
            "la Wikipedia"
        )
    )
    parser.add_argument(
        "--document-limit", help="Número máximo de documentos a capturar",
        type=int, default=10000
    )
    parser.add_argument(
        "--max-depth-level", type=int, default=4,
        help="Profundidad máxima de captura"
    )

    args = parser.parse_args()

    if args.initial_url is None and args.urls_filename is None:
        raise ValueError((
            "Se debe especificar la dirección inicial (--initial-url) o"
            " un fichero de direcciones (--urls-filename)"
        ))

    if not args.out_base_filename.endswith(".json"):
        raise ValueError("Debe de ser un fichero con extensión .json")

    crawler = SAR_Wiki_Crawler()

    if args.initial_url is not None:
        crawler.wikipedia_crawling_from_url(
            args.initial_url, args.document_limit, args.out_base_filename,
            args.batch_size, args.max_depth_level
        )

    else:
        crawler.wikipedia_crawling_from_url_list(
            args.urls_filename, args.document_limit,
            args.out_base_filename, args.batch_size
        )
