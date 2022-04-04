/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controlador;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import modelo.Persona;

/**
 * FXML Controller class
 *
 * @author Adrián Martínez
 */
public class DatosPersonaControlador implements Initializable {

    @FXML private TextField nombrefxID;
    @FXML private TextField apellidosfxID;
    @FXML private Button saveBtn;
    @FXML private Button calcelBtn;
          private Persona p; 
          private boolean isCanceled;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        isCanceled = false;
    }
    
    public void initPersona(Persona p) {
        this.p = new Persona(p.getNombre(), p.getApellidos());
        nombrefxID.setText(p.getNombre());
        apellidosfxID.setText(p.getApellidos());
    }
    
    public boolean getCancelar() {
        return isCanceled;
    }
    
    public Persona getPersona() {
        return p;
    }

    @FXML
    private void saveAction(ActionEvent event) {
        isCanceled = false;
        this.p.setNombre(nombrefxID.getText());
        this.p.setApellidos(apellidosfxID.getText());
        Node source = (Node) event.getSource();
        Stage stage = (Stage) source.getScene().getWindow();
        stage.close();
    }

    @FXML
    private void calcelAction(ActionEvent event) {
        isCanceled = true;
        Node source = (Node) event.getSource();
        Stage stage = (Stage) source.getScene().getWindow();
        stage.close();
    }
    
}
