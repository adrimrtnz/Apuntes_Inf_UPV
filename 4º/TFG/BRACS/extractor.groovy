   
import qupath.lib.io.PathIO

// Ruta al directorio que contiene los archivos de anotación
def dir = 'D:\\Datasets\\BRACS\\BRACS_WSI_Annotations'

// Función recursiva para leer archivos de un directorio y sus subdirectorios
def leerArchivos(def dir) {
    def files = dir.listFiles()
    files.each { file ->
        if (file.isDirectory()) {
            // Si el archivo es un directorio, llama a la función de forma recursiva
            leerArchivos(file)
        } else if (file.getName().endsWith('.qpdata')) {
            // Si el archivo es una anotación de QuPath, lee las anotaciones
            def annotations = PathIO.readObjects(file)
            
            // Guarda las anotationes en formato GeoJSON
            exportObjectsToGeoJson(annotations, file.getPath() + '.geojson', "FEATURE_COLLECTION")
            
            // Imprime el nombre del archivo y el número de anotaciones
            println(file.getName() + ': ' + annotations.size())
        }
    }
}

// Llama a la función en el directorio principal
leerArchivos(new File(dir))
