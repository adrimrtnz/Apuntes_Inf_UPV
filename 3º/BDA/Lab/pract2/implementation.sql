CREATE TABLE Usuario (
    id CHAR(9) PRIMARY KEY,
    nombre VARCHAR(25),
    apellido VARCHAR(25),
    email VARCHAR(150) UNIQUE,
    fecha_reg DATE
);

CREATE TABLE Categoria (
    cod_cat CHAR(5) PRIMARY KEY,
    descripcion VARCHAR(150)
);

CREATE TABLE Programador (
    id CHAR(9) PRIMARY KEY,
    comision FLOAT NOT NULL,
    FOREIGN KEY (id) REFERENCES Usuario(id)
);

CREATE TABLE Revisor (
    id CHAR(9) PRIMARY KEY,
    sueldo FLOAT NOT NULL,
    licencia VARCHAR(10) NOT NULL,
    especialidad CHAR(5) NOT NULL,
    FOREIGN KEY (id) REFERENCES Usuario(id),
    FOREIGN KEY (especialidad) REFERENCES Categoria(cod_cat)
);

CREATE TABLE Aplicacion (
    cod_app CHAR(15) PRIMARY KEY,
    nombre VARCHAR(20) UNIQUE NOT NULL,
    fecha_alta DATE,
    cod_rev CHAR(9) CONSTRAINT fk_cod_rev REFERENCES Revisor(id), 
    descripcion VARCHAR(150)
);
# RI: Todo valor de cod_app de Aplicacion tiene que estar en cod_app de CategoriaApp

CREATE TABLE CategoriaApp (
    cod_app CHAR(15),
    cod_cat CHAR(5),

    PRIMARY KEY (cod_app, cod_cat),
    FOREIGN KEY (cod_app) REFERENCES Aplicacion(cod_app),
    FOREIGN KEY (cod_cat) REFERENCES Categoria(cod_cat)
);

CREATE TABLE Version (
    cod_app CHAR(15) CONSTRAINT fk_cod_app REFERENCES Aplicacion(cod_app),
    num_ver FLOAT,
    fecha_lanz DATE,
    precio_base FLOAT NOT NULL,
    observaciones VARCHAR(150),

    PRIMARY KEY (cod_app, num_ver),
);

CREATE TABLE Comentario (
    cod_u CHAR(9) CONSTRAINT fk_uid REFERENCES Usuario(id),
    cod_app CHAR(15) CONSTRAINT fk_cod_app REFERENCES Aplicacion(cod_app),
    numero_msg INT NOT NULL,
    fecha DATE, 
    mensaje VARCHAR(150) NOT NULL,
    responde_a INT CONSTRAINT fk_response REFERENCES Comentario(numero_msg),

    PRIMARY KEY (cod_u, cod_app, numero_msg)
);

CREATE TABLE Promocion (
    cod_app CHAR(15) CONSTRAINT fk_cod_app REFERENCES Version(cod_app),
    num_ver FLOAT CONSTRAINT fk_num_ver REFERENCES Version(num_ver),
    fecha_ini DATE,
    fecha_fin DATE,
    precio_promo FLOAT NOT NULL,

    PRIMARY KEY (cod_app, num_ver, fecha_ini, fecha_fin)
);
# RI: Para cualquier instante de tiempo sólo puede haber un precio por versión,
#     este precio tiene prioridad sobre el precio base.

CREATE TABLE Descarga (
    cod_u CHAR(9) CONSTRAINT fk_uid REFERENCES Usuario(id),
    cod_app CHAR(15) CONSTRAINT fk_cod_app REFERENCES Version(cod_app),
    num_ver FLOAT CONSTRAINT fk_num_ver REFERENCES Version(num_ver),
    fecha_descarga DATE,

    PRIMARY KEY (cod_u, cod_app, num_ver, fecha_descarga)
);

CREATE TABLE Compra (
    cod_u CHAR(9) CONSTRAINT fk_uid REFERENCES Usuario(id),
    cod_app CHAR(15) CONSTRAINT fk_cod_app REFERENCES Version(cod_app),
    num_ver FLOAT CONSTRAINT fk_num_ver REFERENCES Version(num_ver),
    fecha_compra DATE NOT NULL,
    valoracion INT,

    PRIMARY KEY (cod_u, cod_app, num_ver)
);
# RI: La valoración debe ser un valor comprendido entre 1 y 5.