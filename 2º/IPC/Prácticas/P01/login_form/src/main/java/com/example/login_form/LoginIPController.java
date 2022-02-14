package com.example.login_form;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;

import java.net.URL;
import java.util.ResourceBundle;


public class LoginIPController {
    @FXML
    private TextField texto_usuario;
    @FXML
    private Text mensaje_usuario;

    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }

    @FXML
    protected void pulsadoIniciar(ActionEvent event) {
        if (texto_usuario.getText().equals("")) {
            mensaje_usuario.setText("Debes ingresar un USUARIO");
            return;
        }
        mensaje_usuario.setText("Bienvenido " + texto_usuario.getText());
    }
}