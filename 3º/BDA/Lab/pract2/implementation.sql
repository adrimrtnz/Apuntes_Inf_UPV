CREATE TABLE usuario (
    cod_u     CHAR(9) NOT NULL,
    nombre    VARCHAR2(25),
    apellido  VARCHAR2(25),
    email     VARCHAR2(150),
    fecha_reg DATE
);
ALTER TABLE usuario ADD CONSTRAINT usuario_pk PRIMARY KEY ( cod_u );
ALTER TABLE usuario ADD CONSTRAINT usuario__un UNIQUE ( email );

CREATE TABLE programador (
    cod_u    CHAR(9) NOT NULL,
    comision FLOAT NOT NULL
);
ALTER TABLE programador ADD CONSTRAINT programador_pk PRIMARY KEY ( cod_u );
ALTER TABLE programador
    ADD CONSTRAINT programador_usuario_fk FOREIGN KEY ( cod_u )
        REFERENCES usuario ( cod_u );

CREATE TABLE categoria (
    cod_cat     CHAR(5) NOT NULL,
    descripcion VARCHAR2(150)
);
ALTER TABLE categoria ADD CONSTRAINT categoria_pk PRIMARY KEY ( cod_cat );

CREATE TABLE revisor (
    cod_u    CHAR(9) NOT NULL,
    sueldo   FLOAT NOT NULL,
    licencia INTEGER NOT NULL,
    cod_cat  CHAR(5) NOT NULL
);
ALTER TABLE revisor ADD CONSTRAINT revisor_pk PRIMARY KEY ( cod_u );
ALTER TABLE revisor ADD CONSTRAINT revisor__un UNIQUE ( licencia );
ALTER TABLE revisor
    ADD CONSTRAINT revisor_categoria_fk FOREIGN KEY ( cod_cat )
        REFERENCES categoria ( cod_cat );
ALTER TABLE revisor
    ADD CONSTRAINT revisor_usuario_fk FOREIGN KEY ( cod_u )
        REFERENCES usuario ( cod_u );

CREATE TABLE aplicacion (
    cod_app     CHAR(15) NOT NULL,
    nombre      VARCHAR2(20),
    fecha_alta  DATE,
    cod_u       CHAR(9) NOT NULL,
    descripcion VARCHAR2(150),
    licencia    INTEGER
);
ALTER TABLE aplicacion ADD CONSTRAINT aplicacion_pk PRIMARY KEY ( cod_app );
ALTER TABLE aplicacion ADD CONSTRAINT aplicacion__un UNIQUE ( nombre );
ALTER TABLE aplicacion
    ADD CONSTRAINT aplicacion_programador_fk FOREIGN KEY ( cod_u )
        REFERENCES programador ( cod_u );

CREATE TABLE pertenece (
    cod_app CHAR(15) NOT NULL,
    cod_cat CHAR(5) NOT NULL
);
ALTER TABLE pertenece ADD CONSTRAINT pertenece_pk PRIMARY KEY ( cod_app,
                                                                cod_cat );
ALTER TABLE pertenece
    ADD CONSTRAINT pertenece_aplicacion_fk FOREIGN KEY ( cod_app )
        REFERENCES aplicacion ( cod_app );
ALTER TABLE pertenece
    ADD CONSTRAINT pertenece_categoria_fk FOREIGN KEY ( cod_cat )
        REFERENCES categoria ( cod_cat );

CREATE TABLE comentario (
    cod_app CHAR(15) NOT NULL,
    numero  INTEGER NOT NULL,
    cod_u   CHAR(9) NOT NULL,
    fecha   DATE NOT NULL,
    mensaje VARCHAR2(150) NOT NULL
);
ALTER TABLE comentario
    ADD CONSTRAINT pk_comentario PRIMARY KEY ( cod_app, numero, cod_u );
ALTER TABLE comentario
    ADD CONSTRAINT comentario_aplicacion_fk FOREIGN KEY ( cod_u )
        REFERENCES aplicacion ( cod_app );
ALTER TABLE comentario
    ADD CONSTRAINT comentario_usuario_fk FOREIGN KEY ( cod_u )
        REFERENCES usuario ( cod_u );

CREATE TABLE responde (
    cod_app  CHAR(15) NOT NULL,
    numero   INTEGER NOT NULL,
    cod_u    CHAR(9) NOT NULL,
    cod_appr CHAR(15) NOT NULL,
    numeror  INTEGER NOT NULL,
    cod_ur   CHAR(9) NOT NULL
);
ALTER TABLE responde
    ADD CONSTRAINT pk_responde PRIMARY KEY ( cod_app,
                                             numero,
                                             cod_u );
