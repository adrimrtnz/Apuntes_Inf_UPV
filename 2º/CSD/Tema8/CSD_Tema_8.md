# Tema 8: Comunicación

### Actividad 5

En el mecanismo ROI, la creación de objetos puede realizarse por iniciativa del cliente o del servidor.

**Por iniciativa del cliente:**

1. Un proceso (cliente) solicita a un servidor (factoría) que cree un determinado objeto.

2. El servidor (factoría) crea el objeto (que le han solicitado crear) y lo registra en el ORB.

3. El servidor (factoría) obtiene una referencia al objeto.

4. El servidor (factoría) devuelve al cliente una copia de la referencia del objeto que ha solicitado crear.

**Por iniciativa del servidor:**

1. Un proceso crea un objeto y lo registra en el ORB.

2. El servidor (factoría) obtiene una referencia al objeto.

3. El proceso servidor usa la referencia del objeto para registrarlo en un servidor de nombres, proporcionando una cadena de texto como nombre del objeto.

4. Un proceso que conozca el nombre utilizado para registrar el objeto contacta con el servidor de nombres y obtiene una referencia al objeto.
