/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package demointernacionalizacion;

import java.io.IOException;
import java.net.URL;
import java.util.Locale;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.control.Alert;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

/**
 *
 * @author Juan
 */
public class FXMLDocumentController implements Initializable {
    
    
    @FXML
    private Label mensajeinicial;
    @FXML
    private BorderPane borderPane;
    
    private String Alerta_titulo ;
    private String Alerta_cabecera ;
    private String Alerta_contenido ;
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
        
        mensajeinicial.setText( rb.getString("mensaje.bienvenida"));
        Alerta_titulo = rb.getString("alerta.titulo");
        Alerta_cabecera = rb.getString("alerta.header");
        Alerta_contenido = rb.getString("alerta.contenido");
    }    

    @FXML
    private void cambioSpain(ActionEvent event) throws IOException {
        // cambiar los mensajes a español
        Locale.setDefault(new Locale("es","ES"));
        Stage stage = (Stage) borderPane.getScene().getWindow();
        ResourceBundle bundle = ResourceBundle.getBundle("recursos.cadenas", new Locale("es", "ES"));
        FXMLLoader fxmlLoader =
                            new FXMLLoader(getClass().getResource("FXMLDocument.fxml"), bundle);
                                                               
        Parent root = fxmlLoader.load();
        stage.setTitle(bundle.getString("stage.titulo"));
        stage.getScene().setRoot(root);
    }

    @FXML
    private void cambioUK(ActionEvent event) throws IOException {
        // cambiar los mensajes a inglés
        Locale.setDefault(new Locale("en","GB"));
        Stage stage = (Stage) borderPane.getScene().getWindow();
        ResourceBundle bundle = ResourceBundle.getBundle("recursos.cadenas", new Locale("en", "GB"));
        FXMLLoader fxmlLoader =
                            new FXMLLoader(getClass().getResource("FXMLDocument.fxml"), bundle);
        Parent root = fxmlLoader.load();
        stage.setTitle(bundle.getString("stage.titulo"));
        stage.getScene().setRoot(root);
                    
    }

    @FXML
    private void acercaDe(ActionEvent event) {
        Alert alerta = new Alert(Alert.AlertType.INFORMATION);
        alerta.setTitle(this.Alerta_titulo);
        alerta.setHeaderText(this.Alerta_cabecera);
        alerta.setContentText(this.Alerta_contenido);
        alerta.showAndWait();
    }
    
}