ALTER TABLE responde
    ADD CONSTRAINT responde_comentario_fk FOREIGN KEY ( cod_app,
                                                        numero,
                                                        cod_u )
        REFERENCES comentario ( cod_app,
                                numero,
                                cod_u );
ALTER TABLE responde
    ADD CONSTRAINT responde_comentario_fkv2 FOREIGN KEY ( cod_appr,
                                                          numeror,
                                                          cod_ur )
        REFERENCES comentario ( cod_app,
                                numero,
                                cod_u );

CREATE TABLE revisa (
    cod_app        CHAR(15) NOT NULL,
    cod_rev        CHAR(9) NOT NULL,
    fecha_aprobado DATE
);
COMMENT ON COLUMN revisa.fecha_aprobado IS
    'La fecha puede ser nula, lo que significaría que no se ha aprobado la aplicación';
ALTER TABLE revisa ADD CONSTRAINT pk_revisa PRIMARY KEY ( cod_app,
                                                          cod_rev );
ALTER TABLE revisa
    ADD CONSTRAINT revisa_aplicacion_fk FOREIGN KEY ( cod_app )
        REFERENCES aplicacion ( cod_app );
ALTER TABLE revisa
    ADD CONSTRAINT revisa_revisor_fk FOREIGN KEY ( cod_rev )
        REFERENCES revisor ( cod_u );

CREATE TABLE version (
    cod_app       CHAR(15) NOT NULL,
    num_ver       FLOAT NOT NULL,
    fecha_lanz    DATE NOT NULL,
    precio_base   FLOAT NOT NULL,
    observaciones VARCHAR2(150)
);
ALTER TABLE version ADD CONSTRAINT pk_version PRIMARY KEY ( cod_app,
                                                            num_ver );

ALTER TABLE version
    ADD CONSTRAINT version_aplicacion_fk FOREIGN KEY ( cod_app )
        REFERENCES aplicacion ( cod_app );

CREATE TABLE promocion (
    cod_app      CHAR(15) NOT NULL,
    num_ver      FLOAT NOT NULL,
    fecha_ini    DATE NOT NULL,
    fecha_fin    DATE NOT NULL,
    precio_promo FLOAT NOT NULL
);
ALTER TABLE promocion
    ADD CONSTRAINT pk_promocion PRIMARY KEY ( cod_app,
                                              num_ver,
                                              fecha_ini,
                                              fecha_fin );
ALTER TABLE promocion
    ADD CONSTRAINT promocion_version_fk FOREIGN KEY ( cod_app,
                                                      num_ver )
        REFERENCES version ( cod_app,
                             num_ver );

CREATE TABLE compra (
    cod_u        CHAR(9) NOT NULL,
    cod_app      CHAR(15) NOT NULL,
    num_ver      FLOAT NOT NULL,
    fecha_compra DATE NOT NULL,
    valoracion   INTEGER
);
ALTER TABLE compra
    ADD CONSTRAINT pk_compra PRIMARY KEY ( cod_u,
                                           cod_app,
                                           num_ver );
ALTER TABLE compra
    ADD CONSTRAINT compra_usuario_fk FOREIGN KEY ( cod_u )
        REFERENCES usuario ( cod_u );
ALTER TABLE compra
    ADD CONSTRAINT compra_version_fk FOREIGN KEY ( cod_app,
                                                   num_ver )
        REFERENCES version ( cod_app,
                             num_ver );

CREATE TABLE descarga (
    cod_u          CHAR(9) NOT NULL,
    cod_app        CHAR(15) NOT NULL,
    num_ver        FLOAT NOT NULL,
    fecha_descarga DATE NOT NULL
);
ALTER TABLE descarga
    ADD CONSTRAINT pk_descarga PRIMARY KEY ( cod_u,
                                             cod_app,
                                             num_ver,
                                             fecha_descarga );
ALTER TABLE descarga
    ADD CONSTRAINT descarga_usuario_fk FOREIGN KEY ( cod_u )
        REFERENCES usuario ( cod_u );
ALTER TABLE descarga
    ADD CONSTRAINT descarga_version_fk FOREIGN KEY ( cod_app,
                                                     num_ver )
        REFERENCES version ( cod_app,
                             num_ver );